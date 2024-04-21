#pragma once
#include "ShotBase.h"
class NormalShot :
    public ShotBase
{
public:
    NormalShot(POINTFLOAT pos, bool isPlayerShot, Timer* timer);
    void Update();
};

