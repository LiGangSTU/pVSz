#pragma once
#include ".\\T_Engine\T_Menu.h"
#include "MyConfig.h"
class QuitMenu : public T_Menu
{
public:
	QuitMenu();
	~QuitMenu();

	void initCancelMenu();
	void initQuitMenu();
	void init();
	void DrawMenu(HDC hdc, BYTE btnTrans = 255, bool startState = true);
	int MenuMouseClick(int x, int y);
	void MenuMouseMove(int x, int y);
	int GetMenuIndex(int x, int y);
private :
	T_Graph *bg;	//绘制菜单背景墓碑
	vector<MYSTARTMENUINFO> myMenuItems;		// 菜单项目
};

