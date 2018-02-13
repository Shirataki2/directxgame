#include "Game.h"

FPS Game::*fps = NULL;
SoundObject Game::*dbgSound = NULL;

Game::Game()
{
	Instantiate(GameData::winSizeX, GameData::winSizeY, GameData::isFullScreen,"Sample");
}

/// <summary>
/// ウィンドウの初期化を行う
/// </summary>
/// <param name="sizeX,sizeY">画面サイズ</param>
/// <param name="windowMode">0でフルスクリーン
/// 1でウィンドウ</param>
/// <param name="windowName">ゲーム名</param>
Game::Game(int sizeX, int sizeY, int windowMode, std::string windowName)
{
	GameData::winSizeX = sizeX;
	GameData::winSizeY = sizeY;
	GameData::isFullScreen = windowMode;
	Instantiate(GameData::winSizeX, GameData::winSizeY, GameData::isFullScreen, windowName);
}


Game::~Game()
{
	Destroy();
}


int Game::Instantiate(int sizeX,int sizeY,int windowMode,std::string windowName)
{
	SetWindowIconID(IDI_ICON1);
	SetWindowIconID(IDI_ICON2);
	SetUse3DFlag(FALSE);
	if (DxLib_Init() == -1) {
		return -1;
	}
	SetGraphMode(sizeX, sizeY, 32);
	SetWaitVSyncFlag(TRUE);
	SetMainWindowText(windowName.c_str());
	SetDrawScreen(DX_SCREEN_BACK);
	ChangeWindowMode(windowMode);
	SceneManager::ChangeScene(SceneManager::TITLE);
	fps = new FPS(GameData::NormalizedX(0.9), 0);
	dbgSound = new SoundObject("Data/Music/dummy.mp3",100.0f,1.0f);
	int tt = 0;
	while (CheckHandleASyncLoad(dbgSound->GetHandle()) && !ProcessMessage() && !ClearDrawScreen())
	{
		DrawString(GameData::NormalizedX(1.0) - 100,
			GameData::NormalizedY(1.0) - 25,
			"初期化中…", GetColor(tt % 255, tt % 255, tt % 255));
		tt += 10;
		ScreenFlip();
	}
	dbgSound->SetVolume(255);
	dbgSound->SetPan(0);
	dbgSound->Play();
	return 0;
}

void Game::Destroy()
{
	DxLib_End();
}

int Game::Update()
{
	if (!ProcessMessage() && !ClearDrawScreen()) {
		GameData::KeyUpdate();
		Move();
		Draw();
		ScreenFlip();
		return 0;
	}
	return -1;
}

int Game::Move()
{
	SceneManager::Update();
	fps->Update();
	return 0;
}

int Game::Draw()
{
	SceneManager::Draw();
	return 0;
}

void Game::Run()
{
	char key[256];
	while (Update() == 0) {
		GetHitKeyStateAll(key);
		if (key[KEY_INPUT_ESCAPE]) break;
	}
}
