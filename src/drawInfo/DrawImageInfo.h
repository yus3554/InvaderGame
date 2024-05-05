#pragma once
#include "DrawInfo.h"
#include <windows.h>
#include "../Constants.h"
#include "../ResourceManager.h"

class DrawImageInfo :
    public DrawInfo
{
private:
    ResourceData* resourceData;
    LPDWORD backPixelBits;
public:
    DrawImageInfo(POINT pos, ResourceData* resourceData, LPDWORD backPixelBits);
    void render(HDC hdc);
};
