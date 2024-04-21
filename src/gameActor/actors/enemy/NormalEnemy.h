#pragma once
#include "EnemyBase.h"

class NormalEnemy :
    public EnemyBase
{
public:
    NormalEnemy(POINTFLOAT pos, ShotManager* shotManager, Timer* timer, int returnMovementValue);
    void Update();
};

