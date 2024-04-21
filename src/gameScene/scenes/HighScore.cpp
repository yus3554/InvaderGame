#include "HighScore.h"


HighScore::HighScore(GameState* state, KeyStateManager* keyStateManager)
{
	this->keyStateManager = keyStateManager;
	this->state = state;
}

HighScore::~HighScore()
{
}

void HighScore::Update()
{
	if (this->keyStateManager->getKeyState(VK_RETURN)->getIsDownStart()) {
		*(this->state) = STATE_TITLE;
	}
}

void HighScore::DrawRequest(Renderer& renderer)
{
	// 背景画像設定
	renderer.SetBackground(IDB_BITMAP1);

	// 配置位置のxとy
	POINTFLOAT pos = { WND_SIZE.x / 2.0 , WND_SIZE.y / 2.0 };

	// 結果表示
	renderer.DrawRequestText("HIGH SCORE", pos, 50, RGB(255, 255, 255), FW_BOLD);
}

