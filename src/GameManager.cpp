#include "GameManager.h"

GameManager::GameManager(HWND hwnd, HINSTANCE hInstance)
{
	// �`���S������N���X
	this->dm = new DrawManager(hwnd, hInstance);
	// �^�C�}�[
	this->timer = new Timer(FPS);
	// ���j���[
	this->mm = new MenuManager();
	// �L�[���͊Ǘ��N���X
	this->km = new KeyStateManager();
	// �X�e�[�g�̏�����
	this->currentGameState = STATE_TITLE;

	// �f�[�^�̏�����
	this->GameInit();
}

GameManager::~GameManager() {
	delete this->mm;
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

	// ���C������
	for (int i = 0; i < loop; i++)
	{
		// �L�[���̓A�b�v�f�[�g
		this->km->update();
		// �L�[���͂ɂ�鏈��
		this->keyPress();
		// �`��
		this->dm->paint(this->getCurrentGameState(), this->getMenuManager(), this->getPlayerPos(), this->timer);
	}

	// TODO: ����ϑ҂��Ȃ���CPU�g�p������΂�
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


MenuManager* GameManager::getMenuManager()
{
	return this->mm;
}


void GameManager::keyPress()
{
	switch (this->currentGameState)
	{
	case STATE_TITLE:  // �^�C�g�����
		if (this->km->getKeyState(VK_UP)->getIsDownStart()) {  // ���j���[�J�[�\�������
			this->mm->previousItem();
		}

		if (this->km->getKeyState(VK_DOWN)->getIsDownStart()) {  // ���j���[�J�[�\��������
			this->mm->nextItem();
		}

		if (this->km->getKeyState(VK_RETURN)->getIsDownStart()) {
			// menu�̃J�����gID�ɉ����āA�J�����g�Q�[���X�e�[�g��ύX����
			GameState state;
			switch (this->mm->getCurrentID())
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
