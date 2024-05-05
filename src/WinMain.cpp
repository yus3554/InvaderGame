#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
#include "Constants.h"
#include "Timer.h"
#include "./gameScene/GameScenes.h"
#include "Renderer.h"
#include "ResourceManager.h"

/// <summary>
/// �E�B���h�E�v���V�[�W��
/// </summary>
/// <param name="hwnd"></param>
/// <param name="msg"></param>
/// <param name="wParam"></param>
/// <param name="lParam"></param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (msg)
	{
	case WM_CREATE:
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


/// <summary>
/// �����_�[���s���X���b�h 
/// </summary>
/// <param name="lParam"></param>
/// <returns></returns>
DWORD WINAPI ThreadFunc(LPVOID renderer)
{
	// �����_�����O
	((Renderer*)renderer)->Render();

	return 0;
}


/// <summary>
/// ���C���֐�
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="pCmdLine"></param>
/// <param name="nCmdShow"></param>
/// <returns></returns>
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	HWND hwnd;
	WNDCLASS winc{};
	MSG msg;

	// �E�B���h�E�N���X�쐬
	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = WND_CLASS_NAME;
	// �E�B���h�E�N���X�o�^
	if (!RegisterClass(&winc)) return 0;

	// �E�B���h�E�쐬�E�\��
	hwnd = CreateWindow(
		WND_CLASS_NAME, WND_TITLE, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, WND_SIZE.x, WND_SIZE.y,
		NULL, NULL, hInstance, NULL
	);
	if (hwnd == NULL) return 0;

	// ���\�[�X
	ResourceManager resourceManager = ResourceManager();
	// �L�[�X�e�[�g
	KeyStateManager keyStateManager = KeyStateManager();
	// �^�C�}�[
	Timer timer = Timer(FPS);
	char fpsStr[100] = "";
	// �X�e�[�g�Ǘ�
	GameState state = STATE_TITLE;
	// ���
	Title title = Title(&state, &keyStateManager);
	Game game = Game(&state, &keyStateManager, &timer, &resourceManager);
	Result result = Result(&state, &keyStateManager);
	HighScore highScore = HighScore(&state, &keyStateManager);
	// �����_���[
	Renderer renderer = Renderer(hwnd, hInstance, &resourceManager);
	// �X���b�h�֘A
	HANDLE hThread;
	DWORD dwThreadId;

	// ���b�Z�[�W���[�v�iWM_QUIT���̂݃��[�v�𔲂���j
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			/*JOYINFO joyInfo;
			if (joyGetPos(JOYSTICKID2, &joyInfo) != JOYERR_NOERROR)
				return 0;
			sprintf_s(fpsStr, sizeof(fpsStr), "%d", joyInfo.wButtons);
			OutputDebugString(fpsStr);*/

			// �G�X�P�[�v�L�[���� or State��Quit �̏ꍇ�ɏI��
			if (KEYDOWN(VK_ESCAPE) || state == STATE_QUIT)
			{
				SendMessage(hwnd, WM_CLOSE, 0, 0);
			}

			// �^�C�}�[�A�b�v�f�[�g
			int loop = timer.getDiffFrame();

			// ���C������
			for (int i = 0; i < loop; i++)
			{
				//�X���b�h�N��
				hThread = CreateThread(
					NULL, //�Z�L�����e�B����
					0, //�X�^�b�N�T�C�Y
					ThreadFunc, //�X���b�h�֐�
					(LPVOID)&renderer, //�X���b�h�֐��ɓn������
					0, //�쐬�I�v�V����(0�܂���CREATE_SUSPENDED)
					&dwThreadId);//�X���b�hID
				if (hThread == NULL)
					return 0;

				// �L�[���̓A�b�v�f�[�g
				keyStateManager.update();

				// �A�b�v�f�[�g / ��ʕ`�惊�N�G�X�g
				renderer.DrawRequestImage(
					{ 0.0, 0.0 },
					resourceManager.GetResourceData(RESOURCE_BACKGROUND, 0)
				);

				// FPS�\��
				sprintf_s(fpsStr, sizeof(fpsStr), "%5lf FPS", timer.getRealFPS());
				POINTFLOAT pos = { 70, 10 };
				renderer.DrawRequestText(fpsStr, pos, 20, RGB(255, 255, 255), FW_BOLD);

				if (state == STATE_TITLE)
				{
					title.Update();
					title.DrawRequest(renderer);
				}
				else if (state == STATE_GAME)
				{
					game.Update();
					game.DrawRequest(renderer);
				}
				else if (state == STATE_RESULT)
				{
					result.Update();
					result.DrawRequest(renderer);
				}
				else if (state == STATE_HIGHSCORE)
				{
					highScore.Update();
					highScore.DrawRequest(renderer);
				}

				WaitForSingleObject(hThread, INFINITE);
				renderer.CopyInfos();
			}

			// TODO: ����ϑ҂��Ȃ���CPU�g�p������΂�
			// Sleep(1);
		}
	}

	// �I������


	return (int)msg.wParam;
}