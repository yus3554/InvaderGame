#pragma once
#include "../../GameActor.h"
#include "../../manager/ShotManager.h"
#include "../shot/Shots.h"

class EnemyBase :
    public GameActor
{
protected:
    ShotManager* shotManager;
public:
    EnemyBase();
    virtual void Update() = 0;
};

