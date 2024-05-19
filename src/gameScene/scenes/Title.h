#pragma once
#include "../GameScene.h"
#include "../../Renderer.h"
#include "../../MenuManager.h"

class Title :
    public GameScene
{
private:
    /// <summary>
    /// メニューマネージャー
    /// </summary>
    MenuManager* menuManager;

public:
    Title(GameState* state, GameState* preState, KeyStateManager* keyStateManager);
    ~Title();
    void DrawRequest(Renderer& renderer);
    void Update();
};

