#include "NormalShot.h"

NormalShot::NormalShot(POINT pos, bool isPlayerShot)
{
	this->pos = pos;
	this->isPlayerShot = isPlayerShot;
	this->speed = 100;
}

void NormalShot::Update()
{
	/*if (this->isPlayerShot)
	{
		this->pos.y -= this->speed;
	}
	else
	{
		this->pos.y += this->speed;
	}*/
}
