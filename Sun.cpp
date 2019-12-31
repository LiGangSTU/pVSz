#include "Sun.h"
#include "MyConfig.h"



Sun::Sun(wstring imgPath, int frameWidth, int frameHeight)
	: T_Sprite(imgPath, frameWidth, frameHeight)
{
	srand(GetTickCount());
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

		frameCols = spImg.GetImageWidth() / frameWidth;		// 动画帧图片总列数
		frameRows = spImg.GetImageHeight() / frameHeight;	// 动画帧图片总行数
		totalFrames = frameCols*frameRows;					// 动画总帧数
		rawFrames = frameCols*frameRows;					// 记录原始动画总帧数
		forward = 0;										// 当前帧计数初始化
		backward = totalFrames - 1;
	}

	frameSequence = NULL;
	loopForward = true;
	timeCount = 0;
	mapBlockPT.x = -1;
	mapBlockPT.y = -1;
	endX = 0;
	stayTime = rand() % 300 + 600;
	isGet = false;
	getSpeed = false;
	reached = false;
	recievedCount = 0;
}


Sun::~Sun()
{

}

void Sun::Draw(HDC hdc)
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
	if (!isGet)
	{
		if (this->Y < endY)
		{
			this->Y++;
		}
		if (&spImg != NULL)
		{
			spImg.PaintFrame(
				spImg.GetBmpHandle(), hdc, (int)X, (int)Y, frmIndex,
				frameCols, Width, Height, frameRatio, frameRotate, frameAlpha
			);
		}
	}
	else
	{
		if (!getSpeed)
		{
			speedX = abs(X - endX) / 15;
			speedY = abs(Y - endY) / 15;
			if (speedX == 0 || speedY == 0)
			{
				speedX = 10;
				speedY = 10;
			}
			getSpeed = true;
		}
		X -= speedX;
		Y -= speedY;
		if (X < endX && Y > endY)
		{
			X = endX;
			Y = Y;
		}
		else if (X > endX && Y <= endY)
		{
			Y = endY;
			X = X;
		}
		else if (X < endX && Y < endY)
		{
			Y = endY;
			X = endX;
			reached = true;
		}


		if (&spImg != NULL)
		{
			spImg.PaintFrame(
				spImg.GetBmpHandle(), hdc, (int)X, (int)Y, frmIndex,
				frameCols, Width, Height, frameRatio, frameRotate, frameAlpha
			);
		}
	}
}

void Sun::LoopFrame(bool ahead)
{
	loopForward = ahead;
	timeCount++;
	if (timeCount % 4 == 0)
	{
		if (totalFrames > 0)
		{
			if (ahead == true)
			{
				forward = forward + 1;
				if (forward > totalFrames - 1)
				{
					forward = 0;
				}
			}
			else
			{
				backward = backward - 1;
				if (backward < 0)
				{
					backward = totalFrames - 1;
				}
			}
		}
		timeCount = 0;
	}
}

bool Sun::mouseClickSun(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	RECT rec;
	rec.left = this->X;
	rec.top = this->Y;
	rec.right = rec.left + this->GetWidth();
	rec.bottom = rec.top + this->GetHeight();
	if (PtInRect(&rec, pt))
	{
		return true;
	}
	return false;
}