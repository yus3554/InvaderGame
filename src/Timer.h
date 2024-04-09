#pragma once
#include <windows.h>

class Timer
{
private:
	int targetFPS;
	double realFPS;
	LARGE_INTEGER cpuFreq;
	LARGE_INTEGER startCount;
	LARGE_INTEGER beforeCount;

public:
	Timer(int fps);
	int getDiffFrame();
	int getTargetFPS();
	double getRealFPS();
};

