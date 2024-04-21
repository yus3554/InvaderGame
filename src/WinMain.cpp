#include <windows.h>
#include <stdio.h>
#include "Constants.h"
#include "Timer.h"
#include "./gameScene/GameScenes.h"

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

//スレッド関数
DWORD WINAPI ThreadFunc(LPVOID renderer)
{
	// レンダリング
	((Renderer*)renderer)->Render();
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


	// キーステート
	KeyStateManager keyStateManager = KeyStateManager();
	// タイマー
	Timer timer = Timer(FPS);
	// ステート管理
	GameState state = STATE_TITLE;
	// 画面
	Title title = Title(&state, &keyStateManager);
	Game game = Game(&state, &keyStateManager);
	Result result = Result(&state, &keyStateManager);
	HighScore highScore = HighScore(&state, &keyStateManager);
	// レンダラー
	Renderer renderer = Renderer(hwnd, hInstance, IDB_BITMAP1);

	// スレッド
	HANDLE hThread;
	DWORD dwThreadId;
	

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
			// エスケープキー押下 or StateがQuit の場合に終了
			if (KEYDOWN(VK_ESCAPE) || state == STATE_QUIT)
			{
				SendMessage(hwnd, WM_CLOSE, 0, 0);
			}

			// タイマーアップデート
			int loop = timer.getDiffFrame();

			// メイン処理
			for (int i = 0; i < loop; i++)
			{
				//スレッド起動
				hThread = CreateThread(
					NULL, //セキュリティ属性
					0, //スタックサイズ
					ThreadFunc, //スレッド関数
					(LPVOID)&renderer, //スレッド関数に渡す引数
					0, //作成オプション(0またはCREATE_SUSPENDED)
					&dwThreadId);//スレッドID

				// キー入力アップデート
				keyStateManager.update();

				// アップデート / 画面描画リクエスト
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

				// レンダラーを待つ
				if (hThread != NULL)
					WaitForSingleObject(hThread, INFINITE);

				// レンダラーのinfoをコピーする

			}

			// TODO: やっぱ待たないとCPU使用率がやばい
			Sleep(1);
		}
	}

	// 終了処理


	return (int)msg.wParam;
}