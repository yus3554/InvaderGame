#include "EnemyBase.h"

EnemyBase::EnemyBase(POINTFLOAT pos, int width, int height, int speed, ShotManager* shotManager, Timer* timer, int returnMovementValue)
	: GameActor(pos, width, height, speed, timer)
{
	this->shotManager = shotManager;
	this->currentCount = 0 + (int)(rand() * (100 - 0 + 1.0) / (1.0 + RAND_MAX));
	this->returnMovementValue = returnMovementValue;
}

