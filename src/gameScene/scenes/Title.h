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
    /// ���j���[�}�l�[�W���[
    /// </summary>
    MenuManager* menuManager;

    /// <summary>
    /// �^�C�}�[
    /// </summary>
    Timer* timer;

    /// <summary>
    /// �Q�[����Փx�p�X�e�[�g
    /// </summary>
    GameDifficultyState* difficultyState;

public:
    Title(GameState* state, GameState* preState, KeyStateManager* keyStateManager, Timer* timer, GameDifficultyState* difficultyState);
    ~Title();
    void DrawRequest(Renderer& renderer);
    void Update();
};

