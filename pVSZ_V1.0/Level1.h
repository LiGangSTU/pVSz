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

	T_Map *map;						//地图
	Level1Grass *grass;				//草坪
	void start(HDC hdc);			//开始本关游戏
	void loopLevelFrame();			//改变所有角色的帧数
	void updateLevelSpriteState();	//根据场景中所有角色的状态  进而改变角色的行为 
	void changeSpriteState();
	void mouseMove(int x, int y);
	void mouseClick(int x, int y);
	int getClickBlock(int x, int y);
	bool Win();
	void activeZombieToAppear();
protected:
	int zombiesCount[5] = {0};
protected: 
	//处理角色的死亡
	void handlleSpriteDead();
	void handlePlantDead();
	void handleZombieDead();
	void makeSun();			//随机自动增加阳光
	int sunCount = 0;
	void getSun();			//得到太阳 加能量
	void addPlant();		//种植物

	//移动场景相关函数
	void sceneMove();
	void Draw(HDC hdc, int x, int y);
	bool judgeCanMove();
	//相关初始化函数
	void initMap();					//初始化地图
	void initGrass();				//初始化草坪
	void initSound(HWND m_hWnd);	//初始化音效
	void initZombie();				//初始化level1的僵尸
	void initBoard();				//初始化植物卡片条
	//激活草坪铺开动画
	void activeGrass(HDC hdc);
	//为场景增加僵尸
	void addZombie(int type, int num = 1);
	//场景阳光消失
	void sunDisAppear();

protected:
	AudioDX ds;									//DirectSound对象
	AudioDXBuffer adventureGamePre_buffer;		//冒险游戏开始前音效
	AudioDXBuffer gameRunMenuMouseClick_buffer;	//游戏运行时点击菜单音效
	AudioDXBuffer gameBgm_buffer;				//游戏背景音乐
	AudioDXBuffer plant1_buffer;		
	AudioDXBuffer plant2_buffer;		//种植植物音乐
	vector<Zombie*> zombies;			//场景中的僵尸集合
	vector<GAMELAYER> zombieLayers;		//僵尸图层

	HWND hwnd;			//保存窗口句柄   为其他模块初始化音乐

	vector<GAMELAYER> plantLayers;		//植物图层
	vector<Plant*> plants;				//场景中的植物
	Plant* plant;						//表示选中植物

	vector<T_Sprite*> bullet;		//表示豌豆射手的子弹

	vector<Sun*> suns;				//太阳光
	T_AI *myAI;
	int plantsCount;

	T_Sprite *dirt;					//种植物时的泥土

	PlantCardBoard pcb;
	int sunPower;					//太阳能量
	int startTime;
	int validY;						//该场景有效的坐标位置
	bool canPlayPre;				//保证开始音乐只播放一次
	bool canActiveGrass;			//表示能够激活草坪的动画
	bool canMove;					//标志游戏开始时的场景移动
	bool canToRight;				//标志游戏场景向左移动
	int scnMoveCount;				//计算场景移动次数  移动两次后便不再移动
	int timeCount;					//表示场景的停留时间
	int curentZombieNumber;			//描述场景中的僵尸数
	int blockIndex;					//描述点击的草坪块索引
	bool canMakeSun;

	int winCount = 0;
};

