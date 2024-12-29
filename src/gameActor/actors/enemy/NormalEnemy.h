#pragma once
#include "EnemyBase.h"
#include <stdio.h>

class NormalEnemy :
    public EnemyBase
{
private:
    LARGE_INTEGER startCount;
public:
    NormalEnemy(POINTFLOAT pos, ShotManager* shotManager, Timer* timer, int returnMovementValue);
    void Update();
};

