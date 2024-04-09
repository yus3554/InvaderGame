#pragma once
#include <windows.h>


/// ####################################################
/// 
/// É}ÉNÉç
/// 
/// ####################################################
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


/// ####################################################
///
/// íËêî
/// 
/// ####################################################
#define WND_CLASS_NAME TEXT("WindowClassName")
#define WND_TITLE TEXT("Invader Game")
constexpr POINT WND_SIZE = { 720, 480 };
constexpr PCTSTR UI_TEXT_TITLE = TEXT("Invader Game");

constexpr PCTSTR UI_TEXT_START = TEXT("Start");
constexpr PCTSTR UI_TEXT_HIGHSCORE = TEXT("High Score");
constexpr PCTSTR UI_TEXT_QUIT = TEXT("Quit");

constexpr POINT PLAYER_INIT_POS = {WND_SIZE.x / 2, WND_SIZE.y - 100};
constexpr int FPS = 60;

constexpr PCTSTR ctStrChara = TEXT("ÉLÉÉÉâ");
constexpr PCTSTR ctStrResult = TEXT("GameOver");


constexpr int STATES_LENGTH = 7;
constexpr int KEYCODES[STATES_LENGTH] = {
	VK_UP,
	VK_DOWN,
	VK_LEFT,
	VK_RIGHT,
	VK_SPACE,
	VK_RETURN,
	VK_ESCAPE
};

enum GameState
{
	STATE_TITLE,
	STATE_GAME,
	STATE_HIGHSCORE,
	STATE_RESULT,
	STATE_QUIT,

	STATE_NUM
};

