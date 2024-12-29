#pragma once
#include <windows.h>

class Timer
{
private:
	/// <summary>
	/// 固定FPS
	/// </summary>
	int fixedFPS;

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

	/// <summary>
	/// 今のフレーム
	/// </summary>
	int nowFrame;
	
	/// <summary>
	/// 上限解放用FPS
	/// </summary>
	int infFPS;

	/// <summary>
	/// 上限解放FPSを使用するかどうか
	/// </summary>
	bool isInfFPS;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="fps">固定FPS</param>
	Timer(int fixedFPS);

	/// <summary>
	/// 前のフレームから現在何フレーム経ったかを取得
	/// </summary>
	/// <returns>前のフレームから現在何フレーム経ったか</returns>
	int getDiffFrame();

	/// <summary>
	/// 固定FPSを取得
	/// </summary>
	/// <returns>固定FPS</returns>
	int getFixedFPS() const;

	/// <summary>
	/// FPSの実測値を取得
	/// </summary>
	/// <returns>FPSの実測値</returns>
	double getRealFPS() const;

	LARGE_INTEGER getCPUFreq() const;

	LARGE_INTEGER getNowCount() const;

	/// <summary>
	/// 現在のフレームを取得
	/// </summary>
	/// <returns></returns>
	int getNowFrame() const;

	/// <summary>
	/// 上限解放させる
	/// </summary>
	void UnlockFPS();

	/// <summary>
	/// 上限解放やめて固定FPSにする
	/// </summary>
	void LockFPS();

	/// <summary>
	/// BeforeCountを現在のカウントにリセットする。
	/// </summary>
	void ResetBeforeCount();
};

