#pragma once
#include <windows.h>
#include "GameManager.h"

class DrawManager
{
private:
	GameManager* gm;
	HWND hwnd;
	void drawText(HDC hdc, RECT* rect, PCTSTR text, int fontSize, COLORREF fontColor, int weight, UINT format);
	void drawTitle(HDC hdc, RECT* rect);
	void drawMenuItem(HDC hdc, RECT* rect, MenuItem* menuItem);
	void drawMenu(HDC hdc, RECT* rect);
	void drawPlayer(HDC hdc, RECT* rect);
	void drawBackground(HDC hdc, RECT* rect);
	void drawEnemy(HDC hdc, RECT* rect);
	void drawShot(HDC hdc, RECT* rect);
public:
	DrawManager(GameManager* gm, HWND hwnd);
	void paint(HDC hdc);
	void repaint();
};

