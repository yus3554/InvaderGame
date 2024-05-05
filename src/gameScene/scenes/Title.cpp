#include "Title.h"

Title::Title(GameState* state, KeyStateManager* keyStateManager)
{
	this->keyStateManager = keyStateManager;
	this->menuManager = new MenuManager();
	this->state = state;
}

Title::~Title()
{
	delete this->menuManager;
}

void Title::Update()
{
	if (this->keyStateManager->getKeyState(VK_UP)->getIsDownStart()) {  // ���j���[�J�[�\�������
		this->menuManager->previousItem();
	}

	if (this->keyStateManager->getKeyState(VK_DOWN)->getIsDownStart()) {  // ���j���[�J�[�\��������
		this->menuManager->nextItem();
	}

	if (this->keyStateManager->getKeyState(VK_RETURN)->getIsDownStart()) {
		// menu�̃J�����gID�ɉ����āA�J�����g�Q�[���X�e�[�g��ύX����
		GameState state;
		switch (this->menuManager->getCurrentID())
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

		*(this->state) = state;
	}
}

void Title::DrawRequest(Renderer& renderer)
{
	// ���ׂẴ��j���[�A�C�e���̎擾
	MenuItem** items = this->menuManager->getMenuItems();

	// �z�u�ʒu��x��y
	POINTFLOAT pos = { (FLOAT)(WND_SIZE.x / 2.0) , (FLOAT)(WND_SIZE.y / 2.0) };

	// �^�C�g��
	renderer.DrawRequestText(UI_TEXT_TITLE, pos, 50, RGB(255, 255, 255), FW_BOLD);
	pos.y += 40.0;

	for (int i = 0; i < this->menuManager->getMenuItemsLength(); i++)
	{
		// �I�𒆂̃��j���[�A�C�e���̂ݐԂ�����
		COLORREF fontColor = RGB(255, 255, 255);
		if (items[i]->getSelected()) {
			fontColor = RGB(255, 0, 0);
		}

		renderer.DrawRequestText(
			items[i]->getMenuItemName(), pos, 30, fontColor, FW_BOLD
		);
		pos.y += 30.0;
	}
}
