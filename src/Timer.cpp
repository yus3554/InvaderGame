#include "Timer.h"


Timer::Timer(int fixedFPS) {
	this->fixedFPS = fixedFPS;
	this->realFPS = 0.0;
	this->nowFrame = 0;
	this->infFPS = 10000;
	this->isInfFPS = false;  // 初期は固定FPS
	QueryPerformanceFrequency(&this->cpuFreq);
	QueryPerformanceCounter(&startCount);
	QueryPerformanceCounter(&beforeCount);
}


int Timer::getDiffFrame()
{
	int loop;
	LARGE_INTEGER nowCount;
	int beforeFrame;
	double diffTime;
	int targetFPS;

	if (this->isInfFPS)
	{
		// 上限解放
		targetFPS = this->infFPS;
	}
	else
	{
		// 固定FPS
		targetFPS = this->fixedFPS;
	}

	// 今のカウントを取得
	QueryPerformanceCounter(&nowCount);

	// スタートカウントとnowカウントとの差分から、現在のフレーム数を出す
	beforeFrame = (int)((double)(beforeCount.QuadPart - this->startCount.QuadPart) / ((double)cpuFreq.QuadPart / targetFPS));
	this->nowFrame = (int)((double)(nowCount.QuadPart - this->startCount.QuadPart) / ((double)cpuFreq.QuadPart / targetFPS));

	// 現在のフレームのほうがbeforeフレームより大きくなった場合に、その差分をloopにいれる
	if (this->nowFrame > beforeFrame) {
		// loop = this->nowFrame - beforeFrame;
		loop = 1;

		// realFPS計算
		diffTime = (double)(nowCount.QuadPart - this->beforeCount.QuadPart) / cpuFreq.QuadPart;
		this->realFPS = 1.0 / diffTime;

		// beforeCountの更新
		beforeCount = nowCount;
	}
	else {
		loop = 0;
	}

	return loop;
}


int Timer::getFixedFPS() const
{
	return this->fixedFPS;
}


double Timer::getRealFPS() const
{
	return this->realFPS;
}

int Timer::getNowFrame() const
{
	return this->nowFrame;
}

void Timer::UnlockFPS()
{
	this->isInfFPS = true;
}

void Timer::LockFPS()
{
	this->isInfFPS = false;
}
