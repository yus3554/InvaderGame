#pragma once


class KeyState
{
private:
	int keyCode;
	bool isDownCurrent;
	bool isDownBefore;
public:
	KeyState(int keyCode);
	void update();
	int getKeyCode();
	bool getIsDownCurrent();
	bool getIsDownStart();
};

class KeyStateManager
{
private:
	int statesLength;
	KeyState** states;
public:
	KeyStateManager();
	~KeyStateManager();
	void update();
	KeyState* getKeyState(int keyCode);

};

