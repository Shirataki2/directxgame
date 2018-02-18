#include "GameObject.h"

void * MyShip::operator new(size_t n) {
	return GD::MyShipList->New(n);
}
void MyShip::operator delete(void *p) {
	GD::MyShipList->Delete(p);
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


int MyShip::Move()
{
	static int t = 0, itv = 0;
	static bool grzable = true;
	m_spd = PUSHING(GD::LShift) ? LowSpeed : HighSpeed;
	if (IS_PUSHING(GD::Up | GD::Down) &&
		IS_PUSHING(GD::Left | GD::Right)) {
		m_spd /= sqrt(2.0);
	}
	if (PUSHING(GD::Up))    y += m_spd;
	if (PUSHING(GD::Down))  y -= m_spd;
	if (PUSHING(GD::Left))  x -= m_spd;
	if (PUSHING(GD::Right)) x += m_spd;
	if (PUSHED(GD::B5)) isInvincible = !isInvincible;
	if (x < 40)x = 40;
	if (y < 40)y = 40;
	int max = GD::StageX(1.0) - GD::Res->Find(textureID)->GetSizeX();
	if (x > max)x = max;
	if (y > GD::stageSizeY)y = GD::stageSizeY;

	if (!isInvincible &&
		(IsHit(GD::BulletList) || IsHit(GD::EnemyList))) {
		alive = false;
		GD::Res->SFind(S_DEAD)->Play(96);
	}
	if (IsGraze(GD::BulletList) && grzable) {
		GD::score += 100;
		GD::Res->SFind(S_GRAZE)->Play(160);
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
