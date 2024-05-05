#include "NormalShot.h"

NormalShot::NormalShot(POINTFLOAT pos, bool isPlayerShot, Timer* timer)
	: ShotBase(pos, 10, 20, 3, isPlayerShot, timer)
{
}

void NormalShot::Update()
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
