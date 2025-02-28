#include "NormalEnemy.h"

NormalEnemy::NormalEnemy(POINTFLOAT pos, ShotManager* shotManager, Timer* timer, int returnMovementValue)
	: EnemyBase(pos, 20, 20, 3, shotManager, timer, returnMovementValue)
{
	this->startCount = this->timer->getNowCount();
}

void NormalEnemy::Update()
{
	LARGE_INTEGER nowCount = this->timer->getNowCount();
	// 敵が生成されてから、Updateされるまでに何秒かかったかを計算（1000倍しているのでミリ秒）
	int progMS = (int)(((double)(nowCount.QuadPart - this->startCount.QuadPart) / (double)this->timer->getCPUFreq().QuadPart * 1000));

	// 600ミリ秒ごとに折り返す
	if (progMS > 600)
	{
		// startCountをリセット
		this->startCount = this->timer->getNowCount();

		this->pos.y += 20;
		this->speed *= -1;
	}
	this->pos.x += this->GetAdjustSpeed();

	if (this->currentCount % (int)(this->timer->getRealFPS()) == 0)
		this->shotManager->CreateShot<NormalShot>(this->pos, false);

	this->currentCount++;
}
