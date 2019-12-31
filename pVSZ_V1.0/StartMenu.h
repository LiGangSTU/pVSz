#pragma once
#include ".\\T_Engine\\T_Menu.h"
#include "MyConfig.h"
class StartMenu : public T_Menu
{
public:
	StartMenu();
	~StartMenu();
	//初始化开始菜单
	void init();
	//绘制菜单
	void DrawMenu(HDC hdc, BYTE btnTrans = 255, bool startState = true);
	//初始化冒险游戏菜单项
	void initAdventure();
	//初始化迷你游戏菜单项
	void initMini();
	//初始化益智游戏菜单项
	void initQuiz();
	//初始化图鉴菜单项
	void initHandBook();
	//初始化帮助选项
	void initHelp();
	//初始化关于选项
	void initOption();
	//初始化退出选项
	void initQuit();
	//重置
	void reset();

	//重载父类函数
	void MenuMouseMove(int x, int y);
	int MenuMouseClick(int x, int y);
	int GetMenuIndex(int x, int y);
private:
	vector<MYSTARTMENUINFO> myMenuItems;		// 菜单项目
	T_Graph *adventureShadow;					// 冒险游戏菜单项阴影
	T_Graph *mini;								// 迷你游戏菜单项阴影
	T_Graph *quiz;								// 益智游戏菜单项阴影

public:
	void changeMenuFocusd();		//将当前菜单闪烁
	int countNum;
};