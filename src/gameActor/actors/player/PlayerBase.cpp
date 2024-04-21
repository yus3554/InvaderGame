#include "PlayerBase.h"

PlayerBase::PlayerBase(POINTFLOAT pos, int width, int height, int speed, KeyStateManager* keyStateManager, ShotManager* shotManager, Timer* timer)
	: GameActor(pos, width, height, speed, timer)
{
	this->keyStateManager = keyStateManager;
	this->shotManager = shotManager;
}
