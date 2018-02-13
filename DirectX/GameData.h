#pragma once
#include "DxLib.h"
#include <future>

class GameData {
public:

	static int Font_Gothic_Big; 

	static int isFullScreen;
	static int winSizeX;
	static int winSizeY;
	static char key[256];
	static int NormalizedX(double t);
	static int NormalizedY(double t);
	static void KeyUpdate();
};
