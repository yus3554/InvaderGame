#pragma once
#include "../../GameActor.h"
#include "../../../KeyStateManager.h"
#include "../../manager/ShotManager.h"
#include "../shot/Shots.h"

class PlayerBase :
    public GameActor
{
protected:
    int speed;
    KeyStateManager* keyStateManager;
    ShotManager* shotManager;
public:
    PlayerBase();
    virtual void Update() = 0;
};

