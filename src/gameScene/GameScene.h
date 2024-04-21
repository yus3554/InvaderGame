#pragma once
#include "GameObject.h"
#include "../KeyStateManager.h"
#include "../Renderer.h"

class GameScene :
    public GameObject
{
protected:
    /// <summary>
    /// キー入力マネージャー
    /// </summary>
    KeyStateManager* keyStateManager;
    
    /// <summary>
    /// ステート
    /// </summary>
    GameState* state;
public:
    GameScene();
    virtual void Update() = 0;
    virtual void DrawRequest(Renderer& renderer) = 0;
};

