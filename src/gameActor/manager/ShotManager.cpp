#include "ShotManager.h"

ShotManager::ShotManager()
{
	this->linkedList = new LinkedList<GameActor>();
}

void ShotManager::Update()
{
	for (int i = 0; i < this->linkedList->getLength(); i++)
	{
		this->linkedList->get(i)->Update();
	}
}
