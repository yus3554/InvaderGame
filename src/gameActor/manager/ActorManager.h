#pragma once
#include "../GameActor.h"
#include "../../KeyStateManager.h"
#include "../../LinkedList.h"
#include "../../Timer.h"

class ActorManager
{
protected:
	LinkedList<GameActor>* linkedList;
	Timer* timer;
public:
	ActorManager(Timer* timer);
	virtual void Update() = 0;
	int getListLength();
	GameActor* getActor(int index);
	void removeActor(int index);
	void clear();
};

