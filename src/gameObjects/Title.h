#pragma once
#include "GameScene.h"
#include "../Renderer.h"
#include "../MenuManager.h"
class Title :
    public GameScene
{
private:
    /// <summary>
    /// メニューマネージャー
    /// </summary>
    MenuManager* mm;

public:
    Title(GameState* state, KeyStateManager* km);
    ~Title();
    void Draw(Renderer& renderer);
    void Update();
};

