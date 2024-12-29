#include "Timer.h"


Timer::Timer(int fixedFPS) {
	this->fixedFPS = fixedFPS;
	this->realFPS = 0.0;
	this->nowFrame = 0;
	this->infFPS = 10000;
	this->isInfFPS = false;  // �����͌Œ�FPS
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
		// ������
		targetFPS = this->infFPS;
	}
	else
	{
		// �Œ�FPS
		targetFPS = this->fixedFPS;
	}

	// ���̃J�E���g���擾
	QueryPerformanceCounter(&nowCount);

	// �X�^�[�g�J�E���g��now�J�E���g�Ƃ̍�������A���݂̃t���[�������o��
	beforeFrame = (int)((double)(beforeCount.QuadPart - this->startCount.QuadPart) / ((double)cpuFreq.QuadPart / targetFPS));
	this->nowFrame = (int)((double)(nowCount.QuadPart - this->startCount.QuadPart) / ((double)cpuFreq.QuadPart / targetFPS));

	// ���݂̃t���[���̂ق���before�t���[�����傫���Ȃ����ꍇ�ɁA���̍�����loop�ɂ����
	if (this->nowFrame > beforeFrame) {
		// loop = this->nowFrame - beforeFrame;
		loop = 1;

		// realFPS�v�Z
		diffTime = (double)(nowCount.QuadPart - this->beforeCount.QuadPart) / cpuFreq.QuadPart;
		this->realFPS = 1.0 / diffTime;

		// beforeCount�̍X�V
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
	double realFps = this->realFPS;
	if (realFPS > 1)
	{
		return this->realFPS;
	}
	else
	{
		return 1;
	}
}

LARGE_INTEGER Timer::getCPUFreq() const
{
	return this->cpuFreq;
}

LARGE_INTEGER Timer::getNowCount() const
{
	LARGE_INTEGER nowCount;
	QueryPerformanceCounter(&nowCount);
	return nowCount;
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

void Timer::ResetBeforeCount()
{
	QueryPerformanceCounter(&beforeCount);
}
