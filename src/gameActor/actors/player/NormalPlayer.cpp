#include "NormalPlayer.h"

NormalPlayer::NormalPlayer(POINTFLOAT pos, KeyStateManager* keyStateManager, ShotManager* shotManager, Timer* timer)
	: PlayerBase(pos, 20, 20, 10, keyStateManager, shotManager, timer)
{
}

void NormalPlayer::Update()
{
	if (this->keyStateManager->getKeyState(VK_LEFT)->getIsDownCurrent())
	{
		this->pos.x -= this->GetAdjustSpeed();
	}
	
	if (this->keyStateManager->getKeyState(VK_RIGHT)->getIsDownCurrent())
	{
		this->pos.x += this->GetAdjustSpeed();
	}

	if (this->keyStateManager->getKeyState(VK_SPACE)->getIsDownRepeat(0.5))
	{
		this->shotManager->CreateShot<NormalShot>(this->pos, true);
	}
}
