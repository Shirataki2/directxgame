#pragma once
#include <string>
#include <vector>
#include "GameData.h"
#include "DxLib.h"
class MenuElement
{
protected:
	int m_fontHandle = -1;
	int m_imgHandle;
	int m_imgID;
	int isSelect = 0;
	double m_x, m_y;
	float m_alpha = 1;
	int m_txtColor;
	int m_txtColorNormal;
	int m_txtColorSelected;
	int m_txtColorExecuted;
	char* m_name;
	bool m_isImage;
	int dstx;
public:
	MenuElement(bool isImage, char* name, int fontHandle = -1);
	MenuElement(int id, int fontHandle = -1);
	~MenuElement();
	void SetPosition(int x, int y);
	void SetTextColors(int normal, int select, int execute);
	int Draw();
	int Selected();
	int Disselected();
	virtual int Execute();
};

