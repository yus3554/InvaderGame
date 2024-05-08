#include "Renderer.h"

Renderer::Renderer(HWND hwnd, HINSTANCE hInstance, ResourceManager* resourceManager)
{
	// infoList�̏�����
	this->tempLinkedList = new LinkedList<DrawInfo>();
	this->renderLinkedList = new LinkedList<DrawInfo>();

	this->hwnd = hwnd;
	this->hInstance = hInstance;

	this->resourceManager = resourceManager;

	// �_�u���o�b�t�@�ݒ�
	this->frontHDC = GetDC(hwnd);
	this->backHDC = CreateCompatibleDC(this->frontHDC);

	// �E�B���h�E�T�C�Y�ŕ`��pBMP�̗p��
	this->backBMPInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	this->backBMPInfo.bmiHeader.biWidth = WND_SIZE.x;
	this->backBMPInfo.bmiHeader.biHeight = -WND_SIZE.y;
	this->backBMPInfo.bmiHeader.biPlanes = 1;
	this->backBMPInfo.bmiHeader.biBitCount = 32;
	this->backBMPInfo.bmiHeader.biCompression = BI_RGB;

	this->backBMP = CreateDIBSection(this->backHDC, &this->backBMPInfo, DIB_RGB_COLORS, (void**)&this->backPixelBits, NULL, 0);
	if (this->backBMP == NULL)
		throw "backBMP��NULL�ł��B";
	this->oldBMP = (HBITMAP)SelectObject(this->backHDC, this->backBMP);

	// �摜�ǂݍ���
	this->resourceManager->Load(RESOURCE_BACKGROUND, 0);
	this->resourceManager->Load(RESOURCE_PLAYER, 0);
	this->resourceManager->Load(RESOURCE_ENEMY, 0);
	this->resourceManager->Load(RESOURCE_SHOT, 0);
	this->resourceManager->Load(RESOURCE_SHOT, 1);
}

Renderer::~Renderer()
{
	// infoList�̍폜
	delete this->tempLinkedList;
	delete this->renderLinkedList;

	// �_�u���o�b�t�@�̍폜
	SelectObject(this->backHDC, this->oldBMP);
	DeleteObject(this->backBMP);
	DeleteDC(this->backHDC);
	ReleaseDC(this->hwnd, this->frontHDC);

	// �ݒ��߂�
	ChangeDisplaySettings(NULL, NULL);
}

void Renderer::Render()
{
	// drawinfo��`��
	for (int i = 0; i < this->renderLinkedList->getLength(); i++)
	{
		DrawInfo* info = this->renderLinkedList->pop();
		info->render(this->backHDC);
		delete info;
		i--;
	}

	// �`��pBMP��backHDC�ɕt�^���ABitBlt��frontHDC�ɓ]��
	this->oldBMP = (HBITMAP)SelectObject(this->backHDC, this->backBMP);
	BitBlt(this->frontHDC, 0, 0, WND_SIZE.x, WND_SIZE.y, this->backHDC, 0, 0, SRCCOPY);
}

void Renderer::CopyInfos()
{
	// tempLinkdList����renderLinkedList�ɒ��g���R�s�[���AtempLinkedList�����Z�b�g����B
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

void Renderer::DrawRequestImage(POINTFLOAT pos, ResourceData* resourceData, int pixelOffset)
{
	POINT posLONG = { (LONG)pos.x, (LONG)pos.y };
	auto info = new DrawImageInfo(posLONG, resourceData, this->backPixelBits, pixelOffset);
	this->tempLinkedList->add(info);
}
