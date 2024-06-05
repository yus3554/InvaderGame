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
/// UI ゲームスタート
/// </summary>
constexpr PCTSTR UI_TEXT_START = TEXT("Start");

/// <summary>
/// UI ハイスコア
/// </summary>
constexpr PCTSTR UI_TEXT_HIGHSCORE = TEXT("High Score");

/// <summary>
/// UI 終了
/// </summary>
constexpr PCTSTR UI_TEXT_QUIT = TEXT("Quit");

/// <summary>
/// UI ローディング
/// </summary>
constexpr PCTSTR UI_TEXT_LOADING = TEXT("Now Loading");

/// <summary>
/// Eventネーム レンダースレッド用
/// </summary>
constexpr PCTSTR EVENT_NAME_RENDER_BEGIN = TEXT("RENDER_EVENT_BEGIN");
constexpr PCTSTR EVENT_NAME_RENDER_END = TEXT("RENDER_EVENT_END");

/// <summary>
/// Eventネーム リソースロードスレッド用
/// </summary>
constexpr PCTSTR EVENT_NAME_RESOURCE_BEGIN = TEXT("RESOURCE_EVENT_BEGIN");
constexpr PCTSTR EVENT_NAME_RESOURCE_END = TEXT("RESOURCE_EVENT_END");

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
	/// ローディング画面
	/// </summary>
	STATE_LOADING,

	/// <summary>
	/// ステート数
	/// </summary>
	STATE_NUM
};

enum GameDifficultyState
{
	/// <summary>
	/// normal
	/// </summary>
	DIFFICULTY_STATE_NORMAL,

	/// <summary>
	/// hard
	/// </summary>
	DIFFICULTY_STATE_HARD,

	/// <summary>
	/// ステート数
	/// </summary>
	DIFFICULTY_STATE_NUM
};

/// <summary>
/// リソース種類
/// </summary>
enum ResourceType
{
	/// <summary>
	/// 背景
	/// </summary>
	RESOURCE_BACKGROUND,

	/// <summary>
	/// プレイヤー
	/// </summary>
	RESOURCE_PLAYER,

	/// <summary>
	/// 爆発エフェクト
	/// </summary>
	RESOURCE_EXPLOSION,

	/// <summary>
	/// 敵
	/// </summary>
	RESOURCE_ENEMY,

	/// <summary>
	/// ショット
	/// </summary>
	RESOURCE_SHOT
};


/// <summary>
/// 画像のルートパス
/// </summary>
constexpr char RESOURCE_ROOT_FOLDERPATH[100] = "C:/Users/Yusuke Ota/Development/github/InvaderGame/src/images/";

/// <summary>
/// ルートパス以下の背景画像パス
/// </summary>
constexpr char BACKGROUND_FILEPATHS[2][20] =
{
	"background.bmp",
	"background2.bmp"
};

/// <summary>
/// ルートパス以下のプレイヤー画像パス
/// </summary>
constexpr char PLAYER_FILEPATHS[1][20] = {
	"enemy1.bmp"
};

/// <summary>
/// ルートパス以下の爆発エフェクト画像パス
/// </summary>
constexpr char EXPLOSION_FILEPATHS[6][20] = {
	"explosion1.bmp",
	"explosion2.bmp",
	"explosion3.bmp",
	"explosion4.bmp",
	"explosion5.bmp",
	"explosion6.bmp"
};

/// <summary>
/// ルートパス以下の敵画像パス
/// </summary>
constexpr char ENEMY_FILEPATHS[1][20] = {
	"player1.bmp"
};

/// <summary>
/// ルートパス以下の弾画像パス
/// </summary>
constexpr char SHOT_FILEPATHS[2][20] = {
	"shot1.bmp",
	"shot2.bmp"
};
