#include "EnemyManager.h"

EnemyManager::EnemyManager(ShotManager* shotManager, Timer* timer) : ActorManager(timer)
{
	this->shotManager = shotManager;
}

void EnemyManager::Update()
{
	for (int i = 0; i < ActorManager::linkedList->getLength(); i++)
	{
		ActorManager::linkedList->get(i)->Update();
	}
}
