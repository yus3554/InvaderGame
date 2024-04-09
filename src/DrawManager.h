#pragma once
#include <windows.h>
#include "Constants.h"
#include "Menu.h"
#include "Timer.h"

class DrawManager
{
private:
	HWND hwnd;
	void drawText(HDC hdc, RECT* rect, PCTSTR text, int fontSize, COLORREF fontColor, int weight, UINT format);
	void drawTitle(HDC hdc, RECT* rect);
	void drawMenuItem(HDC hdc, RECT* rect, MenuItem* menuItem);
	void drawMenu(HDC hdc, RECT* rect, Menu* menu);
	void drawPlayer(HDC hdc, RECT* rect, POINT pos);
	void drawBackground(HDC hdc, RECT* rect);
	void drawEnemy(HDC hdc, RECT* rect);
	void drawShot(HDC hdc, RECT* rect);
public:
	DrawManager(HWND hwnd);
	void paint(GameState state, Menu* menu, POINT playerPos, Timer* timer);
	void repaint();
};

