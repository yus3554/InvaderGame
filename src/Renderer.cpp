#include "Renderer.h"

Renderer::Renderer(HWND hwnd, HINSTANCE hInstance, ResourceManager* resourceManager)
{
	// infoListの初期化
	this->tempLinkedList = new LinkedList<DrawInfo>();
	this->renderLinkedList = new LinkedList<DrawInfo>();

	this->hwnd = hwnd;
	this->hInstance = hInstance;

	this->resourceManager = resourceManager;

	// ダブルバッファ設定
	this->frontHDC = GetDC(hwnd);
	this->backHDC = CreateCompatibleDC(this->frontHDC);

	// ウィンドウサイズで描画用BMPの用意
	this->backBMPInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	this->backBMPInfo.bmiHeader.biWidth = WND_SIZE.x;
	this->backBMPInfo.bmiHeader.biHeight = -WND_SIZE.y;
	this->backBMPInfo.bmiHeader.biPlanes = 1;
	this->backBMPInfo.bmiHeader.biBitCount = 32;
	this->backBMPInfo.bmiHeader.biCompression = BI_RGB;

	this->backBMP = CreateDIBSection(this->backHDC, &this->backBMPInfo, DIB_RGB_COLORS, (void**)&this->backPixelBits, NULL, 0);
	if (this->backBMP == NULL)
		throw "backBMPがNULLです。";
	this->oldBMP = (HBITMAP)SelectObject(this->backHDC, this->backBMP);

	// 画像読み込み
	this->resourceManager->Load(RESOURCE_BACKGROUND, 0);
	this->resourceManager->Load(RESOURCE_PLAYER, 0);
	this->resourceManager->Load(RESOURCE_ENEMY, 0);
	this->resourceManager->Load(RESOURCE_SHOT, 0);
	this->resourceManager->Load(RESOURCE_SHOT, 1);
}

Renderer::~Renderer()
{
	// infoListの削除
	delete this->tempLinkedList;
	delete this->renderLinkedList;

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
	// drawinfoを描画
	for (int i = 0; i < this->renderLinkedList->getLength(); i++)
	{
		DrawInfo* info = this->renderLinkedList->pop();
		info->render(this->backHDC);
		delete info;
		i--;
	}

	// 描画用BMPをbackHDCに付与し、BitBltでfrontHDCに転送
	this->oldBMP = (HBITMAP)SelectObject(this->backHDC, this->backBMP);
	BitBlt(this->frontHDC, 0, 0, WND_SIZE.x, WND_SIZE.y, this->backHDC, 0, 0, SRCCOPY);
}

void Renderer::CopyInfos()
{
	// tempLinkdListからrenderLinkedListに中身をコピーし、tempLinkedListをリセットする。
	this->renderLinkedList->clear();
	Node<DrawInfo>* head = this->tempLinkedList->getHead();
	int length = this->tempLinkedList->getLength();
	this->renderLinkedList->Substitute(head, length);
	this->tempLinkedList->Substitute(NULL, 0);
}

void Renderer::DrawRequestText(const char* text, POINTFLOAT pos, int fontSize, COLORREF fontColor, int weight)
{
	POINT posLONG = { (LONG)pos.x, (LONG)pos.y };
	DrawTextInfo* info = new DrawTextInfo(text, posLONG, fontSize, fontColor, weight);
	this->tempLinkedList->add(info);
}


void Renderer::DrawRequestLine()
{
	// auto info = new DrawLineInfo();
	// this->tempLinkedList->add(info);
}

void Renderer::DrawRequestRect(
	POINTFLOAT pos, int width, int height, COLORREF backgroundColor, COLORREF borderColor, int borderWidth)
{
	POINT posLONG = { (LONG)pos.x, (LONG)pos.y };
	auto info = new DrawRectInfo(posLONG, width, height, backgroundColor, borderColor, borderWidth);
	this->tempLinkedList->add(info);
}

void Renderer::DrawRequestImage(POINTFLOAT pos, ResourceData* resourceData)
{
	POINT posLONG = { (LONG)pos.x, (LONG)pos.y };
	auto info = new DrawImageInfo(posLONG, resourceData, this->backPixelBits);
	this->tempLinkedList->add(info);
}
