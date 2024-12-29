#pragma once
#include <windows.h>
#include "Constants.h"
#include "Timer.h"

/// <summary>
/// キーステートを保持するクラス
/// </summary>
class KeyState
{
private:
	/// <summary>
	/// timer
	/// </summary>
	Timer* timer;

	/// <summary>
	/// 仮想キーコード
	/// </summary>
	int keyCode;
	
	/// <summary>
	/// 押されている間カウントが進む。
	/// </summary>
	int count;

	float tempCount;

	int beforeCount;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="timer">timer</param>
	/// <param name="keyCode">仮想キーコード</param>
	KeyState(Timer* timer, int keyCode);

	/// <summary>
	/// 押下されているかを更新する
	/// </summary>
	void update();

	/// <summary>
	/// 仮想キーコードを取得する
	/// </summary>
	/// <returns>仮想キーコード</returns>
	int getKeyCode();

	/// <summary>
	/// インターバルごとにキーリピートを返す
	/// </summary>
	/// <param name="interval">インターバル（秒）</param>
	/// <returns></returns>
	bool getIsDownRepeat(float interval);

	/// <summary>
	/// 現在のフレームで押されているかを取得する
	/// </summary>
	/// <returns>現在のフレームで押されているか</returns>
	bool getIsDownCurrent();

	/// <summary>
	/// 現在のフレームで押され始めたかどうかを取得する
	/// </summary>
	/// <returns>現在のフレームで押され始めたかどうか</returns>
	bool getIsDownStart();
};


/// <summary>
/// 複数のキーステートを管理するクラス
/// </summary>
class KeyStateManager
{
private:
	/// <summary>
	/// timer
	/// </summary>
	Timer* timer;

	/// <summary>
	/// キーステートの数
	/// </summary>
	int statesLength;

	/// <summary>
	/// 複数のキーステートのポインタ
	/// </summary>
	KeyState** states;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	KeyStateManager(Timer* timer);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~KeyStateManager();

	/// <summary>
	/// すべてのキーステートの更新
	/// </summary>
	void update();

	/// <summary>
	/// 指定された仮想キーコードのキーステートを取得する
	/// </summary>
	/// <param name="keyCode">仮想キーコード</param>
	/// <returns>キーステート</returns>
	KeyState* getKeyState(int keyCode);

};

