#pragma once
#include "IBaseScene.h"
#include "GameObject.h"
#include "GameData.h"
#include "Task.h"
#include "Enemies.h"
#include "Score.h"
class StageTemplate :
	public IBaseScene
{
	MyShip *myship = 0;
	Enemy *enemy1 = 0;
	StaticObject *frame = 0;
	Score *score = 0;
public:
	StageTemplate();
	~StageTemplate();
	virtual void Update();
	virtual void UpdateTask(TaskList *list);
	virtual void Draw();
	virtual int DrawTask(TaskList *list);
};

