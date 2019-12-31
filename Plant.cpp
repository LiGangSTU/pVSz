#include "Plant.h"
#include "MyConfig.h"



Plant::Plant(wstring imgPath, int frameWidth, int frameHeight)
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

		frameCols = spImg.GetImageWidth() / frameWidth;		// 动画帧图片总列数
		frameRows = spImg.GetImageHeight() / frameHeight;	// 动画帧图片总行数
		totalFrames = frameCols*frameRows;					// 动画总帧数
		rawFrames = frameCols*frameRows;					// 记录原始动画总帧数
		forward = 0;										// 当前帧计数初始化
		backward = totalFrames - 1;
	}


	frameSequence = NULL;
	loopForward = true;

	mapBlockPT.x = -1;
	mapBlockPT.y = -1;
	state = PLANT_STATIC_STATE;
	weaponCount = 0;
	startTime = GetTickCount();
	endTime = 0;
}

Plant::~Plant()
{
}
//绘制种植前的静态植物
// 草地上的植物虚影
void Plant::PaintPic(HDC hdc, int validRect[])
{
	spImg.PaintImage(hdc, validRect[0] + (validRect[2] - spImg.GetImageWidth())/2, validRect[1], spImg.GetImageWidth(), spImg.GetImageWidth(), 100);
}
//按照类型进行初始化
void Plant::init(int type)
{
	if (type == PEASHOOTER)
	{
		standState = new T_Sprite(PLANTSTAND[PEASHOOTER].img, PLANTSTAND[PEASHOOTER].frameWidth, 
			PLANTSTAND[PEASHOOTER].frameHeight);
		standState->SetPosition(this->X, this->Y);
		standState->SetSequence(PEASHOOTERSTAND_FRAME, 132);
		weapon = new T_Sprite(PEASHOOTER_WEAPON);
		weapon->SetPosition(this->X+this->GetWidth(), this->Y);
		weaponHit = new T_Sprite(PEASHOOTER_WEAPON_HIT);
		weaponHit->SetVisible(false);
		weaponHit->SetPosition(weapon->GetX(), weapon->GetY());
		this->power = PLANT_POWER[type];
		this->remainLive = PLANTE_REMAINLIVE[type];
		this->costSun = COSTSUN[type];
		this->defence = PLANT_DEFENCE[type];
		state = PLANT_STAND_STATE;
	}
	else if (type == SUNFLOWER)
	{
		standState = new T_Sprite(PLANTSTAND[SUNFLOWER].img, PLANTSTAND[SUNFLOWER].frameWidth,
			PLANTSTAND[SUNFLOWER].frameHeight);
		standState->SetPosition(this->X, this->Y);
		standState->SetSequence(SUNFLOWERSTAND_FRAME, 132);
		workState = new T_Sprite(PLANTSTAND[SUNFLOWER].img, PLANTSTAND[SUNFLOWER].frameWidth,
			PLANTSTAND[SUNFLOWER].frameHeight);
		workState->SetPosition(this->X, this->Y);
		workState->SetSequence(SUNFLOWERWORK_FRAME, 132);
		this->power = PLANT_POWER[type];
		this->remainLive = PLANTE_REMAINLIVE[type];
		this->costSun = COSTSUN[type];
		this->defence = PLANT_DEFENCE[type];
		state = PLANT_STAND_STATE;
	}
	else if (type == WALLNUT)
	{
		standState = new T_Sprite(PLANTSTAND[WALLNUT].img, PLANTSTAND[WALLNUT].frameWidth, PLANTSTAND[WALLNUT].frameHeight);
	}
}
//按照不同的状态进行不同的帧循环
void Plant::LoopFrame(bool ahead)
{
	if (state == PLANT_STATIC_STATE)
	{
		loopForward = ahead;
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
	}
	else if (state == PLANT_STAND_STATE)
	{
		standState->LoopFrame(ahead);
	}
	else if (state == PLANT_SHOOT_STATE)
	{
		standState->LoopFrame(ahead);
		weapon->LoopFrame(ahead);
	}
}

bool Plant::LoopFrameOnce(bool ahead)
{
	if (state == PLANT_SUN_STATE)
	{
		return workState->LoopFrameOnce(ahead);
	}
	else
		return this->LoopFrameOnce(ahead);
}

void Plant::Draw(HDC hdc)
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
			if (state == STATIC_STATE)
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
			else if (state == PLANT_STAND_STATE)
			{
				standState->Draw(hdc);
			}
			else if (state == PLANT_SHOOT_STATE)
			{
				standState->Draw(hdc);
				weapon->Draw(hdc);
				weaponHit->Draw(hdc);
				weaponHit->SetVisible(false);
			}
			else if (state == PLANT_SUN_STATE)
			{
				workState->Draw(hdc);
			}
		}
	}
}

void Plant::setState(int state)
{
	this->state = state;
	if (state == PLANT_SHOOT_STATE)
	{
		weapon->SetVisible(true);
		if (weapon->IsVisible() && weapon->GetX() == this->X + this->GetWidth())
		{
			shooter_buffer.Play(false);
		}
	}
}

//进攻
void Plant::attack(Zombie *zombie)
{
	if (type == PEASHOOTER)
	{
		endTime = GetTickCount();
		if (endTime - startTime > 2000 && zombie->getState() != DIE_STATE && CollideWith(zombie) && zombie->getRemianLive() > 0)
		{
			startTime = endTime;
			weaponHit->SetVisible(true);
			int num = rand() % 3;
			if (num == 0)
			{
				hit1_buffer.Play(false);
			}
			else if (num == 1)
			{
				hit2_buffer.Play(false);
			}
			weaponHit->SetPosition(weapon->GetX() - 10, weapon->GetY());
			zombie->setRemainLive(zombie->getRemianLive() - this->power);
			if (zombie->getRemianLive() <= 0)
			{
				if (zombie->getState() == ATTACK_STATE)
				{
					zombie->setState(LOSTHEADATTACK_STATE);
				}
				else if (zombie->getState() == WALK_STATE)
				{
					zombie->setState(LOSTHEADWALK_STATE);
				}
			}
		}
		else
		{
			weaponHit->SetVisible(false);
		}
	}
}

bool Plant::CollideWith(Zombie * zombie, int distance)
{
	if (weapon->GetX() + weapon->GetWidth() >= zombie->GetX() + 70 
		&& weapon->IsVisible() && zombie->getState() != DIE_STATE 
		&& this->getValidY() == zombie->getValidY())
	{
		return true;
	}
	return false;
}

void Plant::weaponMove()
{
	if (type == PEASHOOTER)
	{
		int x = weapon->GetX();
		x += 5;
		weapon->SetX(x);
		weapon->SetPosition(x, weapon->GetY());
	}
}

void Plant::setWeaponVisible(bool flag)
{
	weapon->SetVisible(flag);
	if (flag == false)
	{
		weapon->SetPosition(this->X + this->GetWidth(), this->Y);
	}
}

void Plant::initSound(HWND m_hWnd)
{
	if (!ds.CreateDS(m_hWnd))
	{
		return;
	}
	shooter_buffer.LoadWave(ds, SHOOTER_MUSIC.c_str());
	hit1_buffer.LoadWave(ds, HIT_MUSIC1.c_str());
	hit2_buffer.LoadWave(ds, HIT_MUSIC2.c_str());
}

