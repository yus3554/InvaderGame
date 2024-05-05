#pragma once
#include "ShotBase.h"
class HyperShot :
    public ShotBase
{
public:
    HyperShot(POINTFLOAT pos, bool isPlayerShot, Timer* timer);
    void Update();
};

