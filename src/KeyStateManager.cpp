#include "KeyStateManager.h"


KeyState::KeyState(int keyCode)
{
	this->keyCode = keyCode;
	this->isDownBefore = false;
	this->isDownCurrent = false;
}


void KeyState::update()
{
	this->isDownBefore = this->isDownCurrent;
	this->isDownCurrent = KEYDOWN(this->keyCode);
}


int KeyState::getKeyCode()
{
	return this->keyCode;
}


bool KeyState::getIsDownCurrent()
{
	return this->isDownCurrent;
}


bool KeyState::getIsDownStart()
{
	return this->isDownCurrent && !this->isDownBefore;
}


KeyStateManager::KeyStateManager()
{
	// Žæ“¾‚·‚éƒL[‚Ì‰Šú‰»
	this->statesLength = KEYCODE_LENGTH;
	
	this->states = (KeyState**)malloc(sizeof(KeyState*) * KEYCODE_LENGTH);

	for (int keyIndex = 0; keyIndex < KEYCODE_LENGTH; keyIndex++)
	{
		if (this->states == NULL)
			throw "states‚ªNULL‚Å‚·";
		this->states[keyIndex] = new KeyState(KEYCODES[keyIndex]);
	}
}


KeyStateManager::~KeyStateManager()
{
	for (int keyIndex = 0; keyIndex < this->statesLength; keyIndex++)
	{
		delete this->states[keyIndex];
	}
	delete this->states;
}


void KeyStateManager::update() {
	for (int keyIndex = 0; keyIndex < this->statesLength; keyIndex++)
	{
		this->states[keyIndex]->update();
	}
}


KeyState* KeyStateManager::getKeyState(int keyCode)
{
	for (int keyIndex = 0; keyIndex < this->statesLength; keyIndex++)
	{
		if (this->states[keyIndex]->getKeyCode() == keyCode)
		{
			return this->states[keyIndex];
		}
	}
	return NULL;
}

