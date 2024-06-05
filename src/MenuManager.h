#pragma once
#include <windows.h>
#include "Constants.h"
#include "LinkedList.h"


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
	/// FPS�؂�ւ�
	/// </summary>
	MENU_CHANGE_FPS,

	/// <summary>
	/// ��Փx�؂�ւ�
	/// </summary>
	MENU_CHANGE_DIFFICULT,

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
/// ���j���[�A�C�e�����Ǘ�����N���X
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


