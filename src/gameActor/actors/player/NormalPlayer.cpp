#include "NormalPlayer.h"

NormalPlayer::NormalPlayer(POINTFLOAT pos, KeyStateManager* keyStateManager, ShotManager* shotManager, Timer* timer)
	: PlayerBase(pos, 20, 20, 10, keyStateManager, shotManager, timer)
{
}

void NormalPlayer::Update()
{
	if (this->keyStateManager->getKeyState(VK_LEFT)->getIsDownCurrent())
	{
		this->pos.x -= this->speed * 60.0 / this->timer->getRealFPS();
	}
	
	if (this->keyStateManager->getKeyState(VK_RIGHT)->getIsDownCurrent())
	{
		this->pos.x += this->speed * 60.0 / this->timer->getRealFPS();
	}

	if (this->keyStateManager->getKeyState(VK_SPACE)->getIsDownStart())
	{
		this->shotManager->CreateShot<NormalShot>(this->pos, true);
	}
}
