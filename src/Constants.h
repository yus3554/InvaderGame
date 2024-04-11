#pragma once
#include <windows.h>


/// ####################################################
/// 
/// マクロ
/// 
/// ####################################################

/// 指定されたキーが押されているかどうかを取得
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/// 指定されたキーが離されているかどうかを取得
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


/// ####################################################
///
/// 定数
/// 
/// ####################################################

/// <summary>
/// ウィンドウクラスの名前
/// </summary>
constexpr PCTSTR WND_CLASS_NAME = TEXT("WindowClassName");

/// /// <summary>
/// ウィンドウタイトル
/// </summary>
constexpr PCTSTR WND_TITLE = TEXT("Invader Game");

/// <summary>
/// ウィンドウサイズ
/// </summary>
constexpr POINT WND_SIZE = { 720, 480 };

/// <summary>
/// UI タイトル
/// </summary>
constexpr PCTSTR UI_TEXT_TITLE = TEXT("Invader Game");

/// <summary>
/// UI メニューアイテム ゲームスタート
/// </summary>
constexpr PCTSTR UI_TEXT_START = TEXT("Start");

/// <summary>
/// UI メニューアイテム ハイスコア
/// </summary>
constexpr PCTSTR UI_TEXT_HIGHSCORE = TEXT("High Score");

/// <summary>
/// UI メニューアイテム 終了
/// </summary>
constexpr PCTSTR UI_TEXT_QUIT = TEXT("Quit");

/// <summary>
/// プレイヤーの初期位置
/// </summary>
constexpr POINT PLAYER_INIT_POS = {WND_SIZE.x / 2, WND_SIZE.y - 100};

/// <summary>
/// 描画フレーム
/// </summary>
constexpr int FPS = 60;

/// <summary>
/// 対応キーコードの数
/// </summary>
constexpr int KEYCODE_LENGTH = 7;

/// <summary>
/// 対応キーコード
/// </summary>
constexpr int KEYCODES[KEYCODE_LENGTH] = {
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE
};

/// <summary>
/// ゲームステート
/// </summary>
enum GameState
{
	/// <summary>
	/// タイトル画面
	/// </summary>
	STATE_TITLE,

	/// <summary>
	/// ゲーム画面
	/// </summary>
	STATE_GAME,

	/// <summary>
	/// ハイスコア画面
	/// </summary>
	STATE_HIGHSCORE,

	/// <summary>
	/// リザルト画面
	/// </summary>
	STATE_RESULT,

	/// <summary>
	/// 終了
	/// </summary>
	STATE_QUIT,

	/// <summary>
	/// ステート数
	/// </summary>
	STATE_NUM
};

