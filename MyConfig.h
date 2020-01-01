#pragma once
#include ".\\T_Engine\\T_Engine.h"
/***************************************************************************************************************/
//游戏开始菜单相关设置
static const wstring STARTMENU_BACK = L".\\res\\startMenu\\Surface.png";				//背景图片路径

static const wstring ADVANTURE_MENU = L".\\res\\startMenu\\Adventure.png";				//冒险游戏菜单项背景图片
static const wstring ADVENTURE_MENU_SHADOW = L".\\res\\startMenu\\AdventureShadow.png";	//冒险游戏菜单项阴影图片

static const wstring MINI_MENU = L".\\res\\startMenu\\Mini.png";				//迷你游戏菜单项背景图片
static const wstring MINI_MENU_SHADOW = L".\\res\\startMenu\\MiniShadow.png";	//迷你游戏菜单项阴影图片

static const wstring QUIZ_MENU = L".\\res\\startMenu\\Quiz.png";				//益智游戏菜单项背景图片
static const wstring QUIZ_MENU_SHADOW = L".\\res\\startMenu\\QuizShadow.png";	//益智游戏菜单项阴影图片	

static const wstring HANDBOOK_MENU = L".\\res\\startMenu\\HandBook.png";		//图鉴图片

static const wstring HELP_MENU = L".\\res\\startMenu\\HelpMenu.png";			//帮助图片
static const wstring OPTION_MENU = L".\\res\\startMenu\\aboutMenu.png";			//选项图片
static const wstring QUIT_MENU = L".\\res\\startMenu\\QuitMenu.png";			//退出图片
static const wstring ABOUT_MENU_BG = L".\\res\\aboutMenu\\AboutMenu.png";
/****************************************************************************************************************/



/**************************************************************************************************************/
//音乐资源相关设置
static const wstring START_MENU_MOVE_MUSIC = L".\\res\\sound\\startMenuMove.wav";		//菜单移动音效
static const wstring START_MENU_BGM_MUSIC = L".\\res\\sound\\startMenuBgm.wav";			//开始菜单背景音乐
static const wstring GAME_MENU_CLICK_MUSIC = L".\\res\\sound\\gameMenuClick.wav";		//游戏界面菜单点击音效
static const wstring ENTERGAME_MUSIC = L".\\res\\sound\\enterGame.wav";					//进入游戏僵尸手出现音效
static const wstring START_MENU_CLICK_MUSIC = L".\\res\\sound\\startMenuClick.wav";		//开始菜单点击音效
static const wstring QUITGAME_MENU_CLICK_MUSIC = L".\\res\\sound\\graveMenuClick.wav";	//墓碑菜单点击音效
static const wstring LOSEGAME_MUSIC = L".\\res\\sound\\loseGame.wav";					//游戏失败音效
static const wstring ADVENTURE_GAME_PRE = L".\\res\\sound\\advantureGamePre.wav";		//冒险游戏开始时的音效
static const wstring SEED_SELECT = L".\\res\\sound\\seedlift.wav";
static const wstring PLANT1 = L".\\res\\sound\\plant1.wav";
static const wstring PLANT2 = L".\\res\\sound\\plant2.wav";
static const wstring SHOOTER_MUSIC = L".\\res\\sound\\shoop.wav";
static const wstring HIT_MUSIC1 = L".\\res\\sound\\kernelpult.wav";
static const wstring HIT_MUSIC2 = L".\\res\\sound\\kernelpult2.wav";
static const wstring WIN_MUSIC = L".\\res\\sound\\winmusic.wav";
/**************************************************************************************************************/




/************************************************************************************************************/
//退出游戏菜单相关设置
static const wstring QUITGAME_BG = L".\\res\\quitMenu\\quitBg.png";				//退出菜单中的取消按钮
static const wstring QUITGAME_MENU = L".\\res\\quitMenu\\quitMenu.png";			//退出菜单中的退出按钮
static const wstring CANCEL_MENU = L".\\res\\quitMenu\\cancelMenu.png";			//退出菜单中的取消按钮
/************************************************************************************************************/

/************************************************************************************************************/
//帮助菜单相关设置
static const wstring HELP_MENU_BG = L".\\res\\helpMenu\\helpBg.png";			//帮助菜单中的背景图片
static const wstring HELP_MENU_INFO = L".\\res\\helpMenu\\helpInfo.png";		//帮助菜单中的帮助信息图片
static const wstring HELP_MENU_MAINMANU = L".\\res\\helpMenu\\mainMenu.png";	//回到主界面按钮图片
/************************************************************************************************************/


/************************************************************************/
//角色相关设置
static const wstring ZOMBIEHAND = L".\\res\\startMenu\\ZombieHand.png";					//僵尸手图片
static const int ZOMBIEHAND_REMAIN_TIME = 255;											//僵尸手维持时间
static int ZOMBIEHAND_FRAME[26] = {0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6};
/************************************************************************/


/************************************************************************/
//关卡2
static wchar_t* LEVEL2_MAP = L".\\res\\levels\\level2\\bg.jpg"; //bg1.jpg;			//level2地图
static const int LEVEL2_ZOMBIE_NUMBER = 9;
static const int LEVEL2_ZOMBIE_APPEAR_Y[5] = { 10, 108, 216, 314, 412 };
static int LEVEL2_ZOMBIE_APPEAR_X[9] = { 1080,1110, 1130, 1180, 1230, 1280, 1330, 1380, 1430 };
/************************************************************************/

/************************************************************************/
//关卡3                                                                  
static wchar_t* LEVEL3_MAP = L".\\res\\levels\\level3\\bg.jpg"; //bg1.jpg;			//level3地图
// TODO 其余的内容的添加
/************************************************************************/

/**************************************************************************************************************************/
//关卡1
static wchar_t* LEVEL1_MAP = L".\\res\\levels\\level1\\bg2.jpg"; //bg1.jpg;			//level1地图
static const int LEVEL1_SCENEWIDTH = 1500;//1400;
static const int LEVEL1_SCENEHEIGHT = 600;
static const wstring LEVEL1_GRASS = L".\\res\\levels\\level1\\sod2row.png";		//level1草坪
static const int LEVEL_START_POS_X = 210;
static const wstring LEVEL1_DIRT = L".\\res\\levels\\level1\\dirt.png";			//泥土图片
static const wstring LEVEL1_SODROLL = L".\\res\\levels\\level1\\SodRoll.png";	//草坪卷动图片
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
	// 第一行
	{ 60,70,90,85 },
	{ 150,70,77,85 },
	{ 227,70,98,85 },
	{ 325,70,83,85 },
	{ 408,70,83,85 },
	{ 491,70,94,85 },
	{ 585,70,77,85 },
	{ 662,70,92,85 },
	{ 754,70,104,85 },
	// 第二行
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

//	随机普通僵尸的三种形态
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
//植物卡片相关配置
static const wstring CARDBOARD = L".\\res\\cardBoard\\cardBoard.png";			//植物卡片菜单图片
static const wstring TEXTBG = L".\\res\\cardBoard\\textBg.png";
static const wstring SUNFLOWER_CARD = L".\\res\\cardBoard\\SunFlower.png";		//太阳花
static const wstring PEASHOOTER_CARD = L".\\res\\cardBoard\\Peashooter.png";	//豌豆射手
static const wstring WALLNUT_CARD = L".\\res\\cardBoard\\WallNut.png";			//小坚果
static const wstring SQUASH_CARD = L".\\res\\cardBoard\\Squash.png";			//倭瓜
static const wstring POTATO_CARD = L".\\res\\cardBoard\\PotatoMine.png";		//土豆



/************************************************************************/

typedef struct  
{
	int		width;				// 菜单宽度
	int		height;				// 菜单高度
	POINT	pos;				// 菜单位置
	T_Graph *btn;				// 菜单按钮图片
	bool	isFocused;			// 当前菜单项是否选中
	int		waitTime;			// 菜单冷却时间
	int		type;				// 植物菜单种类
	int		costPower;			// 消耗的阳光
	wstring name;				// 植物的名字
	int     state;				// 植物条状态		0表示冷却   1表示冷却完毕
	int		quiteCount;			// 冷却计时
}MYSTARTMENUINFO;

// 僵尸类型
// TODO 修改僵尸的种类
enum ZOMBIE_TYPE
{
	NORMAL_ZOMBIE,		//普通僵尸
	BUCKETHEAD_ZOMBIE,	//铁桶僵尸
	CONEHEAD_ZOMBIE,	//木桶僵尸
	FLAG_ZOMBIE,		//旗手僵尸
	FOOTBAL_ZOMBIE		//橄榄球僵尸
};

enum ZOMBIE_STATE
{
	STATIC_STATE,			//站立状态
	WALK_STATE,				//走动状态
	ATTACK_STATE,			//攻击状态
	BOOM_STATE,				//炸死状态
	LOSTHEADWALK_STATE,		//掉头走动状态
	LOSTHEADATTACK_STATE,	//掉头攻击状态
	DIE_STATE,				//死亡状态
	DISAPPEAR_STATE			//僵尸消失状态
};

enum PLANT_STATE
{
	PLANT_STATIC_STATE,		//植物静止状态
	PLANT_STAND_STATE,		//植物站立状态
	PLANT_SHOOT_STATE,		//植物发射状态
	PLANT_BOOM_STATE,		//植物爆炸状态
	PLANT_SUN_STATE,		//植物阳光状态
	PLANT_DEAD,				//植物死亡
};

enum PLANT_TYPE
{
	PEASHOOTER,		//豌豆射手
	SUNFLOWER,		//向日葵
	WALLNUT,		//小坚果
	POTATO,			//土豆
	SQUASH,			//倭瓜
	CHERRY			//樱桃炸弹
};
// 等待时间
static const int WAITTIME[6] = {6, 5, 8, 6, 6, 6};
// 消耗阳光
static const int COSTSUN[6]={100, 50, 50, 50, 50, 50};
// 生命值
static const int PLANTE_REMAINLIVE[6] = {1400, 1400, 6000, 1400, 1400, 1400};
// 护甲
static const int PLANT_DEFENCE[6] = {100, 100, 1000, 10000, 10000, 10000};
// 攻击力
static const int PLANT_POWER[6] = {150, 0, 0, 0, 10000000, 100000000};
// 豌豆图片
static const wstring PEASHOOTER_WEAPON = L".\\res\\plant\\peashooter\\bullet.png";
// 击中图片
static const wstring PEASHOOTER_WEAPON_HIT = L".\\res\\plant\\peashooter\\bulletHit.png";

//植物静止图片
static const wstring plantStatic[6]=
{
	L".\\res\\plant\\peashooter\\peaShooterStatic.png",
	L".\\res\\plant\\SunFlower\\SunFlowerStatic.png",
	L".\\res\\plant\\wallnut\\wallNutStatic.png",
	L".\\res\\plant\\SunFlower\\SunFlowerStatic.png",
	L".\\res\\plant\\SunFlower\\SunFlowerStatic.png",
	L".\\res\\plant\\SunFlower\\SunFlowerStatic.png",
};


//阳光连帧图
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
// 植物素材
static PLANTINFO PLANTSTAND[6]=
{
	{L".\\res\\plant\\peashooter\\Peashooter.png", 71, 71},
	{ L".\\res\\plant\\SunFlower\\SunFlower.png", 73, 74 },
	{ L".\\res\\plant\\wallnut\\wallNut1.png", 65, 73 },
	{ L".\\res\\plant\\peashooter\\Peashooter.png", 71, 71 },
	{ L".\\res\\plant\\peashooter\\Peashooter.png", 71, 71 },
	{ L".\\res\\plant\\peashooter\\Peashooter.png", 71, 71 },
};

// 豌豆射手素材
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

// 坚果墙图片帧
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
//关卡标志
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
// 过关图片素材
static const wstring PASSMENUBG = L".\\res\\passMenu\\AwardScreen_Back.jpg";
static const wstring PASSMENU = L".\\res\\passMenu\\nextLevel.png";