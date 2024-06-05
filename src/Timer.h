#pragma once
#include <windows.h>

class Timer
{
private:
	/// <summary>
	/// �Œ�FPS
	/// </summary>
	int fixedFPS;

	/// <summary>
	/// FPS�̎����l
	/// </summary>
	double realFPS;
	
	/// <summary>
	/// CPU���g��
	/// </summary>
	LARGE_INTEGER cpuFreq;

	/// <summary>
	/// �Q�[���N������CPU�J�E���g
	/// </summary>
	LARGE_INTEGER startCount;

	/// <summary>
	/// �O�t���[����CPU�J�E���g
	/// </summary>
	LARGE_INTEGER beforeCount;

	/// <summary>
	/// ���̃t���[��
	/// </summary>
	int nowFrame;
	
	/// <summary>
	/// �������pFPS
	/// </summary>
	int infFPS;

	/// <summary>
	/// ������FPS���g�p���邩�ǂ���
	/// </summary>
	bool isInfFPS;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="fps">�Œ�FPS</param>
	Timer(int fixedFPS);

	/// <summary>
	/// �O�̃t���[�����猻�݉��t���[���o���������擾
	/// </summary>
	/// <returns>�O�̃t���[�����猻�݉��t���[���o������</returns>
	int getDiffFrame();

	/// <summary>
	/// �Œ�FPS���擾
	/// </summary>
	/// <returns>�Œ�FPS</returns>
	int getFixedFPS() const;

	/// <summary>
	/// FPS�̎����l���擾
	/// </summary>
	/// <returns>FPS�̎����l</returns>
	double getRealFPS() const;

	/// <summary>
	/// ���݂̃t���[�����擾
	/// </summary>
	/// <returns></returns>
	int getNowFrame() const;

	/// <summary>
	/// ������������
	/// </summary>
	void UnlockFPS();

	/// <summary>
	/// ��������߂ČŒ�FPS�ɂ���
	/// </summary>
	void LockFPS();
};

