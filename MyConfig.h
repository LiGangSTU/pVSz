#pragma once
#include ".\\T_Engine\\T_Engine.h"
/***************************************************************************************************************/
//��Ϸ��ʼ�˵��������
static const wstring STARTMENU_BACK = L".\\res\\startMenu\\Surface.png";				//����ͼƬ·��

static const wstring ADVANTURE_MENU = L".\\res\\startMenu\\Adventure.png";				//ð����Ϸ�˵����ͼƬ
static const wstring ADVENTURE_MENU_SHADOW = L".\\res\\startMenu\\AdventureShadow.png";	//ð����Ϸ�˵�����ӰͼƬ

static const wstring MINI_MENU = L".\\res\\startMenu\\Mini.png";				//������Ϸ�˵����ͼƬ
static const wstring MINI_MENU_SHADOW = L".\\res\\startMenu\\MiniShadow.png";	//������Ϸ�˵�����ӰͼƬ

static const wstring QUIZ_MENU = L".\\res\\startMenu\\Quiz.png";				//������Ϸ�˵����ͼƬ
static const wstring QUIZ_MENU_SHADOW = L".\\res\\startMenu\\QuizShadow.png";	//������Ϸ�˵�����ӰͼƬ	

static const wstring HANDBOOK_MENU = L".\\res\\startMenu\\HandBook.png";		//ͼ��ͼƬ

static const wstring HELP_MENU = L".\\res\\startMenu\\HelpMenu.png";			//����ͼƬ
static const wstring OPTION_MENU = L".\\res\\startMenu\\aboutMenu.png";			//ѡ��ͼƬ
static const wstring QUIT_MENU = L".\\res\\startMenu\\QuitMenu.png";			//�˳�ͼƬ
static const wstring ABOUT_MENU_BG = L".\\res\\aboutMenu\\AboutMenu.png";
/****************************************************************************************************************/



/**************************************************************************************************************/
//������Դ�������
static const wstring START_MENU_MOVE_MUSIC = L".\\res\\sound\\startMenuMove.wav";		//�˵��ƶ���Ч
static const wstring START_MENU_BGM_MUSIC = L".\\res\\sound\\startMenuBgm.wav";			//��ʼ�˵���������
static const wstring GAME_MENU_CLICK_MUSIC = L".\\res\\sound\\gameMenuClick.wav";		//��Ϸ����˵������Ч
static const wstring ENTERGAME_MUSIC = L".\\res\\sound\\enterGame.wav";					//������Ϸ��ʬ�ֳ�����Ч
static const wstring START_MENU_CLICK_MUSIC = L".\\res\\sound\\startMenuClick.wav";		//��ʼ�˵������Ч
static const wstring QUITGAME_MENU_CLICK_MUSIC = L".\\res\\sound\\graveMenuClick.wav";	//Ĺ���˵������Ч
static const wstring LOSEGAME_MUSIC = L".\\res\\sound\\loseGame.wav";					//��Ϸʧ����Ч
static const wstring ADVENTURE_GAME_PRE = L".\\res\\sound\\advantureGamePre.wav";		//ð����Ϸ��ʼʱ����Ч
static const wstring SEED_SELECT = L".\\res\\sound\\seedlift.wav";
static const wstring PLANT1 = L".\\res\\sound\\plant1.wav";
static const wstring PLANT2 = L".\\res\\sound\\plant2.wav";
static const wstring SHOOTER_MUSIC = L".\\res\\sound\\shoop.wav";
static const wstring HIT_MUSIC1 = L".\\res\\sound\\kernelpult.wav";
static const wstring HIT_MUSIC2 = L".\\res\\sound\\kernelpult2.wav";
static const wstring WIN_MUSIC = L".\\res\\sound\\winmusic.wav";
/**************************************************************************************************************/




/************************************************************************************************************/
//�˳���Ϸ�˵��������
static const wstring QUITGAME_BG = L".\\res\\quitMenu\\quitBg.png";				//�˳��˵��е�ȡ����ť
static const wstring QUITGAME_MENU = L".\\res\\quitMenu\\quitMenu.png";			//�˳��˵��е��˳���ť
static const wstring CANCEL_MENU = L".\\res\\quitMenu\\cancelMenu.png";			//�˳��˵��е�ȡ����ť
/************************************************************************************************************/

/************************************************************************************************************/
//�����˵��������
static const wstring HELP_MENU_BG = L".\\res\\helpMenu\\helpBg.png";			//�����˵��еı���ͼƬ
static const wstring HELP_MENU_INFO = L".\\res\\helpMenu\\helpInfo.png";		//�����˵��еİ�����ϢͼƬ
static const wstring HELP_MENU_MAINMANU = L".\\res\\helpMenu\\mainMenu.png";	//�ص������水ťͼƬ
/************************************************************************************************************/


/************************************************************************/
//��ɫ�������
static const wstring ZOMBIEHAND = L".\\res\\startMenu\\ZombieHand.png";					//��ʬ��ͼƬ
static const int ZOMBIEHAND_REMAIN_TIME = 255;											//��ʬ��ά��ʱ��
static int ZOMBIEHAND_FRAME[26] = {0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6};
/************************************************************************/


/************************************************************************/
//�ؿ�2
static wchar_t* LEVEL2_MAP = L".\\res\\levels\\level2\\bg.jpg"; //bg1.jpg;			//level2��ͼ
static const int LEVEL2_ZOMBIE_NUMBER = 9;
static const int LEVEL2_ZOMBIE_APPEAR_Y[5] = { 10, 108, 216, 314, 412 };
static int LEVEL2_ZOMBIE_APPEAR_X[9] = { 1080,1110, 1130, 1180, 1230, 1280, 1330, 1380, 1430 };
/************************************************************************/

/************************************************************************/
//�ؿ�3                                                                  
static wchar_t* LEVEL3_MAP = L".\\res\\levels\\level3\\bg.jpg"; //bg1.jpg;			//level3��ͼ
// TODO ��������ݵ����
/************************************************************************/

/**************************************************************************************************************************/
//�ؿ�1
static wchar_t* LEVEL1_MAP = L".\\res\\levels\\level1\\bg2.jpg"; //bg1.jpg;			//level1��ͼ
static const int LEVEL1_SCENEWIDTH = 1500;//1400;
static const int LEVEL1_SCENEHEIGHT = 600;
static const wstring LEVEL1_GRASS = L".\\res\\levels\\level1\\sod2row.png";		//level1��ƺ
static const int LEVEL_START_POS_X = 210;
static const wstring LEVEL1_DIRT = L".\\res\\levels\\level1\\dirt.png";			//����ͼƬ
static const wstring LEVEL1_SODROLL = L".\\res\\levels\\level1\\SodRoll.png";	//��ƺ��ͼƬ
static int LEVEL1_DIRT_FRAME[25] = { 0, 0, 0, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5};
static const wstring DIRT_MUSIC = L".\\res\\sound\\dirt_rise.wav";
static const wstring GAME_LEVEL1_BG_MUSIC = L".\\res\\sound\\level1GameBgm.wav";
static const int LEVEL1_ZOMBIE_NUMBER = 5;
static const int NORMAL_ZOMBIE_SPEED = 1;
static const int NORMAL_ZOMBIE_POWER = 250;
static const int NORMAL_ZOMBIE_LIVE = 1000;
static const int ZOMBIE_APPEAR_Y[5] = {10, 108, 216, 314, 412};
static const int ZOMBIE_APPEAR_X[8] = {1080, 1130, 1180, 1230, 1280, 1330, 1380, 1430};

static const int LEVEL2_VALID_BLOCKNUMBER = 27;
static int LEVEL2_VALID_BLOCKPOS[27][4] =
{
	{ 60,154,90,85 },
	{ 150,154,77,85 },
	{ 227,154,98,85 },
	{ 325,154,83,85 },
	{ 408,154,83,85 },
	{ 491,154,94,85 },
	{ 585,154,77,85 },
	{ 662,154,92,85 },
	{ 754,154,104,85 },

	{ 60,254,90,85 },
	{ 150,254,77,85 },
	{ 227,254,98,85 },
	{ 325,254,83,85 },
	{ 408,254,83,85 },
	{ 491,254,94,85 },
	{ 585,254,77,85 },
	{ 662,254,92,85 },
	{ 754,254,104,85 },

	{ 60,354,90,85 },
	{ 150,354,77,85 },
	{ 227,354,98,85 },
	{ 325,354,83,85 },
	{ 408,354,83,85 },
	{ 491,354,94,85 },
	{ 585,254,77,85 },
	{ 662,254,92,85 },
	{ 754,354,104,85 },
};

static const int LEVEL3_VALID_BLOCKNUMBER = 45;
static int LEVEL3_VALID_BLOCKPOS[45][4]=
{
	// ��һ��
	{ 60,70,90,85 },
	{ 150,70,77,85 },
	{ 227,70,98,85 },
	{ 325,70,83,85 },
	{ 408,70,83,85 },
	{ 491,70,94,85 },
	{ 585,70,77,85 },
	{ 662,70,92,85 },
	{ 754,70,104,85 },
	// �ڶ���
	{ 60,154,90,85 },
	{ 150,154,77,85 },
	{ 227,154,98,85 },
	{ 325,154,83,85 },
	{ 408,154,83,85 },
	{ 491,154,94,85 },
	{ 585,154,77,85 },
	{ 662,154,92,85 },
	{ 754,154,104,85 },

	{ 60,254,90,85 },
	{ 150,254,77,85 },
	{ 227,254,98,85 },
	{ 325,254,83,85 },
	{ 408,254,83,85 },
	{ 491,254,94,85 },
	{ 585,254,77,85 },
	{ 662,254,92,85 },
	{ 754,254,104,85 },

	{ 60,354,90,85 },
	{ 150,354,77,85 },
	{ 227,354,98,85 },
	{ 325,354,83,85 },
	{ 408,354,83,85 },
	{ 491,354,94,85 },
	{ 585,354,77,85 },
	{ 662,354,92,85 },
	{ 754,354,104,85 },

	{ 60,454,90,85 },
	{ 150,454,77,85 },
	{ 227,454,98,85 },
	{ 325,454,83,85 },
	{ 408,454,83,85 },
	{ 491,454,94,85 },
	{ 585,454,77,85 },
	{ 662,454,92,85 },
	{ 754,454,104,85 },
};

static int LEVEL1_VALID_BLOCKPOS[9][4]=
{
	{60,254,90,85 },
	{150,254,77,85 },
	{227,254,98,85 },
	{325,254,83,85 },
	{408,254,83,85 },
	{491,254,94,85 },
	{585,254,77,85 },
	{662,254,92,85 },
	{754,254,104,85 },
};
static const int LEVEL1_VALID_BLOCKNUMBER = 9;

//	�����ͨ��ʬ��������̬
typedef struct
{
	wstring img;
	int frameWidth;
	int frameHeight;
}ZOMBIEINFO, PLANTINFO;
/*static const int RANDOM_NORMAL_ZOMBIE_TYPE[2] = { 0, 1};*/
static ZOMBIEINFO normalZombieStatic[3] =
{
	{ L".\\res\\zombie\\normalZombie\\normalZombieStatic1.png", 166, 144 },
	{ L".\\res\\zombie\\normalZombie\\normalZombieStatic2.png", 166, 144 },
	{ L".\\res\\zombie\\normalZombie\\normalZombieStatic3.png", 166, 144 }
};
static int NORMAL_ZOMBIE_STATIC_FRAME[3][132] = 
{
	{
		0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,
		2,2,2,2,2,2,2,2,2,2,2,2,
		3,3,3,3,3,3,3,3,3,3,3,3,
		4,4,4,4,4,4,4,4,4,4,4,4,
		5,5,5,5,5,5,5,5,5,5,5,5,
		6,6,6,6,6,6,6,6,6,6,6,6,
		7,7,7,7,7,7,7,7,7,7,7,7,
		8,8,8,8,8,8,8,8,8,8,8,8,
		9,9,9,9,9,9,9,9,9,9,9,9,
		10,10,10,10,10,10,10,10,10,10,10,10,
	},
	{
		0,0,0,0,0,0,
		1,1,1,1,1,1,
		2,2,2,2,2,2,
		3,3,3,3,3,3,
		4,4,4,4,4,4,
		5,5,5,5,5,5,
		6,6,6,6,6,6,
		7,7,7,7,7,7,
		8,8,8,8,8,8,
		9,9,9,9,9,9,
		10,10,10,10,10,10,
		11,11,11,11,11,11,
		12,12,12,12,12,12,
		13,13,13,13,13,13,
		14,14,14,14,14,14,
		15,15,15,15,15,15,
		16,16,16,16,16,16,
		17,17,17,17,17,17,
		18,18,18,18,18,18,
		19,19,19,19,19,19,
		20,20,20,20,20,20,
		21,21,21,21,21,21,
	},
	{
		0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,
		2,2,2,2,2,2,2,2,2,2,2,2,
		3,3,3,3,3,3,3,3,3,3,3,3,
		4,4,4,4,4,4,4,4,4,4,4,4,
		5,5,5,5,5,5,5,5,5,5,5,5,
		6,6,6,6,6,6,6,6,6,6,6,6,
		7,7,7,7,7,7,7,7,7,7,7,7,
		8,8,8,8,8,8,8,8,8,8,8,8,
		9,9,9,9,9,9,9,9,9,9,9,9,
		10,10,10,10,10,10,10,10,10,10,10,10,
	},
};
static ZOMBIEINFO normalZombieWalk[3] =
{
	{ L".\\res\\zombie\\normalZombie\\normalZombieWalk1.png", 166, 144 },
	{ L".\\res\\zombie\\normalZombie\\normalZombieWalk2.png", 166, 144 },
	{ L".\\res\\zombie\\normalZombie\\normalZombieWalk3.png", 166, 144 }
};
static int NORMAL_ZOMBIE_WALK_FRAME[3][132] = 
{
	{
		0,0,0,0,0,0,
		1,1,1,1,1,1,
		2,2,2,2,2,2,
		3,3,3,3,3,3,
		4,4,4,4,4,4,
		5,5,5,5,5,5,
		6,6,6,6,6,6,
		7,7,7,7,7,7,
		8,8,8,8,8,8,
		9,9,9,9,9,9,
		10,10,10,10,10,10,
		11,11,11,11,11,11,
		12,12,12,12,12,12,
		13,13,13,13,13,13,
		14,14,14,14,14,14,
		15,15,15,15,15,15,
		16,16,16,16,16,16,
		17,17,17,17,17,17,
		18,18,18,18,18,18,
		19,19,19,19,19,19,
		20,20,20,20,20,20,
		21,21,21,21,21,21,
	},
	{
		0,0,0,0,0,
		1,1,1,1,1,
		2,2,2,2,2,
		3,3,3,3,3,
		4,4,4,4,4,
		5,5,5,5,5,
		6,6,6,6,6,
		7,7,7,7,7,
		8,8,8,8,
		9,9,9,9,
		10,10,10,10,
		11,11,11,11,
		12,12,12,12,
		13,13,13,13,
		14,14,14,14,
		15,15,15,15,
		16,16,16,16,
		17,17,17,17,
		18,18,18,18,
		19,19,19,19,
		20,20,20,20,
		21,21,21,21,
		22,22,22,22,
		23,23,23,23,
		24,24,24,24,
		25,25,25,25,
		26,26,26,26,
		27,27,27,27,
		28,28,28,28,
		29,29,29,29,
		30,30,30,30,
	},
	{
		0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,
		2,2,2,2,2,2,2,2,
		3,3,3,3,3,3,3,3,
		4,4,4,4,4,4,4,4,
		5,5,5,5,5,5,5,5,
		6,6,6,6,6,6,6,
		7,7,7,7,7,7,7,
		8,8,8,8,8,8,8,
		9,9,9,9,9,9,9,
		10,10,10,10,10,10,10,
		11,11,11,11,11,11,11,
		12,12,12,12,12,12,12,
		13,13,13,13,13,13,13,
		14,14,14,14,14,14,14,
		15,15,15,15,15,15,15,
		16,16,16,16,16,16,16,
		17,17,17,17,17,17,17
	},
};


static ZOMBIEINFO normalZombieAttack = { L".\\res\\zombie\\normalZombie\\normalZombieAttack.png", 166, 144 };
static int NORMAL_ZOMBIE_ATTACK_FRAME[132] = 
{
	0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,
	6,6,6,6,6,6,
	7,7,7,7,7,7,
	8,8,8,8,8,8,
	9,9,9,9,9,9,
	10,10,10,10,10,10,
	11,11,11,11,11,11,
	12,12,12,12,12,12,
	13,13,13,13,13,13,
	14,14,14,14,14,14,
	15,15,15,15,15,15,
	16,16,16,16,16,16,
	17,17,17,17,17,17,
	18,18,18,18,18,18,
	19,19,19,19,19,19,
	20,20,20,20,20,20,
};
static ZOMBIEINFO zombieBoomDie = { L".\\res\\zombie\\zombieBoomDie.png", 166, 144 };
static int ZOMBIE_BOOM_DIE_FRAME[132] = 
{
	0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,
	7,7,7,7,7,7,7, 
	8,8,8,8,8,8,8,
	9,9,9,9,9,9,9,
	10,10,10,10,10,10,10,
	11,11,11,11,11,11,11,
	12,12,12,12,12,12,
	13,13,13,13,13,13,
	14,14,14,14,14,14,
	15,15,15,15,15,15,
	16,16,16,16,16,16,
	17,17,17,17,17,17,
	18,18,18,18,18,18,
	19,19,19,19,19,19,
};
static ZOMBIEINFO zombieDie = { L".\\res\\zombie\\zombieDie.png", 166, 144 };
static int NORMAL_ZOMBIE_DIE[132]=
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,8,8,8,8,8,8,
	9,9,9,9,9,9,9,9,9,9,9,9,9,
};
static ZOMBIEINFO zombieHead = { L".\\res\\zombie\\zombieHead.png", 150, 186 };
static int NORMAL_ZOMBIE_HEAD[132]=
{
	0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,8,8,8,8,
	9,9,9,9,9,9,9,9,9,9,9,
	10,10,10,10,10,10,10,10,10,10,10,
	11,11,11,11,11,11,11,11,11,11,11,
};
static ZOMBIEINFO zombieLostHead = { L".\\res\\zombie\\zombieLostHead.png", 166, 144 };
static int NORMAL_ZOMBIE_LOSTHEAD_WALK[132] =
{
	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,
	9,9,9,9,9,9,9,
	10,10,10,10,10,10,10,
	11,11,11,11,11,11,11,
	12,12,12,12,12,12,12,
	13,13,13,13,13,13,13,
	14,14,14,14,14,14,14,
	15,15,15,15,15,15,15,
	16,16,16,16,16,16,16,
	17,17,17,17,17,17,17
};
static ZOMBIEINFO zombieLostHeadAttack = { L".\\res\\zombie\\zombieLostHeadAttack.png", 166, 144 };
static int NORMAL_ZOMBIE_LOSTHEAD_ATTACK[132] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,8,8,8,8,8,
	9,9,9,9,9,9,9,9,9,9,9,9,
	10,10,10,10,10,10,10,10,10,10,10,10,
};
/****************************************************************************************************************************/

/************************************************************************/
//ֲ�￨Ƭ�������
static const wstring CARDBOARD = L".\\res\\cardBoard\\cardBoard.png";			//ֲ�￨Ƭ�˵�ͼƬ
static const wstring TEXTBG = L".\\res\\cardBoard\\textBg.png";
static const wstring SUNFLOWER_CARD = L".\\res\\cardBoard\\SunFlower.png";		//̫����
static const wstring PEASHOOTER_CARD = L".\\res\\cardBoard\\Peashooter.png";	//�㶹����
static const wstring WALLNUT_CARD = L".\\res\\cardBoard\\WallNut.png";			//С���
static const wstring SQUASH_CARD = L".\\res\\cardBoard\\Squash.png";			//����
static const wstring POTATO_CARD = L".\\res\\cardBoard\\PotatoMine.png";		//����



/************************************************************************/

typedef struct  
{
	int		width;				// �˵����
	int		height;				// �˵��߶�
	POINT	pos;				// �˵�λ��
	T_Graph *btn;				// �˵���ťͼƬ
	bool	isFocused;			// ��ǰ�˵����Ƿ�ѡ��
	int		waitTime;			// �˵���ȴʱ��
	int		type;				// ֲ��˵�����
	int		costPower;			// ���ĵ�����
	wstring name;				// ֲ�������
	int     state;				// ֲ����״̬		0��ʾ��ȴ   1��ʾ��ȴ���
	int		quiteCount;			// ��ȴ��ʱ
}MYSTARTMENUINFO;

// ��ʬ����
// TODO �޸Ľ�ʬ������
enum ZOMBIE_TYPE
{
	NORMAL_ZOMBIE,		//��ͨ��ʬ
	BUCKETHEAD_ZOMBIE,	//��Ͱ��ʬ
	CONEHEAD_ZOMBIE,	//ľͰ��ʬ
	FLAG_ZOMBIE,		//���ֽ�ʬ
	FOOTBAL_ZOMBIE		//�����ʬ
};

enum ZOMBIE_STATE
{
	STATIC_STATE,			//վ��״̬
	WALK_STATE,				//�߶�״̬
	ATTACK_STATE,			//����״̬
	BOOM_STATE,				//ը��״̬
	LOSTHEADWALK_STATE,		//��ͷ�߶�״̬
	LOSTHEADATTACK_STATE,	//��ͷ����״̬
	DIE_STATE,				//����״̬
	DISAPPEAR_STATE			//��ʬ��ʧ״̬
};

enum PLANT_STATE
{
	PLANT_STATIC_STATE,		//ֲ�ﾲֹ״̬
	PLANT_STAND_STATE,		//ֲ��վ��״̬
	PLANT_SHOOT_STATE,		//ֲ�﷢��״̬
	PLANT_BOOM_STATE,		//ֲ�ﱬը״̬
	PLANT_SUN_STATE,		//ֲ������״̬
	PLANT_DEAD,				//ֲ������
};

enum PLANT_TYPE
{
	PEASHOOTER,		//�㶹����
	SUNFLOWER,		//���տ�
	WALLNUT,		//С���
	POTATO,			//����
	SQUASH,			//����
	CHERRY			//ӣ��ը��
};
// �ȴ�ʱ��
static const int WAITTIME[6] = {6, 5, 8, 6, 6, 6};
// ��������
static const int COSTSUN[6]={100, 50, 50, 50, 50, 50};
// ����ֵ
static const int PLANTE_REMAINLIVE[6] = {1400, 1400, 6000, 1400, 1400, 1400};
// ����
static const int PLANT_DEFENCE[6] = {100, 100, 1000, 10000, 10000, 10000};
// ������
static const int PLANT_POWER[6] = {150, 0, 0, 0, 10000000, 100000000};
// �㶹ͼƬ
static const wstring PEASHOOTER_WEAPON = L".\\res\\plant\\peashooter\\bullet.png";
// ����ͼƬ
static const wstring PEASHOOTER_WEAPON_HIT = L".\\res\\plant\\peashooter\\bulletHit.png";

//ֲ�ﾲֹͼƬ
static const wstring plantStatic[6]=
{
	L".\\res\\plant\\peashooter\\peaShooterStatic.png",
	L".\\res\\plant\\SunFlower\\SunFlowerStatic.png",
	L".\\res\\plant\\wallnut\\wallNutStatic.png",
	L".\\res\\plant\\SunFlower\\SunFlowerStatic.png",
	L".\\res\\plant\\SunFlower\\SunFlowerStatic.png",
	L".\\res\\plant\\SunFlower\\SunFlowerStatic.png",
};


//������֡ͼ
static PLANTINFO SUNPIC = { L".\\res\\plant\\sun\\sun.png", 79, 79 };

static int SUNFLOWERSTAND_FRAME[132]=
{
	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,
	9,9,9,9,9,9,9,
	10,10,10,10,10,10,10,
	11,11,11,11,11,11,11,
	12,12,12,12,12,12,12,
	13,13,13,13,13,13,13,
	14,14,14,14,14,14,14,
	15,15,15,15,15,15,15,
	16,16,16,16,16,16,16,
	17,17,17,17,17,17,17
};
static int SUNFLOWERWORK_FRAME[132]=
{
	18,18,18,18,18,18,18,18,
	19,19,19,19,19,19,19,19,
	20,20,20,20,20,20,20,20,
	21,21,21,21,21,21,21,21,
	22,22,22,22,22,22,22,22,
	23,23,23,23,23,23,23,23,
	24,24,24,24,24,24,24,
	25,25,25,25,25,25,25,
	26,26,26,26,26,26,26,
	27,27,27,27,27,27,27,
	28,28,28,28,28,28,28,
	29,29,29,29,29,29,29,
	30,30,30,30,30,30,30,
	31,31,31,31,31,31,31,
	32,32,32,32,32,32,32,
	33,33,33,33,33,33,33,
	34,34,34,34,34,34,34,
	35,35,35,35,35,35,35,
};
static const int SUN_RECIEVE_X = 10;
// ֲ���ز�
static PLANTINFO PLANTSTAND[6]=
{
	{L".\\res\\plant\\peashooter\\Peashooter.png", 71, 71},
	{ L".\\res\\plant\\SunFlower\\SunFlower.png", 73, 74 },
	{ L".\\res\\plant\\wallnut\\wallNut1.png", 65, 73 },
	{ L".\\res\\plant\\peashooter\\Peashooter.png", 71, 71 },
	{ L".\\res\\plant\\peashooter\\Peashooter.png", 71, 71 },
	{ L".\\res\\plant\\peashooter\\Peashooter.png", 71, 71 },
};

// �㶹�����ز�
static int PEASHOOTERSTAND_FRAME[132]=
{
	0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,8,8,8,
	9,9,9,9,9,9,9,9,9,9,
	10,10,10,10,10,10,10,10,10,10,
	11,11,11,11,11,11,11,11,11,11,
	12,12,12,12,12,12,12,12,12,12,
};

// ���ǽͼƬ֡
static int WALLNUT_FRAME[132] =
{
	0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,
	3,3,3,3,3,3,3,3,
	4,4,4,4,4,4,4,4,
	5,5,5,5,5,5,5,5,
	6,6,6,6,6,6,6,6,6,
	7,7,7,7,7,7,7,7,7,
	8,8,8,8,8,8,8,8,8,
	9,9,9,9,9,9,9,9,9,
	10,10,10,10,10,10,10,
	11,11,11,11,11,11,11,
	12,12,12,12,12,12,12,
	13,13,13,13,13,13,13,
	14,14,14,14,14,14,14,
	15,15,15,15,15,15,15,
};
//�ؿ���־
enum LEVEL_CLASS
{
	LEVEL_1,
	LEVEL_1_2,
	LEVEL_2,
	LEVEL_2_3,
	LEVEL_3,
	LEVEL_3_4,
	LEVEL_4,
	LEVEL_4_5,
	LEVEL_5,
};
// ����ͼƬ�ز�
static const wstring PASSMENUBG = L".\\res\\passMenu\\AwardScreen_Back.jpg";
static const wstring PASSMENU = L".\\res\\passMenu\\nextLevel.png";