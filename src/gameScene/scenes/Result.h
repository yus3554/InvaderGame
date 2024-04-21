#pragma once
#include "../GameScene.h"
#include "../../Renderer.h"

class Result :
    public GameScene
{
private:

public:
    Result(GameState* state, KeyStateManager* keyStateManager);
    ~Result();
    void DrawRequest(Renderer& renderer);
    void Update();
};

