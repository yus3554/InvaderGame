#pragma once
#include "LinkedList.h"
#include "Constants.h"
#include <stdio.h>
#include <string.h>

struct ResourceData
{
	ResourceData(int resourceIndex, int width, int height, LPDWORD pixelBits);
	~ResourceData();
	int resourceIndex;
	int width;
	int height;
	LPDWORD pixelBits;
};

class ResourceManager
{
private:
	LinkedList<ResourceData>* backgroundsResourceList;
	LinkedList<ResourceData>* playersResourceList;
	LinkedList<ResourceData>* enemiesResourceList;
	LinkedList<ResourceData>* shotsResourceList;

public:
	ResourceManager();
	~ResourceManager();
	void Load(ResourceType type, int resourceIndex);
	void Clear(ResourceType type, int resourceIndex);
	ResourceData* GetResourceData(ResourceType type, int resourceIndex);
};

