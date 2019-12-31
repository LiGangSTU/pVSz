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
	int dynamicW;			//动态显示草坪的宽度
	int dynamicH;			//动态显示卷草坪的高度
	int posX;				//卷动草坪的位置
	T_Sprite *dirt[3];		//草坪卷动的泥土
	T_Sprite *sodRoll;		//草坪卷动

	AudioDX ds;						//DirectSound对象
	AudioDXBuffer dirt_buffer;		//泥土音效
};

