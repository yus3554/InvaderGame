#include "ResourceManager.h"

ResourceDataInfo::ResourceDataInfo(ResourceType type, int resourceIndex, bool force)
{
	this->type = type;
	this->resourceIndex = resourceIndex;
	this->force = force;
}

ResourceData* ResourceDataInfo::Load()
{
	char filepath[120] = "";
	strcpy_s(filepath, RESOURCE_ROOT_FOLDERPATH);
	switch (type)
	{
	case RESOURCE_BACKGROUND:
		strcat_s(filepath, BACKGROUND_FILEPATHS[resourceIndex]);
		break;
	case RESOURCE_PLAYER:
		strcat_s(filepath, PLAYER_FILEPATHS[resourceIndex]);
		break;
	case RESOURCE_EXPLOSION:
		strcat_s(filepath, EXPLOSION_FILEPATHS[resourceIndex]);
		break;
	case RESOURCE_ENEMY:
		strcat_s(filepath, ENEMY_FILEPATHS[resourceIndex]);
		break;
	case RESOURCE_SHOT:
		strcat_s(filepath, SHOT_FILEPATHS[resourceIndex]);
		break;
	default:
		throw "illegal ResourceType.";
		break;
	}

	// ロード
	FILE* file;
	if (fopen_s(&file, filepath, "rb") != 0)
	{
		throw "file open error";
	}
	int offBits;
	int width;
	int height;
	fseek(file, 0xA, SEEK_SET);
	fread_s(&offBits, sizeof(offBits), sizeof(offBits), 1, file);

	fseek(file, 0x12, SEEK_SET);
	fread_s(&width, sizeof(width), sizeof(width), 1, file);
	fread_s(&height, sizeof(height), sizeof(height), 1, file);

	LPDWORD pixelBits = (LPDWORD)malloc(sizeof(DWORD) * width * height);

	fseek(file, offBits, SEEK_SET);
	BYTE blue;
	BYTE green;
	BYTE red;
	BYTE alpha;
	for (int i = height - 1; i >= 0; i--)
	{
		for (int j = 0; j < width; j++)
		{
			fread_s(&blue, sizeof(blue), sizeof(blue), 1, file);
			fread_s(&green, sizeof(green), sizeof(green), 1, file);
			fread_s(&red, sizeof(red), sizeof(red), 1, file);

			if (red == 0xff && green == 0xff && blue == 0xff)
				alpha = 0x00;
			else
				alpha = 0xff;

			pixelBits[i * width + j] =
				0x00000000 |
				((DWORD)alpha << 24) |
				((DWORD)red << 16) |
				((DWORD)green << 8) |
				((DWORD)blue);
		}
	}
	fclose(file);

	ResourceData* data = new ResourceData(resourceIndex, width, height, pixelBits);
	return data;
}

ResourceType ResourceDataInfo::GetType()
{
	return this->type;
}

int ResourceDataInfo::GetIndex()
{
	return this->resourceIndex;
}

bool ResourceDataInfo::GetForce()
{
	return this->force;
}

ResourceData::ResourceData(int resourceIndex, int width, int height, LPDWORD pixelBits)
{
	this->resourceIndex = resourceIndex;
	this->width = width;
	this->height = height;
	this->pixelBits = pixelBits;
}

ResourceData::~ResourceData()
{
	free(pixelBits);
}

ResourceManager::ResourceManager()
{
	this->resourceInfoList = new LinkedList<ResourceDataInfo>();
	this->backgroundsResourceList = new LinkedList<ResourceData>();
	this->playersResourceList = new LinkedList<ResourceData>();
	this->explosionsResourceList = new LinkedList<ResourceData>();
	this->enemiesResourceList = new LinkedList<ResourceData>();
	this->shotsResourceList = new LinkedList<ResourceData>();
	this->isCompletedLoad = true;
}

ResourceManager::~ResourceManager()
{
	delete this->resourceInfoList;
	delete this->backgroundsResourceList;
	delete this->playersResourceList;
	delete this->explosionsResourceList;
	delete this->enemiesResourceList;
	delete this->shotsResourceList;
}

void ResourceManager::LoadRequest(ResourceType type, int resourceIndex, bool force)
{
	this->isCompletedLoad = false;
	auto info = new ResourceDataInfo(type, resourceIndex, force);
	this->resourceInfoList->add(info);
}

void ResourceManager::Load()
{
	ResourceDataInfo* info;
	ResourceData* data;
	LinkedList<ResourceData>* list;

	for (int i = 0; i < this->resourceInfoList->getLength(); i++)
	{
		bool isLoaded = false;

		info = this->resourceInfoList->pop();
		switch (info->GetType())
		{
		case RESOURCE_BACKGROUND:
			list = this->backgroundsResourceList;
			break;
		case RESOURCE_PLAYER:
			list = this->playersResourceList;
			break;
		case RESOURCE_ENEMY:
			list = this->enemiesResourceList;
			break;
		case RESOURCE_SHOT:
			list = this->shotsResourceList;
			break;
		case RESOURCE_EXPLOSION:
			list = this->explosionsResourceList;
			break;
		default:
			throw "illegal ResourceType.";
			break;
		}

		// すでに同じresourceIndexのデータが入っている場合は、それを削除する
		for (int j = 0; j < list->getLength(); j++)
		{
			if (list->get(j)->resourceIndex == info->GetIndex())
			{
				if (info->GetForce())
					list->remove(j);
				isLoaded = true;
				break;
			}
		}

		// ロード（forceがtrue または isLoadedがfalse）
		if (info->GetForce() || !isLoaded)
		{
			data = info->Load();

			// 格納
			list->add(data);
		}
		delete info;
		i--;
	}

	Sleep(2000);
	this->isCompletedLoad = true;
}

void ResourceManager::Clear(ResourceType type, int resourceIndex)
{
	LinkedList<ResourceData>* list;
	switch (type)
	{
	case RESOURCE_BACKGROUND:
		list = this->backgroundsResourceList;
		break;
	case RESOURCE_PLAYER:
		list = this->playersResourceList;
		break;
	case RESOURCE_ENEMY:
		list = this->enemiesResourceList;
		break;
	case RESOURCE_SHOT:
		list = this->shotsResourceList;
		break;
	case RESOURCE_EXPLOSION:
		list = this->explosionsResourceList;
		break;
	default:
		throw "illegal ResourceType.";
		break;
	}

	for (int i = 0; i < list->getLength(); i++)
	{
		if (list->get(i)->resourceIndex == resourceIndex)
		{
			list->remove(i);
			break;
		}
	}
}

ResourceData* ResourceManager::GetResourceData(ResourceType type, int resourceIndex)
{
	LinkedList<ResourceData>* list;
	switch (type)
	{
	case RESOURCE_BACKGROUND:
		list = this->backgroundsResourceList;
		break;
	case RESOURCE_PLAYER:
		list = this->playersResourceList;
		break;
	case RESOURCE_EXPLOSION:
		list = this->explosionsResourceList;
		break;
	case RESOURCE_ENEMY:
		list = this->enemiesResourceList;
		break;
	case RESOURCE_SHOT:
		list = this->shotsResourceList;
		break;
	default:
		throw "illegal ResourceType.";
		break;
	}

	for (int i = 0; i < list->getLength(); i++)
	{
		if (list->get(i)->resourceIndex == resourceIndex)
		{
			return list->get(i);
		}
	}
	return NULL;
}

bool ResourceManager::GetIsCompletedLoad()
{
	return this->isCompletedLoad;
}
