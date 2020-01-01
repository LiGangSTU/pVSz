#include "Level3.h"



Level3::Level3()
{
	srand(GetTickCount());
	lastSceneX = 0;
	lastSceneY = 0;
	SceneY = 0;
	SceneX = 0;
	SceneWidth = 0;
	SceneHeight = 0;
	WinWidth = 0;
	WinHeight = 0;
	pBarrier = NULL;		//��ײͼ��ָ��
	pMask = NULL;			//���ֲ�ָ��
	LayerChanged = false;
	timeCount = 0;

	//�Լ�����ı���
	// 	scnOffsetX = 0;
	// 	scnOffsetY = 0;
	scnMoveCount = 0;
	canMove = false;
	canToRight = false;
	canPlayPre = true;
	validY = 2;
	curentZombieNumber = 0;
	blockIndex = -1;
	plant = NULL;
	canMakeSun = false;

	startTime = 0;
	endTime = 0;
}


Level3::~Level3()
{
	RemoveAll();
}



void Level3::init(HWND m_hWnd)
{
	hwnd = m_hWnd;
	this->InitScene(0, 0, LEVEL1_SCENEWIDTH, LEVEL1_SCENEHEIGHT, WIN_WIDTH, WIN_WIDTH);
	initMap();
	initZombie();
	initBoard();
	initSound(m_hWnd);
	//T_Util::GetRandomNum(8, ZOMBIE_APPEAR_X);
	dirt = new T_Sprite(LEVEL1_DIRT, 48, 31);
	dirt->SetActive(true);
	dirt->SetVisible(false);
	dirt->SetRatio(1);
	dirt->SetAlpha(255);
	dirt->SetRotation(TRANS_NONE);
	dirt->SetSequence(LEVEL1_DIRT_FRAME, 25);
}

void Level3::initMap()
{
	GAMELAYER layer;
	map = new T_Map(LEVEL3_MAP);
	map->SetLayerTypeID(LAYER_MAP_BACK);
	layer.layer = map;
	layer.type_id = LAYER_MAP_BACK;
	layer.z_order = this->getSceneLayers()->size() + 1;
	this->Append(layer);
}

void Level3::start(HDC hdc)
{
	//���Ƴ���
	this->Draw(hdc, this->SceneX, this->SceneY);
	/*	pcb.DrawMenu(hdc);*/
	dirt->Draw(hdc);
	//����͸��ֲ��
	if (blockIndex >= 0 && plant != NULL)
	{
		plant->PaintPic(hdc, LEVEL3_VALID_BLOCKPOS[blockIndex]);
	}
	//����ѡ��ֲ��
	if (plant != NULL)
	{
		plant->Draw(hdc);
	}
	//����һ�ο�������
	if (canPlayPre)
	{
		startTime = GetTickCount();
		canPlayPre = false;
		adventureGamePre_buffer.Play(false);
	}
	//�ƶ�һ�γ���
	if (judgeCanMove())
	{
		//�����ƶ�
		sceneMove();
		return;
	}
	if (canMakeSun)
	{
		makeSun();
		sunDisAppear();
		getSun();
	}
	handlleSpriteDead();
}

void Level3::loopLevelFrame()
{
	if (zombies.size() <= 0)
	{
		return;
	}
	vector<Zombie*>::iterator p;
	for (p = zombies.begin(); p != zombies.end(); p++)
	{
		(*p)->LoopFrame(true);
	}
	if (dirt->IsVisible() && dirt->LoopFrameOnce(true))
	{
		dirt->SetVisible(false);
	}
	vector<Plant*>::iterator iter;
	for (iter = plants.begin(); iter != plants.end(); iter++)
	{
		if ((*iter)->getType() == SUNFLOWER && (*iter)->getState() == PLANT_SUN_STATE)
		{
			if ((*iter)->LoopFrameOnce(true))
			{
				suns.push_back(new Sun(SUNPIC.img, SUNPIC.frameWidth, SUNPIC.frameHeight));
				Sun *sun = suns.back();
				sun->SetPosition((*iter)->getPlantX(), (*iter)->GetY());
				GAMELAYER layer;
				layer.layer = sun;
				layer.z_order = sceneLayers.size() + 1;
				layer.type_id = LAYER_BONUS;
				Append(layer);
				this->sunPower += 50;
				sunCount = 0;
				(*iter)->setState(PLANT_STAND_STATE);
			}
		}
		else
		{
			(*iter)->LoopFrame(true);
		}

	}
	vector<Sun*>::iterator p2;
	for (p2 = suns.begin(); p2 != suns.end(); p2++)
	{
		(*p2)->LoopFrame(true);
	}
}

void Level3::updateLevelSpriteState()
{
	vector<Zombie*>::iterator p;
	for (p = zombies.begin(); p != zombies.end(); p++)
	{
		if ((*p)->IsActive() == true && (*p)->IsVisible() == true)
		{
			if ((*p)->getState() == WALK_STATE)
			{
				(*p)->walk();
			}
			else if ((*p)->getState() == ATTACK_STATE)
			{
				(*p)->setAllStatePos();
			}
			else if ((*p)->getState() == LOSTHEADWALK_STATE)
			{
				(*p)->lostHeadWalk();
			}
		}
	}

	vector<Plant*>::iterator p2;
	for (p2 = plants.begin(); p2 != plants.end(); p2++)
	{
		if ((*p2)->IsActive() == true && (*p2)->IsVisible() == true)
		{
			if ((*p2)->getState() == PLANT_SHOOT_STATE)
			{
				(*p2)->weaponMove();
				vector<Zombie*>::iterator p3;
				for (p3 = zombies.begin(); p3 != zombies.end(); p3++)
				{
					if ((*p2)->CollideWith(*p3))
					{
						(*p2)->attack((*p3));
						(*p2)->setWeaponVisible(false);
					}
				}
			}
		}
	}
}

void Level3::changeSpriteState()
{
	//  �ı�ֲ���״̬
	vector<Zombie*>::iterator p;
	for (p = zombies.begin(); p != zombies.end(); p++)
	{
		//if((*p)->CollideWith(this->getBarrier())) (*p)->setState(ATTACK_STATE);

		vector<Plant*>::iterator p2;
		for (p2 = plants.begin(); p2 != plants.end(); p2++)
		{
			if ((*p2)->getType() == SUNFLOWER)
			{
				if (rand() % 40000 < 1)
				{
					(*p2)->setState(PLANT_SUN_STATE);
				}
			}

			//����ʬ��ײ�� ֲ��  ��ʬ����ֲ��
			if ((*p2)->getValidY() == (*p)->getValidY() && (*p)->CollideWith(*p2) && (*p)->getRemianLive() > 0)
			{
				(*p)->setState(ATTACK_STATE);
				(*p)->attack(*p2);
			}
			// ����ʬ���֡�������ͬһ����ֲ��ʱ��ֲ������Ϊ����ʱ���������
			if ((*p2)->getValidY() == (*p)->getValidY() && (*p)->getState() != DIE_STATE)
			{
				if ((*p2)->getType() == PEASHOOTER)
				{
					if ((*p)->GetX() <= 810 && (*p2)->getPlantX() + (*p2)->GetWidth() <= (*p)->GetX() + 135)
					{
						(*p2)->setState(PLANT_SHOOT_STATE);	//���ֵĽ���״̬
					}
				}
			}
		}
	}
}

void Level3::mouseMove(int x, int y)
{
	pcb.MenuMouseMove(x, y);			//ֲ�������ƶ��¼�
	blockIndex = getClickBlock(x, y);	//����ƶ�ʱ ��ȡ��ƺ����
	if (plant == NULL)
	{
		return;
	}
	//plant��Ϊ��  ��ʾ��ѡ�е�ֲ��	��������������ƶ�
	plant->SetPosition(x - plant->GetWidth() / 2, y - plant->GetHeight() / 2);
}

void Level3::mouseClick(int x, int y)
{
	int plantType = pcb.MenuMouseClick(x, y);
	//���ֲ���ʱ����ȡֲ������
	// �����ж��ص�ֲ��
	if (plantType >= 0 && pcb.getSelected())	//����ȡ����ֲ������   ����  ֲ��۵�״̬Ϊѡ��ʱ  �Ž��д���ֲ��  ���ǲ�û����ӽ�������
	{
		plant = new Plant(plantStatic[plantType]);
		plant->SetRatio(1);
		plant->SetActive(true);
		plant->SetRotation(TRANS_NONE);
		plant->SetVisible(true);
		plant->setState(PLANT_STATIC_STATE);
		plant->setCostSun(COSTSUN[plantType]);
		plant->SetAlpha(255);
		plant->SetPosition(x - plant->GetWidth() / 2, y - plant->GetHeight() / 2);
		plant->setType(plantType);
		plant->SetLayerTypeID(LAYER_PLY);
	}
	else if (plantType >= 0 && !pcb.getSelected())
	{
		plant = NULL;
	}
	// TODO ������ǽ��֡����
	//��  ֲ���Ϊѡ��״̬ʱ���ҵ���˲�ƺ   ��ֲ����ӽ�����
	addPlant();
	vector<Sun*>::iterator p;
	for (p = suns.begin(); p != suns.end(); p++)
	{
		if ((*p)->mouseClickSun(x, y))
		{
			(*p)->setIsGet(true);
			(*p)->setEndX(8);
			(*p)->setEndY(-3);
			break;
		}
	}
}

int Level3::getClickBlock(int x, int y)
{
	int Index = -1;
	POINT pt;
	pt.x = x;
	pt.y = y;

	RECT rec;

	int iCount = 0;
	for (int i = 0; i < LEVEL3_VALID_BLOCKNUMBER; i++)
	{
		rec.left = LEVEL3_VALID_BLOCKPOS[i][0];
		rec.top = LEVEL3_VALID_BLOCKPOS[i][1];
		rec.right = rec.left + LEVEL3_VALID_BLOCKPOS[i][2];
		rec.bottom = rec.top + LEVEL3_VALID_BLOCKPOS[i][3];
		if (PtInRect(&rec, pt))
		{
			return iCount;
		}
		iCount++;
	}
	return Index;
}

bool Level3::Win()
{
	if (curentZombieNumber == 9)
	{
		if (zombies.size() == 0)
		{
			return true;
		}
	}
	return false;
}

bool Level3::Lose()
{
	// �����ʬ��Ϊ�ղ��ж�
	if (!zombies.empty())
	{
		// �������еĽ�ʬ���Ƿ񴥼���
		vector<Zombie*>::iterator p;
		for (p = zombies.begin(); p != zombies.end(); p++)
		{
			// ���ͻ�Ʒ��ߣ���ʧ��
			if ((*p)->GetX() + (*p)->GetRatioSize().cx < 0)
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

void Level3::activeZombieToAppear()
{
	if (curentZombieNumber < 10)
	{
		int number = 1;
		if (curentZombieNumber > 3)
		{
			number = rand() % 2 + 1;
		}
		else if (curentZombieNumber > 5)
		{
			number = rand() % 4 + 1;
		}
		else if (curentZombieNumber > 7)
		{
			number = rand() % 5 + 1;
		}
		zombiesCount[curentZombieNumber]++;
		if (curentZombieNumber == 0 && zombiesCount[curentZombieNumber] > 1000)
		{
			addZombie(NORMAL_ZOMBIE, number);
			curentZombieNumber++;
		}
		else if (zombiesCount[curentZombieNumber] > 1000 || (zombies.size() == 0 && zombiesCount[curentZombieNumber] > 200))
		{
			addZombie(NORMAL_ZOMBIE, number);
			curentZombieNumber++;
		}
	}
}

void Level3::initSound(HWND m_hWnd)
{
	if (!ds.CreateDS(m_hWnd))
	{
		return;
	}
	pcb.initSound(m_hWnd);
	gameRunMenuMouseClick_buffer.LoadWave(ds, GAME_MENU_CLICK_MUSIC.c_str());
	adventureGamePre_buffer.LoadWave(ds, ADVENTURE_GAME_PRE.c_str());
	gameBgm_buffer.LoadWave(ds, GAME_LEVEL1_BG_MUSIC.c_str());
	plant1_buffer.LoadWave(ds, PLANT1.c_str());
	plant2_buffer.LoadWave(ds, PLANT2.c_str());
}

void Level3::initZombie()
{
	for (int i = 0; i < LEVEL2_ZOMBIE_NUMBER; i++)
	{
		int type = rand() % 3;
		Zombie *zombie = new Zombie(normalZombieStatic[type]);
		zombie->SetSequence(NORMAL_ZOMBIE_STATIC_FRAME[type], 132);
		SPRITEINFO info;
		info.Dir = DIR_LEFT;
		info.Speed = NORMAL_ZOMBIE_SPEED;
		info.Level = 1;
		info.Visible = true;
		info.Active = false;
		info.Dead = false;
		info.Alpha = 255;
		info.Ratio = 1;
		info.Rotation = TRANS_NONE;
		info.X = LEVEL2_ZOMBIE_APPEAR_X[i];
		info.Y = ZOMBIE_APPEAR_Y[rand() % 5];
		zombie->SetLayerTypeID(LAYER_NPC);
		zombie->Initiate(info);
		zombie->setState(STATIC_STATE);
		GAMELAYER layer;
		layer.layer = zombie;
		layer.type_id = LAYER_NPC;
		layer.z_order = this->getSceneLayers()->size() + 1;
		this->Append(layer);
		zombieLayers.push_back(layer);
		zombies.push_back(zombie);
	}
}

void Level3::initBoard()
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(PEASHOOTER_CARD);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.isFocused = false;
	info.type = PEASHOOTER;
	info.state = 1;
	info.quiteCount = 0;
	info.name = L"�㶹����";
	info.costPower = 100;
	info.waitTime = WAITTIME[info.type];
	info.quiteCount = 0;
	info.pos.x = 75;
	info.pos.y = 1;
	pcb.addCardItem(info);

	MYSTARTMENUINFO info2;
	info2.btn = new T_Graph(SUNFLOWER_CARD);
	info2.width = info.btn->GetImageWidth();
	info2.height = info.btn->GetImageHeight() / 2;
	info2.isFocused = false;
	info2.type = SUNFLOWER;
	info2.state = 1;
	info2.quiteCount = 0;
	info2.name = L"���տ�";
	info2.costPower = 50;
	info2.waitTime = WAITTIME[info.type];
	info2.quiteCount = 0;
	info2.pos.x = 75 + info2.width + 5;
	info2.pos.y = 1;
	pcb.addCardItem(info2);

	info2.btn = new T_Graph(WALLNUT_CARD);
	info2.width = info.btn->GetImageWidth();
	info2.height = info.btn->GetImageHeight() / 2;
	info2.isFocused = false;
	info2.type = WALLNUT;
	info2.state = 1;
	info2.quiteCount = 0;
	info2.name = L"С���ǽ";
	info2.costPower = 50;
	info2.waitTime = WAITTIME[info.type];
	info2.quiteCount = 0;
	info2.pos.x = 75 + info2.width + 5 + info2.width + 5;
	info2.pos.y = 1;
	pcb.addCardItem(info2);
}

void Level3::handlleSpriteDead()
{
	handlePlantDead();
	handleZombieDead();
}

void Level3::handlePlantDead()
{
	//����ֲ�������
	vector<Plant*>::iterator p;
	for (p = plants.begin(); p != plants.end(); )
	{
		if ((*p)->IsDead())
		{
			vector<GAMELAYER>::iterator p2;
			for (p2 = sceneLayers.begin(); p2 != sceneLayers.end(); p2++)
			{
				if (p2->layer == *p)
				{
					this->Remove(*p2);
					break;
				}
			}
			p = plants.erase(p);
			if (p == plants.end())
			{
				break;
			}
		}
		else
		{
			p++;
		}
	}
}

void Level3::handleZombieDead()
{
	//����ʬ����
	vector<Zombie*>::iterator p;
	for (p = zombies.begin(); p != zombies.end(); )
	{
		if ((*p)->IsDead())
		{
			vector<GAMELAYER>::iterator p2;
			for (p2 = sceneLayers.begin(); p2 != sceneLayers.end(); p2++)
			{
				if (p2->layer == *p)
				{
					this->Remove(*p2);
					break;
				}
			}
			p = zombies.erase(p);
			if (p == zombies.end())
			{
				break;
			}
		}
		else
		{
			p++;
		}
	}
}

void Level3::makeSun()
{
	sunCount++;
	if ((sunCount % 900 == 250 + rand() % 400 && zombies.size() == 0) || (sunCount % 900 == 400 && zombies.size() > 0))
	{
		suns.push_back(new Sun(SUNPIC.img, SUNPIC.frameWidth, SUNPIC.frameHeight));
		Sun *sun = suns.back();
		sun->setEndY(rand() % 240 + 200);
		sun->SetPosition(rand() % 500 + 100, -rand() % 100 - 70);
		GAMELAYER layer;
		layer.layer = sun;
		layer.z_order = sceneLayers.size() + 1;
		layer.type_id = LAYER_BONUS;
		Append(layer);
		this->sunPower += 50;
		sunCount = 0;
	}
}

void Level3::getSun()
{
	vector<Sun*>::iterator p;
	for (p = suns.begin(); p != suns.end(); )
	{
		if ((*p)->getReached())
		{
			float ratio = (*p)->GetRatio();
			int ratioCount = (*p)->getReceive();
			ratioCount++;
			(*p)->setReceive(ratioCount);
			if (ratioCount % int(5000 + (1 - ratio) * 5000) == 0)
			{
				ratio -= 0.05f;
				(*p)->setReceive(0);
				(*p)->SetRatio(ratio);		//��̫���𽥱�С   С��һ���̶�ʱ  ɾ��
			}
			if (ratio <= 0.2f)
			{
				vector<GAMELAYER>::iterator p2;
				for (p2 = sceneLayers.begin(); p2 != sceneLayers.end(); p2++)
				{
					if (p2->layer == *p)
					{
						this->Remove(*p2);
						this->sunPower += 50;
						pcb.addSunPower(50);
						break;
					}
				}
				p = suns.erase(p);
				if (p == suns.end())
				{
					break;
				}
			}
		}
		else
		{
			p++;
		}
	}
}

void Level3::addPlant()
{
	if (pcb.getSelected() && blockIndex >= 0)
	{
		GAMELAYER plantLayer;
		//����Ϊ��ֲ��λ��
		int random = rand() % 2;		//���������ֲ����
		if (random == 0)
		{
			plant1_buffer.Play(false);
		}
		else
		{
			plant2_buffer.Play(false);
		}
		plant->SetPosition(LEVEL3_VALID_BLOCKPOS[blockIndex][0] +
			(LEVEL3_VALID_BLOCKPOS[blockIndex][2] - plant->GetWidth()) / 2, LEVEL3_VALID_BLOCKPOS[blockIndex][1]);
		plant->init(plant->getType());	//��ʼ��ʼ��ֲ��
		// TODO �ж�ֲ���Ƿ���Լ���
		plants.push_back(plant);		//�����ֲ����
		int num = blockIndex / 9;
		plant->setValidY(num + 1);
		plant->initSound(hwnd);
		plant->setState(PLANT_STAND_STATE);
		plantLayer.layer = plants.back();
		plantLayer.type_id = LAYER_MAP_BARR;
		plantLayers.push_back(plantLayer);
		plantLayer.z_order = this->getSceneLayers()->size() + 1;
		this->Insert(plantLayer, 2);//��ӽ�����
		pcb.setSelected(false);		//����ֲ���Ϊδѡ��
		dirt->SetPosition(LEVEL3_VALID_BLOCKPOS[blockIndex][0] +
			(LEVEL3_VALID_BLOCKPOS[blockIndex][2] - plant->GetWidth()) / 2 + 8,
			LEVEL3_VALID_BLOCKPOS[blockIndex][1] + plant->GetHeight());
		dirt->SetVisible(true);
		this->sunPower -= plant->getCostSun();
		pcb.addSunPower(-plant->getCostSun());
		pcb.setState(plant->getType(), 0);

		plant = NULL;				//ѡ��ֲ��Ҳ���
	}
}

void Level3::addZombie(int zomeType, int num)
{
	for (int i = 0; i < num; i++)
	{
		int type = rand() % 3;
		Zombie *zombie = new Zombie(normalZombieStatic[type]);
		zombie->SetSequence(NORMAL_ZOMBIE_STATIC_FRAME[type], 132);
		SPRITEINFO info;
		info.Dir = DIR_LEFT;
		info.Speed = NORMAL_ZOMBIE_SPEED;
		info.Level = 1;
		info.Visible = true;
		info.Active = true;
		info.Dead = false;
		info.Alpha = 255;
		info.Ratio = 1;
		info.Rotation = TRANS_NONE;
		info.X = rand() % 200 + 900;
		int num = rand() % 5;
		info.Y = ZOMBIE_APPEAR_Y[num];
		zombie->setValidY(num+1);
		zombie->SetLayerTypeID(LAYER_NPC);
		zombie->Initiate(info);
		zombie->init(zomeType);
		zombie->setState(WALK_STATE);
		GAMELAYER layer;
		layer.layer = zombie;
		layer.type_id = LAYER_NPC;
		layer.z_order = this->getSceneLayers()->size() + 1;
		this->Append(layer);
		zombieLayers.push_back(layer);
		zombies.push_back(zombie);
	}
}

void Level3::sunDisAppear()
{
	vector<Sun*>::iterator p;
	for (p = suns.begin(); p != suns.end(); )
	{
		if ((*p)->GetY() == (*p)->getEndY())
		{
			int stayTime = (*p)->getSunStayTime();
			stayTime--;
			(*p)->setSunStayTime(stayTime);
			if (stayTime <= 0)
			{
				vector<GAMELAYER>::iterator p2;
				for (p2 = sceneLayers.begin(); p2 != sceneLayers.end(); p2++)
				{
					if (p2->layer == *p)
					{
						this->Remove(*p2);
						break;
					}
				}
				p = suns.erase(p);
				if (p == suns.end())
				{
					break;
				}
			}
			else
			{
				p++;
			}
		}
		else
		{
			p++;
		}
	}
}

void Level3::sceneMove()
{
	if (canMove)
	{
		if (!canToRight)
		{
			SceneX -= 4;
			if (SceneX <= LEVEL_START_POS_X)
			{
				SceneX = LEVEL_START_POS_X;
				canMove = !canMove;
				canMakeSun = true;
				pcb.setVisible(true);
				adventureGamePre_buffer.Stop();
				gameBgm_buffer.Play(true);
			}
		}
		else
		{
			SceneX += 4;
			if (SceneX >= LEVEL1_SCENEWIDTH - WIN_WIDTH)
			{
				SceneX = LEVEL1_SCENEWIDTH - WIN_WIDTH;
				canMove = !canMove;
			}
		}
	}
}

void Level3::Draw(HDC hdc, int x, int y)
{
	// ���㳡����ǰ�����볡����һ������Ĳ�ֵ
	int offsetX = 0;
	int offsetY = 0;
	offsetX = (abs(lastSceneX) - abs(SceneX));
	offsetY = (abs(lastSceneY) - abs(SceneY));
	// 	// ���ͼ�㷢�����κα仯
	// 	if (LayerChanged == true)
	// 	{
	// 		SortLayers();//��ͼ����������
	// 	}

	int pX, pY;
	// ����ȫ��ͼ��
	SCENE_LAYERS::iterator p;
	for (p = sceneLayers.begin(); p != sceneLayers.end(); p++)
	{
		// ����ÿ��ͼ��Ҫƽ�ƵĲ���
		pX = (*p).layer->GetX();
		pX += offsetX;
		pY = (*p).layer->GetY();
		pY += offsetY;
		(*p).layer->SetPosition(pX, pY);
		// ���ͼ��ɼ�,������Ƴ���
		if ((*p).layer->IsVisible() == true)
		{
			if (p - sceneLayers.begin() == 1)
			{
				pcb.DrawMenu(hdc);
			}
			(*p).layer->Draw(hdc);//����ͼ���Լ��Ļ��Ʒ���
		}
	}

	//�����ݸ�λ
	lastSceneX = SceneX;
	lastSceneY = SceneY;
}

bool Level3::judgeCanMove()
{
	//��֤����ֻ�ƶ�����  ���ظ�һ��
	if (scnMoveCount < 2 && !canMove)
	{
		//�ó���ͣ��170��ѭ����λ
		timeCount++;
		if (timeCount > 170)
		{
			timeCount = 0;
			scnMoveCount++;
			canMove = !canMove;
			canToRight = !canToRight;
		}
	}
	return canMove;
}
