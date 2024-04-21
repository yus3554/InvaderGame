#include "NormalPlayer.h"

NormalPlayer::NormalPlayer(POINT pos, KeyStateManager* keyStateManager, ShotManager* shotManager)
{
	this->pos = pos;
	this->speed = 10;
	this->keyStateManager = keyStateManager;
	this->shotManager = shotManager;
}

void NormalPlayer::Update()
{
	if (this->keyStateManager->getKeyState(VK_LEFT)->getIsDownCurrent())
	{
		this->pos.x -= this->speed;
	}
	
	if (this->keyStateManager->getKeyState(VK_RIGHT)->getIsDownCurrent())
	{
		this->pos.x += this->speed;
	}

	if (this->keyStateManager->getKeyState(VK_SPACE)->getIsDownStart())
	{
		this->shotManager->CreateShot<NormalShot>(this->pos, true);
	}
}
