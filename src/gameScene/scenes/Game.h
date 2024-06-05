#pragma once
#include "../GameScene.h"
#include "../../Renderer.h"
#include "../../gameActor/actors/player/Players.h"
#include "../../gameActor/manager/EnemyManager.h"
#include "../../gameActor/manager/ShotManager.h"
#include "../../Timer.h"
#include "../../ResourceManager.h"
#include "../../Constants.h"
#include <stdio.h>

enum InnerState
{
    PLAY,
    PRE_GAMEOVER,
    GAMEOVER,
    CLEAR
};

class Game :
    public GameScene
{
private:
    ResourceManager* resourceManager;
    GameDifficultyState* difficultyState;
    bool isNeedInit;
    PlayerBase* player;
    EnemyManager* enemyManager;
    ShotManager* shotManager;
    Timer* timer;
    InnerState innerState;
    int playerDeathFrame;
    int playerExplosionResourceIndex;
public:
    Game(GameState* state, GameState* preState, KeyStateManager* keyStateManager, Timer* timer, ResourceManager* resourceManager, GameDifficultyState* difficultyState);
    ~Game();
    void DrawRequest(Renderer& renderer);
    void Update();
    void GameInitialize();
    void GameFinalize();
    void HitCheckPlayer();
    void HitCheckEnemy();
};


