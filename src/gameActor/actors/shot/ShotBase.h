#pragma once
#include "../../GameActor.h"

class ShotBase :
    public GameActor
{
protected:
    bool isPlayerShot;
public:
    ShotBase(POINTFLOAT pos, int width, int height, int speed, bool isPlayerShot, Timer* timer);
    virtual void Update() = 0;
};

