#pragma once
#include <windows.h>
#include "LinkedList.h"
#include "Constants.h"
#include "drawInfo/DrawInfos.h"
#include "ResourceManager.h"

class Renderer
{
private:
	// �ꎞ�I�ȃ����N�h���X�g�i�������Ɋi�[�j
	LinkedList<DrawInfo>* tempLinkedList;
	// �����_�����O���郊���N�h���X�g�iRender()���ɕ`��j
	LinkedList<DrawInfo>* renderLinkedList;

	ResourceManager* resourceManager;

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
	/// 
	/// </summary>
	BITMAPINFO backBMPInfo;

	/// <summary>
	/// 
	/// </summary>
	LPDWORD backPixelBits;

	/// <summary>
	/// �C���X�^���X�n���h��
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
	void DrawRequestImage(POINTFLOAT pos, ResourceData* resourceData);
};

