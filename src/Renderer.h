#pragma once
#include <windows.h>
#include "LinkedList.h"
#include "Constants.h"
#include "drawInfo/DrawInfos.h"
#include "ResourceManager.h"

class Renderer
{
private:
	// 一時的なリンクドリスト（処理時に格納）
	LinkedList<DrawInfo>* tempLinkedList;
	// レンダリングするリンクドリスト（Render()時に描画）
	LinkedList<DrawInfo>* renderLinkedList;

	ResourceManager* resourceManager;

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
	/// 
	/// </summary>
	BITMAPINFO backBMPInfo;

	/// <summary>
	/// 
	/// </summary>
	LPDWORD backPixelBits;

	/// <summary>
	/// インスタンスハンドル
	/// </summary>
	HINSTANCE hInstance;

public:
	Renderer(HWND hwnd, HINSTANCE hInstance, ResourceManager* resourceManager);
	~Renderer();
	void Render();
	void CopyInfos();
	void DrawRequestText(const char* text, POINTFLOAT pos, int fontSize, COLORREF fontColor, int weight);
	void DrawRequestLine();
	void DrawRequestRect(POINTFLOAT pos, int width, int height, COLORREF backgroundColor, COLORREF borderColor, int borderWidth);
	void DrawRequestImage(POINTFLOAT pos, ResourceData* resourceData, int pixelOffset);
};

