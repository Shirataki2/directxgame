#pragma once
#include <chrono>
#include "DxLib.h"
#include <deque>
class FPS
{
	std::chrono::system_clock::time_point st, ed;
	int m_n = 20;
	long long count = 0;
	std::deque<double> dq_fps;
	double m_fps = 60.0;
	double m_sumFps = 0.0;
	int m_x, m_y;
	double m_duration;
public:
	FPS(int x,int y);
	void SetDuration(int n);
	void Update();
};

