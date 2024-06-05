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
	ResourceLoadThreadArgs(bool isFor, ResourceManager* manager, CRITICAL_SECTION* cs);
	bool isFor;
	ResourceManager* manager;
	CRITICAL_SECTION* cs;
};

ResourceLoadThreadArgs::ResourceLoadThreadArgs(bool isFor, ResourceManager* manager, CRITICAL_SECTION* cs)
{
	this->isFor = isFor;
	this->manager = manager;
	this->cs = cs;
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

		// レンダリング
		args->renderer->Render();
		
		SetEvent(hEventEnd);
	}

	CloseHandle(hEventBegin);
	CloseHandle(hEventEnd);
	return 0;
}

/// <summary>
/// リソースロードを行うスレッド 
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
		OutputDebugString("a\n");

		// 画像１枚ロード
		args->manager->LoadOnce();
	}

	CloseHandle(hEvent);
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

	/***********************************************************
	///
	/// メインウィンドウ
	///
	************************************************************/
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


	/***********************************************************
	///
	/// 変数初期化
	///
	************************************************************/
	// レンダースレッド用イベント
	HANDLE hRenderEventBegin = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME_RENDER_BEGIN);
	HANDLE hRenderEventEnd = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME_RENDER_END);
	if (hRenderEventBegin == NULL || hRenderEventEnd == NULL)
		return 0;
	// リソースロードスレッド用イベント
	HANDLE hResourceLoadEventBegin = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME_RESOURCE_BEGIN);
	HANDLE hResourceLoadEventEnd = CreateEvent(NULL, TRUE, FALSE, EVENT_NAME_RESOURCE_END);
	if (hResourceLoadEventBegin == NULL || hResourceLoadEventEnd == NULL)
		return 0;

	// リソースリロード用クリティカルセクション
	CRITICAL_SECTION cs;
	InitializeCriticalSection(&cs);
	// リソース
	ResourceManager resourceManager = ResourceManager(&cs);
	// キーステート
	KeyStateManager keyStateManager = KeyStateManager();
	// タイマー
	Timer timer = Timer(60);
	char fpsStr[100] = "";
	// ステート管理
	GameState state = STATE_TITLE;
	GameState preState = STATE_TITLE;
	GameDifficultyState difficultyState = DIFFICULTY_STATE_NORMAL;
	// 画面
	Title title = Title(&state, &preState, &keyStateManager, &timer, &difficultyState);
	Game game = Game(&state, &preState, &keyStateManager, &timer, &resourceManager, &difficultyState);
	Result result = Result(&state, &preState, &keyStateManager);
	HighScore highScore = HighScore(&state, &preState, &keyStateManager);
	Loading loading = Loading(&state, &preState, &keyStateManager, &resourceManager);
	// レンダラー
	Renderer renderer = Renderer(hwnd, hInstance, &resourceManager);
	// 背景pixelOffset用（スクロール）
	int backgroundPixelOffset = 0;


	/***********************************************************
	///
	/// レンダースレッド
	///
	************************************************************/
	DWORD dwRenderThreadId;
	RenderThreadArgs renderThreadArgs = {true, &renderer};
	HANDLE hRenderThread = CreateThread(
		NULL, //セキュリティ属性
		0, //スタックサイズ
		RenderThreadFunc, //スレッド関数
		(LPVOID)&renderThreadArgs, //スレッド関数に渡す引数
		0, //作成オプション(0またはCREATE_SUSPENDED)
		&dwRenderThreadId//スレッドID
	);
	if (hRenderThread == NULL)
		return 0;


	/***********************************************************
	///
	/// リソースロードスレッド
	///
	************************************************************/
	DWORD dwResourceLoadThreadId;
	ResourceLoadThreadArgs resourceLoadThreadArgs = { true, &resourceManager, &cs};
	HANDLE hResourceLoadThread = CreateThread(
		NULL, //セキュリティ属性
		0, //スタックサイズ
		ResourceLoadThreadFunc, //スレッド関数
		(LPVOID)&resourceLoadThreadArgs, //スレッド関数に渡す引数
		0, //作成オプション(0またはCREATE_SUSPENDED)
		&dwResourceLoadThreadId//スレッドID
	);
	if (hResourceLoadThread == NULL)
		return 0;


	/***********************************************************
	///
	/// メインループ
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

			// エスケープキー押下 or StateがQuit の場合に終了
			if (KEYDOWN(VK_ESCAPE) || state == STATE_QUIT)
			{
				renderThreadArgs.isFor = false;
				resourceLoadThreadArgs.isFor = false;
				SetEvent(hRenderEventEnd);
				SendMessage(hwnd, WM_CLOSE, 0, 0);
				continue;
			}

			// タイマーアップデート
			int loop = timer.getDiffFrame();

			// メイン処理
			for (int i = 0; i < loop; i++)
			{
				SetEvent(hRenderEventBegin);

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
				else if (state == STATE_LOADING)
				{
					loading.Update();
					loading.DrawRequest(renderer);
				}

				WaitForSingleObject(hRenderEventEnd, INFINITE);
				ResetEvent(hRenderEventEnd);
				renderer.SwitchDrawInfoList();
			}

			// TODO: やっぱ待たないとCPU使用率がやばい
			// Sleep(1);
		}
	}

	// 終了処理


	return (int)msg.wParam;
}