#include "Renderer.h"

Renderer::Renderer(HWND hwnd, HINSTANCE hInstance, int backgroundBitmapID)
{
	this->backgroundBitmapID = backgroundBitmapID;
	// infoListの初期化
	this->infoList = new DrawInfoLinkedList();

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
	delete this->infoList;

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
	for (int i = 0; i < this->infoList->getLength(); i++)
	{
		DrawInfo* info = this->infoList->pop();
		info->render(this->backHDC);
		delete info;
	}

	// ダブルバッファのバック側のHDCをフロント側に転送
	BitBlt(this->frontHDC, 0, 0, WND_SIZE.x, WND_SIZE.y, this->backHDC, 0, 0, SRCCOPY);
}

void Renderer::RequestDrawText(const char* text, double x, double y, int fontSize, COLORREF fontColor, int weight)
{
	DrawTextInfo* info = new DrawTextInfo(text, x, y, fontSize, fontColor, weight);
	this->infoList->add(info);
}

void Renderer::SetBackground(int backgroundBitmapID)
{
	this->backgroundBitmapID = backgroundBitmapID;
}

void Renderer::RequestDrawLine()
{
	// auto info = new DrawLineInfo();
	// this->infoList->add(info);
}

void Renderer::RequestDrawRect()
{
	// auto info = new DrawRectInfo();
	// this->infoList->add(info);
}
