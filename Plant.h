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
	AudioDX ds;									//DirectSound����
	AudioDXBuffer shooter_buffer;		//�㶹������Ч
	AudioDXBuffer hit1_buffer;
	AudioDXBuffer hit2_buffer;
/*	T_Sprite *staticState;		//��ֹ״̬	��Ƭ��ֹ��״̬*/
	T_Sprite *standState;		//ֲ����ֲʱ״̬
	T_Sprite *workState;		//ֲ��Ĺ���״̬
	T_Sprite *weapon;			//ֲ��Ľ�������
	T_Sprite *weaponHit;		//�������н�ʬ
	int power;					//ս����
	int type;					//ֲ������
	int defence;				//����ֵ
	int state;					//״̬
	int remainLive;				//ʣ��Ѫ��
	int costSun;				//���ĵ�̫��
	int validY;					//ֲ�����ڵ���Ч����  ��1��ʼ

	int weaponCount;			//���Ʒ����ʱ��
	int startTime;
	int endTime;
};

