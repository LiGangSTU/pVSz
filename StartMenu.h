#pragma once
#include ".\\T_Engine\\T_Menu.h"
#include "MyConfig.h"
class StartMenu : public T_Menu
{
public:
	StartMenu();
	~StartMenu();
	//��ʼ����ʼ�˵�
	void init();
	//���Ʋ˵�
	void DrawMenu(HDC hdc, BYTE btnTrans = 255, bool startState = true);
	//��ʼ��ð����Ϸ�˵���
	void initAdventure();
	//��ʼ��������Ϸ�˵���
	void initMini();
	//��ʼ��������Ϸ�˵���
	void initQuiz();
	//��ʼ��ͼ���˵���
	void initHandBook();
	//��ʼ������ѡ��
	void initHelp();
	//��ʼ������ѡ��
	void initOption();
	//��ʼ���˳�ѡ��
	void initQuit();
	//����
	void reset();

	//���ظ��ຯ��
	void MenuMouseMove(int x, int y);
	int MenuMouseClick(int x, int y);
	int GetMenuIndex(int x, int y);
private:
	vector<MYSTARTMENUINFO> myMenuItems;		// �˵���Ŀ
	T_Graph *adventureShadow;					// ð����Ϸ�˵�����Ӱ
	T_Graph *mini;								// ������Ϸ�˵�����Ӱ
	T_Graph *quiz;								// ������Ϸ�˵�����Ӱ

public:
	void changeMenuFocusd();		//����ǰ�˵���˸
	int countNum;
};