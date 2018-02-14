#pragma once
#include "DxLib.h"
#include <string>
#include "../resource.h"
#include "GameObject.h"
#include "GameData.h"
#include "SceneManager.h"
#include "SoundObject.h"
#include "FPS.h"

class Game
{
protected:
	FPS *fps;
	MusicObject *dbgSound;
public:
	Game();
	Game(int sizeX, int sizeY, int windowMode,std::string windowName="Game");
	~Game();
	int Instantiate(int sizeX, int sizeY, int WindowMode, std::string windowName);
	void Destroy();
	int Update();
	virtual int Move();
	virtual int Draw();
	void Run();
};

