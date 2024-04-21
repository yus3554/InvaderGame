#include "Result.h"


Result::Result(GameState* state, KeyStateManager* keyStateManager)
{
	this->keyStateManager = keyStateManager;
	this->state = state;
}

Result::~Result()
{
}

void Result::Update()
{
	if (this->keyStateManager->getKeyState(VK_RETURN)->getIsDownStart()) {
		*(this->state) = STATE_TITLE;
	}
}

void Result::DrawRequest(Renderer& renderer)
{
	// 背景画像設定
	renderer.SetBackground(IDB_BITMAP1);

	// 配置位置のxとy
	POINT pos = { (LONG)(WND_SIZE.x / 2.0) , (LONG)(WND_SIZE.y / 2.0) };

	// 結果表示
	renderer.DrawRequestText("RESULT", pos, 50, RGB(255, 255, 255), FW_BOLD);
}

