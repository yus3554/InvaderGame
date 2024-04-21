#include "ActorManager.h"

ActorManager::ActorManager()
{
	this->linkedList = NULL;
}

int ActorManager::getListLength()
{
	return this->linkedList->getLength();
}

GameActor* ActorManager::getActor(int index)
{
	return this->linkedList->get(index);
}

void ActorManager::removeActor(int index)
{
	this->linkedList->remove(index);
}

void ActorManager::clear()
{
	for (int i = 0; i < this->linkedList->getLength(); i++)
	{
		this->linkedList->remove(i);
	}
}
