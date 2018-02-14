#pragma once
#include "DxLib.h"
class Texture
{
	int m_handle;
	int sizeX, sizeY;
public:
	int ID;
	int GetHandle();
	int GetSizeX();
	int GetSizeY();
	bool IsLoading();
	Texture(int id,char *src, bool async = true);
	~Texture();
};

