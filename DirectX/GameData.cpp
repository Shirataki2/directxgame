#include "GameData.h"

int GameData::Font_Gothic_Big = CreateFontToHandle(NULL, 35, 5);
int GameData::isFullScreen = 1;
int GameData::winSizeX = 1920;
int GameData::winSizeY = 1080;
char GameData::key[256] = {0};

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
}
