#pragma once
#include <windows.h>
#include "Menu.h"

enum GameState
{
	STATE_TITLE,
	STATE_GAME,
	STATE_HIGHSCORE,
	STATE_RESULT,
	STATE_QUIT,
	
	STATE_NUM
};


class GameManager
{
private:
	Menu* menu;
	GameState currentGameState;
	POINT playerPos;  // TODO: キャラクターの場所は、おそらくGM内じゃなくてキャラクタクラス内に書くべき
	int score;

public:
	GameManager();
	~GameManager();
	GameState getCurrentGameState();
	void setCurrentGameState(GameState state);
	POINT getPlayerPos();
	void setPlayerPos(POINT pos);
	Menu* getMenu();
	void keyPress(WPARAM wParam);
};

