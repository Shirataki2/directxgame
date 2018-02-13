#pragma once
#include <string>
#include <vector>
#include "DxLib.h"
class MenuElement
{
protected:
	int m_fontHandle = -1;
	int m_imgHandle;
	int m_x, m_y;
	int m_txtColor;
	int m_txtColorNormal;
	int m_txtColorSelected;
	int m_txtColorExecuted;
	char* m_name;
	bool m_isImage;
public:
	MenuElement(bool isImage,char* name, int fontHandle = -1);
	~MenuElement();
	void SetPosition(int x, int y);
	void SetTextColors(int normal, int select, int execute);
	int Draw();
	int Selected();
	int Disselected();
	int Execute();
};

