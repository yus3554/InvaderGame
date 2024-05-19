#pragma once
#include <windows.h>
#include "../GameScene.h"
#include "../../Renderer.h"
#include "../../ResourceManager.h"

class Loading :
    public GameScene
{
private:
    ResourceManager* resourceManager;
    bool isNeedInit;

public:
    Loading(GameState* state, GameState* preState, KeyStateManager* keyStateManager, ResourceManager* resourceManager);
    ~Loading();
    void DrawRequest(Renderer& renderer);
    void Update();
};

