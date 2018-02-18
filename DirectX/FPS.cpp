#include "FPS.h"



FPS::FPS(int x, int y)
	:m_x(x),
	m_y(y)
{
	st = std::chrono::system_clock::now();
	for (size_t i = 0; i < m_n; i++)
	{
		dq_fps.push_front(60.0);
	}
}

void FPS::SetDuration(int n)
{
	m_n = n;
}

void FPS::Update()
{
	static double aveFps = 0;
	m_sumFps = 0.0;
	ed = std::chrono::system_clock::now();
	m_duration = std::chrono::duration_cast<std::chrono::milliseconds>(ed - st).count();
	m_fps = 1000.0 / m_duration;
	dq_fps.pop_back();
	dq_fps.push_front(m_fps);
	for (auto it=dq_fps.begin();it!=dq_fps.end();it++)
	{
		m_sumFps += *it;
	}
	if (count%m_n == 0) {
		aveFps = m_sumFps / (m_n - 1);
	}
	DrawFormatString(m_x, m_y, GetColor(255, 255, 255),
		"%.2f", aveFps);

	st = ed;
	count++;
}

