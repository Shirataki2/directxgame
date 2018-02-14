#pragma once
#include "IBaseScene.h"
#include "GameObject.h"
#include "GameData.h"
#include "Task.h"
class StageTemplate :
	public IBaseScene
{
	MyShip *myship;
	Texture *t_myship;
	bool Loading(int skip = false);
public:
	StageTemplate();
	~StageTemplate();
	void Update();
	void UpdateTask(TaskList *list);
	void Draw();
	void DrawTask(TaskList *list);
};

