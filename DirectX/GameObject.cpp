#include "GameObject.h"


GameObject::GameObject(TaskList *list, double x, double y, double angle,int colsize,int grz)
	:Task(list),
	x(x),y(y),angle(angle),scale(1),alpha(1),
	alive(true),colSize(colsize),grzSize(grz),
	isMultiTexture(false)
{
}

GameObject::GameObject(TaskList * list, double x, double y, int stopMotionID, int stopMotionNum, int leftMotionID, int leftMotionNum, int rightMotionID, int rightMotionNum, int colsize, int grzSize)
	: Task(list),x(x),y(y), angle(angle), scale(1), alpha(1),
	alive(true), colSize(colsize), grzSize(grzSize),
	m_smid(stopMotionID),
	m_lmid(leftMotionID),
	m_rmid(rightMotionID),
	m_smnm(stopMotionNum),
	m_lmnm(leftMotionNum),
	m_rmnm(rightMotionNum),
	isMultiTexture(true)
{

}



GameObject::~GameObject()
{
}

int GameObject::Move()
{
	return 0;
}


int GameObject::Draw()
{
	//DrawGraph(x, y, textureHandle, TRUE);
	DrawRotaGraph2(x + cx, y + cy, cx, cy, scale, 2 * pi*angle + pi/2, textureHandle, TRUE);
	if (GD::isColVisible) {
		DrawCircle(x + cx, y + cy, grzSize, GetColor(0, 0, 255));
		DrawCircle(x + cx, y + cy, colSize, GetColor(0, 255, 0));
	}

	return 0;
}

void GameObject::CalcResion()
{
	int col = (x + cx) / GD::regionSizeX;
	int row = (y + cy / 2) / GD::regionSizeY;
	region = row*GD::regionNumX + col;
}

void GameObject::SetColSize(int size)
{
	colSize = size;
}

void GameObject::SetMotionInterval(int stop, int left, int right)
{
	m_smiv = stop;
	m_lmiv = left;
	m_rmiv = right;
}

bool GameObject::IsHit(GameObject * obj)
{
	if (region != obj->region)return false;
	Texture* t_obj = GD::Res->Find(obj->textureID);
	static Texture* t_this = GD::Res->Find(textureID);
	double
		dx = (obj->x + obj->cx) - (x + cx),
		dy = (obj->y + obj->cy) - (y + cy),
		hit = obj->colSize + this->colSize;
	return dx*dx + dy*dy < hit * hit;
}

bool GameObject::IsHit(TaskList * list)
{
	for (TaskIter i(list); i.HasNext();) {
		GameObject *obj = static_cast<GameObject*>(i.Next());
		if (IsHit(obj)) return true;
	}
	return false;
}
bool GameObject::IsGraze(GameObject * obj)
{
	if (region != obj->region)return false;
	Texture* t_obj = GD::Res->Find(obj->textureID);
	static Texture* t_this = GD::Res->Find(textureID);
	double
		dx = (obj->x + obj->cx) - (x + cx),
		dy = (obj->y + obj->cy) - (y + cy),
		grz = obj->grzSize + this->grzSize;
	return dx*dx + dy*dy < grz * grz;
}

bool GameObject::IsGraze(TaskList * list)
{
	for (TaskIter i(list); i.HasNext();) {
		GameObject *obj = static_cast<GameObject*>(i.Next());
		if (IsGraze(obj)) return true;
	}
	return false;
}

void GameObject::SetTexture(Texture * texture)
{
	textureHandle = texture->GetHandle();
	textureID = texture->ID;
	cx = GD::Res->Find(textureID)->GetSizeX() / 2;
	cy = GD::Res->Find(textureID)->GetSizeY() / 2;
}

void MyShip::MoveSub()
{
	m_spd = PUSHING(GD::LShift) ? LowSpeed : HighSpeed;
	if (IS_PUSHING(GD::Up | GD::Down) &&
		IS_PUSHING(GD::Left | GD::Right)) {
		m_spd /= sqrt(2.0);
	}
	switch (isMultiTexture)
	{
	case true:
		if (PUSHING(GD::Left | GD::Right) == 0) {
			m_lmpt = m_rmpt = 0;
			m_lmps = m_rmps = 0;
			if ((++m_smpt%m_smiv) == 0) {
				m_smps = (++m_smps) % m_smnm;
			}
			SetTexture(GD::Res->Find(m_smid + m_smps));
			textureID = m_smid + m_smps;
		}
		if (PUSHING(GD::Left)) {
			m_rmpt = m_smpt = 0;
			m_rmps = m_smps = 0;
			if ((++m_lmpt%m_lmiv) == 0) {
				m_lmps = (++m_lmps) % m_lmnm;
			}
			SetTexture(GD::Res->Find(m_lmid + m_lmps));
		}
		if (PUSHING(GD::Right)) {
			m_lmpt = m_smpt = 0;
			m_lmps = m_smps = 0;
			if ((++m_rmpt%m_rmiv) == 0) {
				m_rmps = (++m_rmps) % m_rmnm;
			}
			SetTexture(GD::Res->Find(m_rmid + m_rmps));
		}
	case false:
		if (PUSHING(GD::Up))    y += m_spd;
		if (PUSHING(GD::Down))  y -= m_spd;
		if (PUSHING(GD::Left))  x -= m_spd;
		if (PUSHING(GD::Right)) x += m_spd;
		break;
	}
	if (PUSHED(GD::B5)) isInvincible = !isInvincible;
	if (x < 40)x = 40;
	if (y < 40)y = 40;
	int max = GD::StageX(1.0) - GD::Res->Find(textureID)->GetSizeX();
	if (x > max)x = max;
	if (y > GD::stageSizeY)y = GD::stageSizeY;
}

void MyShip::ShotSub()
{
	static int t = 0, shotItv = 2, beamItv = 1;
	if (PUSHING(GD::Button1)) {
		if (PUSHING(GD::LShift)) {
			if (t%beamItv == 0) {
				new MyShipShot(GD::Res->Find(T_MYBEAM),
					m_beamspd, this, 2, true, 0, 25);
			}
		}
		else if (t%shotItv == 0) {
			for (int i = -3; i <= 3; i++) {
				new MyShipShot(GD::Res->Find(T_MYSHOT),
					m_shotspd, this, 4, false, i*0.0125, 20);
			}
		}
	}
	t++;
}

void * MyShip::operator new(size_t n) {
	return GD::MyShipList->New(n);
}
void MyShip::operator delete(void *p) {
	GD::MyShipList->Delete(p);
}

int MyShip::Draw()
{
	DrawRotaGraph2(x + cx, y + cx, cx, cy, scale, 2 * pi*angle, textureHandle, TRUE);
	if (GD::isColVisible) {
		DrawCircle(x + cx, y + cy, grzSize, GetColor(0, 0, 255));
		DrawCircle(x + cx, y + cy, colSize, GetColor(0, 255, 0));
	}
	return 0;
}


MyShip::MyShip()
	:GameObject(GD::MyShipList,
		GD::NormalizedX(0.5),
		GD::NormalizedY(0.5),
		0)
{
}

MyShip::MyShip(Texture * myshiptexture, int colsize, int grzSize)
	:GameObject(GD::MyShipList,
		GD::StageX(0.5),
		GD::StageY(0.8),
		0,
		colsize,
		grzSize)
{
	this->SetTexture(myshiptexture);
}

MyShip::MyShip(Texture * myshiptextures, int stopMotionID, int stopMotionNum, int leftMotionID, int leftMotionNum, int rightMotionID, int rightMotionNum, int colsize, int grzSize)
	:GameObject(GD::MyShipList,GD::StageX(0.5),
		GD::stageSizeY-40,stopMotionID,stopMotionNum,
		leftMotionID,leftMotionNum,rightMotionID,rightMotionNum,
		colsize,grzSize)
{
}

MyShip::MyShip(Texture * myshiptextures, int stopMotionID, int stopMotionNum, int leftMotionNum, int rightMotionNum, int colsize, int grzSize)
	:GameObject(GD::MyShipList, GD::StageX(0.5),
		GD::stageSizeY - 40, stopMotionID, stopMotionNum,
		stopMotionID+stopMotionNum, leftMotionNum,
		stopMotionID+stopMotionNum+leftMotionNum, rightMotionNum,
		colsize, grzSize)
{
}


int MyShip::Move()
{
	static int t = 0, itv = 0;
	static bool grzable = true;
	MoveSub();
	ShotSub();

	if ((IsHit(GD::BulletList) || IsHit(GD::EnemyList))) {
		if(!isInvincible) {alive = false;}
		GD::Res->SFind(S_DEAD)->Play(160);
	}
	if (IsGraze(GD::BulletList) && grzable) {
		GD::score += 200;
		GD::Res->SFind(S_GRAZE)->Play(250);
		grzable = false;
		itv = 1;
	}
	itv--;
	if (itv < 0) grzable = true;
	CalcResion();
	return 0;
}


MyShip::~MyShip()
{

}

void * Enemy::operator new(size_t n)
{
	return GD::EnemyList->New(n);
}

void Enemy::operator delete(void * p)
{
	GD::EnemyList->Delete(p);
}

int Enemy::Draw()
{
	DrawGraph(x , y , textureHandle, TRUE);
	if (GD::isColVisible) {
		DrawCircle(x + cx, y + cy, grzSize, GetColor(0, 0, 255));
		DrawCircle(x + cx, y + cy, colSize, GetColor(0, 255, 0));
	}
	return 0;
}


Enemy::Enemy()
	:GameObject(
		GD::EnemyList,
		GD::NormalizedX(0.5),
		GD::NormalizedY(0.25),
		0)
{
}

Enemy::Enemy(Texture * enemyTexture)
	:GameObject(
		GD::EnemyList,
		GD::NormalizedX(0.5),
		GD::NormalizedY(0.25),
		0)
{
	this->SetTexture(enemyTexture);
}

void * Bullet::operator new(size_t n)
{
	return GD::BulletList->New(n);
}

void Bullet::operator delete(void * p)
{
	GD::BulletList->Delete(p);
}

Bullet::Bullet(int x, int y, float angle, float v_angle, float speed, float v_speed)
	:GameObject(
		GD::BulletList,
		x, y, angle),
	v_angle(v_angle),
	speed(speed),
	v_speed(v_speed)
{
}

Bullet::Bullet(Texture * bulletTexture, int x, int y, float angle, float v_angle, float speed, float v_speed,int colSize,int grzSize)
	:GameObject(
		GD::BulletList,
		x, y, angle,colSize,grzSize),
	v_angle(v_angle),
	speed(speed),
	v_speed(v_speed)
{
	this->SetTexture(bulletTexture);
}

int Bullet::Move()
{
	angle += v_angle;
	speed += v_speed;
	angle -= floor(angle);
	double
		cs = cos(2 * pi*angle),
		sn = sin(2 * pi*angle),
		dx = GD::SPD*GD::stageSizeX*speed*cs,
		dy = GD::SPD*GD::stageSizeX*speed*sn;
	x += dx;
	y += dy;
	if (x > GD::StageX(1.0)*1.2 ||
		x<-300 ||
		y>GD::stageSizeY*1.2 ||
		y < -300) {
		alive = false;
	}
	CalcResion();
	return 0;
}

StaticObject::StaticObject(Texture *texture)
	: GameObject(GD::CommonList, 0, 0, 0, 0)
{
	SetTexture(texture);
}
StaticObject::StaticObject(int textureid,int x=0,int y=0,int nums=1)
	: GameObject(GD::CommonList, 0, 0, 0, 0)
{
	for (size_t i = 0; i < nums; i++)
	{
		handles.push_back(GD::Res->Find(textureid + i)->GetHandle());
		ids.push_back(GD::Res->Find(textureid + i)->ID);
	}
	cx = GD::Res->Find(textureid)->GetSizeX() / 2;
	cy = GD::Res->Find(textureid)->GetSizeY() / 2;
}

StaticObject::StaticObject(Texture * texture, double x, double y)
	: GameObject(GD::CommonList, x, y, 0, 0)
{
	SetTexture(texture);
}

void * StaticObject::operator new(size_t n)
{
	return GD::CommonList->New(n);
}

void StaticObject::operator delete(void * p)
{
	GD::CommonList->Delete(p);
}

int StaticObject::Draw()
{
	DrawGraph(x, y, textureHandle, TRUE);
	return 0;
}

MyShipShot::MyShipShot(Texture *texture, float speed, MyShip *target, float power, bool syncX, double angle, int col, int grz)
	:m_target(target),
	sync(syncX),
	m_pow(power),
	m_spd(speed),
	GameObject(GD::MyShotList, target->x, target->y, angle, col, grz)
{
	SetTexture(texture);
}

void MyShipShot::SetPower(float pow)
{
	m_pow = pow;
}

int MyShipShot::Move()
{
	if (sync) {
		x = m_target->x;
	}
	else {
		x += m_spd * cos(angle * 2 * pi + pi / 2);
	}
	y -= m_spd * sin(angle*2*pi + pi / 2) ;

	for (TaskIter i(GD::EnemyList); i.HasNext();) {
		Enemy *e = (Enemy*)i.Next();
		if (IsHit(e)) {
			e->m_hp -= m_pow;
			GD::Res->SFind(S_E_HIT)->Play(180);
			GD::score += 5;
			alive = false;
		}
	}

	if (y < -50) alive = false;
	return 0;
}

void * MyShipShot::operator new(size_t n) {
	return GD::MyShotList->New(n);
}
void MyShipShot::operator delete(void *p) {
	GD::MyShotList->Delete(p);
}
int MyShipShot::Draw()
{
	DrawRotaGraph(x + m_target->cx,
		y,
		0.5, -2*pi*angle, textureHandle, TRUE);
	if (GD::isColVisible) {
		DrawCircle(x + cx, y + cy, grzSize, GetColor(0, 0, 255));
		DrawCircle(x + cx, y + cy, colSize, GetColor(0, 255, 0));
	}

	return 0;
}

void * OnPauseObject::operator new(size_t n)
{
	return GD::OnPauseList->New(n);
}

void OnPauseObject::operator delete(void * p)
{
	GD::OnPauseList->Delete(p);
}

OnPauseObject::OnPauseObject(int textureid, int x, int y, bool isBlink)
	:GameObject(GD::OnPauseList,x,y,0),
	isBlink(isBlink)
{
	time = 0;
	SetTexture(GD::Res->Find(textureid));
}

OnPauseObject::~OnPauseObject()
{
}

int OnPauseObject::Move()
{
	if (!GD::isPaused) { time = 0; return 0; };
	time++;
	if (time < fadein)x = GD::StageX(0.5) - 0.3*time / fadein;
}

int OnPauseObject::Draw()
{
	SetUseBackBufferTransColorFlag(FALSE);
	if (isBlink)SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 192+63*sin(time/20.0));
	DrawRotaGraph(x, y, 1, 0, textureHandle, TRUE);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, NULL);
	return 0;
}
