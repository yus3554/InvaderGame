#pragma once
#include <windows.h>

class GameActor
{
protected:
	POINT pos;
	int speed;
public:
	GameActor();
	virtual void Update() = 0;
	POINT getPos();
};

