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


int MyShip::Move()
{
	m_spd = PUSHING(GD::LShift) ? 0.8 : 2.4;
	if (PUSHING(GD::Up))    y += m_spd;
	if (PUSHING(GD::Down))  y -= m_spd;
	if (PUSHING(GD::Left))  x -= m_spd;
	if (PUSHING(GD::Right)) x += m_spd;
	return 0;
}


MyShip::~MyShip()
{
}
