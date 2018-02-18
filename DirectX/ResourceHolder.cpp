#include "ResourceHolder.h"

std::map<int, Texture*> ResourceHolder::resourceMap;
std::map<int, DivTexture*> ResourceHolder::divResourceMap;
std::map<int, SoundObject*> ResourceHolder::soundMap;


void ResourceHolder::Register(int id, Texture *resource)
{
	resourceMap[id] = resource;
}
void ResourceHolder::Register(int id, DivTexture * resources)
{
	divResourceMap[id] =resources;
	for (int i = 0; i < resources->GetNum();++i) {
		resourceMap[id + i] =
			new Texture(id + i, 
				resources->GetHandle(i),
				resources->GetSizeX(),
				resources->GetSizeY());
	}
}
void ResourceHolder::Register(int id, SoundObject *resource)
{
	soundMap[id] = resource;
}

bool ResourceHolder::IsLoading()
{
	for (auto it = resourceMap.begin(); it != resourceMap.end(); ++it) {
		if (CheckHandleASyncLoad(it->second->GetHandle())) return true;
	}
	for (auto it = divResourceMap.begin(); it != divResourceMap.end(); ++it) {
		if (it->second->IsLoading()) return true;
	}
	for (auto it = soundMap.begin(); it != soundMap.end(); ++it) {
		if (CheckHandleASyncLoad(it->second->GetHandle())) return true;
	}
	return false;
}

Texture * ResourceHolder::Find(int id)
{
	auto it = resourceMap.find(id);
	if (it != resourceMap.end()) {
		return it->second;
	}
	else {
		return 0;
	}
}
Texture * ResourceHolder::DFind(int id)
{
	auto it = divResourceMap.find(id);
	if (it != divResourceMap.end()) {
		return it->second;
	}
	else {
		return 0;
	}
}
SoundObject * ResourceHolder::SFind(int id)
{
	auto it = soundMap.find(id);
	if (it != soundMap.end()) {
		return it->second;
	}
	else {
		return 0;
	}
}


void ResourceHolder::Delete(int id)
{
	auto it = resourceMap.find(id);
	if (it != resourceMap.end()) {
		delete it->second;
		resourceMap.erase(it);
	}
	auto it2 = soundMap.find(id);
	if (it2 != soundMap.end()) {
		delete it2->second;
		soundMap.erase(it2);
	}
}
