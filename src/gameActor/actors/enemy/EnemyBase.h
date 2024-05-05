#pragma once
#include "../../GameActor.h"
#include "../../manager/ShotManager.h"
#include "../shot/Shots.h"
#include <stdlib.h>

class EnemyBase :
    public GameActor
{
protected:
    ShotManager* shotManager;
    int currentCount;
    int returnMovementValue;
public:
    EnemyBase(POINTFLOAT pos, int width, int height, int speed, ShotManager* shotManager, Timer* timer, int returnMovementValue);
    virtual void Update() = 0;
};

