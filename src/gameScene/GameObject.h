#pragma once
#include "../Renderer.h"
class GameObject
{
public:
	virtual void Update() = 0;
	virtual void DrawRequest(Renderer& renderer) = 0;
};

