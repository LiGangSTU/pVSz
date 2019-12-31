#include "Zombie.h"


Zombie::Zombie(wstring imgPath, int frameWidth, int frameHeight) : T_Sprite(imgPath, frameWidth, frameHeight)
{
	srand(GetTickCount());
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

		frameCols = spImg.GetImageWidth() / frameWidth;		// ����֡ͼƬ������
		frameRows = spImg.GetImageHeight() / frameHeight;	// ����֡ͼƬ������
		totalFrames = frameCols*frameRows;					// ������֡��
		rawFrames = frameCols*frameRows;					// ��¼ԭʼ������֡��
		forward = 0;										// ��ǰ֡������ʼ��
		backward = totalFrames - 1;
	}


	frameSequence = NULL;
	loopForward = true;
	Visible = true;
	dir = DIR_LEFT;
	active = true;
	dead = false;
	level = 1;
	frameRatio = 1;
	frameRotate = TRANS_NONE;
	frameAlpha = 255;
	mapBlockPT.x = -1;
	mapBlockPT.y = -1;
	timeCount = 0;
	state = STATIC_STATE;
	startTime = GetTickCount();
}

Zombie::Zombie(ZOMBIEINFO info) : T_Sprite(info.img, info.frameWidth, info.frameHeight)
{
	Zombie(info.img, info.frameWidth, info.frameHeight);
}

Zombie::~Zombie()
{
}
//��ʬ  ���ս�ʬ���ͽ��г�ʼ��
void Zombie::init(int type)
{
	srand(GetTickCount());
	if (type == NORMAL_ZOMBIE)
	{
		this->speed = NORMAL_ZOMBIE_SPEED;
		this->power = NORMAL_ZOMBIE_POWER;
		this->remainLive = NORMAL_ZOMBIE_LIVE + rand() % 200;
		attackState = new T_Sprite(normalZombieAttack.img, normalZombieAttack.frameWidth, normalZombieAttack.frameHeight);
		attackState->SetPosition(this->X, this->Y);
		attackState->SetSequence(NORMAL_ZOMBIE_ATTACK_FRAME, 132);
		boomState = new T_Sprite(zombieBoomDie.img, zombieBoomDie.frameWidth, zombieBoomDie.frameHeight);
		boomState->SetPosition(this->X, this->Y);
		boomState->SetSequence(ZOMBIE_BOOM_DIE_FRAME, 132);
		int a = rand() % 3;
		walkState = new T_Sprite(normalZombieWalk[a].img, normalZombieWalk[a].frameWidth, normalZombieWalk[a].frameHeight);
		walkState->SetPosition(this->X, this->Y);
		walkState->SetSequence(NORMAL_ZOMBIE_WALK_FRAME[a], 132);
		lostHeadWalkState = new T_Sprite(zombieLostHead.img, zombieLostHead.frameWidth, zombieLostHead.frameHeight);
		lostHeadWalkState->SetPosition(this->X, this->Y);
		lostHeadWalkState->SetSequence(NORMAL_ZOMBIE_LOSTHEAD_WALK, 132);
		dieState = new T_Sprite(zombieDie.img, zombieDie.frameWidth, zombieDie.frameHeight);
		dieState->SetPosition(this->X, this->Y);
		dieState->SetSequence(NORMAL_ZOMBIE_DIE, 132);
		lostHeadAttackState = new T_Sprite(zombieLostHeadAttack.img, zombieLostHeadAttack.frameWidth, zombieLostHeadAttack.frameHeight);
		lostHeadAttackState->SetPosition(X, Y);
		lostHeadAttackState->SetSequence(NORMAL_ZOMBIE_LOSTHEAD_ATTACK, 132);
		head = new T_Sprite(zombieHead.img, zombieHead.frameWidth, zombieHead.frameHeight);
		head->SetPosition(X, Y);
		head->SetSequence(NORMAL_ZOMBIE_HEAD, 132);
		zombieStates.push_back(attackState);
		zombieStates.push_back(boomState);
		zombieStates.push_back(walkState);
		zombieStates.push_back(lostHeadWalkState);
		zombieStates.push_back(dieState);
		zombieStates.push_back(lostHeadAttackState);
		zombieStates.push_back(head);
	}
}
//��ʬ����
void Zombie::walk()
{
	timeCount++;
	if (timeCount % 4 == 0)
	{
		this->X -= this->speed;
		setAllStatePos();
		timeCount = 0;
	}
}
//��ʬ��ֲ��
void Zombie::attack(Plant * plant)
{
	if (state == ATTACK_STATE)
	{
		timeCount++;
		if (timeCount % 50 == 0)
		{
			timeCount = 0;
			plant->setRemainLive(plant->getRemianLive() - this->power);
			if (plant->getRemianLive() <= 0)
			{
				plant->SetDead(true);			//ֲ������
				this->state = WALK_STATE;
			}
		}
	}
}
void Zombie::lostHeadWalk()
{
	timeCount++;
	if (timeCount % 4 == 0)
	{
		this->X -= this->speed;
		setAllStatePos();
		head->SetPosition(this->X + 130, this->Y);
	}
}
//��������״̬ͬ��
void Zombie::setAllStatePos()
{
	vector<T_Sprite*>::iterator p;
	for (p = zombieStates.begin(); p != zombieStates.end(); p++)
	{
		if ((*p) != head)
		{
			(*p)->SetPosition(X, Y);
		}

	}
}
//����״̬
void Zombie::setState(int state)
{
	this->state = state;
}

//����ֲ��
bool Zombie::CollideWith(Plant * plant, int distance)
{
	if (this->X + 85 >= plant->getPlantX() + plant->GetWidth() - 50 && 
		this->X + 85 <= plant->getPlantX() + plant->GetWidth())
	{
		return true;
	}
	return false;
}

//���ղ�ͬ״̬���л���
void Zombie::Draw(HDC hdc)
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
		{	//��ֹ
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
			else if (state == WALK_STATE)	//�߶�
			{
				walkState->Draw(hdc);
			}

			else if (state == ATTACK_STATE)	//����
			{
				attackState->Draw(hdc);
			}
			else if (state == BOOM_STATE)	//��ը
			{
				boomState->Draw(hdc);
			}
			else if (state == LOSTHEADWALK_STATE)	//��ͷ��
			{
				lostHeadWalkState->Draw(hdc);
				head->Draw(hdc);
			}
			else if (state == DIE_STATE)
			{
				dieState->Draw(hdc);
			}
			else if (state == LOSTHEADATTACK_STATE)
			{
				lostHeadAttackState->Draw(hdc);
			}
		}
	}
}
//���ղ�ͬ״̬����ѭ��
void Zombie::LoopFrame(bool ahead)
{
	if (state == STATIC_STATE)
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
	else if (state == WALK_STATE)
	{
		walkState->LoopFrame(ahead);
	}
	else if (state == ATTACK_STATE)
	{
		attackState->LoopFrame(ahead);
	}
	else if (state == LOSTHEADWALK_STATE)
	{
		if (lostHeadWalkState->LoopFrameOnce(ahead))
		{
			lostHeadWalkState->SetVisible(false);
			state = DIE_STATE;
		}
		if (head->LoopFrameOnce(ahead))
		{
			head->SetVisible(false);
			state = DIE_STATE;
		}
	}
	else if (state == LOSTHEADATTACK_STATE)
	{
		if (lostHeadAttackState->LoopFrameOnce(ahead))
		{
			lostHeadAttackState->SetVisible(false);
			state = DIE_STATE;
		}
	}
	else if (state == DIE_STATE)
	{
		if (dieState->LoopFrameOnce(ahead))
		{
			this->dead = true;
		}
	}
}

bool Zombie::LoopFrameOnce(bool ahead)
{
	if (state == ATTACK_STATE)
	{
		return attackState->LoopFrameOnce(true);
	}
	else if(state == LOSTHEADWALK_STATE)
	{
		return head->LoopFrameOnce(true);
	}
	else if(state == DIE_STATE)
	{
		return dieState->LoopFrameOnce(ahead);
	}
	else if (state == LOSTHEADATTACK_STATE)
	{
		return lostHeadAttackState->LoopFrameOnce(ahead);
	}
	else return this->LoopFrameOnce(true);
}
