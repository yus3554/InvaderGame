#pragma once
#include "PlayerBase.h"
class HyperPlayer :
    public PlayerBase
{
public:
    HyperPlayer(POINTFLOAT pos, KeyStateManager* keyStateManager, ShotManager* shotManager, Timer* timer);
    void Update();
};

