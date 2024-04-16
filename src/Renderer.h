#pragma once
#include <windows.h>
#include "DrawInfoLinkedList.h"
#include "resource.h"
#include "Constants.h"
#include "drawInfos/DrawTextInfo.h"

class Renderer
{
private:
	DrawInfoLinkedList* infoList;

	/// <summary>
	/// ウィンドウ
	/// </summary>
	HWND hwnd;

	/// <summary>
	/// ダブルバッファ用のデバイスコンテキスト フロント側
	/// </summary>
	HDC frontHDC;

	/// <summary>
	/// ダブルバッファ用のデバイスコンテキスト バック側
	/// </summary>
	HDC backHDC;

	/// <summary>
	/// バック側のデバイスコンテキスト用のビットマップ
	/// </summary>
	HBITMAP backBMP;

	/// <summary>
	/// 
	/// </summary>
	HBITMAP oldBMP;

	/// <summary>
	/// インスタンスハンドル
	/// </summary>
	HINSTANCE hInstance;

	int backgroundBitmapID;
public:
	Renderer(HWND hwnd, HINSTANCE hInstance, int backgroundBitmapID);
	~Renderer();
	void SetBackground(int BITMAP_ID);
	void Render();
	void RequestDrawText(const char* text, double x, double y, int fontSize, COLORREF fontColor, int weight);
	void RequestDrawLine();
	void RequestDrawRect();
};

