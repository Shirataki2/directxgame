#pragma once
#include "IBaseScene.h"
#include "GameObject.h"
#include "GameData.h"
#include "Task.h"
#include "Enemies.h"
#include "Score.h"
#include "SceneManager.h"
class SceneManager;
class StageTemplate :
	public IBaseScene
{
public:
	MyShip *myship = 0;
	Enemy *enemy1=0,*enemy2 = 0;
	StaticObject *frame = 0;
	Score *score = 0;
	OnPauseObject *pause = 0;
	OnPauseObject *back = 0;
	MusicObject *bgm = 0;
	static bool myshipAlive;
	StageTemplate();
	~StageTemplate();
	virtual void Update();
	virtual void UpdateTask(TaskList *list);
	virtual void Draw();
	virtual int DrawTask(TaskList *list);
};

