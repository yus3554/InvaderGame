#pragma once
#include <windows.h>
#include "../Constants.h"
#include "../MenuManager.h"
#include "../Timer.h"
#include "../resource.h"

/// <summary>
/// 描画を管理するクラス
/// </summary>
class DrawManager
{
private:
	/// <summary>
	/// ウィンドウ
	/// </summary>
	HWND hwnd;

	/// <summary>
	/// ダブルバッファ用のデバイスコンテキスト フロント側
	/// </summary>
	HDC frontHDC;

	/// <summary>
	/// ダブルバッファ用のデバイスコンテキスト バック側
	/// </summary>
	HDC backHDC;

	/// <summary>
	/// バック側のデバイスコンテキスト用のビットマップ
	/// </summary>
	HBITMAP backBMP;

	/// <summary>
	/// 
	/// </summary>
	HBITMAP oldBMP;

	/// <summary>
	/// インスタンスハンドル
	/// </summary>
	HINSTANCE hInstance;
	
	/// <summary>
	/// テキスト表示する
	/// </summary>
	/// <param name="hdc">デバイスコンテキスト</param>
	/// <param name="rect">ウィンドウサイズ</param>
	/// <param name="text">表示したいテキスト</param>
	/// <param name="fontSize">フォントサイズ</param>
	/// <param name="fontColor">フォントカラー</param>
	/// <param name="weight">太さ</param>
	/// <param name="format">配置フォーマット</param>
	void drawText(HDC hdc, RECT* rect, PCTSTR text, int fontSize, COLORREF fontColor, int weight, UINT format);
	
	/// <summary>
	/// タイトルの表示
	/// </summary>
	/// <param name="hdc">デバイスコンテキスト</param>
	/// <param name="rect">ウィンドウサイズ</param>
	void drawTitle(HDC hdc, RECT* rect);

	/// <summary>
	/// メニューアイテムの表示
	/// </summary>
	/// <param name="hdc">デバイスコンテキスト</param>
	/// <param name="rect">ウィンドウサイズ</param>
	/// <param name="menuItem">メニューアイテム</param>
	void drawMenuItem(HDC hdc, RECT* rect, MenuItem* menuItem);

	/// <summary>
	/// メニューの表示
	/// </summary>
	/// <param name="hdc">デバイスコンテキスト</param>
	/// <param name="rect">ウィンドウサイズ</param>
	/// <param name="menu">メニューマネージャー</param>
	void drawMenu(HDC hdc, RECT* rect, MenuManager* mm);

	/// <summary>
	/// プレイヤーの表示
	/// </summary>
	/// <param name="hdc">デバイスコンテキスト</param>
	/// <param name="rect">ウィンドウサイズ</param>
	/// <param name="pos">プレイヤーの位置</param>
	void drawPlayer(HDC hdc, RECT* rect, POINT pos);

	/// <summary>
	/// 背景の表示
	/// </summary>
	/// <param name="hdc">デバイスコンテキスト</param>
	/// <param name="rect">ウィンドウサイズ</param>
	void drawBackground(HDC hdc, RECT* rect);

	/// <summary>
	/// 背景の表示
	/// </summary>
	/// <param name="hdc">デバイスコンテキスト</param>
	/// <param name="rect">ウィンドウサイズ</param>
	void drawEnemy(HDC hdc, RECT* rect);

	/// <summary>
	/// 弾の表示
	/// </summary>
	/// <param name="hdc">デバイスコンテキスト</param>
	/// <param name="rect">ウィンドウサイズ</param>
	void drawShot(HDC hdc, RECT* rect);

	/// <summary>
	/// FPS値を表示
	/// </summary>
	/// <param name="hdc">デバイスコンテキスト</param>
	/// <param name="rect">ウィンドウサイズ</param>
	/// <param name="timer">タイマー</param>
	void drawFPS(HDC hdc, RECT* rect, Timer* timer);

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="hwnd">ウィンドウ</param>
	/// <param name="hInstance">インスタンスハンドル</param>
	DrawManager(HWND hwnd, HINSTANCE hInstance);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~DrawManager();

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="state"></param>
	/// <param name="mm"></param>
	/// <param name="playerPos"></param>
	/// <param name="timer"></param>
	void paint(GameState state, MenuManager* mm, POINT playerPos, Timer* timer);
};

