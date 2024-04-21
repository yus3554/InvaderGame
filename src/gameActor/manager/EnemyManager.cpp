#include "EnemyManager.h"

EnemyManager::EnemyManager(ShotManager* shotManager)
{
	this->linkedList = new LinkedList<GameActor>();
	this->shotManager = shotManager;
}

void EnemyManager::Update()
{
	for (int i = 0; i < this->linkedList->getLength(); i++)
	{
		this->linkedList->get(i)->Update();
	}
}
