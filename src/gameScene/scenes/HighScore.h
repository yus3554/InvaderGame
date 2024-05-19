#pragma once
#include "../GameScene.h"
#include "../../Renderer.h"

class HighScore :
    public GameScene
{
private:

public:
    HighScore(GameState* state, GameState* preState, KeyStateManager* keyStateManager);
    ~HighScore();
    void DrawRequest(Renderer& renderer);
    void Update();
};

