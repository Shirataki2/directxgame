#include "StageTemplate.h"

StageTemplate::StageTemplate()
{
}


StageTemplate::~StageTemplate()
{
}

void StageTemplate::Update()
{
}

void StageTemplate::Draw()
{
	DrawString(0, 0, "You Are on Debug Stage!",
		GetColor(255, 255, 255));

}
