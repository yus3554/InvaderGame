#pragma once
#include "GameObject.h"
#include "../KeyStateManager.h"
class GameScene :
    public GameObject
{
protected:
    /// <summary>
    /// キー入力マネージャー
    /// </summary>
    KeyStateManager* km;

    GameState* state;
public:
    void Update();
    void Draw();
};

