#pragma once
#include "../GameScene.h"
#include "../../Renderer.h"
#include "../../MenuManager.h"
#include "../../Timer.h"
#include "../../Constants.h"

class Title :
    public GameScene
{
private:
    /// <summary>
    /// メニューマネージャー
    /// </summary>
    MenuManager* menuManager;

    /// <summary>
    /// タイマー
    /// </summary>
    Timer* timer;

    /// <summary>
    /// ゲーム難易度用ステート
    /// </summary>
    GameDifficultyState* difficultyState;

public:
    Title(GameState* state, GameState* preState, KeyStateManager* keyStateManager, Timer* timer, GameDifficultyState* difficultyState);
    ~Title();
    void DrawRequest(Renderer& renderer);
    void Update();
};

