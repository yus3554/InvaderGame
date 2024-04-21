#pragma once
#include "ActorManager.h"
#include "../actors/shot/Shots.h"

class ShotManager :
    public ActorManager
{
public:
    ShotManager();
    void Update();
    template <class T>
    void CreateShot(POINT pos, bool isPlayerShot);
};

template <class T>
void ShotManager::CreateShot(POINT pos, bool isPlayerShot)
{
    auto actor = new T(pos, isPlayerShot);
    this->linkedList->add(actor);
}
