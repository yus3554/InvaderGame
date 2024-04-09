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
	case STATE_TITLE:  // �^�C�g�����
		if (KEYDOWN(VK_UP)) {  // ���j���[�J�[�\�������
			this->menu->previousItem();
		}

		if (KEYDOWN(VK_DOWN)) {  // ���j���[�J�[�\��������
			this->menu->nextItem();
		}

		if (KEYDOWN(VK_RETURN)) {
			// menu�̃J�����gID�ɉ����āA�J�����g�Q�[���X�e�[�g��ύX����
			GameState state;
			switch (this->menu->getCurrentID())
			{
			case MENU_START:
				state = STATE_GAME;
				// TODO: �v���C���[��L�����N�^�[�̃C�j�V�����C�Y
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

	case STATE_GAME:  // �Q�[��
		POINT pos = this->getPlayerPos();

		if (KEYDOWN(VK_LEFT)) {  // ���Ɉړ�
			pos.x -= 10;
			this->setPlayerPos(pos);
		}

		if (KEYDOWN(VK_RIGHT)) {  // �E�Ɉړ�
			pos.x += 10;
			this->setPlayerPos(pos);
		}

		if (KEYDOWN(VK_SPACE)) {  // �e��ł�
		}

		if (pos.x < 0 || pos.x > WND_SIZE.x) {
			this->setCurrentGameState(STATE_RESULT);
		}
		break;
	
	case STATE_HIGHSCORE:  // �n�C�X�R�A���
		if (KEYDOWN(VK_RETURN)) {  // �^�C�g����ʂ֑J��
			this->setCurrentGameState(STATE_TITLE);
		}
		break;

	case STATE_RESULT:  // ���U���g���
		if (KEYDOWN(VK_RETURN)) {  // �^�C�g����ʂ֑J��
			this->setCurrentGameState(STATE_TITLE);
		}
		break;

	default:
		break;
	}
}
