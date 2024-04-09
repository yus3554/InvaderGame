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
	POINT playerPos;  // TODO: �L�����N�^�[�̏ꏊ�́A�����炭GM������Ȃ��ăL�����N�^�N���X���ɏ����ׂ�

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

