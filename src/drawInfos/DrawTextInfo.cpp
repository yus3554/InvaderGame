#include "DrawTextInfo.h"

DrawTextInfo::DrawTextInfo(const char* text, double x, double y, int fontSize, COLORREF fontColor, int weight)
{
	this->text = TEXT(text);
	this->x = x;
	this->y = y;
	this->fontSize = fontSize;
	this->fontColor = fontColor;
	this->weight = weight;
}

void DrawTextInfo::render(HDC hdc)
{
	HFONT font;
	HGDIOBJ hgdi;

	SaveDC(hdc);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, fontColor);
	SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
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
	TextOut(hdc, this->x, this->y, this->text, lstrlen(this->text));
	SelectObject(hdc, hgdi);
	DeleteObject(font);

	RestoreDC(hdc, -1);
}

