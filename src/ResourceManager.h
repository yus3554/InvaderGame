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


class ResourceDataInfo
{
private:
	ResourceType type;
	int resourceIndex;
	bool force;
public:
	ResourceDataInfo(ResourceType type, int resourceIndex, bool force);
	ResourceData* Load();
	ResourceType GetType();
	bool GetForce();
	int GetIndex();
};


class ResourceManager
{
private:
	LinkedList<ResourceDataInfo>* resourceInfoList;
	LinkedList<ResourceData>* backgroundsResourceList;
	LinkedList<ResourceData>* playersResourceList;
	LinkedList<ResourceData>* explosionsResourceList;
	LinkedList<ResourceData>* enemiesResourceList;
	LinkedList<ResourceData>* shotsResourceList;
	bool isLoading;
	CRITICAL_SECTION* cs;
	HANDLE hResourceEvent;

public:
	ResourceManager(CRITICAL_SECTION* cs);
	~ResourceManager();
	void LoadOnce();
	void LoadRequest(ResourceType type, int resourceIndex, bool force = false);
	void Clear(ResourceType type, int resourceIndex);
	ResourceData* GetResourceData(ResourceType type, int resourceIndex);
	bool GetIsCompletedLoad();
};

