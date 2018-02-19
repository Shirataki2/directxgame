#pragma once
#include "DxLib.h"
#include "GameData.h"
#include "Task.h"
#include "Texture.h"
#include <vector>

class GameObject :
	public Task
{
protected:
	const double pi = 3.14159265;
	std::vector<int> handles, ids;
	bool isMultiTexture = false;
	int m_smid, m_lmid, m_rmid;
	int m_smnm, m_lmnm, m_rmnm;
	int m_smps, m_lmps, m_rmps;
	int m_smpt, m_lmpt, m_rmpt;
	int m_smiv = 4, m_lmiv = 4, m_rmiv = 4;
public:
	int textureHandle;
	int textureID;
	int region = -1;
	double x, y;
	double cx, cy;
	double angle;
	float scale;
	float alpha;
	int colSize = 2;
	int grzSize = 8;
	bool isColVisible = false;

	bool alive;

	GameObject(TaskList *list, double x, double y, double angle, int colsize = 2, int grz = 8);
	GameObject(TaskList *list,
		double x,double y,
		int stopMotionID, int stopMotionNum,
		int leftMotionID, int leftMotionNum,
		int rightMotionID, int rightMotionNum,
		int colsize = 4, int grzSize = 11);
	~GameObject();
	virtual int Move();
	virtual int Draw();
	void CalcResion();
	void SetColSize(int size);
	void SetMotionInterval(int stop, int left, int right);
	bool IsHit(GameObject *obj);
	bool IsHit(TaskList *list);
	bool IsGraze(GameObject *obj);
	bool IsGraze(TaskList *list);
	void SetTexture(Texture *texture);
};


class MyShip :
	public GameObject
{
	float m_spd;
	bool isInvincible = false;
	void MoveSub();
public:
	float HighSpeed = 4.0, LowSpeed = 1.8;
	void *operator new(size_t n);
	void operator delete(void *p);
	virtual int Draw();
	MyShip();
	MyShip(Texture *myshiptexture, int colsize = 4, int grzSize = 11);
	MyShip(Texture *myshiptextures,
		int stopMotionID, int stopMotionNum,
		int leftMotionID, int leftMotionNum,
		int rightMotionID, int rightMotionNum,
		int colsize, int grzSize);
	MyShip(Texture *myshiptextures,
		int stopMotionID, int stopMotionNum,
		int leftMotionNum,
		int rightMotionNum,
		int colsize, int grzSize);
	virtual int Move();
	~MyShip();
};

class Enemy :
	public GameObject
{
public:
	int t = 0;
	void *operator new(size_t n);
	void operator delete(void *p);
	virtual int Draw();
	Enemy();
	Enemy(Texture *enemyTexture);
};

class Bullet :
	public GameObject
{
	float v_angle = 0.0;
	float speed = 5.0;
	float v_speed = 0.0;
public:
	void *operator new(size_t n);
	void operator delete(void *p);
	Bullet(int x, int y,
		float angle, float v_angle,
		float speed, float v_speed);
	Bullet(Texture *bulletTexture,
		int x, int y,
		float angle, float v_angle,
		float speed, float v_speed,
		int colSize = 2,
		int grzSize = 8);
	int Move();
};

class StaticObject :
	public GameObject {
public:
	void *operator new(size_t n);
	void operator delete(void *p);
	StaticObject(Texture *texture);
	StaticObject(int textureid, int x, int y, int nums);
	virtual int Draw();
	StaticObject(Texture *texture,double x,double y);
};
