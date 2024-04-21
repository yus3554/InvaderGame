#include "ShotManager.h"

ShotManager::ShotManager(Timer* timer) : ActorManager(timer)
{
}

void ShotManager::Update()
{
	for (int i = 0; i < ActorManager::linkedList->getLength(); i++)
	{
		ActorManager::linkedList->get(i)->Update();
	}
}
