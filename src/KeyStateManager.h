#pragma once
#include <windows.h>
#include "Constants.h"

/// <summary>
/// キーステートを保持するクラス
/// </summary>
class KeyState
{
private:
	/// <summary>
	/// 仮想キーコード
	/// </summary>
	int keyCode;
	
	/// <summary>
	/// 現在のフレームで押されているかどうか
	/// </summary>
	bool isDownCurrent;

	/// <summary>
	/// 前フレームで押されていたかどうか
	/// </summary>
	bool isDownBefore;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="keyCode">仮想キーコード</param>
	KeyState(int keyCode);

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
	KeyStateManager();

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

