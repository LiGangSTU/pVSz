#include "ZombieHand.h"
#include "MyConfig.h"



ZombieHand::ZombieHand(wstring imgPath, int frameWidth, int frameHeight) 
	: T_Sprite(imgPath, frameWidth, frameHeight)
{
	if (wcslen(imgPath.c_str()) > 0)
	{
		spImg.LoadImageFile(imgPath);
		spOldImg = spImg;
	}
	else
	{
		throw L"图像路径为空!";
	}

	// 无动画的角色图片
	if (frameWidth == 0 && frameHeight == 0)
	{
		SetWidth(spImg.GetImageWidth());
		SetHeight(spImg.GetImageHeight());

		totalFrames = rawFrames = 0; // 动画总帧数
	}
	else// 具有动画的角色图片
	{
		SetWidth(frameWidth);
		SetHeight(frameHeight);

		frameCols = spImg.GetImageWidth() / frameWidth;			// 动画帧图片总列数
		frameRows = spImg.GetImageHeight() / frameHeight;		// 动画帧图片总行数
		totalFrames = frameCols*frameRows;						// 动画总帧数
		rawFrames = frameCols*frameRows;						// 记录原始动画总帧数
		forward = 0;											// 当前帧计数初始化
		backward = totalFrames - 1;
	}


	frameSequence = NULL;
	loopForward = true;

	mapBlockPT.x = -1;
	mapBlockPT.y = -1;
}


ZombieHand::~ZombieHand()
{
}

void ZombieHand::init()
{
	this->SetActive(false);
	this->SetVisible(false);
	this->SetAlpha(255);
	this->SetRatio(1);
	this->SetSequence(ZOMBIEHAND_FRAME, 26);
	this->SetPosition(262, 264);
	this->SetRotation(TRANS_NONE);
}

bool ZombieHand::LoopFrameOnce(bool ahead)
{
	loopForward = ahead;
	if (forward == totalFrames - 1 || backward == 0)
	{
		return true;
	}
	if (totalFrames <= 0) return true;
	if (totalFrames > 0)
	{
		if (ahead == true)
		{
			forward = forward + 1;
			if (forward > totalFrames - 1)
			{
				forward = totalFrames - 1;
				return true;//播放完一轮所有帧
			}
			else
			{
				return false;
			}
		}
		if (ahead == false)
		{
			backward = backward - 1;
			if (backward < 0)
			{
				backward = 0;
				return true;//播放完一轮所有帧
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

void ZombieHand::reset()
{
	this->forward = 0;
	this->backward = totalFrames - 1;
	this->SetActive(false);
	this->SetVisible(false);
}
