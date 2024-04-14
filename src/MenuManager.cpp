#include "MenuManager.h"


MenuItem::MenuItem(
	PCTSTR menuItemName,
	MenuItemID id
)
{
	this->menuItemName = menuItemName;
	this->id = id;
	this->selected = false;
}

bool MenuItem::getSelected()
{
	return selected;
}


void MenuItem::setSelected(bool selected)
{
	this->selected = selected;
}


MenuItemID MenuItem::getID()
{
	return this->id;
}


PCTSTR MenuItem::getMenuItemName()
{
	return this->menuItemName;
}


MenuManager::MenuManager()
{
	// ���j���[�A�C�e���̏�����
	this->menuItemsLength = MENU_ITEM_ID_NUM;
	this->menuItems = (MenuItem**)malloc(sizeof(MenuItem*) * MENU_ITEM_ID_NUM);
	if (this->menuItems == NULL)
		throw "menuItems��NULL�ł�";

	this->menuItems[MENU_START] = new MenuItem(UI_TEXT_START, MENU_START);
	this->menuItems[MENU_HIGHSCORE] = new MenuItem(UI_TEXT_HIGHSCORE, MENU_HIGHSCORE);
	this->menuItems[MENU_QUIT] = new MenuItem(UI_TEXT_QUIT, MENU_QUIT);

	// �J�����g�A�C�e����������
	this->currentID = MENU_START;
	this->menuItems[this->currentID]->setSelected(true);
}


MenuManager::~MenuManager()
{
	for (int menuItemsIndex = 0; menuItemsIndex < this->menuItemsLength; menuItemsIndex++) {
		delete this->menuItems[menuItemsIndex];
	}
	delete this->menuItems;
}


void MenuManager::setCurrentSelectItems()
{
	for (int menuItemIndex = 0; menuItemIndex < MENU_ITEM_ID_NUM; menuItemIndex++)
	{
		MenuItem* menuItem = this->menuItems[menuItemIndex];
		if (menuItem->getID() == this->currentID) {
			this->menuItems[menuItemIndex]->setSelected(true);
		}
		else {
			this->menuItems[menuItemIndex]->setSelected(false);
		}
	}
}


void MenuManager::nextItem()
{
	if (this->currentID + 1 >= MENU_ITEM_ID_NUM) {
		this->currentID = MENU_START;
	}
	else
	{
		this->currentID = static_cast<MenuItemID>(this->currentID + 1);
	}
	this->setCurrentSelectItems();
}


void MenuManager::previousItem()
{
	if (this->currentID - 1 < 0) {
		this->currentID = static_cast<MenuItemID>(MENU_ITEM_ID_NUM - 1);
	}
	else
	{
		this->currentID = static_cast<MenuItemID>(this->currentID - 1);
	}
	this->setCurrentSelectItems();
}


MenuItemID MenuManager::getCurrentID()
{
	return this->currentID;
}


MenuItem** MenuManager::getMenuItems()
{
	return this->menuItems;
}


int MenuManager::getMenuItemsLength()
{
	return this->menuItemsLength;
}
