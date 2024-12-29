#include "KeyStateManager.h"


KeyState::KeyState(Timer* timer, int keyCode)
{
	this->timer = timer;
	this->keyCode = keyCode;
	this->count = 0;
	this->tempCount = 0.0;
	this->beforeCount = 0;
}


void KeyState::update()
{
	if (KEYDOWN(this->keyCode))
	{
		this->tempCount += 30 / this->timer->getRealFPS();
		if (this->tempCount < 1)
			this->tempCount = 1;
		this->beforeCount = this->count;
		this->count = (int)this->tempCount;
	}
	else
	{
		this->count = 0;
		this->tempCount = 0.0;
	}
}


int KeyState::getKeyCode()
{
	return this->keyCode;
}


bool KeyState::getIsDownRepeat(float interval)
{
	if ((this->count % (int)(30 * interval)) == 1 && this->count != this->beforeCount)
	{
		return true;
	}
	return false;
}


bool KeyState::getIsDownCurrent()
{
	return (this->count > 0);
}


bool KeyState::getIsDownStart()
{
	if (this->count == 1 && this->count != this->beforeCount)
	{
		return true;
	}
	return false;
}


KeyStateManager::KeyStateManager(Timer* timer)
{
	this->timer = timer;

	// Žæ“¾‚·‚éƒL[‚Ì‰Šú‰»
	this->statesLength = KEYCODE_LENGTH;
	
	this->states = (KeyState**)malloc(sizeof(KeyState*) * KEYCODE_LENGTH);

	for (int keyIndex = 0; keyIndex < KEYCODE_LENGTH; keyIndex++)
	{
		if (this->states == NULL)
			throw "states‚ªNULL‚Å‚·";
		this->states[keyIndex] = new KeyState(timer, KEYCODES[keyIndex]);
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

