#include <stdio.h>
#include <windows.h>
#include "GameManager.h"
#include "Constants.h"
#include "Menu.h"
#include "Timer.h"
#include "KeyStateManager.h"


GameManager::GameManager(HWND hwnd)
{
	// �`���S������N���X
	this->dm = new DrawManager(hwnd);
	// �^�C�}�[
	this->timer = new Timer(FPS);
	// ���j���[
	this->menu = new Menu();
	// �L�[���͊Ǘ��N���X
	this->km = new KeyStateManager();
	// �X�e�[�g�̏�����
	this->currentGameState = STATE_TITLE;

	// �f�[�^�̏�����
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
	// �X�R�A�̏�����
	this->score = 0;
	// �v���C���[�̏�����
	this->playerPos = PLAYER_INIT_POS;
}


void GameManager::GameUpdate()
{
	// �^�C�}�[�A�b�v�f�[�g
	int loop = timer->getDiffFrame();

	// �G�X�P�[�v�L�[���� or State��Quit �̏ꍇ�ɏI��
	if (KEYDOWN(VK_ESCAPE) || this->getCurrentGameState() == STATE_QUIT)
		SendMessage(this->hwnd, WM_CLOSE, 0, 0);

	// ���C������
	for (int i = 0; i < loop; i++)
	{
		// �L�[���̓A�b�v�f�[�g
		this->km->update();

		// �`��
		this->keyPress();
		this->dm->paint(this->getCurrentGameState(), this->getMenu(), this->getPlayerPos(), this->timer);
	}

	Sleep(5);
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
	case STATE_TITLE:  // �^�C�g�����
		if (this->km->getKeyState(VK_UP)->getIsDownStart()) {  // ���j���[�J�[�\�������
			this->menu->previousItem();
		}

		if (this->km->getKeyState(VK_DOWN)->getIsDownStart()) {  // ���j���[�J�[�\��������
			this->menu->nextItem();
		}

		if (this->km->getKeyState(VK_RETURN)->getIsDownStart()) {
			// menu�̃J�����gID�ɉ����āA�J�����g�Q�[���X�e�[�g��ύX����
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

	case STATE_GAME:  // �Q�[��
		POINT pos = this->getPlayerPos();

		if (this->km->getKeyState(VK_LEFT)->getIsDownCurrent()) {  // ���Ɉړ�
			pos.x -= 10;
			this->setPlayerPos(pos);
		}

		if (this->km->getKeyState(VK_RIGHT)->getIsDownCurrent()) {  // �E�Ɉړ�
			pos.x += 10;
			this->setPlayerPos(pos);
		}

		if (this->km->getKeyState(VK_SPACE)->getIsDownStart()) {  // �e��ł�
		}

		if (pos.x < 0 || pos.x > WND_SIZE.x) {
			this->setCurrentGameState(STATE_RESULT);
		}
		break;
	
	case STATE_HIGHSCORE:  // �n�C�X�R�A���
		if (this->km->getKeyState(VK_RETURN)->getIsDownStart()) {  // �^�C�g����ʂ֑J��
			this->setCurrentGameState(STATE_TITLE);
		}
		break;

	case STATE_RESULT:  // ���U���g���
		if (this->km->getKeyState(VK_RETURN)->getIsDownStart()) {  // �^�C�g����ʂ֑J��
			this->setCurrentGameState(STATE_TITLE);
		}
		break;

	default:
		break;
	}
}
