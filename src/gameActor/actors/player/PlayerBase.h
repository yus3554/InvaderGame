#pragma once
#include "../../GameActor.h"
#include "../../../KeyStateManager.h"
#include "../../manager/ShotManager.h"
#include "../shot/Shots.h"

class PlayerBase :
    public GameActor
{
protected:
    KeyStateManager* keyStateManager;
    ShotManager* shotManager;
public:
    PlayerBase(POINTFLOAT pos, int width, int height, int speed, KeyStateManager* keyStateManager, ShotManager* shotManager, Timer* timer);
    virtual void Update() = 0;
};

