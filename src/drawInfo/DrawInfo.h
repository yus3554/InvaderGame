#pragma once
#include <windows.h>
class DrawInfo
{
protected:
	POINT pos;
public:
	DrawInfo();
	virtual void render(HDC hdc) = 0;
};

