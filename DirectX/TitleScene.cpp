#include "TitleScene.h"




TitleImage TitleScene::*m_title = NULL;
MenuContainer TitleScene::*mainmenu = NULL;

TitleScene::TitleScene()
{
	mainmenu = new MenuContainer(4, false);
	mainmenu->SetSource(0, "New Game");
	mainmenu->SetSource(1, "Load Game");
	mainmenu->SetSource(2, "Config");
	mainmenu->SetSource(3, "Exit");
	mainmenu->SetTextColors(GetColor(255, 255, 255),
		GetColor(255, 0, 0), GetColor(0, 0, 255));
	mainmenu->SetPosition(350, 450, 40);

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
	typedef GameData gd;
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
