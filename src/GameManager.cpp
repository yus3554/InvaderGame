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


void GameManager::keyPress(WPARAM wParam)
{
	switch (this->currentGameState)
	{
	case STATE_TITLE:
		switch (wParam)
		{
		case VK_UP:
			this->menu->previousItem();
			break;

		case VK_DOWN:
			this->menu->nextItem();
			break;

		case VK_RETURN:
			// menuのカレントIDに応じて、カレントゲームステートを変更する
			GameState state;
			switch (this->menu->getCurrentID())
			{
			case MENU_START:
				state = STATE_GAME;
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
			break;

		default:
			break;
		}
		break;

	case STATE_GAME:
		break;
	default:
		break;
	}
}
