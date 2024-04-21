#pragma once
#include "PlayerBase.h"
class NormalPlayer :
    public PlayerBase
{
public:
    NormalPlayer(POINTFLOAT pos, KeyStateManager* keyStateManager, ShotManager* shotManager, Timer* timer);
    void Update();
};

