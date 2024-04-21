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
	// �w�i�摜�ݒ�
	renderer.SetBackground(IDB_BITMAP1);

	// �z�u�ʒu��x��y
	POINTFLOAT pos = { WND_SIZE.x / 2.0 , WND_SIZE.y / 2.0 };

	// ���ʕ\��
	renderer.DrawRequestText("RESULT", pos, 50, RGB(255, 255, 255), FW_BOLD);
}

