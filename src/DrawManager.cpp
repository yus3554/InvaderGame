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
		fontSize, 0,			//����, ��
		0, 0,					//�p�x1, �p�x2
		weight,					//����
		FALSE, FALSE, FALSE,	//�Α�, ����, �ŏ�����
		SHIFTJIS_CHARSET,		//�����Z�b�g
		OUT_DEFAULT_PRECIS,		//���x
		CLIP_DEFAULT_PRECIS,	//���x
		DEFAULT_QUALITY,		//�i��
		DEFAULT_PITCH | FF_DONTCARE, //�s�b�`�ƃt�@�~��
		L"���C���I");			//�t�H���g��
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


void DrawManager::drawBackground(HDC hdc, RECT* rect)
{

}


void DrawManager::drawPlayer(HDC hdc, RECT* rect)
{
	SaveDC(hdc);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, this->gm->getPlayerPos().x, this->gm->getPlayerPos().y, TEXT("��"), lstrlen(TEXT("��")));
	RestoreDC(hdc, -1);
}


void DrawManager::drawEnemy(HDC hdc, RECT* rect)
{

}


void DrawManager::drawShot(HDC hdc, RECT* rect)
{

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
		this->drawBackground(hdc, &rect);
		this->drawEnemy(hdc, &rect);
		this->drawPlayer(hdc, &rect);
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
}

void DrawManager::repaint()
{
	InvalidateRect(this->hwnd, NULL, TRUE);
}
