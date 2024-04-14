#pragma once
#include <windows.h>
#include "Constants.h"


/// <summary>
/// ���j���[�A�C�e�����ʗp��Enum
/// </summary>
enum MenuItemID
{
	/// <summary>
	/// �Q�[���X�^�[�g
	/// </summary>
	MENU_START,

	/// <summary>
	/// �n�C�X�R�A���
	/// </summary>
	MENU_HIGHSCORE,

	/// <summary>
	/// �Q�[���I��
	/// </summary>
	MENU_QUIT,

	/// <summary>
	/// ���j���[�A�C�e���̐�
	/// </summary>
	MENU_ITEM_ID_NUM
};


/// <summary>
/// ���j���[�A�C�e��
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
/// ���j���[�A�C�e�����Ǘ�����N���X
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


