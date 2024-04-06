#pragma once
#include <windows.h>


/// <summary>
/// メニューアイテム識別用のEnum
/// </summary>
enum MenuItemID
{
	MENU_START,
	MENU_HIGHSCORE,
	MENU_QUIT,

	MENU_ITEM_ID_NUM
};


static const char** MENU_ITEM_TEXTS;


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


class Menu
{
private:
	int menuItemsLength;
	MenuItem** menuItems;
	MenuItemID currentID;
	void setCurrentSelectItems();

public:
	Menu();
	~Menu();
	void nextItem();
	void previousItem();
	MenuItemID getCurrentID();
	MenuItem** getMenuItems();
	int getMenuItemsLength();
};


