#include "HyperPlayer.h"

HyperPlayer::HyperPlayer(POINTFLOAT pos, KeyStateManager* keyStateManager, ShotManager* shotManager, Timer* timer)
	: PlayerBase(pos, 32, 32, 10, keyStateManager, shotManager, timer)
{
}

void HyperPlayer::Update()
{
	if (this->keyStateManager->getKeyState(VK_LEFT)->getIsDownCurrent())
	{
		this->pos.x -= (FLOAT)(this->speed * 60.0 / this->timer->getRealFPS());
	}
	
	if (this->keyStateManager->getKeyState(VK_RIGHT)->getIsDownCurrent())
	{
		this->pos.x += (FLOAT)(this->speed * 60.0 / this->timer->getRealFPS());
	}

	if (this->keyStateManager->getKeyState(VK_SPACE)->getIsDownStart())
	{
		this->shotManager->CreateShot<HyperShot>(this->pos, true);
	}
}
