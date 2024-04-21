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
	if (this->keyStateManager->getKeyState(VK_UP)->getIsDownStart()) {  // メニューカーソルを上に
		this->menuManager->previousItem();
	}

	if (this->keyStateManager->getKeyState(VK_DOWN)->getIsDownStart()) {  // メニューカーソルを下に
		this->menuManager->nextItem();
	}

	if (this->keyStateManager->getKeyState(VK_RETURN)->getIsDownStart()) {
		// menuのカレントIDに応じて、カレントゲームステートを変更する
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
	// 背景画像設定
	renderer.SetBackground(IDB_BITMAP1);

	// すべてのメニューアイテムの取得
	MenuItem** items = this->menuManager->getMenuItems();

	// 配置位置のxとy
	POINTFLOAT pos = { WND_SIZE.x / 2.0 , WND_SIZE.y / 2.0 };

	// タイトル
	renderer.DrawRequestText(UI_TEXT_TITLE, pos, 50, RGB(255, 255, 255), FW_BOLD);
	pos.y += 40.0;

	for (int i = 0; i < this->menuManager->getMenuItemsLength(); i++)
	{
		// 選択中のメニューアイテムのみ赤くする
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
