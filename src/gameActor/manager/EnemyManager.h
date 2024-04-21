#pragma once
#include "ActorManager.h"
#include "../actors/enemy/Enemys.h"

class EnemyManager :
    public ActorManager
{
private:
    ShotManager* shotManager;
public:
    EnemyManager(ShotManager* shotManager);
    void Update();

    template <class T>
    void CreateEnemy(POINT pos);
};

template <class T>
void EnemyManager::CreateEnemy(POINT pos)
{
    auto actor = new T(pos, this->shotManager);
    this->linkedList->add(actor);
}

