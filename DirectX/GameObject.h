#pragma once
#include "DxLib.h"
#include "GameData.h"
#include "Task.h"
#include "Texture.h"

class GameObject :
	public Task
{
public:
	int textureHandle;
	double x, y;
	double angle;
	float scale;
	float alpha;
	float colSize;

	bool alive;

	GameObject(TaskList *list, double x, double y, double angle);
	~GameObject();
	virtual int Move();
	virtual int Draw();

	bool IsHit(GameObject *obj);
	bool IsHit(TaskList *list);
	void SetTexture(Texture *texture);
};


class MyShip :
	public GameObject
{
	float m_spd;
public:
	void *operator new(size_t n);
	void operator delete(void *p);
	MyShip();
	virtual int Move();
	~MyShip();
};
