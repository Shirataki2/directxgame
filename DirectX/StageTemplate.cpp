#include "StageTemplate.h"

bool StageTemplate::myshipAlive = true;

StageTemplate::StageTemplate()
{
	myshipAlive = true;
	//myship = new MyShip(GD::Res->Find(T_MSHIP),3);
	GD::score = 0;
	myship = new MyShip(GD::Res->DFind(T_MYSHIP),
		T_MYSHIP, 2, 2, 2, 3, 13);
	//enemy1 = new YukariEmemy(GD::Res->Find(T_D_ENEMY));
	enemy2 = new DebugEmemy(GD::Res->Find(T_D_ENEMY),
		0.02, 0.18, 2000, 10);
	frame = new StaticObject(GD::Res->Find(T_BACK));
	score = new Score(T_BITNUM, 750, 156, 10);
	bgm = new MusicObject("Data/Music/dummy.mp3",128);
	pause = new OnPauseObject(T_PAUSE,
		GD::StageX(0.5), GD::StageY(0.5));
	back = new OnPauseObject(T_P_BACK, 0, 540, false);
}


StageTemplate::~StageTemplate()
{
	bgm->Stop();
	delete myship, enemy1, frame, score, bgm;
}

void StageTemplate::Update()
{
	if (!myship->alive)myshipAlive = false;
	if (GD::isPaused) {
		UpdateTask(GD::OnPauseList);
	}
	else {
		UpdateTask(GD::MyShotList);
		UpdateTask(GD::MyShipList);
		UpdateTask(GD::BulletList);
		UpdateTask(GD::EnemyList);
		UpdateTask(GD::CommonList);
	}
	if (PUSHED(GD::Button4))GD::isPaused = !GD::isPaused;
#ifdef _DEBUG
	if (PUSHED(GD::B8))SceneManager::ChangeScene(SceneManager::TITLE);
#endif // _DEBUG

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
	DrawTask(GD::MyShotList);
	int num = DrawTask(GD::BulletList);
	DrawTask(GD::MyShipList);
	DrawTask(GD::EnemyList);
	DrawTask(GD::CommonList);
	DrawFormatString(0, 0, GetColor(255, 255, 255),
		"%d", num);
	if (GD::isPaused) {
		DrawTask(GD::OnPauseList);
	}

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
