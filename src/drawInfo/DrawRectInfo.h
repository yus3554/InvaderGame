#pragma once
#include "DrawInfo.h"
#include <windows.h>

class DrawRectInfo :
    public DrawInfo
{
private:
    RECT rect;
    COLORREF backgroundColor;
    COLORREF borderColor;
    int borderWidth;
public:
    DrawRectInfo(POINT pos, int width, int height, COLORREF backgroundColor, COLORREF borderColor, int borderWidth);
    void render(HDC hdc);
};
