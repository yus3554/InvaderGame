#include "Renderer.h"

Renderer::Renderer(HWND hwnd, HINSTANCE hInstance, ResourceManager* resourceManager)
{
	this->drawInfoListIndex = 0;

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
	this->resourceManager->LoadRequest(RESOURCE_BACKGROUND, 0);

	this->resourceManager->Load();
}

Renderer::~Renderer()
{
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
	for (int i = 0; i < this->drawInfoList[!this->drawInfoListIndex].getLength(); i++)
	{
		DrawInfo* info = this->drawInfoList[!this->drawInfoListIndex].pop();
		info->render(this->backHDC);
		delete info;
		i--;
	}

	// �`��pBMP��backHDC�ɕt�^���ABitBlt��frontHDC�ɓ]��
	this->oldBMP = (HBITMAP)SelectObject(this->backHDC, this->backBMP);
	BitBlt(this->frontHDC, 0, 0, WND_SIZE.x, WND_SIZE.y, this->backHDC, 0, 0, SRCCOPY);
}

/// <summary>
/// �����_�[�p��DrawRequest�p�Ƃ�Index��؂�ւ���
/// </summary>
void Renderer::SwitchDrawInfoList()
{
	this->drawInfoListIndex = !this->drawInfoListIndex;
}


/// <summary>
/// �e�L�X�g�`������N�G�X�g����B
/// </summary>
/// <param name="text">�\���������e�L�X�g</param>
/// <param name="pos">�\���������ʒu</param>
/// <param name="fontSize">�t�H���g�T�C�Y</param>
/// <param name="fontColor">�t�H���g�J���[</param>
/// <param name="weight">����</param>
void Renderer::DrawRequestText(const char* text, POINTFLOAT pos, int fontSize, COLORREF fontColor, int weight)
{
	POINT posLONG = { (LONG)pos.x, (LONG)pos.y };
	DrawTextInfo* info = new DrawTextInfo(text, posLONG, fontSize, fontColor, weight);
	this->drawInfoList[this->drawInfoListIndex].add(info);
}


void Renderer::DrawRequestLine()
{
	// auto info = new DrawLineInfo();
	// this->tempLinkedList->add(info);
}

/// <summary>
/// �����`�`������N�G�X�g����B
/// </summary>
/// <param name="pos"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="backgroundColor"></param>
/// <param name="borderColor"></param>
/// <param name="borderWidth"></param>
void Renderer::DrawRequestRect(
	POINTFLOAT pos, int width, int height, COLORREF backgroundColor, COLORREF borderColor, int borderWidth)
{
	POINT posLONG = { (LONG)pos.x, (LONG)pos.y };
	auto info = new DrawRectInfo(posLONG, width, height, backgroundColor, borderColor, borderWidth);
	this->drawInfoList[this->drawInfoListIndex].add(info);
}

/// <summary>
/// �摜�`������N�G�X�g����B
/// </summary>
/// <param name="pos"></param>
/// <param name="resourceData"></param>
/// <param name="pixelOffset"></param>
void Renderer::DrawRequestImage(POINTFLOAT pos, ResourceData* resourceData, int pixelOffset)
{
	POINT posLONG = { (LONG)pos.x, (LONG)pos.y };
	auto info = new DrawImageInfo(posLONG, resourceData, this->backPixelBits, pixelOffset);
	this->drawInfoList[this->drawInfoListIndex].add(info);
}
