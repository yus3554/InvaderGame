#include "GameManager.h"
#include "DrawManager.h"
#include "Constants.h"


DrawManager::DrawManager(GameManager* gm, HWND hwnd)
{
	this->gm = gm;
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
	rect->top += DrawTextW(hdc, text, -1, rect, format);
	SelectObject(hdc, hgdi);
	DeleteObject(font);

	RestoreDC(hdc, -1);
}


void DrawManager::drawTitle(HDC hdc, RECT* rect)
{
	this->drawText(
		hdc, rect, UI_TEXT_TITLE, 30, RGB(255, 255, 255),
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
		hdc, rect, menuItem->getMenuItemName(), 20, fontColor, FW_BOLD, DT_CENTER
	);
}


void DrawManager::drawMenu(HDC hdc, RECT* rect)
{
	Menu* menu;

	rect->top += 20;
	menu = this->gm->getMenu();
	for (int menuItemIndex = 0; menuItemIndex < menu->getMenuItemsLength(); menuItemIndex++)
	{
		MenuItem* menuItem = menu->getMenuItems()[menuItemIndex];
		this->drawMenuItem(hdc, rect, menuItem);
	}
}


void DrawManager::paint(HDC hdc)
{
	RECT rect;
	GetClientRect(hwnd, &rect);

	switch (this->gm->getCurrentGameState())
	{
	case STATE_TITLE:
		this->drawTitle(hdc, &rect);
		this->drawMenu(hdc, &rect);
		break;
	case STATE_GAME:
		TextOut(hdc, 100, 100, TEXT("GAME"), lstrlen(TEXT("GAME")));
		break;
	case STATE_HIGHSCORE:
		TextOut(hdc, 100, 100, TEXT("HIGHSCORE"), lstrlen(TEXT("HIGHSCORE")));
		break;
	case STATE_RESULT:
		TextOut(hdc, 100, 100, TEXT("RESULT"), lstrlen(TEXT("RESULT")));
		break;
	default:
		break;
	}
}

void DrawManager::repaint()
{
	InvalidateRect(this->hwnd, NULL, TRUE);
}
