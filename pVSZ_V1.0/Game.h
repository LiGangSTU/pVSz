#pragma once
#include ".\\T_Engine\\T_Engine.h"
#include ".\\T_Engine\\T_Audio.h"
#include "StartMenu.h"
#include "HelpMenu.h"
#include "QuitMenu.h"
#include "ZombieHand.h"
#include "Level1.h"
#include "PassGameMenu.h"
#include "Level2.h"
#include "Level3.h"
#include "AboutMenu.h"
class Game : public T_Engine
{
public:
	Game(HINSTANCE hInstance, LPCTSTR szWindowClass, LPCTSTR szTitle,
		WORD Icon = NULL, WORD SmIcon = NULL,
		int iWidth = WIN_WIDTH, int iHeight = WIN_HEIGHT);
	~Game();

public:
	void GameInit();
	void GameLogic();
	void GameEnd();
	void GamePaint(HDC hdc);
	void GameKeyAction(int Action = KEY_SYS_NONE);
	void GameMouseAction(int x, int y, int Action);

private:
	//开启游戏，激活僵尸手
	void activeZombieHand();
	//僵尸手动画完成，准备进入游戏
	bool readyToGameAdventure();
	//初始化角色
	void initRole();
	//初始化菜单
	void initMenu();
	//初始化音乐
	void initSound();
	//加载所有的关卡
	void initLevels();
	//处理鼠标在菜单界面的移动
	void MouseMoveHandle(int x, int y, int Action, int GameState);
private :
	int wndHeight, wndWidth;	//窗体宽高
	int clickMenuIndex;			//用户点击的菜单索引，用其指示那个菜单闪烁
private :
	//菜单
	StartMenu *startMenu;			//开始菜单
	QuitMenu *quitMenu;				//退出游戏菜单
	HelpMenu *helpMenu;				//帮助菜单
	PassGameMenu *passGameMenu;
	AboutMenu *aboutMenu;		//
	//角色
	ZombieHand *zombieHand;			//僵尸手

	//关卡1
	Level1 *level1;			//关卡1场景
	Level2 *level2;			//关卡2场景
	Level3 *level3;			//关卡3场景
	AudioDX ds;									//DirectSound对象
	AudioDXBuffer startMenuMouseMove_buffer;	//开始菜单鼠标移动音效
	AudioDXBuffer startMenuMouseClick_buffer;	//开始菜单点击菜单项音效
	AudioDXBuffer bgm_buffer;					//开始的背景音乐音效
	AudioDXBuffer graveMenu_buffer;				//墓碑菜单点击音效
	AudioDXBuffer enter_buffer;					//进入游戏僵尸手音效
	AudioDXBuffer loseGame_buffer;				//游戏失败背景音效
	AudioDXBuffer win_buffer;

};

