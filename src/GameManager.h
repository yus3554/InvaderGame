#pragma once
#include <windows.h>
#include <stdio.h>
#include "MenuManager.h"
#include "Timer.h"
#include "DrawManager.h"
#include "KeyStateManager.h"
#include "Constants.h"

class GameManager
{
private:
	/// <summary>
	/// ���j���[�}�l�[�W���[
	/// </summary>
	MenuManager* mm;

	/// <summary>
	/// �^�C�}�[
	/// </summary>
	Timer* timer;

	/// <summary>
	/// �`��}�l�[�W���[
	/// </summary>
	DrawManager* dm;

	/// <summary>
	/// �L�[���̓}�l�[�W���[
	/// </summary>
	KeyStateManager* km;

	/// <summary>
	/// �E�B���h�E
	/// </summary>
	HWND hwnd;

	/// <summary>
	/// �C���X�^���X�n���h��
	/// </summary>
	HINSTANCE hInstance;

	/// <summary>
	/// ���݂̃Q�[���X�e�[�g
	/// </summary>
	GameState currentGameState;

	/// <summary>
	/// �X�R�A
	/// </summary>
	int score;

	/// <summary>
	/// �v���C���[�̈ʒu
	/// </summary>
	POINT playerPos;  // TODO: �L�����N�^�[�̏ꏊ�́A�����炭GM������Ȃ��ăL�����N�^�N���X���ɏ����ׂ�

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="hwnd">�E�B���h�E</param>
	/// <param name="hInstance">�C���X�^���X�n���h��</param>
	GameManager(HWND hwnd, HINSTANCE hInstance);

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameManager();

	/// <summary>
	/// �Q�[���̏�����
	/// </summary>
	void GameInit();

	/// <summary>
	/// �Q�[���̃��C������
	/// </summary>
	void GameUpdate();

	/// <summary>
	/// �Q�[���I�����̏���
	/// </summary>
	void GameQuit();

	/// <summary>
	/// ���݂̃Q�[���X�e�[�g���擾
	/// </summary>
	/// <returns>���݂̃Q�[���X�e�[�g</returns>
	GameState getCurrentGameState();

	/// <summary>
	/// ���݂̃Q�[���X�e�[�g��ݒ�
	/// </summary>
	/// <param name="state">�Q�[���X�e�[�g</param>
	void setCurrentGameState(GameState state);

	/// <summary>
	/// �v���C���[�̈ʒu���擾
	/// </summary>
	/// <returns>�v���C���[�̈ʒu</returns>
	POINT getPlayerPos();

	/// <summary>
	/// �v���C���[�̈ʒu��ݒ�
	/// </summary>
	/// <param name="pos">�v���C���[�̈ʒu</param>
	void setPlayerPos(POINT pos);

	/// <summary>
	/// ���j���[�}�l�[�W���[�̎擾
	/// </summary>
	/// <returns> ���j���[ </returns>
	MenuManager* getMenuManager();

	/// <summary>
	/// �L�[�������̏���
	/// </summary>
	void keyPress();
};

