#pragma once
#include <windows.h>
class DrawInfo
{
protected:
	double x;
	double y;
public:
	virtual void render(HDC hdc) = 0;
};

