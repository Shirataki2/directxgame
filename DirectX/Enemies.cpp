#include "Enemies.h"



int DebugEmemy::Move()
{
	if (t < 40) {
		GD::MoveTo(x, y, x, GD::StageY(0.1), .1);
	}
	if (t > 100) {
		GD::MoveTo(x, y, rx, ry, 0.05);
	}
	if (t >= 500) { n = 8; itv1 = 60; }
	if (t >= 1000) { n = 8; itv2 = 45; }
	if (t >= 1500) { n = 8; itv2 = 30; itv1 = 25; }
	if (t >= 3500) { n = 16; itv2 = 20; itv1 = 15; }
	if (t > 80 && t % itv1 == 0) {
		double rnd = GetRand(100000) / 100000.0;
		int rnd2 = GetRand(8);
		for (int i = 0; i < n; i++)
		{
			new Bullet(GD::Res->Find(rnd2 + T_NBUL), x, y,
				i / (double)n + rnd, 0, speed, v_speed,1,8);
		}
		GD::Res->SFind(S_E_SHOT)->Play(255);
		m_angle += v_angle;
	}
	if (t > 600 && t % itv2 == 0) {
		double rnd = GetRand(100000) / 100000.0;
		int rnd2 = GetRand(7);
		n = GetRand(8) + 8 +(n * 3) / 10;
		for (int i = 0; i < n; i++)
		{
			new Bullet(GD::Res->Find(rnd2 + T_SBIGBUL), x, y,
				i / (double)n + rnd, 0, speed, v_speed,20,32);
		}
		GD::Res->SFind(S_E_SHOT)->Play(255);
		m_angle += v_angle;
	}
	if (t > 120 && t%30==0) {
		int rn = GetRand(1 + n / 4 + t / 1000);
		for (int i = 0; i < rn; i++) {
			int rnd = GetRand(100000);
			int rnd3 = GetRand(600);
			int rnd2 = GetRand(7) + T_FUGUBUL;
			int rnd4 = GetRand(7) + T_KNIFBUL;
			int rnd5 = GetRand(9) + T_FUDABUL;
			new Bullet(GD::Res->Find(rnd2), x, y,
				rnd / 100000.0, 0, (rnd3 + 900), 15, 1);
			rnd = GetRand(100000);
			new Bullet(GD::Res->Find(rnd5), x, y,
				rnd / 100000.0, -0.002, (rnd3 + 1900), 15, 1);
			rnd = GetRand(100000);
			new Bullet(GD::Res->Find(rnd4), x, y,
				rnd / 100000.0, 0.0015, (rnd3 + 2900), 15, 1);
		}
	}

	if (t == MoveNext) {
		rx = GetRand(GD::StageX(0.4)) + GD::StageX(0.3);
		ry = GetRand(GD::StageY(0.2)) + GD::StageY(0.1);
		MoveNext += GetRand(50) + 40;
	}
	if (StageTemplate::myshipAlive) {
		if (t > 3500) { GD::score += 128; }
		else if (t > 2500) { GD::score += 82; }
		else if (t > 2000) { GD::score += 37; }
		else if (t > 1000) { GD::score += 15; }
		else if (t > 500) { GD::score += 8; }
		else { GD::score += 3; }
	}
	t++;
	return 0;
}

DebugEmemy::DebugEmemy(Texture *texture,float angle, float v_angle, float speed, float v_speed)
	:m_angle(angle),
	v_angle(v_angle),
	speed(speed),
	v_speed(v_speed),
	Enemy(texture)
{
	x = GD::StageX(0.5);
	y = -40;
}


DebugEmemy::~DebugEmemy()
{
	t = 0;
}

int YukariEmemy::Move()
{
	t++;
	if (t < 40) {
		GD::MoveTo(x, y, x, GD::StageY(0.3), .1);
	}
	if (t < 80)return 0;
	double _angle = 200 * sin(t / 2000.0);
	if (t % 2 == 0) return 0;
	int n = 4;
	for (int i = 0; i < n; i++)
	{
		new Bullet(GD::Res->Find(T_FUDABUL + 4 + i),
			x, y, _angle + i*(1.0 / n), 0, 2000, 10);
	}
	return 0;
}

YukariEmemy::YukariEmemy(Texture * texture)
	:Enemy(texture)
{
	colSize = 20;
	x = GD::StageX(0.5);
	y = -40;

}

YukariEmemy::~YukariEmemy()
{
}
