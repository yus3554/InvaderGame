#pragma once
#include <windows.h>
#include "Constants.h"


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
	PCTSTR menuItemName;
	MenuItemID id;
	bool selected;

public:
	MenuItem(PCTSTR menuName, MenuItemID id);
	bool getSelected();
	void setSelected(bool selected);
	MenuItemID getID();
	PCTSTR getMenuItemName();
};


/// <summary>
/// メニューアイテムを管理するクラス
/// </summary>
class MenuManager
{
private:
	int menuItemsLength;
	MenuItem** menuItems;
	MenuItemID currentID;
	void setCurrentSelectItems();

public:
	MenuManager();
	~MenuManager();
	void nextItem();
	void previousItem();
	MenuItemID getCurrentID();
	MenuItem** getMenuItems();
	int getMenuItemsLength();
};


