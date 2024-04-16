#include "Title.h"

Title::Title(GameState* state, KeyStateManager* km)
{
	this->km = km;
	this->mm = new MenuManager();
	this->state = state;
}

Title::~Title()
{
	delete this->mm;
}

void Title::Update()
{
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

void Title::Draw(Renderer& renderer)
{
	// �w�i�摜�ݒ�
	renderer.SetBackground(IDB_BITMAP1);

	// ���ׂẴ��j���[�A�C�e���̎擾
	MenuItem** items = this->mm->getMenuItems();

	// �z�u�ʒu��x��y
	double pos_x = WND_SIZE.x / 2.0;
	double pos_y = WND_SIZE.y / 2.0;

	// �^�C�g��
	renderer.RequestDrawText(UI_TEXT_TITLE, pos_x, pos_y, 50, RGB(255, 255, 255), FW_BOLD);
	pos_y += 40.0;

	for (int i = 0; i < this->mm->getMenuItemsLength(); i++)
	{
		// �I�𒆂̃��j���[�A�C�e���̂ݐԂ�����
		COLORREF fontColor = RGB(255, 255, 255);
		if (items[i]->getSelected()) {
			fontColor = RGB(255, 0, 0);
		}

		renderer.RequestDrawText(
			items[i]->getMenuItemName(), pos_x, pos_y, 30, fontColor, FW_BOLD
		);
		pos_y += 30.0;
	}
}
