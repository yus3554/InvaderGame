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
		this->pos.x - (this->width / 2),
		this->pos.y - (this->height / 2),
		this->pos.x + (this->width / 2),
		this->pos.y + (this->height / 2),
	};
	return rect;
}

int GameActor::GetWidth()
{
	return this->width;
}

int GameActor::GetHeight()
{
	return this->height;
}
