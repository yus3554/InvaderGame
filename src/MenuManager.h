#pragma once
#include <windows.h>
#include "Constants.h"
#include "LinkedList.h"


/// <summary>
/// メニューアイテム識別用のEnum
/// </summary>
enum MenuItemID
{
	/// <summary>
	/// ゲームスタート
	/// </summary>
	MENU_START,

	/// <summary>
	/// ハイスコア画面
	/// </summary>
	MENU_HIGHSCORE,

	/// <summary>
	/// FPS切り替え
	/// </summary>
	MENU_CHANGE_FPS,

	/// <summary>
	/// 難易度切り替え
	/// </summary>
	MENU_CHANGE_DIFFICULT,

	/// <summary>
	/// ゲーム終了
	/// </summary>
	MENU_QUIT,

	/// <summary>
	/// メニューアイテムの数
	/// </summary>
	MENU_ITEM_ID_NUM
};


/// <summary>
/// メニューアイテム
/// </summary>
class MenuItem
{
private:
	LinkedList<const char> nameList;
	int currentNameIndex;
	MenuItemID id;
	bool selected;

public:
	MenuItem(MenuItemID id);
	void AddName(const char* name);
	bool getSelected();
	void setSelected(bool selected);
	MenuItemID getID();
	const char* getCurrentMenuItemName();
	void NextNameIndex();
	int GetCurrentNameIndex();
};


/// <summary>
/// メニューアイテムを管理するクラス
/// </summary>
class MenuManager
{
private:
	LinkedList<MenuItem> menuList;
	MenuItemID currentID;
	void setCurrentSelectItems();

public:
	MenuManager();
	~MenuManager();
	void nextItem();
	void previousItem();
	MenuItem* getCurrentItem();
	MenuItemID getCurrentID();
	LinkedList<MenuItem>* getMenuList();
	int getMenuListLength();
};


