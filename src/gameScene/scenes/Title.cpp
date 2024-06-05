#include "Title.h"

Title::Title(GameState* state, GameState* preState, KeyStateManager* keyStateManager, Timer* timer, GameDifficultyState* difficultyState)
{
	this->keyStateManager = keyStateManager;
	this->menuManager = new MenuManager();
	this->state = state;
	this->preState = preState;
	this->timer = timer;
	this->difficultyState = difficultyState;
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
		GameState state = STATE_TITLE;
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
		case MENU_CHANGE_FPS:
			this->menuManager->getCurrentItem()->NextNameIndex();
			state = STATE_TITLE;
			if (this->menuManager->getCurrentItem()->GetCurrentNameIndex() == 0)
			{
				// 固定FPS
				this->timer->LockFPS();
			}
			else
			{
				// 上限解放
				this->timer->UnlockFPS();
			}
			break;
		case MENU_CHANGE_DIFFICULT:
			this->menuManager->getCurrentItem()->NextNameIndex();
			state = STATE_TITLE;
			if (this->menuManager->getCurrentItem()->GetCurrentNameIndex() == 0)
			{
				// Normal
				*this->difficultyState = DIFFICULTY_STATE_NORMAL;
			}
			else
			{
				// Hard
				*this->difficultyState = DIFFICULTY_STATE_HARD;
			}
			break;
		default:
			state = STATE_QUIT;
			break;
		}

		*(this->preState) = *(this->state);
		*(this->state) = state;
	}
}

void Title::DrawRequest(Renderer& renderer)
{
	LinkedList<MenuItem>* menuList = this->menuManager->getMenuList();

	// 配置位置のxとy
	POINTFLOAT pos = { (FLOAT)(WND_SIZE.x / 2.0) , (FLOAT)(WND_SIZE.y / 2.0) };

	// タイトル
	renderer.DrawRequestText(UI_TEXT_TITLE, pos, 50, RGB(255, 255, 255), FW_BOLD);
	pos.y += 40.0;

	for (int i = 0; i < this->menuManager->getMenuListLength(); i++)
	{
		// 選択中のメニューアイテムのみ赤くする
		COLORREF fontColor = RGB(255, 255, 255);
		if (menuList->get(i)->getSelected()) {
			fontColor = RGB(255, 0, 0);
		}

		renderer.DrawRequestText(
			menuList->get(i)->getCurrentMenuItemName(), pos, 30, fontColor, FW_BOLD
		);
		pos.y += 30.0;
	}
}
