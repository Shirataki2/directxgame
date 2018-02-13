#pragma once
#include "DxLib.h"

class IBaseScene
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;
};