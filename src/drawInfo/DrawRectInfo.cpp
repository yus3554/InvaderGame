#include "DrawRectInfo.h"

DrawRectInfo::DrawRectInfo(
	POINT pos, int width, int height, COLORREF backgroundColor, COLORREF borderColor, int borderWidth)
{
	this->pos = pos;
	this->backgroundColor = backgroundColor;
	this->borderColor = borderColor;
	this->borderWidth = borderWidth;

	this->rect.left = pos.x - (LONG)(width / 2.0);
	this->rect.top = pos.y - (LONG)(height / 2.0);
	this->rect.right = pos.x + (LONG)(width / 2.0);
	this->rect.bottom = pos.y + (LONG)(height / 2.0);
}

void DrawRectInfo::render(HDC hdc)
{
	SaveDC(hdc);

	// border�ݒ�
	HPEN hpen = CreatePen(PS_SOLID, this->borderWidth, this->borderColor);
	SelectObject(hdc, hpen);
	// background color�ݒ�
	HBRUSH hbrush = CreateSolidBrush(this->backgroundColor);
	SelectObject(hdc, hbrush);

	// �`��
	Rectangle(hdc, this->rect.left, this->rect.top, this->rect.right, this->rect.bottom);

	// �I�u�W�F�N�g�폜
	DeleteObject(hpen);
	DeleteObject(hbrush);

	RestoreDC(hdc, -1);
}

