#pragma once
#include "TitleScene.h"
#include "StageTemplate.h"
#include "GameData.h"

class SceneManager
{
private:
	static IBaseScene *pScene;
public:
	enum SCENE {
		TITLE,
		STAGE_DEBUG,
	};
	static void Update();
	static void Draw();
	static int ChangeScene(SCENE scene);
};

