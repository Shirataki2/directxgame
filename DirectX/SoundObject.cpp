#include "SoundObject.h"



void SoundObject::Init()
{
	InitSoundMem();
}

int SoundObject::GetHandle()
{
	return m_SHandle;
}

SoundObject::SoundObject(char *src,
	float pitchCent,
	float stretchRate,
	bool async)
{
	SetPitch(pitchCent);
	SetStretch(stretchRate);
	if(async) SetUseASyncLoadFlag(TRUE);
	m_SHandle = LoadSoundMem(src);
	if(async) SetUseASyncLoadFlag(FALSE);
	assert(m_SHandle != -1);
}

bool SoundObject::IsPlay()
{
	return CheckSoundMem(m_SHandle) == 1;
}

void SoundObject::Play()
{
	
	PlaySoundMem(m_SHandle, DX_PLAYTYPE_BACK);
}

void SoundObject::Stop()
{
	if (IsPlay()) StopSoundMem(m_SHandle);
}

void SoundObject::Delete()
{
	Stop();
	delete this;
}

void SoundObject::SetVolume(int volume)
{
	if (volume < 0 || volume>255) return;
	ChangeVolumeSoundMem(volume, m_SHandle);
}

void SoundObject::SetPan(int pan)
{
	if (pan < -255 || pan>255) return;
	ChangePanSoundMem(pan, m_SHandle);
}

void SoundObject::SetPitch(float cent)
{
	SetCreateSoundPitchRate(cent);
}

void SoundObject::SetStretch(float rate)
{
	SetCreateSoundTimeStretchRate(rate);
}


SoundObject::~SoundObject()
{
	DeleteSoundMem(m_SHandle);
}

MusicObject::MusicObject(char * src)
{
	PlayMusic(src, DX_PLAYTYPE_BACK);
}

void MusicObject::Stop()
{
	StopMusic();
}
