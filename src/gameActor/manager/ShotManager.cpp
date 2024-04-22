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


	for (int i = 0; i < ActorManager::linkedList->getLength(); i++)
	{
		POINTFLOAT pos = ActorManager::linkedList->get(i)->getPos();
		if (pos.x < -100 || pos.x > WND_SIZE.x + 100 || pos.y < -100 || pos.y > WND_SIZE.y + 100)
		{
			ActorManager::linkedList->remove(i);
			i--;
		}
	}
}
