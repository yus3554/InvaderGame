#include <stdio.h>
#include "DrawManager.h"
#include "Menu.h"
#include "Timer.h"
#include "Constants.h"
#include "resource.h"


DrawManager::DrawManager(HWND hwnd, HINSTANCE hInstance)
{
	this->hwnd = hwnd;
	this->hInstance = hInstance;

	// �_�u���o�b�t�@�ݒ�
	this->frontHDC = GetDC(hwnd);
	this->backHDC = CreateCompatibleDC(this->frontHDC);
	// this->backBMP = CreateCompatibleBitmap(this->frontHDC, WND_SIZE.x, WND_SIZE.y);
	// this->backBMP = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	// this->oldBMP = (HBITMAP)SelectObject(this->backHDC, this->backBMP);
}


DrawManager::~DrawManager()
{
	// �_�u���o�b�t�@�̍폜
	SelectObject(this->backHDC, this->oldBMP);
	DeleteObject(this->backBMP);
	DeleteDC(this->backHDC);
	ReleaseDC(this->hwnd, this->frontHDC);

	// �ݒ��߂�
	ChangeDisplaySettings(NULL, NULL);
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
	this->backBMP = LoadBitmap(this->hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
	this->oldBMP = (HBITMAP)SelectObject(this->backHDC, this->backBMP);
}


void DrawManager::drawPlayer(HDC hdc, RECT* rect, POINT pos)
{
	SaveDC(hdc);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, pos.x, pos.y, TEXT("��"), lstrlen(TEXT("��")));
	RestoreDC(hdc, -1);
}


void DrawManager::drawEnemy(HDC hdc, RECT* rect)
{

}


void DrawManager::drawShot(HDC hdc, RECT* rect)
{

}

void DrawManager::drawFPS(HDC hdc, RECT* rect, Timer* timer)
{
	// FPS�\���p
	char fpsStr[20];
	snprintf(fpsStr, 20, "%3.3f FPS", timer->getRealFPS());
	TextOut(this->backHDC, 0, 0, (LPCSTR)fpsStr, lstrlen((LPCSTR)fpsStr));
}


void DrawManager::paint(GameState state, Menu* menu, POINT playerPos, Timer* timer)
{
	// �E�B���h�E�T�C�Y
	RECT rect = {0, 0, WND_SIZE.x, WND_SIZE.y};

	// �w�i
	this->drawBackground(this->backHDC, &rect);

	switch (state)
	{
	case STATE_TITLE:  // �^�C�g�����
		this->drawTitle(this->backHDC, &rect);
		this->drawMenu(this->backHDC, &rect, menu);
		break;

	case STATE_GAME:  // �Q�[�����
		this->drawEnemy(this->backHDC, &rect);
		this->drawPlayer(this->backHDC, &rect, playerPos);
		this->drawShot(this->backHDC, &rect);
		break;

	case STATE_HIGHSCORE:  //�n�C�X�R�A���
		this->drawText(
			this->backHDC, &rect, TEXT("HIGHSCORE"), 30, RGB(255, 255, 255),
			FW_BOLD, DT_CENTER | DT_SINGLELINE | DT_VCENTER
		);
		this->drawText(
			this->backHDC, &rect, TEXT("Please Enter to Title."), 25, RGB(255, 255, 255),
			FW_BOLD, DT_CENTER | DT_SINGLELINE
		);
		break;

	case STATE_RESULT:  // ���U���g���
		this->drawText(
			this->backHDC, &rect, TEXT("RESULT"), 30, RGB(255, 255, 255),
			FW_BOLD, DT_CENTER | DT_SINGLELINE | DT_VCENTER
		);
		this->drawText(
			this->backHDC, &rect, TEXT("Please Enter to Title."), 25, RGB(255, 255, 255),
			FW_BOLD, DT_CENTER | DT_SINGLELINE
		);
		break;

	default:
		break;
	}

	// fps�\��
	this->drawFPS(this->backHDC, &rect, timer);

	// �_�u���o�b�t�@�̃o�b�N����HDC���t�����g���ɓ]��
	BitBlt(this->frontHDC, 0, 0, WND_SIZE.x, WND_SIZE.y, this->backHDC, 0, 0, SRCCOPY);
}

