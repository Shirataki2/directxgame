#include "Enemies.h"



int DebugEmemy::Move()
{
	static int n = 16;
	int next;
	static int MoveNext = 100, rx = 0, ry = 0, itv1 = 60, itv2 = 150;
	if (t < 40) {
		GD::MoveTo(x, y, x, GD::StageY(0.1), .1);
	}
	if (t > 100) {
		GD::MoveTo(x, y, rx, ry, 0.05);
	}
	if (t >= 300) { n = 32; itv1 = 50; }
	if (t > 80 && t % itv1 == 0) {
		n = 16;
		double rnd = GetRand(100000) / 100000.0;
		int rnd2 = GetRand(8);
		for (int i = 0; i < n; i++)
		{
			new Bullet(GD::Res->Find(rnd2 + T_NBUL), x, y,
				i / (double)n + rnd, 0, speed, v_speed);
		}
		GD::Res->SFind(S_E_SHOT)->Play(255);
		m_angle += v_angle;
	}
	if (t > 600 && t % itv2 == 0) {
		double rnd = GetRand(100000) / 100000.0;
		int rnd2 = GetRand(7);
		n = GetRand(8) + 8;
		for (int i = 0; i < n; i++)
		{
			new Bullet(GD::Res->Find(rnd2 + T_SBIGBUL), x, y,
				i / (double)n + rnd, 0, speed, v_speed,20,32);
		}
		GD::Res->SFind(S_E_SHOT)->Play(255);
		m_angle += v_angle;
	}
	if (t > 120 && t%5==0) {
		int rn = GetRand(4);
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
		next = GetRand(60) + 40;
		MoveNext += next;
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
}
