#pragma once
#include <windows.h>

class Timer
{
private:
	/// <summary>
	/// �ڕW�Ƃ���FPS
	/// </summary>
	int targetFPS;

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

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="fps">�ڕW�Ƃ���FPS</param>
	Timer(int fps);

	/// <summary>
	/// �O�̃t���[�����猻�݉��t���[���o���������擾
	/// </summary>
	/// <returns>�O�̃t���[�����猻�݉��t���[���o������</returns>
	int getDiffFrame();

	/// <summary>
	/// �ڕW�Ƃ���FPS���擾
	/// </summary>
	/// <returns>�ڕW�Ƃ���FPS</returns>
	int getTargetFPS();

	/// <summary>
	/// FPS�̎����l���擾
	/// </summary>
	/// <returns>FPS�̎����l</returns>
	double getRealFPS();
};

