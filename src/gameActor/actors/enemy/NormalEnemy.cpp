#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(POINT pos, ShotManager* shotManager)
{
	this->pos = pos;
	this->shotManager = shotManager;
	this->speed = 2;
}

void NormalEnemy::Update()
{
	this->pos.x += this->speed;
	this->pos.y += 2;
	// this->shotManager->CreateShot<NormalShot>(this->pos, false);
}
