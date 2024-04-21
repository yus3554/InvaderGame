#pragma once
#include "GameObject.h"
#include "../KeyStateManager.h"
#include "../Renderer.h"

class GameScene :
    public GameObject
{
protected:
    /// <summary>
    /// �L�[���̓}�l�[�W���[
    /// </summary>
    KeyStateManager* keyStateManager;
    
    /// <summary>
    /// �X�e�[�g
    /// </summary>
    GameState* state;
public:
    GameScene();
    virtual void Update() = 0;
    virtual void DrawRequest(Renderer& renderer) = 0;
};

