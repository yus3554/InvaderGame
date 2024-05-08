#pragma once
#include "DrawInfo.h"
#include <windows.h>
#include "../Constants.h"
#include "../ResourceManager.h"
#include <math.h>

class DrawImageInfo :
    public DrawInfo
{
private:
    ResourceData* resourceData;
    LPDWORD backPixelBits;
    int pixelOffset;
public:
    DrawImageInfo(POINT pos, ResourceData* resourceData, LPDWORD backPixelBits, int pixelOffset);
    void render(HDC hdc);
};
