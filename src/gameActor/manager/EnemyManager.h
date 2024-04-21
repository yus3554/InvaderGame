#pragma once
#include "ActorManager.h"
#include "../actors/enemy/Enemys.h"

class EnemyManager :
    public ActorManager
{
private:
    ShotManager* shotManager;
public:
    EnemyManager(ShotManager* shotManager, Timer* timer);
    void Update();

    template <class T>
    void CreateEnemy(POINTFLOAT pos, int returnMovementValue);
};

template <class T>
void EnemyManager::CreateEnemy(POINTFLOAT pos, int returnMovementValue)
{
    auto actor = new T(pos, this->shotManager, ActorManager::timer, returnMovementValue);
    ActorManager::linkedList->add(actor);
}

