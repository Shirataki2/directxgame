#include "Game.h"

FPS Game::*fps = NULL;
MusicObject Game::*dbgSound = NULL;

bool Game::Loading()
{
	return GD::Res->IsLoading();
}

void Game::ResourceInit()
{
	GD::Res->Register(
		T_D_MSHIP,
		new Texture(T_D_MSHIP, "Data/Img/MyShip.png"));
	GD::Res->Register(
		T_MYSHIP,
		new DivTexture(T_MYSHIP, "Data/Img/reimu.png",
			6, 2, 3, 50, 50));
	GD::Res->Register(
		T_D_ENEMY,
		new Texture(T_D_ENEMY, "Data/Img/EnemyDummy.png"));
	GD::Res->Register(
		T_D_BUL,
		new Texture(T_D_BUL, "Data/Img/BulletDummy.png"));
	GD::Res->Register(
		T_BACK,
		new Texture(T_BACK, "Data/Img/back2.png"));
	GD::Res->Register(
		T_NBUL,
		new DivTexture(T_NBUL, "Data/Img/bul.png",
			9, 9, 1, 16, 16));
	GD::Res->Register(
		T_FUGUBUL,
		new DivTexture(T_FUGUBUL, "Data/Img/fgss.png",
			8, 8, 1, 20, 18));
	GD::Res->Register(
		T_SBIGBUL,
		new DivTexture(T_SBIGBUL, "Data/Img/big.png",
			8, 4, 2, 64, 64));
	GD::Res->Register(
		T_KNIFBUL,
		new DivTexture(T_KNIFBUL, "Data/Img/knife.png",
			8, 8, 1, 17, 32));
	GD::Res->Register(
		T_FUDABUL,
		new DivTexture(T_FUDABUL, "Data/Img/fuda.png",
			10, 10, 1, 17, 18));
	GD::Res->Register(
		T_BITNUM,
		new DivTexture(T_BITNUM, "Data/Img/nums.png",
			10, 10, 1, 32, 32));
	GD::Res->Register(
		S_DEAD,
		new SoundObject("Data/Sound/Th/dead.wav"));
	GD::Res->Register(
		S_E_SHOT,
		new SoundObject("Data/Sound/Th/shot1.wav"));
	GD::Res->Register(
		S_GRAZE,
		new SoundObject("Data/Sound/Th/graze.wav"));
}

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
	SetUseBackBufferTransColorFlag(FALSE);
	ChangeWindowMode(windowMode);
	ResourceInit();
	while (Loading()) {
		ProcessMessage();
		ClearDrawScreen();
		DrawString(0, 0, "初期化中…", GetColor(255, 255, 255));
		ScreenFlip();
	}
	SceneManager::ChangeScene(SceneManager::TITLE);
	fps = new FPS(GameData::NormalizedX(0.9), 0);
	return 0;
}

void Game::Destroy()
{
	DxLib_End();
}

int Game::Update()
{
	if (!ProcessMessage()) {
		GameData::KeyUpdate();
		Move();
		ClearDrawScreen();
		Draw();
		ScreenFlip();
		return 0;
	}
	return -1;
}

int Game::Move()
{
	SceneManager::Update();
	return 0;
}

int Game::Draw()
{
	SceneManager::Draw();
	DrawFormatString(0, 25, GetColor(255, 255, 255),
		"%8d", GD::score);
	fps->Update();
	return 0;
}

void Game::Run()
{
	char key[256];
	while (Update() == 0) {
		GetHitKeyStateAll(key);
		if (key[KEY_INPUT_ESCAPE]) break;
		if (PUSHED(GD::B6))GD::isColVisible = !GD::isColVisible;
	}
}
