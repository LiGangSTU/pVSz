#pragma once
#include ".\\T_Engine\\T_Scene.h"
#include ".\\T_Engine\\T_Audio.h"
#include "Level1Grass.h"
#include "Zombie.h"
#include "PlantCardBoard.h"
#include "Plant.h"
#include "Sun.h"
#include ".\\T_Engine\\T_AI.h"
class Level1 : public T_Scene
{
public:
	Level1();
	~Level1();

public :
	void init(HWND m_hWnd);

	T_Map *map;						//��ͼ
	Level1Grass *grass;				//��ƺ
	void start(HDC hdc);			//��ʼ������Ϸ
	void loopLevelFrame();			//�ı����н�ɫ��֡��
	void updateLevelSpriteState();	//���ݳ��������н�ɫ��״̬  �����ı��ɫ����Ϊ 
	void changeSpriteState();
	void mouseMove(int x, int y);
	void mouseClick(int x, int y);
	int getClickBlock(int x, int y);
	bool Win();
	void activeZombieToAppear();
protected:
	int zombiesCount[5] = {0};
protected: 
	//�����ɫ������
	void handlleSpriteDead();
	void handlePlantDead();
	void handleZombieDead();
	void makeSun();			//����Զ���������
	int sunCount = 0;
	void getSun();			//�õ�̫�� ������
	void addPlant();		//��ֲ��

	//�ƶ�������غ���
	void sceneMove();
	void Draw(HDC hdc, int x, int y);
	bool judgeCanMove();
	//��س�ʼ������
	void initMap();					//��ʼ����ͼ
	void initGrass();				//��ʼ����ƺ
	void initSound(HWND m_hWnd);	//��ʼ����Ч
	void initZombie();				//��ʼ��level1�Ľ�ʬ
	void initBoard();				//��ʼ��ֲ�￨Ƭ��
	//�����ƺ�̿�����
	void activeGrass(HDC hdc);
	//Ϊ�������ӽ�ʬ
	void addZombie(int type, int num = 1);
	//����������ʧ
	void sunDisAppear();

protected:
	AudioDX ds;									//DirectSound����
	AudioDXBuffer adventureGamePre_buffer;		//ð����Ϸ��ʼǰ��Ч
	AudioDXBuffer gameRunMenuMouseClick_buffer;	//��Ϸ����ʱ����˵���Ч
	AudioDXBuffer gameBgm_buffer;				//��Ϸ��������
	AudioDXBuffer plant1_buffer;		
	AudioDXBuffer plant2_buffer;		//��ֲֲ������
	vector<Zombie*> zombies;			//�����еĽ�ʬ����
	vector<GAMELAYER> zombieLayers;		//��ʬͼ��

	HWND hwnd;			//���洰�ھ��   Ϊ����ģ���ʼ������

	vector<GAMELAYER> plantLayers;		//ֲ��ͼ��
	vector<Plant*> plants;				//�����е�ֲ��
	Plant* plant;						//��ʾѡ��ֲ��

	vector<T_Sprite*> bullet;		//��ʾ�㶹���ֵ��ӵ�

	vector<Sun*> suns;				//̫����
	T_AI *myAI;
	int plantsCount;

	T_Sprite *dirt;					//��ֲ��ʱ������

	PlantCardBoard pcb;
	int sunPower;					//̫������
	int startTime;
	int validY;						//�ó�����Ч������λ��
	bool canPlayPre;				//��֤��ʼ����ֻ����һ��
	bool canActiveGrass;			//��ʾ�ܹ������ƺ�Ķ���
	bool canMove;					//��־��Ϸ��ʼʱ�ĳ����ƶ�
	bool canToRight;				//��־��Ϸ���������ƶ�
	int scnMoveCount;				//���㳡���ƶ�����  �ƶ����κ�㲻���ƶ�
	int timeCount;					//��ʾ������ͣ��ʱ��
	int curentZombieNumber;			//���������еĽ�ʬ��
	int blockIndex;					//��������Ĳ�ƺ������
	bool canMakeSun;

	int winCount = 0;
};

