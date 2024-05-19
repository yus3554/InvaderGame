#include "Loading.h"

Loading::Loading(GameState* state, GameState* preState, KeyStateManager* keyStateManager, ResourceManager* resourceManager)
{
	this->keyStateManager = keyStateManager;
	this->resourceManager = resourceManager;
	this->isNeedInit = true;
	this->state = state;
	this->preState = preState;
}

Loading::~Loading()
{
}

void Loading::Update()
{
	// レンダースレッド用イベント
	HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, FALSE, EVENT_NAME_RESOURCE_BEGIN);
	if (hEvent == NULL)
	{
		throw "RESOURCE_LOAD_EVENT is NULL.";
		return;
	}
	
	if (this->isNeedInit)
	{
		SetEvent(hEvent);
		this->isNeedInit = false;
	}

	if (this->resourceManager->GetIsCompletedLoad())
	{
		OutputDebugString("aaa");
		*(this->state) = *(this->preState);
		*(this->preState) = STATE_LOADING;
		this->isNeedInit = true;
	}

	CloseHandle(hEvent);
}

void Loading::DrawRequest(Renderer& renderer)
{
	// 配置位置のxとy
	POINTFLOAT pos = { (FLOAT)(WND_SIZE.x / 2.0) , (FLOAT)(WND_SIZE.y / 2.0) };

	// タイトル
	renderer.DrawRequestText(UI_TEXT_LOADING, pos, 50, RGB(255, 255, 255), FW_BOLD);
	pos.y += 40.0;
}
