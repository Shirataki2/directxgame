#pragma once
#include "GameObject.h"
class DebugEmemy :
	public Enemy
{
	float m_angle;
	float v_angle;
	float speed;
	float v_speed;
public:
	int Move();
	DebugEmemy(Texture *texture, float angle, float v_angle, float speed, float v_speed);
	~DebugEmemy();
};

