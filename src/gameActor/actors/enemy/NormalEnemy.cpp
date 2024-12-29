#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(POINTFLOAT pos, ShotManager* shotManager, Timer* timer, int returnMovementValue)
	: EnemyBase(pos, 20, 20, 3, shotManager, timer, returnMovementValue)
{
	this->startCount = this->timer->getNowCount();
}

void NormalEnemy::Update()
{
	LARGE_INTEGER nowCount = this->timer->getNowCount();
	// “G‚ª¶¬‚³‚ê‚Ä‚©‚çAUpdate‚³‚ê‚é‚Ü‚Å‚É‰½•b‚©‚©‚Á‚½‚©‚ðŒvŽZi1000”{‚µ‚Ä‚¢‚é‚Ì‚Åƒ~ƒŠ•bj
	int progMS = (int)(((double)(nowCount.QuadPart - this->startCount.QuadPart) / (double)this->timer->getCPUFreq().QuadPart * 1000));

	// 600ƒ~ƒŠ•b‚²‚Æ‚ÉÜ‚è•Ô‚·
	if (progMS > 600)
	{
		// startCount‚ðƒŠƒZƒbƒg
		this->startCount = this->timer->getNowCount();

		this->pos.y += 20;
		this->speed *= -1;
	}
	this->pos.x += this->GetAdjustSpeed();

	if (this->currentCount % (int)(this->timer->getRealFPS()) == 0)
		this->shotManager->CreateShot<NormalShot>(this->pos, false);

	this->currentCount++;
}
