#if !defined(MYLIB_CONSTANTS_H)
#define MYLIB_CONSTANTS_H 1
#include <windows.h>



#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)


#define WND_CLASS_NAME TEXT("WindowClassName")
#define WND_TITLE TEXT("Invader Game")
constexpr POINT WND_SIZE = { 720, 480 };
constexpr PCTSTR UI_TEXT_TITLE = TEXT("Invader Game");

constexpr PCTSTR UI_TEXT_START = TEXT("Start");
constexpr PCTSTR UI_TEXT_HIGHSCORE = TEXT("High Score");
constexpr PCTSTR UI_TEXT_QUIT = TEXT("Quit");

constexpr POINT PLAYER_INIT_POS = {WND_SIZE.x / 2, WND_SIZE.y - 100};

constexpr PCTSTR ctStrChara = TEXT("ƒLƒƒƒ‰");
constexpr PCTSTR ctStrResult = TEXT("GameOver");

#endif
