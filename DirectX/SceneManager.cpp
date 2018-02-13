#include "SceneManager.h"

IBaseScene *SceneManager::pScene = NULL;

void SceneManager::Update()
{
	pScene->Update();
}

void SceneManager::Draw()
{
	pScene->Draw();
}

int SceneManager::ChangeScene(SCENE scene)
{
	if (pScene != NULL) {
		delete pScene;
	}
	switch (scene) {
	case SCENE::TITLE:
		pScene = new TitleScene();
		return 0;
	case SCENE::STAGE_DEBUG:
		pScene = new StageTemplate();
		return 0;
	default:
		return -1;
	}
}
