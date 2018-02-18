#pragma once
#include "DxLib.h"
#include <vector>
class Texture
{
	int m_handle;
	int sizeX, sizeY;
public:
	int ID;
	virtual int GetHandle();
	virtual int GetSizeX();
	virtual int GetSizeY();
	Texture();
	Texture(int id,char *src, bool async = true);
	Texture(int id, int handle, int sizeX, int sizeY);
	~Texture();
};

class DivTexture :
	public Texture {
	std::vector<Texture*> textures;
	int row, col,num;
	int rowSize, colSize;
	int Handles[256];
	int ids[256];
	int startid;
public:
	int GetHandle(int row, int col);
	int GetHandle(int i);
	bool IsLoading();
	int GetID(int row, int col);
	int GetSizeX();
	int GetSizeY();
	int GetNum();
	int GetNumX();
	int GetNumY();
	DivTexture(int startID, char *src,
		int num,int xNum,int yNum,
		int xSize,int ySize,
		bool async = true);

};