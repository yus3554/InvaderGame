#pragma once
#include "../../GameActor.h"

class ShotBase :
    public GameActor
{
protected:
    int speed;
    bool isPlayerShot;
public:
    ShotBase();
    virtual void Update() = 0;
};

