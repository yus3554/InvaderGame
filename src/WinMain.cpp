#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
#include "Constants.h"
#include "Timer.h"
#include "./gameScene/GameScenes.h"
#include "Renderer.h"
#include "ResourceManager.h"


struct RenderThreadArgs
{
	RenderThreadArgs(bool isFor, Renderer* renderer);
	bool isFor;
	Renderer* renderer;
};

RenderThreadArgs::RenderThreadArgs(bool isFor, Renderer* renderer)
{
	this->isFor = isFor;
	this->renderer = renderer;
}

struct ResourceLoadThreadArgs
{
	ResourceLoadThreadArgs(bool isFor, ResourceManager* manager);
	bool isFor;
	ResourceManager* manager;
};

ResourceLoadThreadArgs::ResourceLoadThreadArgs(bool isFor, ResourceManager* manager)
{
	this->isFor = isFor;
	this->manager = manager;
}

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
DWORD WINAPI RenderThreadFunc(LPVOID lParam)
{
	HANDLE hEventBegin = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_NAME_RENDER_BEGIN);
	HANDLE hEventEnd = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_NAME_RENDER_END);
	if (hEventBegin == NULL || hEventEnd == NULL)
		return 0;
	RenderThreadArgs* args = (RenderThreadArgs*)lParam;

	while (args->isFor)
	{
		WaitForSingleObject(hEventBegin, INFINITE);
		ResetEvent(hEventBegin);

		// �����_�����O
		args->renderer->Render();
		
		SetEvent(hEventEnd);
	}

	CloseHandle(hEventBegin);
	CloseHandle(hEventEnd);
	return 0;
}

/// <summary>
/// ���\�[�X���[�h���s���X���b�h 
/// </summary>
/// <param name="lParam"></param>
/// <returns></returns>
DWORD WINAPI ResourceLoadThreadFunc(LPVOID lParam)
{
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_NAME_RESOURCE_BEGIN);
	if (hEvent == NULL)
		return 0;
	ResourceLoadThreadArgs* args = (ResourceLoadThreadArgs*)lParam;

	while (args->isFor)
	{
		WaitForSingleObject(hEvent, INFINITE);
		ResetEvent(hEvent);

		// �����_�����O
		args->manager->Load();
	}

	CloseHandle(hEvent);
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

	/***********************************************************
	///
	/// ���C���E�B���h�E
	///
	************************************************************/
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


	/***********************************************************
	///
	/// �ϐ�������
	///
	************************************************************/
	// ���\�[�X
	ResourceManager resourceManager = ResourceManager();
	// �L�[�X�e�[�g
	KeyStateManager keyStateManager = KeyStateManager();
	// �^�C�}�[
	Timer timer = Timer(FPS);
	char fpsStr[100] = "";
	// �X�e�[�g�Ǘ�
	GameState state = STATE_TITLE;
	GameState preState = STATE_TITLE;
	// ���
	Title title = Title(&state, &preState, &keyStateManager);
	Game game = Game(&state, &preState, &keyStateManager, &timer, &resourceManager);
	Result result = Result(&state, &preState, &keyStateManager);
	HighScore highScore = HighScore(&state, &preState, &keyStateManager);
	Loading loading = Loading(&state, &preState, &keyStateManager, &resourceManager);
	// �����_���[
	Renderer renderer = Renderer(hwnd, hInstance, &resourceManager);
	// �w�ipixelOffset�p�i�X�N���[���j
	int backgroundPixelOffset = 0;


	/***********************************************************
	///
	/// �����_�[�X���b�h
	///
	************************************************************/
	DWORD dwRenderThreadId;
	RenderThreadArgs renderThreadArgs = {true, &renderer};
	HANDLE hRenderThread = CreateThread(
		NULL, //�Z�L�����e�B����
		0, //�X�^�b�N�T�C�Y
		RenderThreadFunc, //�X���b�h�֐�
		(LPVOID)&renderThreadArgs, //�X���b�h�֐��ɓn������
		0, //�쐬�I�v�V����(0�܂���CREATE_SUSPENDED)
		&dwRenderThreadId//�X���b�hID
	);
	if (hRenderThread == NULL)
		return 0;

	// �����_�[�X���b�h�p�C�x���g
	HANDLE hRenderEventBegin = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME_RENDER_BEGIN);
	HANDLE hRenderEventEnd = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME_RENDER_END);
	if (hRenderEventBegin == NULL || hRenderEventEnd == NULL)
		return 0;


	/***********************************************************
	///
	/// ���\�[�X���[�h�X���b�h
	///
	************************************************************/
	DWORD dwResourceLoadThreadId;
	ResourceLoadThreadArgs resourceLoadThreadArgs = { true, &resourceManager };
	HANDLE hResourceLoadThread = CreateThread(
		NULL, //�Z�L�����e�B����
		0, //�X�^�b�N�T�C�Y
		ResourceLoadThreadFunc, //�X���b�h�֐�
		(LPVOID)&resourceLoadThreadArgs, //�X���b�h�֐��ɓn������
		0, //�쐬�I�v�V����(0�܂���CREATE_SUSPENDED)
		&dwResourceLoadThreadId//�X���b�hID
	);
	if (hResourceLoadThread == NULL)
		return 0;

	// ���\�[�X���[�h�X���b�h�p�C�x���g
	HANDLE hResourceLoadEventBegin = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME_RESOURCE_BEGIN);
	HANDLE hResourceLoadEventEnd = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME_RESOURCE_END);
	if (hResourceLoadEventBegin == NULL || hResourceLoadEventEnd == NULL)
		return 0;


	/***********************************************************
	///
	/// ���C�����[�v
	///
	************************************************************/
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
				renderThreadArgs.isFor = false;
				resourceLoadThreadArgs.isFor = false;
				SetEvent(hRenderEventEnd);
				SendMessage(hwnd, WM_CLOSE, 0, 0);
				continue;
			}

			// �^�C�}�[�A�b�v�f�[�g
			int loop = timer.getDiffFrame();

			// ���C������
			for (int i = 0; i < loop; i++)
			{
				SetEvent(hRenderEventBegin);

				// �L�[���̓A�b�v�f�[�g
				keyStateManager.update();

				// �w�i�`��
				renderer.DrawRequestImage(
					{ 0.0, 0.0 },
					resourceManager.GetResourceData(RESOURCE_BACKGROUND, 0),
					WND_SIZE.x * backgroundPixelOffset
				);
				backgroundPixelOffset--;

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
				else if (state == STATE_LOADING)
				{
					loading.Update();
					loading.DrawRequest(renderer);
				}

				WaitForSingleObject(hRenderEventEnd, INFINITE);
				ResetEvent(hRenderEventEnd);
				renderer.SwitchDrawInfoList();
			}

			// TODO: ����ϑ҂��Ȃ���CPU�g�p������΂�
			// Sleep(1);
		}
	}

	// �I������


	return (int)msg.wParam;
}