#include "EnemyBase.h"

EnemyBase::EnemyBase(POINTFLOAT pos, int width, int height, int speed, ShotManager* shotManager, Timer* timer, int returnMovementValue)
	: GameActor(pos, width, height, speed, timer)
{
	this->shotManager = shotManager;
	this->currentCount = 0;
	this->returnMovementValue = returnMovementValue;
}

