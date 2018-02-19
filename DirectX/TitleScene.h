#pragma once
#include "IBaseScene.h"
#include "GameData.h"
#include "MenuContainer.h"
#include "Macros.h"
#include "GameObject.h"
#include "SceneManager.h"
class SceneManager;

class TitleImage :public GameObject{
public:

};

class TitleScene :
	public IBaseScene
{
private:
	MenuContainer *mainmenu;
	TitleImage *m_title;
	MusicObject *bgm = 0;
public:
	TitleScene();
	~TitleScene();
	void Update();
	void Draw();
	void Execute();
};

