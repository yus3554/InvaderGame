#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")
#include "Constants.h"
#include "Timer.h"
#include "./gameScene/GameScenes.h"
#include "Renderer.h"
#include "ResourceManager.h"


struct ThreadArgs
{
	ThreadArgs(bool isFor, Renderer* renderer);
	bool isFor;
	Renderer* renderer;
};

ThreadArgs::ThreadArgs(bool isFor, Renderer* renderer)
{
	this->isFor = isFor;
	this->renderer = renderer;
}

/// <summary>
/// ウィンドウプロシージャ
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
/// レンダーを行うスレッド 
/// </summary>
/// <param name="lParam"></param>
/// <returns></returns>
DWORD WINAPI ThreadFunc(LPVOID lParam)
{
	HANDLE hEvent;
	ThreadArgs* threadArgs = (ThreadArgs*)lParam;

	while (threadArgs->isFor)
	{
		hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, "event");
		if (hEvent == NULL)
			return 0;
		WaitForSingleObject(hEvent, INFINITE);
		ResetEvent(hEvent);

		// レンダリング
		threadArgs->renderer->Render();
		
		SetEvent(hEvent);
		CloseHandle(hEvent);
	}

	return 0;
}


/// <summary>
/// メイン関数
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

	// ウィンドウクラス作成
	winc.style = CS_HREDRAW | CS_VREDRAW;
	winc.lpfnWndProc = WndProc;
	winc.cbClsExtra = winc.cbWndExtra = 0;
	winc.hInstance = hInstance;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = WND_CLASS_NAME;
	// ウィンドウクラス登録
	if (!RegisterClass(&winc)) return 0;

	// ウィンドウ作成・表示
	hwnd = CreateWindow(
		WND_CLASS_NAME, WND_TITLE, WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, WND_SIZE.x, WND_SIZE.y,
		NULL, NULL, hInstance, NULL
	);
	if (hwnd == NULL) return 0;

	// リソース
	ResourceManager resourceManager = ResourceManager();
	// キーステート
	KeyStateManager keyStateManager = KeyStateManager();
	// タイマー
	Timer timer = Timer(FPS);
	char fpsStr[100] = "";
	// ステート管理
	GameState state = STATE_TITLE;
	// 画面
	Title title = Title(&state, &keyStateManager);
	Game game = Game(&state, &keyStateManager, &timer, &resourceManager);
	Result result = Result(&state, &keyStateManager);
	HighScore highScore = HighScore(&state, &keyStateManager);
	// レンダラー
	Renderer renderer = Renderer(hwnd, hInstance, &resourceManager);
	// スレッド関連
	HANDLE hThread;
	DWORD dwThreadId;

	// 背景pixelOffset用（スクロール）
	int backgroundPixelOffset = 0;

	//スレッド起動
	ThreadArgs threadArgs = {true, &renderer};
	hThread = CreateThread(
		NULL, //セキュリティ属性
		0, //スタックサイズ
		ThreadFunc, //スレッド関数
		(LPVOID)&threadArgs, //スレッド関数に渡す引数
		0, //作成オプション(0またはCREATE_SUSPENDED)
		&dwThreadId//スレッドID
	);
	if (hThread == NULL)
		return 0;

	// スレッド用イベント
	HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, "event");
	if (hEvent == NULL)
		return 0;

	// メッセージループ（WM_QUIT時のみループを抜ける）
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

			// エスケープキー押下 or StateがQuit の場合に終了
			if (KEYDOWN(VK_ESCAPE) || state == STATE_QUIT)
			{
				threadArgs.isFor = false;
				SendMessage(hwnd, WM_CLOSE, 0, 0);
			}

			// タイマーアップデート
			int loop = timer.getDiffFrame();

			// メイン処理
			for (int i = 0; i < loop; i++)
			{
				SetEvent(hEvent);

				// キー入力アップデート
				keyStateManager.update();

				// 背景描画
				renderer.DrawRequestImage(
					{ 0.0, 0.0 },
					resourceManager.GetResourceData(RESOURCE_BACKGROUND, 0),
					WND_SIZE.x * backgroundPixelOffset
				);
				backgroundPixelOffset--;

				// FPS表示
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

				WaitForSingleObject(hEvent, INFINITE);
				renderer.SwitchDrawInfoList();
			}

			// TODO: やっぱ待たないとCPU使用率がやばい
			// Sleep(1);
		}
	}

	// 終了処理


	return (int)msg.wParam;
}