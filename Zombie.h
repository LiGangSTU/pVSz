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
	void init(int type);			//���ݽ�ʬ�Ĳ�ͬ������в�ͬ����ĳ�ʼ��

	//����
	void Draw(HDC hdc);
	void LoopFrame(bool ahead = true);
	bool LoopFrameOnce(bool ahead = true);
	//��ʬ�߶�
	void walk();
	//��ʬ����������ֲ��
	void attack(Plant *plant);
	//��ʬ��ͷ  ��
	void lostHeadWalk();
	//�������е�����״̬ͬ��һ��
	void setAllStatePos();

	void setValidY(int y) { validY = y; }
	int getValidY() { return validY; }
	//�뽩ʬ״̬��ȡ������صĺ���
	int getState() { return state; }
	void setState(int state);
	bool CollideWith(Plant *plant, int distance = 0);
	int getRemianLive() { return remainLive; }
	void setRemainLive(int live) { this->remainLive = live; }
private:
	int state;						//��ʬ��״̬
	int remainLive;					//ʣ��Ѫ��
	int power;						//ս����
	T_Sprite *attackState;			//����״̬�Ľ�ʬ
	T_Sprite *boomState;			//ը��״̬�Ľ�ʬ
	T_Sprite *walkState;			//�߶�״̬�Ľ�ʬ
	T_Sprite *lostHeadWalkState;	//��ͷ�߶�״̬�Ľ�ʬ
	T_Sprite *dieState;				//����״̬�Ľ�ʬ
	T_Sprite *lostHeadAttackState;	//��ͷ����״̬�Ľ�ʬ
	T_Sprite *head;					//ͷ���䶯��
	// TODO ���ص�Sprite ��˳���޸�
	vector<T_Sprite*> zombieStates;	//��ʬ�Ĳ�ͬ״̬
	unsigned int timeCount;			//���ƽ�ʬ�ٶ�
	int validY;						//��ʬ���ڵ���Ч����  ��1��ʼ
};