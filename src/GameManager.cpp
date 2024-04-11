#include <stdio.h>
#include <windows.h>
#include "GameManager.h"
#include "Constants.h"
#include "Menu.h"
#include "Timer.h"
#include "KeyStateManager.h"

GameManager::GameManager(HWND hwnd, HINSTANCE hInstance)
{
	// 描画を担当するクラス
	this->dm = new DrawManager(hwnd, hInstance);
	// タイマー
	this->timer = new Timer(FPS);
	// メニュー
	this->menu = new Menu();
	// キー入力管理クラス
	this->km = new KeyStateManager();
	// ステートの初期化
	this->currentGameState = STATE_TITLE;

	// データの初期化
	this->GameInit();
}

GameManager::~GameManager() {
	delete this->menu;
	delete this->dm;
	delete this->timer;
	delete this->km;
}

void GameManager::GameInit()
{
	// スコアの初期化
	this->score = 0;
	// プレイヤーの初期化
	this->playerPos = PLAYER_INIT_POS;
}

void GameManager::GameUpdate()
{
	// タイマーアップデート
	int loop = timer->getDiffFrame();

	// メイン処理
	for (int i = 0; i < loop; i++)
	{
		// キー入力アップデート
		this->km->update();
		// キー入力による処理
		this->keyPress();
		// 描画
		this->dm->paint(this->getCurrentGameState(), this->getMenu(), this->getPlayerPos(), this->timer);
	}

	// TODO: やっぱ待たないとCPU使用率がやばい
	Sleep(1);
}

void GameManager::GameQuit()
{

}

GameState GameManager::getCurrentGameState() {
	return this->currentGameState;
}

void GameManager::setCurrentGameState(GameState state)
{
	this->currentGameState = state;
}


POINT GameManager::getPlayerPos()
{
	return this->playerPos;
}

void GameManager::setPlayerPos(POINT pos) {
	this->playerPos = pos;
}


Menu* GameManager::getMenu()
{
	return this->menu;
}


void GameManager::keyPress()
{
	switch (this->currentGameState)
	{
	case STATE_TITLE:  // タイトル画面
		if (this->km->getKeyState(VK_UP)->getIsDownStart()) {  // メニューカーソルを上に
			this->menu->previousItem();
		}

		if (this->km->getKeyState(VK_DOWN)->getIsDownStart()) {  // メニューカーソルを下に
			this->menu->nextItem();
		}

		if (this->km->getKeyState(VK_RETURN)->getIsDownStart()) {
			// menuのカレントIDに応じて、カレントゲームステートを変更する
			GameState state;
			switch (this->menu->getCurrentID())
			{
			case MENU_START:
				state = STATE_GAME;
				this->GameInit();
				break;
			case MENU_HIGHSCORE:
				state = STATE_HIGHSCORE;
				break;
			case MENU_QUIT:
				state = STATE_QUIT;
				break;
			default:
				state = STATE_QUIT;
				break;
			}

			this->setCurrentGameState(state);
		}
		break;

	case STATE_GAME:  // ゲーム
		POINT pos = this->getPlayerPos();

		if (this->km->getKeyState(VK_LEFT)->getIsDownCurrent()) {  // 左に移動
			pos.x -= 10;
			this->setPlayerPos(pos);
		}

		if (this->km->getKeyState(VK_RIGHT)->getIsDownCurrent()) {  // 右に移動
			pos.x += 10;
			this->setPlayerPos(pos);
		}

		if (this->km->getKeyState(VK_SPACE)->getIsDownStart()) {  // 弾を打つ
		}

		if (pos.x < 0 || pos.x > WND_SIZE.x) {
			this->setCurrentGameState(STATE_RESULT);
		}
		break;
	
	case STATE_HIGHSCORE:  // ハイスコア画面
		if (this->km->getKeyState(VK_RETURN)->getIsDownStart()) {  // タイトル画面へ遷移
			this->setCurrentGameState(STATE_TITLE);
		}
		break;

	case STATE_RESULT:  // リザルト画面
		if (this->km->getKeyState(VK_RETURN)->getIsDownStart()) {  // タイトル画面へ遷移
			this->setCurrentGameState(STATE_TITLE);
		}
		break;

	default:
		break;
	}
}
