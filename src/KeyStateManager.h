#pragma once
#include <windows.h>
#include "Constants.h"

/// <summary>
/// �L�[�X�e�[�g��ێ�����N���X
/// </summary>
class KeyState
{
private:
	/// <summary>
	/// ���z�L�[�R�[�h
	/// </summary>
	int keyCode;
	
	/// <summary>
	/// ���݂̃t���[���ŉ�����Ă��邩�ǂ���
	/// </summary>
	bool isDownCurrent;

	/// <summary>
	/// �O�t���[���ŉ�����Ă������ǂ���
	/// </summary>
	bool isDownBefore;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="keyCode">���z�L�[�R�[�h</param>
	KeyState(int keyCode);

	/// <summary>
	/// ��������Ă��邩���X�V����
	/// </summary>
	void update();

	/// <summary>
	/// ���z�L�[�R�[�h���擾����
	/// </summary>
	/// <returns>���z�L�[�R�[�h</returns>
	int getKeyCode();

	/// <summary>
	/// ���݂̃t���[���ŉ�����Ă��邩���擾����
	/// </summary>
	/// <returns>���݂̃t���[���ŉ�����Ă��邩</returns>
	bool getIsDownCurrent();

	/// <summary>
	/// ���݂̃t���[���ŉ�����n�߂����ǂ������擾����
	/// </summary>
	/// <returns>���݂̃t���[���ŉ�����n�߂����ǂ���</returns>
	bool getIsDownStart();
};


/// <summary>
/// �����̃L�[�X�e�[�g���Ǘ�����N���X
/// </summary>
class KeyStateManager
{
private:
	/// <summary>
	/// �L�[�X�e�[�g�̐�
	/// </summary>
	int statesLength;

	/// <summary>
	/// �����̃L�[�X�e�[�g�̃|�C���^
	/// </summary>
	KeyState** states;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	KeyStateManager();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~KeyStateManager();

	/// <summary>
	/// ���ׂẴL�[�X�e�[�g�̍X�V
	/// </summary>
	void update();

	/// <summary>
	/// �w�肳�ꂽ���z�L�[�R�[�h�̃L�[�X�e�[�g���擾����
	/// </summary>
	/// <param name="keyCode">���z�L�[�R�[�h</param>
	/// <returns>�L�[�X�e�[�g</returns>
	KeyState* getKeyState(int keyCode);

};

