#include "ActorManager.h"

ActorManager::ActorManager(Timer* timer)
{
	this->linkedList = new LinkedList<GameActor>();
	this->timer = timer;
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
	this->linkedList->clear();
}
