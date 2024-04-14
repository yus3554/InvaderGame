#include "Timer.h"


Timer::Timer(int targetFPS) {
	this->targetFPS = targetFPS;
	this->realFPS = 0.0;
	QueryPerformanceFrequency(&this->cpuFreq);
	QueryPerformanceCounter(&startCount);
	QueryPerformanceCounter(&beforeCount);
}


int Timer::getDiffFrame()
{
	int loop;
	LARGE_INTEGER nowCount;
	int nowFrame;
	int beforeFrame;
	double diffTime;

	// 今のカウントを取得
	QueryPerformanceCounter(&nowCount);

	// スタートカウントとnowカウントとの差分から、現在のフレーム数を出す
	beforeFrame = (int)((beforeCount.QuadPart - this->startCount.QuadPart) / (cpuFreq.QuadPart / this->targetFPS));
	nowFrame = (int)((nowCount.QuadPart - this->startCount.QuadPart) / (cpuFreq.QuadPart / this->targetFPS));

	// 現在のフレームのほうがbeforeフレームより大きくなった場合に、その差分をloopにいれる
	if (nowFrame > beforeFrame) {
		loop = nowFrame - beforeFrame;

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


int Timer::getTargetFPS()
{
	return this->targetFPS;
}


double Timer::getRealFPS()
{
	return this->realFPS;
}


