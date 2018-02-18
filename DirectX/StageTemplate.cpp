#include "StageTemplate.h"


StageTemplate::StageTemplate()
{
	myship = new MyShip(GD::Res->Find(T_MSHIP),3);
	enemy1 = new DebugEmemy(GD::Res->Find(T_D_ENEMY),
		0.0f, 0.008f, 1200.0 , 3.0);
	frame = new StaticObject(GD::Res->Find(T_BACK));
	score = new Score(T_BITNUM, 750, 153, 10);
}


StageTemplate::~StageTemplate()
{
}

void StageTemplate::Update()
{
	UpdateTask(GD::MyShipList);
	UpdateTask(GD::BulletList);
	UpdateTask(GD::EnemyList);
	UpdateTask(GD::CommonList);
}

void StageTemplate::UpdateTask(TaskList * list)
{
	for (TaskIter i(list); i.HasNext();) {
		GameObject *obj = static_cast<GameObject*>(i.Next());
		obj->Move();
		if (!obj->alive) i.Remove();
	}
}

void StageTemplate::Draw()
{
	int num = DrawTask(GD::BulletList);
	DrawTask(GD::MyShipList);
	DrawTask(GD::EnemyList);
	DrawTask(GD::CommonList);
	DrawFormatString(0, 0, GetColor(255, 255, 255),
		"%d", num);
	DrawFormatString(0, 50, GetColor(255, 255, 255),
		"%d", enemy1->t);
}

int StageTemplate::DrawTask(TaskList * list)
{
	int j = 0;
	for (TaskIter i(list); i.HasNext();) {
		GameObject *obj = static_cast<GameObject*>(i.Next());
		obj->Draw();
		j++;
	}
	return j;
}
