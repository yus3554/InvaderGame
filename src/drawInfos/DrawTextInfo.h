#pragma once
#include "DrawInfo.h"
#include <windows.h>
class DrawTextInfo :
    public DrawInfo
{
private:
    PCTSTR text;
    int fontSize;
    COLORREF fontColor;
    int weight;
public:
    DrawTextInfo(const char* text, double x, double y, int fontSize, COLORREF fontColor, int weight);
    void render(HDC hdc);
};

