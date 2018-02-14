#include "StageTemplate.h"

MyShip StageTemplate::*myship = NULL;
Texture StageTemplate::*t_myship = NULL;

StageTemplate::StageTemplate()
{
	myship = new MyShip();
	t_myship = new Texture(0,"Data/Img/MyShip.png");
	myship->SetTexture(t_myship);
}

bool StageTemplate::Loading(int skip) {
	static int t = 0;
	bool loading = CheckHandleASyncLoad(t_myship->GetHandle());
	if (skip) return loading;
	if (loading) {
		DrawFormatString(
			GD::winSizeX - 100,
			GD::winSizeY - 25,
			GetColor(t % 255, t % 255, t % 255),
			"Loading%4d", t/25);
		t += 25;
	}
	return loading;
}

StageTemplate::~StageTemplate()
{
}

void StageTemplate::Update()
{
	if (Loading(true))return;
	UpdateTask(GD::MyShipList);
}

void StageTemplate::UpdateTask(TaskList * list)
{
	for (TaskIter i(list); i.HasNext();) {
		GameObject *obj = static_cast<GameObject*>(i.Next());
		obj->Move();
	}
}

void StageTemplate::Draw()
{
	if (Loading()) return;
	DrawString(0, 0, "You Are on Debug Stage!",
		GetColor(255, 255, 255));
	DrawTask(GD::MyShipList);
}

void StageTemplate::DrawTask(TaskList * list)
{
	for (TaskIter i(list); i.HasNext();) {
		GameObject *obj = static_cast<GameObject*>(i.Next());
		obj->Draw();
	}
}
