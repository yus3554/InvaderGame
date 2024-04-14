#pragma once
#include <windows.h>

class Timer
{
private:
	/// <summary>
	/// 目標とするFPS
	/// </summary>
	int targetFPS;

	/// <summary>
	/// FPSの実測値
	/// </summary>
	double realFPS;
	
	/// <summary>
	/// CPU周波数
	/// </summary>
	LARGE_INTEGER cpuFreq;

	/// <summary>
	/// ゲーム起動時のCPUカウント
	/// </summary>
	LARGE_INTEGER startCount;

	/// <summary>
	/// 前フレームのCPUカウント
	/// </summary>
	LARGE_INTEGER beforeCount;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="fps">目標とするFPS</param>
	Timer(int fps);

	/// <summary>
	/// 前のフレームから現在何フレーム経ったかを取得
	/// </summary>
	/// <returns>前のフレームから現在何フレーム経ったか</returns>
	int getDiffFrame();

	/// <summary>
	/// 目標とするFPSを取得
	/// </summary>
	/// <returns>目標とするFPS</returns>
	int getTargetFPS();

	/// <summary>
	/// FPSの実測値を取得
	/// </summary>
	/// <returns>FPSの実測値</returns>
	double getRealFPS();
};

