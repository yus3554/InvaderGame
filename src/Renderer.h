#pragma once
#include <windows.h>
#include "LinkedList.h"
#include "resource.h"
#include "Constants.h"
#include "drawInfo/DrawInfos.h"

class Renderer
{
private:
	LinkedList<DrawInfo>* linkedList;
	// LinkedList<DrawInfo>* renderLinkedList;

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
	// void CopyInfos();
	void DrawRequestText(const char* text, POINTFLOAT pos, int fontSize, COLORREF fontColor, int weight);
	void DrawRequestLine();
	void DrawRequestRect(POINTFLOAT pos, int width, int height, COLORREF backgroundColor, COLORREF borderColor, int borderWidth);
};

