#pragma once
#include "DxLib.h"
#include "Texture.h"
#include "SoundObject.h"
#include <map>
class Texture;
class SoundObject;

class ResourceHolder
{
	static std::map<int, Texture*> resourceMap;
	static std::map<int, DivTexture*> divResourceMap;
	static std::map<int, SoundObject*> soundMap;
public:
	
	static void Register(int id, Texture *resource);
	static void Register(int id, DivTexture *resources);
	static void Register(int id, SoundObject *resource);
	static bool IsLoading();
	static Texture* Find(int id);
	static Texture * DFind(int id);
	static SoundObject* SFind(int id);
	static void Delete(int id);
};
