#pragma once
#include ".\\T_Engine\\T_Sprite.h"
#include "Zombie.h"
#include ".\\T_Engine\\T_Audio.h"
#include "Sun.h"
class Zombie;
class Plant :
	public T_Sprite
{
public:
	Plant(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~Plant();
	void PaintPic(HDC hdc, int validRect[]);
	void setPower(int power) { this->power = power; }
	int getPower() { return power; }
	void init(int type);
	void setType(int type) { this->type = type; }
	int getType() { return type; }
	void LoopFrame(bool ahead = true);
	bool LoopFrameOnce(bool ahead = true);
	void Draw(HDC hdc);
	void setState(int state);
	int getState() { return state; }
	int getCostSun() { return costSun; }
	void setCostSun(int costSun) { this->costSun = costSun; }
	int GetX() { return this->X; }
	int GetWeaponX() { return weapon->GetX(); }
	void attack(Zombie *zombie);
	void setValidY(int y) { validY = y; }
	int getValidY() { return validY; }
	void setRemainLive(int live) { this->remainLive = live; }
	int getRemianLive() { return remainLive; }
	int getPlantX() { return this->X; }
	int getDefence() { return defence; }
	void setDefence(int defence) { this->defence = defence; }
	bool CollideWith(Zombie* zombie, int distance = 0);
	void weaponMove();
	void setWeaponVisible(bool flag);
	void initSound(HWND m_hwnd);
private :
	AudioDX ds;									//DirectSound对象
	AudioDXBuffer shooter_buffer;		//豌豆射手音效
	AudioDXBuffer hit1_buffer;
	AudioDXBuffer hit2_buffer;
/*	T_Sprite *staticState;		//静止状态	卡片静止的状态*/
	T_Sprite *standState;		//植物种植时状态
	T_Sprite *workState;		//植物的工作状态
	T_Sprite *weapon;			//植物的进攻武器
	T_Sprite *weaponHit;		//武器击中僵尸
	int power;					//战斗力
	int type;					//植物种类
	int defence;				//防御值
	int state;					//状态
	int remainLive;				//剩余血量
	int costSun;				//消耗的太阳
	int validY;					//植物所在的有效行数  从1开始

	int weaponCount;			//控制发射的时间
	int startTime;
	int endTime;
};

