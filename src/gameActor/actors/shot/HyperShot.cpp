#include "HyperShot.h"

HyperShot::HyperShot(POINTFLOAT pos, bool isPlayerShot, Timer* timer)
	: ShotBase(pos, 10, 20, 10, isPlayerShot, timer)
{
}

void HyperShot::Update()
{
	if (this->isPlayerShot)
	{
		this->pos.y -= (FLOAT)(this->speed * 60.0 / this->timer->getRealFPS());
	}
	else
	{
		this->pos.y += (FLOAT)(this->speed * 60.0 / this->timer->getRealFPS());
	}
}
