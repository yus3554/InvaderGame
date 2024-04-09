#pragma once
#include <windows.h>
#include "Menu.h"
#include "Timer.h"
#include "DrawManager.h"
#include "KeyStateManager.h"


class GameManager
{
private:
	Menu* menu;
	Timer* timer;
	DrawManager* dm;
	KeyStateManager* km;
	HWND hwnd;
	GameState currentGameState;
	unsigned char downKeys[2];

	int score;
	POINT playerPos;  // TODO: キャラクターの場所は、おそらくGM内じゃなくてキャラクタクラス内に書くべき

public:
	GameManager(HWND hwnd);
	~GameManager();
	void GameInit();
	void GameUpdate();
	void GameQuit();
	GameState getCurrentGameState();
	void setCurrentGameState(GameState state);
	POINT getPlayerPos();
	void setPlayerPos(POINT pos);
	Menu* getMenu();
	void keyPress();
};

