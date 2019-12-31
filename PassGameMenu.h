#pragma once
#include ".\T_Engine\\T_Menu.h"
#include "MyConfig.h"
class PassGameMenu : public T_Menu
{
public:
	PassGameMenu();
	~PassGameMenu();
public :
	void init();
	void initCard(wstring card);

	void MenuMouseMove(int x, int y);
	int MenuMouseClick(int x, int y);
	int GetMenuIndex(int x, int y);
	void DrawMenu(HDC hdc, BYTE btnTrans = 255 , bool startState = true );
private :
	vector<MYSTARTMENUINFO> myMenuItems;		// ²Ëµ¥ÏîÄ¿
	T_Graph *bg;
	T_Graph *plantCard;
};

