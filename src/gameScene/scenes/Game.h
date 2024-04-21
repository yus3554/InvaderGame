#pragma once
#include "../GameScene.h"
#include "../../Renderer.h"
#include "../../gameActor/actors/player/Players.h"
#include "../../gameActor/manager/EnemyManager.h"
#include "../../gameActor/manager/ShotManager.h"
#include "../../Timer.h"

class Game :
    public GameScene
{
private:
    bool isNeedInit;
    PlayerBase* player;
    EnemyManager* enemyManager;
    ShotManager* shotManager;
    Timer* timer;
    bool isGameOver;
    bool isClear;
public:
    Game(GameState* state, KeyStateManager* keyStateManager, Timer* timer);
    ~Game();
    void DrawRequest(Renderer& renderer);
    void Update();
    void GameInitialize();
    void GameFinalize();
    void HitCheckPlayer();
    void HitCheckEnemy();
};


