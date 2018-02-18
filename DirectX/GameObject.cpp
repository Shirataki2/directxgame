#include "GameObject.h"


GameObject::GameObject(TaskList *list, double x, double y, double angle,int colsize,int grz)
	:Task(list),
	x(x),y(y),angle(angle),scale(1),alpha(1),
	alive(true),colSize(colsize),grzSize(grz)
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
	DrawGraph(x, y, textureHandle, TRUE);
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

Bullet::Bullet(Texture * bulletTexture, int x, int y, float angle, float v_angle, float speed, float v_speed,int colSize)
	:GameObject(
		GD::BulletList,
		x, y, angle,colSize),
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
	return GD::EnemyList->New(n);
}

void StaticObject::operator delete(void * p)
{
	GD::EnemyList->Delete(p);
}

int StaticObject::Draw()
{
	DrawGraph(x, y, textureHandle, TRUE);
	return 0;
}
