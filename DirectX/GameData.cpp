#include "GameData.h"
int GameData::Font_Gothic_Big = CreateFontToHandle(NULL, 35, 5);
int GameData::isFullScreen = 1;
int GameData::winSizeX = 1920;
int GameData::winSizeY = 1080;
char GameData::key[256] = {0};
unsigned int GameData::keyState = 0;
unsigned int GameData::keyStateOn = 0;
TaskList* GameData::MyShipList = new TaskList(800, 5);

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
	char Up = key[KEY_INPUT_S];
	char Dn = key[KEY_INPUT_W];
	char Lf = key[KEY_INPUT_A];
	char Rt = key[KEY_INPUT_D];
	char B1 = key[KEY_INPUT_Z];
	char B2 = key[KEY_INPUT_X];
	char B3 = key[KEY_INPUT_C];
	char B4 = key[KEY_INPUT_V];
	char Sft = key[KEY_INPUT_LSHIFT];
	char Ctl = key[KEY_INPUT_LCONTROL];
	char A[10] = { Up,Dn,Lf,Rt,B1,B2,B3,B4,Sft,Ctl };
	for (int i = 0; i < 10; i++)
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

