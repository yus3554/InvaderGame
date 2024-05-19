#include "Result.h"


Result::Result(GameState* state, GameState* preState, KeyStateManager* keyStateManager)
{
	this->keyStateManager = keyStateManager;
	this->state = state;
	this->preState = preState;
}

Result::~Result()
{
}

void Result::Update()
{
	if (this->keyStateManager->getKeyState(VK_RETURN)->getIsDownStart()) {
		*(this->preState) = *(this->state);
		*(this->state) = STATE_TITLE;
	}
}

void Result::DrawRequest(Renderer& renderer)
{
	// �z�u�ʒu��x��y
	POINTFLOAT pos = { (FLOAT)(WND_SIZE.x / 2.0) , (FLOAT)(WND_SIZE.y / 2.0) };

	// ���ʕ\��
	renderer.DrawRequestText("RESULT", pos, 50, RGB(255, 255, 255), FW_BOLD);
}

