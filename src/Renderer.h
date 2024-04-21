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
	/// �E�B���h�E
	/// </summary>
	HWND hwnd;

	/// <summary>
	/// �_�u���o�b�t�@�p�̃f�o�C�X�R���e�L�X�g �t�����g��
	/// </summary>
	HDC frontHDC;

	/// <summary>
	/// �_�u���o�b�t�@�p�̃f�o�C�X�R���e�L�X�g �o�b�N��
	/// </summary>
	HDC backHDC;

	/// <summary>
	/// �o�b�N���̃f�o�C�X�R���e�L�X�g�p�̃r�b�g�}�b�v
	/// </summary>
	HBITMAP backBMP;

	/// <summary>
	/// 
	/// </summary>
	HBITMAP oldBMP;

	/// <summary>
	/// �C���X�^���X�n���h��
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

