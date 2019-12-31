#pragma once
#include ".\\T_Engine\\T_Menu.h"
#include "MyConfig.h"
class PlantCardBoard : public T_Menu
{
public:
	PlantCardBoard();
	~PlantCardBoard();
	void addCardItem(MYSTARTMENUINFO info);	//����ֲ�￨Ƭ
	void changeFocus(int index);			//�ı䵱ǰ�˵���ľ۽�

	// ����  ����ֲ�￨Ƭ
	void DrawMenu(HDC hdc, BYTE btnTrans =255 , bool startState = true);
	void MenuMouseMove(int x, int y);
	int GetMenuIndex(int x, int y);
	int MenuMouseClick(int x, int y);
	void initSound(HWND m_hWnd);
	void setVisible(bool visible) { this->visible = visible; }
	void addSunPower(int power);
	void setSelected(bool selected) { this->selected = selected; }
	bool getSelected() { return selected; }
	void setState(int type, int state);
private :
	vector<MYSTARTMENUINFO> myMenuItems;
	T_Graph *board;
	T_Graph *textBg;
	bool selected;			//�Ƿ�ѡ��ֲ��
	bool visible;
	int dynamicY;
	int sunPower;
	RectF sunNumRect;
	WCHAR sunNum[10];
	WCHAR remainTime[10];
	AudioDX ds;									//DirectSound����
	AudioDXBuffer plantSelected_buffer;
	AudioDXBuffer gameMenu_buffeer;
	int startTime;
	int endTime;
};