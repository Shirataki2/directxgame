#pragma once
#include "GameObject.h"

class Score :
	public StaticObject
{
	int m_x, m_y;
	int m_score;
public:
	Score(int startTexID,int x,int y,int num=10);
	int Move();
	int Draw();
	~Score();
};