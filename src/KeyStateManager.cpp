#include <windows.h>
#include "KeyStateManager.h"
#include "Constants.h"


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
	if (this->isDownCurrent && !this->isDownBefore)
	{
		return true;
	}
	return false;
}


KeyStateManager::KeyStateManager()
{
	// �擾����L�[�̏�����
	this->statesLength = STATES_LENGTH;
	
	this->states = (KeyState**)malloc(sizeof(KeyState*) * STATES_LENGTH);

	for (int keyIndex = 0; keyIndex < STATES_LENGTH; keyIndex++)
	{
		if (this->states == NULL)
			throw "states��NULL�ł�";
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

