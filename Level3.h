#pragma once
#include "Level1.h"
class Level3 : public T_Scene
{
public:
	Level3();
	~Level3();
	void init(HWND m_hWnd);
	void initMap();
	void start(HDC hdc);			//��ʼ������Ϸ
	void loopLevelFrame();			//�ı����н�ɫ��֡��
	void updateLevelSpriteState();	//���ݳ��������н�ɫ��״̬  �����ı��ɫ����Ϊ 
	void changeSpriteState();
	void mouseMove(int x, int y);
	void mouseClick(int x, int y);
	int getClickBlock(int x, int y);
	bool Win();
	void activeZombieToAppear();
	void initSound(HWND m_hWnd);	//��ʼ����Ч
	void initZombie();				//��ʼ��level1�Ľ�ʬ
	void initBoard();				//��ʼ��ֲ�￨Ƭ��
	void handlleSpriteDead();
	void handlePlantDead();
	void handleZombieDead();
	void makeSun();			//����Զ���������
	int sunCount = 0;
	void getSun();			//�õ�̫�� ������
	void addPlant();		//��ֲ��
							//Ϊ�������ӽ�ʬ
	void addZombie(int type, int num = 1);
	//����������ʧ
	void sunDisAppear();
	//�ƶ�������غ���
	void sceneMove();
	void Draw(HDC hdc, int x, int y);
	bool judgeCanMove();


private:
	T_Map *map;						//��ͼ
	int zombiesCount[9] = { 0 };
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


	vector<Sun*> suns;				//̫����
	vector<T_Sprite*> bullet;		//��ʾ�㶹���ֵ��ӵ�

	T_Sprite *dirt;					//��ֲ��ʱ������

	PlantCardBoard pcb;
	int sunPower;					//̫������
	int startTime;
	int endTime;
	int validY;						//�ó�����Ч������λ��
	bool canPlayPre;				//��֤��ʼ����ֻ����һ��
	bool canMove;					//��־��Ϸ��ʼʱ�ĳ����ƶ�
	bool canToRight;				//��־��Ϸ���������ƶ�
	int scnMoveCount;				//���㳡���ƶ�����  �ƶ����κ�㲻���ƶ�
	int timeCount;					//��ʾ������ͣ��ʱ��
	int curentZombieNumber;			//���������еĽ�ʬ��
	int blockIndex;					//��������Ĳ�ƺ������
	bool canMakeSun;

	int winCount = 0;
};

