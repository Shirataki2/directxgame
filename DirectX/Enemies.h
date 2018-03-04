#pragma once
#include "GameObject.h"
#include "StageTemplate.h"
class StageTemplate;
class DebugEmemy :
	public Enemy
{
	int t = 0;
	int n = 4;
	int next = 0;
	int MoveNext = 100, rx = 0, ry = 0, itv1 = 60, itv2 = 150;

	float m_angle;
	float v_angle;
	float speed;
	float v_speed;
public:
	int Move();
	DebugEmemy(Texture *texture, float angle, float v_angle, float speed, float v_speed);
	~DebugEmemy();
};

class YukariEmemy :
	public Enemy
{
	int t = 0;

	float m_angle;
	float v_angle;
	float speed;
	float v_speed;
public:
	int Move();
	YukariEmemy(Texture *texture);
	~YukariEmemy();
};

