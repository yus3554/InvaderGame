#pragma once
#include "../GameScene.h"
#include "../../Renderer.h"
#include "../../gameActor/actors/player/Players.h"
#include "../../gameActor/manager/EnemyManager.h"
#include "../../gameActor/manager/ShotManager.h"

class Game :
    public GameScene
{
private:
    bool isNeedInit;
    PlayerBase* player;
    EnemyManager* enemyManager;
    ShotManager* shotManager;
public:
    Game(GameState* state, KeyStateManager* keyStateManager);
    ~Game();
    void DrawRequest(Renderer& renderer);
    void Update();
    void GameInitialize();
    void GameFinalize();
};


