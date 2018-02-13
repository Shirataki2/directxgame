#include "GameObject.h"



GameObject::GameObject(char* src)
{
	handle = LoadGraph(src);
	if (handle == -1) {
		DrawString(0, 0, "Can't Read Image", GetColor(255, 0, 0));
	}
	x = y = 100;
}


GameObject::~GameObject()
{
}

int GameObject::Move()
{
	if (GameData::key[KEY_INPUT_A]) {
		x--;
	}
	if (GameData::key[KEY_INPUT_D]) {
		x++;
	}
	if (GameData::key[KEY_INPUT_S]) {
		y++;
	}
	if (GameData::key[KEY_INPUT_W]) {
		y--;
	}

	return 0;
}

int GameObject::Draw()
{
	DrawGraph(x, y, handle, TRUE);
	return 0;
}
