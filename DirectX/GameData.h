#pragma once
#include "DxLib.h"
#include "Task.h"
#include <math.h>
#include "ResourceHolder.h"
#include "SoundObject.h"
class ResouceHolder;

#define PUSHED(button) (GD::keyState & (button))
#define IS_PUSHED(button) ((GD::keyState & (button)) != 0)
#define PUSHED_ONLY(button) (GD::keyState & (button) == (button))
#define PUSHING(button) (GD::keyStateOn & (button))
#define IS_PUSHING(button) ((GD::keyStateOn & (button))!=0)
#define PUSHING_ONLY(button) (GD::keyStateOn & (button) == (button))

#define T_NIL		0x000
#define T_MSHIP		0x010
#define T_D_ENEMY	0x020
#define T_D_BUL		0x030
#define T_NBUL		0x031 // 31 - 39
#define S_DEAD		0x100
#define S_E_SHOT	0x101
#define S_GRAZE		0x102
#define T_BACK		0x300
#define T_BITNUM	0x310 // 310-319

class GameData {
public:
	enum KeyState {
		Up			= 1 << 0,
		Down		= 1 << 1,
		Left		= 1 << 2,
		Right		= 1 << 3,
		Button1		= 1 << 4,
		Button2		= 1 << 5,
		Button3		= 1 << 6,
		Button4		= 1 << 7,
		LShift		= 1 << 8,
		LCtrl		= 1 << 9,
		B5			= 1 << 10,
		B6			= 1 << 11,
		B7			= 1 << 12,
		B8			= 1 << 13,
		B9			= 1 << 14,
		B0			= 1 << 15,
	};
	static int score;
	static int isColVisible;
	static ResourceHolder *Res;
	static unsigned int keyState;
	static unsigned int keyStateOn;
	static int isFullScreen;
	static int winSizeX;
	static int winSizeY;
	static int stageSizeX;
	static int stageSizeY;
	static int regionNumX;
	static int regionNumY;
	static int regionSizeX;
	static int regionSizeY;
	static char key[256];
	static int NormalizedX(double t);
	static int NormalizedY(double t);
	static int StageX(double t);
	static int StageY(double t);
	static void KeyUpdate();
	static void MoveTo(double & x, double & y, int dst_x, int dst_y, double t);
	static TaskList *MyShipList;
	static TaskList *EnemyList;
	static TaskList *BulletList;
	static TaskList *CommonList;
	static const float SPD;

};

typedef GameData GD;
