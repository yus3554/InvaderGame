#include <windows.h>
#include <stdio.h>
#include "Constants.h"
#include "Timer.h"
#include "./gameObjects/Title.h"

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


	// �L�[�X�e�[�g
	KeyStateManager* km = new KeyStateManager();
	// �^�C�}�[
	Timer* timer = new Timer(FPS);
	// �X�e�[�g�Ǘ�
	GameState state = STATE_TITLE;
	// ���
	Title* title = new Title(&state, km);
	// �����_���[
	Renderer renderer = Renderer(hwnd, hInstance, IDB_BITMAP1);
	

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
			// �G�X�P�[�v�L�[���� or State��Quit �̏ꍇ�ɏI��
			if (KEYDOWN(VK_ESCAPE) || state == STATE_QUIT)
			{
				SendMessage(hwnd, WM_CLOSE, 0, 0);
			}

			// �^�C�}�[�A�b�v�f�[�g
			int loop = timer->getDiffFrame();

			// ���C������
			for (int i = 0; i < loop; i++)
			{
				// �L�[���̓A�b�v�f�[�g
				km->update();

				// �A�b�v�f�[�g
				title->Update();

				// �����_���[�ɕ`��˗�
				title->Draw(renderer);


				// �����_�����O
				renderer.Render();
			}

			// TODO: ����ϑ҂��Ȃ���CPU�g�p������΂�
			Sleep(1);
		}
	}

	// �I������
	delete timer;

	return (int)msg.wParam;
}