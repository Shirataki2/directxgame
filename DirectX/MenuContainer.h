#pragma once
#include <string>
#include <vector>
#include "MenuElement.h"
#include "GameData.h"
#include "SoundObject.h"
#include "Macros.h"

class MenuContainer
{
	static const int maxElem = 32;
	int m_fontHandle = -1;
	int m_nElem, m_isImage;
	int m_txtColorNormal;
	int m_txtColorSelected;
	int m_txtColorExecuted;
	int m_pSelect;
	char *names[maxElem];
	int ids[maxElem], handles[maxElem];
	SoundObject *selectSound;
	SoundObject *executeSound;
	MenuElement *elements[maxElem];
public:
	bool IsLoadingResources();
	MenuContainer(int nElem, bool isImage,int fontHandle = -1);
	void SetSource(int numid, char *name);
	void SetSource(int numid, int texid);
	void SetTextColors(int normal, int select, int execute);
	void SetPosition(int x, int y, int interval);
	void SetSelect(int numid);
	int GetSelect();
	void Update();
	void Draw();
	void Execute();
	~MenuContainer();
};

