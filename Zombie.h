#pragma once
#include ".\\T_Engine\\T_Sprite.h"
#include "MyConfig.h"
#include "Plant.h"
class Plant;
class Zombie : public T_Sprite
{
public:
	Zombie(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	Zombie(ZOMBIEINFO info);
	~Zombie();
	void init(int type);			//根据僵尸的不同种类进行不同种类的初始化

	//重载
	void Draw(HDC hdc);
	void LoopFrame(bool ahead = true);
	bool LoopFrameOnce(bool ahead = true);
	//僵尸走动
	void walk();
	//僵尸攻击遇到的植物
	void attack(Plant *plant);
	//僵尸掉头  走
	void lostHeadWalk();
	//设置所有的坐标状态同步一致
	void setAllStatePos();

	void setValidY(int y) { validY = y; }
	int getValidY() { return validY; }
	//与僵尸状态获取设置相关的函数
	int getState() { return state; }
	void setState(int state);
	bool CollideWith(Plant *plant, int distance = 0);
	int getRemianLive() { return remainLive; }
	void setRemainLive(int live) { this->remainLive = live; }
private:
	int state;						//僵尸的状态
	int remainLive;					//剩余血量
	int power;						//战斗力
	T_Sprite *attackState;			//攻击状态的僵尸
	T_Sprite *boomState;			//炸死状态的僵尸
	T_Sprite *walkState;			//走动状态的僵尸
	T_Sprite *lostHeadWalkState;	//掉头走动状态的僵尸
	T_Sprite *dieState;				//死亡状态的僵尸
	T_Sprite *lostHeadAttackState;	//掉头攻击状态的僵尸
	T_Sprite *head;					//头掉落动画
	// TODO 独特的Sprite ，顺便修改
	vector<T_Sprite*> zombieStates;	//僵尸的不同状态
	unsigned int timeCount;			//控制僵尸速度
	int validY;						//僵尸所在的有效行数  从1开始
};