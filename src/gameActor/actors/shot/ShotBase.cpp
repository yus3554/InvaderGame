#include "ShotBase.h"

ShotBase::ShotBase(POINTFLOAT pos, int width, int height, int speed, bool isPlayerShot, Timer* timer) 
	: GameActor(pos, width, height, speed, timer)
{
	this->isPlayerShot = isPlayerShot;
}

bool ShotBase::GetIsPlayerShot()
{
	return this->isPlayerShot;
}
