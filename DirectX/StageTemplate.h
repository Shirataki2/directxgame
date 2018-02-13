#pragma once
#include "IBaseScene.h"
class StageTemplate :
	public IBaseScene
{
public:
	StageTemplate();
	~StageTemplate();
	void Update();
	void Draw();
};

