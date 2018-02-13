#pragma once
#include "DxLib.h"
#include "GameData.h"

class GameObject
{
public:
	int handle;
	double x, y;
	GameObject(char* src);
	~GameObject();
	virtual int Move();
	virtual int Draw();
};
