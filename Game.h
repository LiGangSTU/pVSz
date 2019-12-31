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
	//������Ϸ�����ʬ��
	void activeZombieHand();
	//��ʬ�ֶ�����ɣ�׼��������Ϸ
	bool readyToGameAdventure();
	//��ʼ����ɫ
	void initRole();
	//��ʼ���˵�
	void initMenu();
	//��ʼ������
	void initSound();
	//�������еĹؿ�
	void initLevels();
	//��������ڲ˵�������ƶ�
	void MouseMoveHandle(int x, int y, int Action, int GameState);
private :
	int wndHeight, wndWidth;	//������
	int clickMenuIndex;			//�û�����Ĳ˵�����������ָʾ�Ǹ��˵���˸
private :
	//�˵�
	StartMenu *startMenu;			//��ʼ�˵�
	QuitMenu *quitMenu;				//�˳���Ϸ�˵�
	HelpMenu *helpMenu;				//�����˵�
	PassGameMenu *passGameMenu;
	AboutMenu *aboutMenu;		//
	//��ɫ
	ZombieHand *zombieHand;			//��ʬ��

	//�ؿ�1
	Level1 *level1;			//�ؿ�1����
	Level2 *level2;			//�ؿ�2����
	Level3 *level3;			//�ؿ�3����
	AudioDX ds;									//DirectSound����
	AudioDXBuffer startMenuMouseMove_buffer;	//��ʼ�˵�����ƶ���Ч
	AudioDXBuffer startMenuMouseClick_buffer;	//��ʼ�˵�����˵�����Ч
	AudioDXBuffer bgm_buffer;					//��ʼ�ı���������Ч
	AudioDXBuffer graveMenu_buffer;				//Ĺ���˵������Ч
	AudioDXBuffer enter_buffer;					//������Ϸ��ʬ����Ч
	AudioDXBuffer loseGame_buffer;				//��Ϸʧ�ܱ�����Ч
	AudioDXBuffer win_buffer;

};

