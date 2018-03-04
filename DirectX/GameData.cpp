#include "GameData.h"
int GameData::isFullScreen = 1;
int GameData::winSizeX = 1440;
int GameData::stageSizeX = 700;
int GameData::winSizeY = 1080;
int GameData::stageSizeY = 640;
int GameData::regionNumX = 2;
int GameData::regionNumY = 2;
int GameData::regionSizeX = 740 / 2;
int GameData::regionSizeY = 680 / 2;

char GameData::key[256] = {0};
bool GameData::isPaused = false;
unsigned int GameData::keyState = 0;
unsigned int GameData::keyStateOn = 0;
TaskList* GameData::MyShipList = new TaskList(500, 3);
TaskList* GameData::MyShotList = new TaskList(500, 200);
TaskList* GameData::EnemyList = new TaskList(500, 100);
TaskList* GameData::BulletList = new TaskList(300, 10000);
TaskList* GameData::CommonList = new TaskList(500, 200);
TaskList* GameData::OnPauseList = new TaskList(500, 10);
ResourceHolder* GameData::Res = NULL;
int GameData::isColVisible = 0;
const float GameData::SPD = 0.000002;
unsigned long long GameData::score = 0uLL;



int GameData::NormalizedX(double t)
{
	if (t > 1.0)return winSizeX;
	if (t < 0.0)return 0;
	return winSizeX*t;
}
int GameData::NormalizedY(double t)
{
	if (t > 1.0)return winSizeY;
	if (t < 0.0)return 0;
	return winSizeY*t;
}

int GameData::StageX(double t)

{
	if (t > 1.0)return stageSizeX + 40;
	if (t < 0.0)return 40;
	return 40 + stageSizeX*t;
}

int GameData::StageY(double t)
{
	if (t > 1.0)return stageSizeY+40;
	if (t < 0.0)return 40;
	return  40 + stageSizeX * t;
}


void GameData::KeyUpdate()
{
	char buf[256];
	GetHitKeyStateAll(buf);
	for (size_t i = 0; i < 256; i++)
	{
		if (buf[i]) {
			if (key[i] == 0) key[i] = 1;
			else if (key[i] == 1) key[i] = 2;
		}
		else {
			key[i] = 0;
		}
	}
	char Up = key[KEY_INPUT_S] | key[KEY_INPUT_DOWN];
	char Dn = key[KEY_INPUT_W] | key[KEY_INPUT_UP];
	char Lf = key[KEY_INPUT_A] | key[KEY_INPUT_LEFT];
	char Rt = key[KEY_INPUT_D] | key[KEY_INPUT_RIGHT];
	char B1 = key[KEY_INPUT_Z];
	char B2 = key[KEY_INPUT_X];
	char B3 = key[KEY_INPUT_C];
	char B4 = key[KEY_INPUT_V];
	char Sft = key[KEY_INPUT_LSHIFT];
	char Ctl = key[KEY_INPUT_LCONTROL];
	char B5 = key[KEY_INPUT_B];
	char B6 = key[KEY_INPUT_N];
	char B7 = key[KEY_INPUT_M];
	char B8 = key[KEY_INPUT_U];
	char B9 = key[KEY_INPUT_I];
	char B0 = key[KEY_INPUT_O];
#ifndef _DEBUG
	B5 = B6 = B7 = B8 = B9 = B0 = 0;
#endif // !_DEBUG

	char A[16] = { Up,Dn,Lf,Rt,B1,B2,B3,B4,Sft,Ctl,
	B5,B6,B7,B8,B9,B0 };
	for (int i = 0; i < 16; i++)
	{
		if (A[i] == 1) {
			keyState = keyState | (1 << i);
		}
		if (A[i] == 2) {
			keyState = keyState & ~(1 << i);
			keyStateOn = keyStateOn | (1 << i);
		}
		if (A[i] == 0) {
			keyState = keyState & ~(1 << i);
			keyStateOn = keyStateOn & ~(1 << i);
		}

	}
}

void GameData::MoveTo(double & x, double & y, int dst_x, int dst_y, double t)
{
	x += (dst_x - x)*t;
	y += (dst_y - y)*t;
}

void GameData::InitTask(TaskList * list)
{
	for (TaskIter i(list); i.HasNext(); i.Next(), i.Remove());
}

