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

	// ���̃J�E���g���擾
	QueryPerformanceCounter(&nowCount);

	// �X�^�[�g�J�E���g��now�J�E���g�Ƃ̍�������A���݂̃t���[�������o��
	beforeFrame = (int)((beforeCount.QuadPart - this->startCount.QuadPart) / (cpuFreq.QuadPart / this->targetFPS));
	nowFrame = (int)((nowCount.QuadPart - this->startCount.QuadPart) / (cpuFreq.QuadPart / this->targetFPS));

	// ���݂̃t���[���̂ق���before�t���[�����傫���Ȃ����ꍇ�ɁA���̍�����loop�ɂ����
	if (nowFrame > beforeFrame) {
		loop = nowFrame - beforeFrame;

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


int Timer::getTargetFPS()
{
	return this->targetFPS;
}


double Timer::getRealFPS()
{
	return this->realFPS;
}


