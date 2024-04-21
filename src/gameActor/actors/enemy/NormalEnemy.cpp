#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(POINTFLOAT pos, ShotManager* shotManager, Timer* timer, int returnMovementValue)
	: EnemyBase(pos, 20, 20, 3, shotManager, timer, returnMovementValue)
{
}

void NormalEnemy::Update()
{
	if (this->pos.x < this->initPos.x || this->pos.x > this->initPos.x + this->returnMovementValue)
	{
		this->pos.y += 20;
		if ((this->pos.x < this->initPos.x && this->speed < 0) ||
			(this->pos.x > this->initPos.x + this->returnMovementValue && this->speed > 0)
			)
		{
			this->speed *= -1;
		}
	}
	this->pos.x += this->speed * 60.0 / this->timer->getRealFPS();

	if (this->currentCount % (int)(this->timer->getRealFPS() / 3) == 0)
		this->shotManager->CreateShot<NormalShot>(this->pos, false);

	this->currentCount++;
}
