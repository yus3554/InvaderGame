#pragma once
#include <windows.h>
#include "Menu.h"
#include "Timer.h"
#include "DrawManager.h"
#include "KeyStateManager.h"


class GameManager
{
private:
	/// <summary>
	/// メニュー
	/// </summary>
	Menu* menu;

	/// <summary>
	/// タイマー
	/// </summary>
	Timer* timer;

	/// <summary>
	/// 描画マネージャー
	/// </summary>
	DrawManager* dm;

	/// <summary>
	/// キー入力マネージャー
	/// </summary>
	KeyStateManager* km;

	/// <summary>
	/// ウィンドウ
	/// </summary>
	HWND hwnd;

	/// <summary>
	/// インスタンスハンドル
	/// </summary>
	HINSTANCE hInstance;

	/// <summary>
	/// 現在のゲームステート
	/// </summary>
	GameState currentGameState;

	/// <summary>
	/// スコア
	/// </summary>
	int score;

	/// <summary>
	/// プレイヤーの位置
	/// </summary>
	POINT playerPos;  // TODO: キャラクターの場所は、おそらくGM内じゃなくてキャラクタクラス内に書くべき

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="hwnd">ウィンドウ</param>
	/// <param name="hInstance">インスタンスハンドル</param>
	GameManager(HWND hwnd, HINSTANCE hInstance);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameManager();

	/// <summary>
	/// ゲームの初期化
	/// </summary>
	void GameInit();

	/// <summary>
	/// ゲームのメイン処理
	/// </summary>
	void GameUpdate();

	/// <summary>
	/// ゲーム終了時の処理
	/// </summary>
	void GameQuit();

	/// <summary>
	/// 現在のゲームステートを取得
	/// </summary>
	/// <returns>現在のゲームステート</returns>
	GameState getCurrentGameState();

	/// <summary>
	/// 現在のゲームステートを設定
	/// </summary>
	/// <param name="state">ゲームステート</param>
	void setCurrentGameState(GameState state);

	/// <summary>
	/// プレイヤーの位置を取得
	/// </summary>
	/// <returns>プレイヤーの位置</returns>
	POINT getPlayerPos();

	/// <summary>
	/// プレイヤーの位置を設定
	/// </summary>
	/// <param name="pos">プレイヤーの位置</param>
	void setPlayerPos(POINT pos);

	/// <summary>
	/// メニューの取得
	/// </summary>
	/// <returns> メニュー </returns>
	Menu* getMenu();

	/// <summary>
	/// キー押下時の処理
	/// </summary>
	void keyPress();
};

