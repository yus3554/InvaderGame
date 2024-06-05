#include "MenuManager.h"


MenuItem::MenuItem(
	MenuItemID id
)
{
	this->nameList = LinkedList<const char>();
	this->currentNameIndex = 0;
	this->id = id;
	this->selected = false;
}

void MenuItem::AddName(const char* name)
{
	this->nameList.add(name);
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


const char* MenuItem::getCurrentMenuItemName()
{
	return this->nameList.get(this->currentNameIndex);
}

void MenuItem::NextNameIndex()
{
	this->currentNameIndex = (this->currentNameIndex + 1) % this->nameList.getLength();
}

int MenuItem::GetCurrentNameIndex()
{
	return this->currentNameIndex;
}


MenuManager::MenuManager()
{
	// メニューアイテムの初期化
	this->menuList = LinkedList<MenuItem>();

	MenuItem* start = new MenuItem(MENU_START);
	MenuItem* highscore = new MenuItem(MENU_HIGHSCORE);
	MenuItem* fps = new MenuItem(MENU_CHANGE_FPS);
	MenuItem* difficult = new MenuItem(MENU_CHANGE_DIFFICULT);
	MenuItem* quit = new MenuItem(MENU_QUIT);

	start->AddName(UI_TEXT_START);
	highscore->AddName(UI_TEXT_HIGHSCORE);
	fps->AddName("FPS : 60");
	fps->AddName("FPS : Inf");
	difficult->AddName("DIFFICULT : Normal");
	difficult->AddName("DIFFICULT : Hard");
	quit->AddName(UI_TEXT_QUIT);

	this->menuList.add(start);
	this->menuList.add(highscore);
	this->menuList.add(fps);
	this->menuList.add(difficult);
	this->menuList.add(quit);

	// カレントアイテムを初期化
	this->currentID = MENU_START;
	this->menuList.get(this->currentID)->setSelected(true);
}


MenuManager::~MenuManager()
{
	this->menuList.clear();
}


void MenuManager::setCurrentSelectItems()
{
	for (int menuItemIndex = 0; menuItemIndex < this->menuList.getLength(); menuItemIndex++)
	{
		MenuItem* menuItem = this->menuList.get(menuItemIndex);
		if (menuItem->getID() == this->currentID) {
			menuItem->setSelected(true);
		}
		else {
			menuItem->setSelected(false);
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

MenuItem* MenuManager::getCurrentItem()
{
	return this->menuList.get(this->currentID);
}

LinkedList<MenuItem>* MenuManager::getMenuList()
{
	return &this->menuList;
}


int MenuManager::getMenuListLength()
{
	return this->menuList.getLength();
}
