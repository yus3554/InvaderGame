#pragma once
#include "EnemyBase.h"

class NormalEnemy :
    public EnemyBase
{
public:
    NormalEnemy(POINT pos, ShotManager* shotManager);
    void Update();
};

