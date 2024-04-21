#pragma once
#include "../GameActor.h"
#include "../../KeyStateManager.h"
#include "../../LinkedList.h"

class ActorManager
{
protected:
	LinkedList<GameActor>* linkedList;
public:
	ActorManager();
	virtual void Update() = 0;
	int getListLength();
	GameActor* getActor(int index);
	void removeActor(int index);
	void clear();
};

