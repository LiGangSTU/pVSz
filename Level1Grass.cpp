#include "Level1Grass.h"
#include "MyConfig.h"



Level1Grass::Level1Grass(wstring imgPath, int frameWidth, int frameHeight)
	: T_Sprite(imgPath, frameWidth, frameHeight)
{
	if (wcslen(imgPath.c_str()) > 0)
	{
		spImg.LoadImageFile(imgPath);
		spOldImg = spImg;
	}
	else
	{
		throw L"ͼ��·��Ϊ��!";
	}

	// �޶����Ľ�ɫͼƬ
	if (frameWidth == 0 && frameHeight == 0)
	{
		SetWidth(spImg.GetImageWidth());
		SetHeight(spImg.GetImageHeight());

		totalFrames = rawFrames = 0; // ������֡��
	}
	else// ���ж����Ľ�ɫͼƬ
	{
		SetWidth(frameWidth);
		SetHeight(frameHeight);

		frameCols = spImg.GetImageWidth() / frameWidth;			// ����֡ͼƬ������
		frameRows = spImg.GetImageHeight() / frameHeight;		// ����֡ͼƬ������
		totalFrames = frameCols*frameRows;						// ������֡��
		rawFrames = frameCols*frameRows;						// ��¼ԭʼ������֡��
		forward = 0;											// ��ǰ֡������ʼ��
		backward = totalFrames - 1;
	}


	frameSequence = NULL;
	loopForward = true;

	mapBlockPT.x = -1;
	mapBlockPT.y = -1;

	dynamicW = 0;
	posX = 0;
}

Level1Grass::~Level1Grass()
{
}

void Level1Grass::Draw(HDC hdc)
{
	int frmIndex = 0;
	if (frameSequence != NULL && backward >= 0 && forward >= 0)
	{
		if (loopForward == false)
			frmIndex = frameSequence[backward];
		else
			frmIndex = frameSequence[forward];
	}
	else
	{
		if (loopForward == false)
			frmIndex = backward;
		else
			frmIndex = forward;
	}

	if (&spImg != NULL)
	{
		if (Visible == true)
		{
			if (totalFrames == 0)
			{
				spImg.PaintRegion(
					spImg.GetBmpHandle(), hdc, (int)X, (int)Y,
					0, 0, Width, Height, frameRatio, frameRotate, frameAlpha
				);
			}
			else
			{
				spImg.PaintFrame(
					spImg.GetBmpHandle(), hdc, (int)X, (int)Y, frmIndex,
					frameCols, Width, Height, frameRatio, frameRotate, frameAlpha
				);
			}
		}
	}
}

bool Level1Grass::FinishedDrawGrass(HDC hdc)
{
	if (dynamicW < spImg.GetImageWidth())
	{
		dynamicW += 10;
		if (dynamicW >= spImg.GetImageWidth())
		{
			dynamicW = spImg.GetImageWidth();
		}
		spImg.PaintRegion(spImg.GetBmpHandle(), hdc, (int)X, (int)Y,
			0, 0, dynamicW, Height, frameRatio, frameRotate, frameAlpha);
		for (int i = 0; i < 3; i++)
		{
			dirt[i]->DynamicDraw(hdc, dynamicW, dirt[i]->GetY());
			dirt[i]->LoopFrame(true);
			dirt_buffer.Play(false);
		}
		sodRoll->DynamicDraw(hdc, 13 + dynamicW + posX, sodRoll->GetY());
		//posX = 0;
		if (dynamicW % 20 == 0)
		{
// 			int h = sodRoll->GetHeight() - 1;
// 			sodRoll->SetHeight(h);
			int w = sodRoll->GetWidth() - 1;
			sodRoll->SetWidth(w);
			posX += 1;
		}
		return false;
	}
	return true;
}

void Level1Grass::init()
{
	initDirt();
	initSodRoll();
}

void Level1Grass::initDirt()
{

	for (int i = 0; i < 3; i++)
	{
		dirt[i] = new T_Sprite(LEVEL1_DIRT, 48, 31);
		dirt[i]->SetActive(true);
		dirt[i]->SetVisible(true);
		dirt[i]->SetRatio(1);
		dirt[i]->SetAlpha(255);
		dirt[i]->SetRotation(TRANS_NONE);
		dirt[i]->SetPosition(posX, 268 + i * 39);
		dirt[i]->SetSequence(LEVEL1_DIRT_FRAME, 25);
	}
}

void Level1Grass::initSodRoll()
{
	sodRoll = new T_Sprite(LEVEL1_SODROLL);
	sodRoll->SetVisible(true);
	sodRoll->SetActive(true);
	sodRoll->SetRatio(1);
	sodRoll->SetRotation(TRANS_NONE);
	sodRoll->SetPosition(posX, 260);
	sodRoll->SetAlpha(255);
}

void Level1Grass::initSound(HWND m_hWnd)
{
	if (!ds.CreateDS(m_hWnd))
	{
		return;
	}
	dirt_buffer.LoadWave(ds, DIRT_MUSIC.c_str());
}
