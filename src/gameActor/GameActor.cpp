#include "GameActor.h"

GameActor::GameActor()
{
	this->pos = { 0, 0 };
	this->speed = 0;
}

POINT GameActor::getPos()
{
	return this->pos;
}
