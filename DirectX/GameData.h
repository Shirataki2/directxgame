#pragma once
#include "DxLib.h"
#include "Task.h"

#define PUSHED(button) GD::keyState & button
#define PUSHING(button) GD::keyStateOn & button
class GameData {
public:
	enum KeyState {
		Up      = 1,
		Down    = 2,
		Left    = 4,
		Right   = 8,
		Button1 = 16,
		Button2 = 32,
		Button3 = 64,
		Button4 = 128,
		LShift  = 256,
		LCtrl   = 512,
	};

	static int Font_Gothic_Big; 
	static unsigned int keyState;
	static unsigned int keyStateOn;
	static int isFullScreen;
	static int winSizeX;
	static int winSizeY;
	static char key[256];
	static int NormalizedX(double t);
	static int NormalizedY(double t);
	static void KeyUpdate();
	static TaskList *MyShipList;
};

typedef GameData GD;


