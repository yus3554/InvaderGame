#pragma once
#include "DrawInfo.h"
#include <windows.h>
#include "../Constants.h"

class DrawImageInfo :
    public DrawInfo
{
private:
    int width;
    int height;
    BYTE* pixelBits;
    LPDWORD backPixelBits;
public:
    DrawImageInfo(POINT pos, int width, int height, BYTE* pixelBits, LPDWORD backPixelBits);
    void render(HDC hdc);
};
