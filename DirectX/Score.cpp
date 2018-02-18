#include "Score.h"



Score::Score(int startTexID, int x, int y, int num)
	:StaticObject(
		startTexID,
		x, y, num),
	m_x(x),m_y(y)
{
}

int Score::Move()
{
	m_score = GD::score;
	return 0;
}

int Score::Draw()
{
	int numDigit = 9;
	int _n = m_score;
	int xr;
	//for (int i = 10; i <= m_score; i*=10)
	//{
	//	numDigit++;
	//}
	xr = m_x + numDigit*cx * 2;
	for (int i = 0; i <= numDigit; i++)
	{
		DrawGraph(xr, m_y,
			GD::Res->Find(ids[_n % 10])->GetHandle(),
			TRUE);
		_n /= 10;
		xr -= cx * 2;

	}
	return 0;
}


Score::~Score()
{
}
