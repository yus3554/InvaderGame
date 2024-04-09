#include <windows.h>
#include <stdio.h>
#include "Constants.h"
#include "DrawManager.h"
#include "GameManager.h"


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
/// メイン関数
/// </summary>
/// <param name="hInstance"></param>
/// <param name="hPrevInstance"></param>
/// <param name="pCmdLine"></param>
/// <param name="nCmdShow"></param>
/// <returns></returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
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
	winc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winc.lpszMenuName = NULL;
	winc.lpszClassName = WND_CLASS_NAME;
	// ウィンドウクラス登録
	if (!RegisterClass(&winc)) return 0;

	// ウィンドウ作成・表示
	hwnd = CreateWindow(
		WND_CLASS_NAME, WND_TITLE, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT, CW_USEDEFAULT, WND_SIZE.x, WND_SIZE.y,
		NULL, NULL, hInstance, NULL
	);
	if (hwnd == NULL) return 0;

	// ゲームの状態や様々な値を管理するクラス
	GameManager* gm = new GameManager();
	// 描画を担当するクラス
	DrawManager* dm = new DrawManager(gm, hwnd);

	HDC hdc;

	// 時間計測
	int fps = 240;
	int loop;
	int nowFrame;
	int beforeFrame = 0;
	LARGE_INTEGER cpuFreq;  // CPU周波数
	QueryPerformanceFrequency(&cpuFreq);
	LARGE_INTEGER startCount;
	LARGE_INTEGER nowCount;
	QueryPerformanceCounter(&startCount);

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
			if(KEYDOWN(VK_ESCAPE) || gm->getCurrentGameState() == STATE_QUIT)
				SendMessage(hwnd, WM_CLOSE, 0, 0);

			// キー入力
			// TODO: ここでkeyが押されるたびに内部の値を変えてしまうと、ループのスピード次第で変わってしまう
			// TODO: つまり、CPUの性能が良いほど早く動ける
			// TODO: かといって、keyPressをforの中にいれると、forに入っている間しかkeyを取れない
			// TODO: そこで、keyPressは取り続けつつ、実際に値が動くのはforに入ったときだけにしたほうがいい
			// TODO: keyPressに入るたびに現在押されているKeyを更新しつづける
			// TODO: forに入ったときに、現在押されているKeyを取得して実行する
			gm->keyPress();

			// フレームレート計算
			QueryPerformanceCounter(&nowCount);
			nowFrame = (int)((nowCount.QuadPart - startCount.QuadPart) / (cpuFreq.QuadPart / fps));
			if (nowFrame != beforeFrame) {
				loop = nowFrame - beforeFrame;
				beforeFrame = nowFrame;
			}
			else {
				loop = 0;
			}

			// メイン処理
			for (int i = 0; i < loop; i++)
			{
				// TODO: キー入力の処理もこっちで行う
				// TODO: カーソルの速度が早くなりすぎるので、一つ前のフレームと同じキーが押されていたら無視するようにしたほうがいい
				hdc = GetDC(hwnd);
				dm->paint(hdc);
				ReleaseDC(hwnd, hdc);
			}

			Sleep(3);
		}
	}
	delete gm;
	delete dm;

	return msg.wParam;
}