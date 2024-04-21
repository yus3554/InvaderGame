#pragma once
#include "ShotBase.h"
class NormalShot :
    public ShotBase
{
public:
    NormalShot(POINT pos, bool isPlayerShot);
    void Update();
};

