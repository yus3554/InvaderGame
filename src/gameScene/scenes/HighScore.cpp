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
	// �z�u�ʒu��x��y
	POINTFLOAT pos = { (FLOAT)(WND_SIZE.x / 2.0) , (FLOAT)(WND_SIZE.y / 2.0) };

	// ���ʕ\��
	renderer.DrawRequestText("HIGH SCORE", pos, 50, RGB(255, 255, 255), FW_BOLD);
}

