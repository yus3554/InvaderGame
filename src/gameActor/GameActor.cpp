#include "GameActor.h"

GameActor::GameActor(POINTFLOAT pos, int width, int height, int speed, Timer* timer)
{
	this->pos = pos;
	this->initPos = { pos.x , pos.y };
	this->width = width;
	this->height = height;
	this->speed = speed;
	this->timer = timer;
}

POINTFLOAT GameActor::getPos()
{
	return this->pos;
}

void GameActor::InitPos()
{
	this->pos = {this->initPos.x, this->initPos.y};
}

RECT GameActor::GetRect()
{
	// ‚±‚±‚Å‚Ìpos‚Í’†S
	RECT rect = { 
		(LONG)(this->pos.x - (this->width / 2)),
		(LONG)(this->pos.y - (this->height / 2)),
		(LONG)(this->pos.x + (this->width / 2)),
		(LONG)(this->pos.y + (this->height / 2)),
	};
	return rect;
}

int GameActor::GetWidth() const
{
	return this->width;
}

int GameActor::GetHeight()
{
	return this->height;
}

float GameActor::GetAdjustSpeed()
{
	return (FLOAT)(this->speed * 60.0 / this->timer->getRealFPS());
}
