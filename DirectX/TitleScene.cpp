#include "TitleScene.h"




TitleImage TitleScene::*m_title = NULL;
MenuContainer TitleScene::*mainmenu = NULL;

TitleScene::TitleScene()
{
	mainmenu = new MenuContainer(4, true);
	for (int i = 0; i < 4; i++)
	{
		mainmenu->SetSource(i, T_TMENU + i);
	}
	mainmenu->SetPosition(360, 380, 60);

	bgm = new MusicObject("Data/Music/d_title.mp3");
}


TitleScene::~TitleScene()
{
	bgm->Stop();
	delete bgm;
	delete mainmenu;
}

void TitleScene::Update()
{
	if (mainmenu->IsLoadingResources()) return;
	mainmenu->Update();
	if (PUSHED(GD::Button1)) {
		Execute();
	}
}

void Loading() {
	static int t = 0;
	DrawString(GameData::NormalizedX(1.0) - 100,
		GameData::NormalizedY(1.0) - 25,
		"Loading…", GetColor(t % 255, t % 255, t % 255));
	t += 25;
}

void TitleScene::Draw()
{
	if (mainmenu->IsLoadingResources()) { Loading(); return; }
	DrawString(0, 0, "You Are on Title Scene!",
		GetColor(255, 255, 255));
	mainmenu->Draw();
}

void TitleScene::Execute()
{
	int selected = mainmenu->GetSelect();
	mainmenu->Execute();
	switch (selected)
	{
	case TITLE_NEW_GAME:
		SceneManager::ChangeScene(SceneManager::STAGE_DEBUG);
		break;
	case TITLE_LOAD_GAME:
		break;
	case TITLE_CONFIG:
		break;
	case TITLE_EXIT:
		exit(0);
		break;
	default:
		break;
	}
}
