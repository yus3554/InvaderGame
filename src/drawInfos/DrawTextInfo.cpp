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
	TextOut(hdc, this->x, this->y, this->text, lstrlen(this->text));
	SelectObject(hdc, hgdi);
	DeleteObject(font);

	RestoreDC(hdc, -1);
}

