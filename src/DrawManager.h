#pragma once
#include <windows.h>
#include "Constants.h"
#include "Menu.h"
#include "Timer.h"

class DrawManager
{
private:
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
	
	/// <summary>
	/// �e�L�X�g�\������
	/// </summary>
	/// <param name="hdc">�f�o�C�X�R���e�L�X�g</param>
	/// <param name="rect">�E�B���h�E�T�C�Y</param>
	/// <param name="text">�\���������e�L�X�g</param>
	/// <param name="fontSize">�t�H���g�T�C�Y</param>
	/// <param name="fontColor">�t�H���g�J���[</param>
	/// <param name="weight">����</param>
	/// <param name="format">�z�u�t�H�[�}�b�g</param>
	void drawText(HDC hdc, RECT* rect, PCTSTR text, int fontSize, COLORREF fontColor, int weight, UINT format);
	
	/// <summary>
	/// �^�C�g���̕\��
	/// </summary>
	/// <param name="hdc">�f�o�C�X�R���e�L�X�g</param>
	/// <param name="rect">�E�B���h�E�T�C�Y</param>
	void drawTitle(HDC hdc, RECT* rect);

	/// <summary>
	/// ���j���[�A�C�e���̕\��
	/// </summary>
	/// <param name="hdc">�f�o�C�X�R���e�L�X�g</param>
	/// <param name="rect">�E�B���h�E�T�C�Y</param>
	/// <param name="menuItem">���j���[�A�C�e��</param>
	void drawMenuItem(HDC hdc, RECT* rect, MenuItem* menuItem);

	/// <summary>
	/// ���j���[�̕\��
	/// </summary>
	/// <param name="hdc">�f�o�C�X�R���e�L�X�g</param>
	/// <param name="rect">�E�B���h�E�T�C�Y</param>
	/// <param name="menu">���j���[</param>
	void drawMenu(HDC hdc, RECT* rect, Menu* menu);

	/// <summary>
	/// �v���C���[�̕\��
	/// </summary>
	/// <param name="hdc">�f�o�C�X�R���e�L�X�g</param>
	/// <param name="rect">�E�B���h�E�T�C�Y</param>
	/// <param name="pos">�v���C���[�̈ʒu</param>
	void drawPlayer(HDC hdc, RECT* rect, POINT pos);

	/// <summary>
	/// �w�i�̕\��
	/// </summary>
	/// <param name="hdc">�f�o�C�X�R���e�L�X�g</param>
	/// <param name="rect">�E�B���h�E�T�C�Y</param>
	void drawBackground(HDC hdc, RECT* rect);

	/// <summary>
	/// �w�i�̕\��
	/// </summary>
	/// <param name="hdc">�f�o�C�X�R���e�L�X�g</param>
	/// <param name="rect">�E�B���h�E�T�C�Y</param>
	void drawEnemy(HDC hdc, RECT* rect);

	/// <summary>
	/// �e�̕\��
	/// </summary>
	/// <param name="hdc">�f�o�C�X�R���e�L�X�g</param>
	/// <param name="rect">�E�B���h�E�T�C�Y</param>
	void drawShot(HDC hdc, RECT* rect);

	/// <summary>
	/// FPS�l��\��
	/// </summary>
	/// <param name="hdc">�f�o�C�X�R���e�L�X�g</param>
	/// <param name="rect">�E�B���h�E�T�C�Y</param>
	/// <param name="timer">�^�C�}�[</param>
	void drawFPS(HDC hdc, RECT* rect, Timer* timer);

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="hwnd">�E�B���h�E</param>
	/// <param name="hInstance">�C���X�^���X�n���h��</param>
	DrawManager(HWND hwnd, HINSTANCE hInstance);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~DrawManager();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="state"></param>
	/// <param name="menu"></param>
	/// <param name="playerPos"></param>
	/// <param name="timer"></param>
	void paint(GameState state, Menu* menu, POINT playerPos, Timer* timer);
};

