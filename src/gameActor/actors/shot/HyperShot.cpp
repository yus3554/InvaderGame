#include "HyperShot.h"

HyperShot::HyperShot(POINTFLOAT pos, bool isPlayerShot, Timer* timer)
	: ShotBase(pos, 32, 32, 10, isPlayerShot, timer)
{
}

void HyperShot::Update()
{
	if (this->isPlayerShot)
	{
		this->pos.y -= this->GetAdjustSpeed();
	}
	else
	{
		this->pos.y += this->GetAdjustSpeed();
	}
}
