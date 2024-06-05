#pragma once
#include "EnemyBase.h"

class HyperEnemy :
    public EnemyBase
{
public:
    HyperEnemy(POINTFLOAT pos, ShotManager* shotManager, Timer* timer, int returnMovementValue);
    void Update();
};

