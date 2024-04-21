#pragma once
#include "ActorManager.h"
#include "../actors/shot/Shots.h"

class ShotManager :
    public ActorManager
{
public:
    ShotManager(Timer* timer);
    void Update();
    template <class T>
    void CreateShot(POINTFLOAT pos, bool isPlayerShot);
};

template <class T>
void ShotManager::CreateShot(POINTFLOAT pos, bool isPlayerShot)
{
    auto actor = new T(pos, isPlayerShot, ActorManager::timer);
    ActorManager::linkedList->add(actor);
}
