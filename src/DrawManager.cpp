#include <stdio.h>
#include "DrawManager.h"
#include "Menu.h"
#include "Timer.h"
#include "Constants.h"


DrawManager::DrawManager(HWND hwnd)
{
	this->hwnd = hwnd;
}


void DrawManager::drawText(
	HDC hdc, RECT* rect, PCTSTR text, int fontSize, COLORREF fontColor, int weight, UINT format
) {
	HFONT font;
	HGDIOBJ hgdi;

	SaveDC(hdc);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, fontColor);

	font = CreateFontW(
		fontSize, 0,			//高さ, 幅
		0, 0,					//角度1, 角度2
		weight,					//太さ
		FALSE, FALSE, FALSE,	//斜体, 下線, 打消し線
		SHIFTJIS_CHARSET,		//文字セット
		OUT_DEFAULT_PRECIS,		//精度
		CLIP_DEFAULT_PRECIS,	//精度
		DEFAULT_QUALITY,		//品質
		DEFAULT_PITCH | FF_DONTCARE, //ピッチとファミリ
		L"メイリオ");			//フォント名
	hgdi = SelectObject(hdc, font);
	rect->top += DrawText(hdc, text, -1, rect, format);
	SelectObject(hdc, hgdi);
	DeleteObject(font);

	RestoreDC(hdc, -1);
}


void DrawManager::drawTitle(HDC hdc, RECT* rect)
{
	this->drawText(
		hdc, rect, UI_TEXT_TITLE, 50, RGB(255, 255, 255),
		FW_BOLD, DT_CENTER | DT_SINGLELINE | DT_VCENTER
	);
}


void DrawManager::drawMenuItem(HDC hdc, RECT* rect, MenuItem* menuItem)
{
	COLORREF fontColor;
	if (menuItem->getSelected()) {
		fontColor = RGB(255, 0, 0);
	}
	else {
		fontColor = RGB(255, 255, 255);
	}

	this->drawText(
		hdc, rect, menuItem->getMenuItemName(), 30, fontColor, FW_BOLD, DT_CENTER
	);
}


void DrawManager::drawMenu(HDC hdc, RECT* rect, Menu* menu)
{
	rect->top += 20;
	for (int menuItemIndex = 0; menuItemIndex < menu->getMenuItemsLength(); menuItemIndex++)
	{
		MenuItem* menuItem = menu->getMenuItems()[menuItemIndex];
		this->drawMenuItem(hdc, rect, menuItem);
	}
}


void DrawManager::drawBackground(HDC hdc, RECT* rect)
{

}


void DrawManager::drawPlayer(HDC hdc, RECT* rect, POINT pos)
{
	SaveDC(hdc);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, pos.x, pos.y, TEXT("▲"), lstrlen(TEXT("▲")));
	RestoreDC(hdc, -1);
}


void DrawManager::drawEnemy(HDC hdc, RECT* rect)
{

}


void DrawManager::drawShot(HDC hdc, RECT* rect)
{

}


void DrawManager::paint(GameState state, Menu* menu, POINT playerPos, Timer* timer)
{
	RECT rect;
	HDC hdc;
	char fpsStr[10];

	GetClientRect(hwnd, &rect);
	hdc = GetDC(hwnd);

	// 背景塗りつぶし
	SelectObject(hdc, GetStockObject(BLACK_BRUSH));
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

	switch (state)
	{
	case STATE_TITLE:
		this->drawTitle(hdc, &rect);
		this->drawMenu(hdc, &rect, menu);
		break;
	case STATE_GAME:
		this->drawBackground(hdc, &rect);
		this->drawEnemy(hdc, &rect);
		this->drawPlayer(hdc, &rect, playerPos);
		this->drawShot(hdc, &rect);
		break;
	case STATE_HIGHSCORE:
		this->drawText(
			hdc, &rect, TEXT("HIGHSCORE"), 30, RGB(255, 255, 255),
			FW_BOLD, DT_CENTER | DT_SINGLELINE | DT_VCENTER
		);
		this->drawText(
			hdc, &rect, TEXT("Please Enter to Title."), 25, RGB(255, 255, 255),
			FW_BOLD, DT_CENTER | DT_SINGLELINE
		);
		break;
	case STATE_RESULT:
		this->drawText(
			hdc, &rect, TEXT("RESULT"), 30, RGB(255, 255, 255),
			FW_BOLD, DT_CENTER | DT_SINGLELINE | DT_VCENTER
		);
		this->drawText(
			hdc, &rect, TEXT("Please Enter to Title."), 25, RGB(255, 255, 255),
			FW_BOLD, DT_CENTER | DT_SINGLELINE
		);
		break;
	default:
		break;
	}

	snprintf(fpsStr, 10, "%f FPS", timer->getRealFPS());
	TextOut(hdc, 20, 20, (LPCSTR)fpsStr, lstrlen((LPCSTR)fpsStr));

	ReleaseDC(hwnd, hdc);
}

