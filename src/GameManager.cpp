#include "GameManager.h"
#include "Constants.h"
#include "Menu.h"
#include <windows.h>

GameManager::GameManager()
{
	this->menu = new Menu();
	this->currentGameState = STATE_TITLE;
	this->playerPos = PLAYER_INIT_POS;
}


GameManager::~GameManager() {
	delete this->menu;
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
		if (KEYDOWN(VK_UP)) {  // メニューカーソルを上に
			this->menu->previousItem();
		}

		if (KEYDOWN(VK_DOWN)) {  // メニューカーソルを下に
			this->menu->nextItem();
		}

		if (KEYDOWN(VK_RETURN)) {
			// menuのカレントIDに応じて、カレントゲームステートを変更する
			GameState state;
			switch (this->menu->getCurrentID())
			{
			case MENU_START:
				state = STATE_GAME;
				// TODO: プレイヤーやキャラクターのイニシャライズ
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

		if (KEYDOWN(VK_LEFT)) {  // 左に移動
			pos.x -= 10;
			this->setPlayerPos(pos);
		}

		if (KEYDOWN(VK_RIGHT)) {  // 右に移動
			pos.x += 10;
			this->setPlayerPos(pos);
		}

		if (KEYDOWN(VK_SPACE)) {  // 弾を打つ
		}

		if (pos.x < 0 || pos.x > WND_SIZE.x) {
			this->setCurrentGameState(STATE_RESULT);
		}
		break;
	
	case STATE_HIGHSCORE:  // ハイスコア画面
		if (KEYDOWN(VK_RETURN)) {  // タイトル画面へ遷移
			this->setCurrentGameState(STATE_TITLE);
		}
		break;

	case STATE_RESULT:  // リザルト画面
		if (KEYDOWN(VK_RETURN)) {  // タイトル画面へ遷移
			this->setCurrentGameState(STATE_TITLE);
		}
		break;

	default:
		break;
	}
}
