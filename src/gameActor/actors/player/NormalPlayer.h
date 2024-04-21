#pragma once
#include "PlayerBase.h"
class NormalPlayer :
    public PlayerBase
{
public:
    NormalPlayer(POINT pos, KeyStateManager* keyStateManager, ShotManager* shotManager);
    void Update();
};

