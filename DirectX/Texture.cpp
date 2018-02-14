#include "Texture.h"



int Texture::GetHandle()
{
	return this->m_handle;
}

int Texture::GetSizeX()
{
	if (IsLoading()) return 0;
	return sizeX;
}

int Texture::GetSizeY()
{
	if (IsLoading()) return 0;
	return sizeY;
}

bool Texture::IsLoading()
{
	bool loading = CheckHandleASyncLoad(m_handle);
	if (!loading) {
		GetGraphSize(m_handle, &sizeX, &sizeY);
	}
	return loading;
}

Texture::Texture(int id,char *src, bool async)
	:ID(id)
{
	if (async) SetUseASyncLoadFlag(TRUE);
	m_handle = LoadGraph(src);
	if (async) SetUseASyncLoadFlag(FALSE);
}


Texture::~Texture()
{
	DeleteGraph(m_handle);
}
