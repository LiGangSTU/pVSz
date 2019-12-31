#pragma once
#include ".\\T_Engine\\T_Sprite.h"
#include "T_Engine\T_Audio.h"
class Level1Grass :
	public T_Sprite
{
public:
	Level1Grass(wstring imgPath, int frameWidth = 0, int frameHeight = 0);
	~Level1Grass();
	void Draw(HDC hdc);
	bool FinishedDrawGrass(HDC hdc);

	void init();
	void initDirt();
	void initSodRoll();
	void initSound(HWND m_hWnd);
private:
	int dynamicW;			//��̬��ʾ��ƺ�Ŀ��
	int dynamicH;			//��̬��ʾ���ƺ�ĸ߶�
	int posX;				//����ƺ��λ��
	T_Sprite *dirt[3];		//��ƺ��������
	T_Sprite *sodRoll;		//��ƺ��

	AudioDX ds;						//DirectSound����
	AudioDXBuffer dirt_buffer;		//������Ч
};

