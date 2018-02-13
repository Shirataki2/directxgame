#pragma once
#include "DxLib.h"
#include <assert.h>
class SoundObject
{
	int m_SHandle;
	int m_volume = 255;
	int m_pan = 0;
	float m_pitch = 0.0f;
	float m_stretch = 1.0f;
	void SetPitch(float cent);
	void SetStretch(float rate);
public:
	static void Init();
	int GetHandle();
	SoundObject(char *src, float pitchCent = 0.0f, float stretchRate = 1.0f, bool async = true);
	bool IsPlay();
	virtual void Play();
	virtual void Stop();
	virtual void Delete();
	void SetVolume(int volume);
	void SetPan(int pan);
	~SoundObject();
};

