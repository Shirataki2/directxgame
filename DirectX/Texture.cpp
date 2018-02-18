#include "Texture.h"



int Texture::GetHandle()
{
	GetGraphSize(m_handle, &sizeX, &sizeY);
	return this->m_handle;
}

int Texture::GetSizeX()
{
	return sizeX;
}

int Texture::GetSizeY()
{
	return sizeY;
}


Texture::Texture(){}

Texture::Texture(int id,char *src, bool async)
	:ID(id)
{
	if (async) SetUseASyncLoadFlag(TRUE);
	m_handle = LoadGraph(src);
	if (async) SetUseASyncLoadFlag(FALSE);
}

Texture::Texture(int id, int handle, int sizeX, int sizeY)
	:ID(id),m_handle(handle),sizeX(sizeX),sizeY(sizeY)
{
}


Texture::~Texture()
{
	DeleteGraph(m_handle);
}

int DivTexture::GetHandle(int row, int col)
{
	return Handles[row*this->col + col];
}

int DivTexture::GetHandle(int i)
{
	return Handles[i];
}

bool DivTexture::IsLoading()
{
	for (size_t i = 0; i < row*col; i++)
	{
		if (CheckHandleASyncLoad(Handles[i]))return true;
	}
	return false;
}

int DivTexture::GetID(int row, int col)
{
	return ids[row*this->col + col];
}

int DivTexture::GetSizeX()
{
	return colSize;
}

int DivTexture::GetSizeY()
{
	return rowSize;
}

int DivTexture::GetNum()
{
	return num;
}

int DivTexture::GetNumX()
{
	return col;
}

int DivTexture::GetNumY()
{
	return row;
}


DivTexture::DivTexture(int startID, char * src, int num, int xNum, int yNum, int xSize, int ySize, bool async)
	:row(yNum),col(xNum),startid(startID),
	rowSize(ySize),colSize(xSize),num(num)
{
	if (async) SetUseASyncLoadFlag(TRUE);
	LoadDivGraph(src, num, col, row, colSize, rowSize, Handles);
	if (async) SetUseASyncLoadFlag(FALSE);
	for (int j = 0; j < yNum; j++)
	{
		for (int i = 0; i < xNum; i++)
		{
			ids[j*xNum + i] = startID + j*xNum + i;
		}
	}
}

