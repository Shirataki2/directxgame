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
	int numDigit = 0;
	unsigned long long _n = m_score;
	int xr;
	for (unsigned long long i = 10uLL; i <= m_score; i*=10uLL)
	{
		numDigit++;
		if (numDigit == 19) break;
	}
	numDigit = numDigit <= 9 ? 9: numDigit;
	int over;
	over = numDigit >= 10 ? numDigit - 9 : 0;
	xr = m_x - over * cx * 2 + numDigit*cx * 2;
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
