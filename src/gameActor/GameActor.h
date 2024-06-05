#pragma once
#include <windows.h>
#include "../Timer.h"

class GameActor
{
protected:
	POINTFLOAT pos;
	POINTFLOAT initPos;
	int width;
	int height;
	int speed;
	Timer* timer;
public:
	GameActor(POINTFLOAT pos, int width, int height, int speed, Timer* timer);
	virtual void Update() = 0;
	POINTFLOAT getPos();
	void InitPos();
	RECT GetRect();
	int GetWidth() const;
	int GetHeight();

	/// <summary>
	/// �t���[�����[�g�ŕ␳���ꂽ�X�s�[�h
	/// </summary>
	/// <returns></returns>
	float GetAdjustSpeed();
};

