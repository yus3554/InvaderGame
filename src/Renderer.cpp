#include "Renderer.h"

Renderer::Renderer(HWND hwnd, HINSTANCE hInstance, int backgroundBitmapID)
{
	this->backgroundBitmapID = backgroundBitmapID;
	// infoListの初期化
	this->linkedList = new LinkedList<DrawInfo>();

	this->hwnd = hwnd;
	this->hInstance = hInstance;

	// ダブルバッファ設定
	this->frontHDC = GetDC(hwnd);
	this->backHDC = CreateCompatibleDC(this->frontHDC);
	// this->backBMP = CreateCompatibleBitmap(this->frontHDC, WND_SIZE.x, WND_SIZE.y);
	this->backBMP = LoadBitmap(hInstance, MAKEINTRESOURCE(this->backgroundBitmapID));
	this->oldBMP = (HBITMAP)SelectObject(this->backHDC, this->backBMP);
}

Renderer::~Renderer()
{
	// infoListの削除
	delete this->linkedList;

	// ダブルバッファの削除
	SelectObject(this->backHDC, this->oldBMP);
	DeleteObject(this->backBMP);
	DeleteDC(this->backHDC);
	ReleaseDC(this->hwnd, this->frontHDC);

	// 設定を戻す
	ChangeDisplaySettings(NULL, NULL);
}

void Renderer::Render()
{
	// background
	this->backBMP = LoadBitmap(this->hInstance, MAKEINTRESOURCE(this->backgroundBitmapID));
	this->oldBMP = (HBITMAP)SelectObject(this->backHDC, this->backBMP);

	// drawinfoを描画
	for (int i = 0; i < this->linkedList->getLength(); i++)
	{
		DrawInfo* info = this->linkedList->pop();
		info->render(this->backHDC);
		delete info;
	}

	// ダブルバッファのバック側のHDCをフロント側に転送
	BitBlt(this->frontHDC, 0, 0, WND_SIZE.x, WND_SIZE.y, this->backHDC, 0, 0, SRCCOPY);
}

void Renderer::SetBackground(int backgroundBitmapID)
{
	this->backgroundBitmapID = backgroundBitmapID;
}

void Renderer::DrawRequestText(const char* text, POINT pos, int fontSize, COLORREF fontColor, int weight)
{
	DrawTextInfo* info = new DrawTextInfo(text, pos, fontSize, fontColor, weight);
	this->linkedList->add(info);
}


void Renderer::DrawRequestLine()
{
	// auto info = new DrawLineInfo();
	// this->linkedList->add(info);
}

void Renderer::DrawRequestRect(
	POINT pos, int width, int height, COLORREF backgroundColor, COLORREF borderColor, int borderWidth)
{
	auto info = new DrawRectInfo(pos, width, height, backgroundColor, borderColor, borderWidth);
	this->linkedList->add(info);
}
