#include "Level1.h"
#include "MyConfig.h"


Level1::Level1()
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
	canActiveGrass = false;
	validY = 2;
	curentZombieNumber = 0;
	plantsCount = 0;
	blockIndex = -1;
	plant = NULL;
	canMakeSun = false;
}


Level1::~Level1()
{
	RemoveAll();
}
//������Դ��ʼ��
void Level1::init(HWND m_hWnd)
{
	hwnd = m_hWnd;
	this->InitScene(0, 0, LEVEL1_SCENEWIDTH, LEVEL1_SCENEHEIGHT, WIN_WIDTH, WIN_WIDTH);
	initMap();
	initGrass();
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
//��ʼ����ͼ
void Level1::initMap()
{
	GAMELAYER layer;
	map = new T_Map(LEVEL1_MAP);
	map->SetLayerTypeID(LAYER_MAP_BACK);
	layer.layer = map;
	layer.type_id = LAYER_MAP_BACK;
	layer.z_order = this->getSceneLayers()->size() + 1;
	this->Append(layer);
}
//��ʼ����ƺ
void Level1::initGrass()
{
	GAMELAYER layer;
	grass = new Level1Grass(LEVEL1_GRASS);
	grass->SetLayerTypeID(LAYER_MAP_BACK);
	grass->SetActive(false);
	grass->SetVisible(false);
	grass->SetRotation(TRANS_NONE);
	grass->SetAlpha(255);
	grass->SetRatio(1);
	grass->SetPosition(266, 264);
	grass->init();
	layer.layer = grass;
	layer.type_id = LAYER_MAP_BACK;
	layer.z_order = this->getSceneLayers()->size() + 1;
	this->Append(layer);
}

//��ʼ������
void Level1::initSound(HWND m_hWnd)
{
	if (!ds.CreateDS(m_hWnd))
	{
		return;
	}
	grass->initSound(m_hWnd);
	pcb.initSound(m_hWnd);
	gameRunMenuMouseClick_buffer.LoadWave(ds, GAME_MENU_CLICK_MUSIC.c_str());
	adventureGamePre_buffer.LoadWave(ds, ADVENTURE_GAME_PRE.c_str());
	gameBgm_buffer.LoadWave(ds, GAME_LEVEL1_BG_MUSIC.c_str());
	plant1_buffer.LoadWave(ds, PLANT1.c_str());
	plant2_buffer.LoadWave(ds, PLANT2.c_str());
}

//���ÿ��� �Ҳ�ڶ���ʬ
void Level1::initZombie()
{
	for (int i = 0; i < LEVEL1_ZOMBIE_NUMBER; i++)
	{
		// TODO ���ݽ�ʬ����������֣����벻ͬ�Ľ�ʬ��̬����
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
		info.X = ZOMBIE_APPEAR_X[i];
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
//��ʼ��ֲ���
void Level1::initBoard()
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
}

//�����ƺ�̿�����
void Level1::activeGrass(HDC hdc)
{
	if (grass->FinishedDrawGrass(hdc))
	{
		canActiveGrass = false;
		grass->SetActive(true);
		grass->SetVisible(true);
		adventureGamePre_buffer.Stop();
		gameBgm_buffer.Play(true);
		vector<GAMELAYER>::iterator p;
		for (p = zombieLayers.begin(); p != zombieLayers.end(); p++)
		{
			Remove(*p);
		}
		zombies.clear();
		pcb.setVisible(true);
		canMakeSun = true;
	}
}

//��ӽ�ʬ
void Level1::addZombie(int zombieType, int num)
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
		info.Y = ZOMBIE_APPEAR_Y[2];
		zombie->setValidY(3);
		zombie->SetLayerTypeID(LAYER_NPC);
		zombie->Initiate(info);
		zombie->init(zombieType);
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

//���������ͣ��һ��ʱ�� Ȼ����ʧ
void Level1::sunDisAppear()
{
	vector<Sun*>::iterator p;
	for (p = suns.begin(); p!=suns.end(); )
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

//������ʼ
void Level1::start(HDC hdc)
{
	//���Ƴ���
	this->Draw(hdc, this->SceneX, this->SceneY);
/*	pcb.DrawMenu(hdc);*/
	dirt->Draw(hdc);
	//����͸��ֲ��
	if (blockIndex >= 0 && plant != NULL)
	{
		plant->PaintPic(hdc, LEVEL1_VALID_BLOCKPOS[blockIndex]);
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
	//�̿���ƺ
	if (canActiveGrass)
	{
		//�����ƺ������
		activeGrass(hdc);
	}
	if (canMakeSun)
	{
		makeSun();
		sunDisAppear();
		getSun();
	}
	handlleSpriteDead();
}

//�ı䳡�����н�ɫ֡��
void Level1::loopLevelFrame()
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
		(*iter)->LoopFrame(true);
	}
	vector<Sun*>::iterator p2;
	for (p2 = suns.begin(); p2 != suns.end(); p2++)
	{
		(*p2)->LoopFrame(true);
	}
}

//���ݳ��������н�ɫ��״̬  �����ı��ɫ����Ϊ
void Level1::updateLevelSpriteState()
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
//���ݳ����е�����  �ı䳡���еĽ�ɫ��״̬  �������ֲ�ͬ����Ϊ
void Level1::changeSpriteState()
{
	//  �ı�ֲ���״̬
	vector<Zombie*>::iterator p;
	for (p=zombies.begin(); p!=zombies.end(); p++)
	{
		//if((*p)->CollideWith(this->getBarrier())) (*p)->setState(ATTACK_STATE);
		vector<Plant*>::iterator p2;
		for (p2 = plants.begin(); p2 != plants.end(); p2++)
		{
			//����ʬ��ײ�� ֲ��  ��ʬ����ֲ��
			if ((*p)->CollideWith(*p2) && (*p)->getRemianLive()>0)
			{
				(*p)->setState(ATTACK_STATE);
				(*p)->attack(*p2);
			}
			// ����ʬ���֡�������ͬһ����ֲ��ʱ��ֲ������Ϊ����ʱ���������
			if ((*p2)->getValidY() == (*p)->getValidY() && (*p)->getState() != DIE_STATE)
			{
				if ((*p2)->getType() == PEASHOOTER)
				{
					if ((*p)->GetX() <= 810 && (*p2)->getPlantX()+(*p2)->GetWidth() <= (*p)->GetX()+135
						&& (*p)->getValidY() == (*p2)->getValidY())
					{
						(*p2)->setState(PLANT_SHOOT_STATE);	//���ֵĽ���״̬
					}
				}
			}
		}
	}
}

//����ƶ��¼�
void Level1::mouseMove(int x, int y)
{
	pcb.MenuMouseMove(x, y);			//ֲ�������ƶ��¼�
	blockIndex = getClickBlock(x, y);	//����ƶ�ʱ ��ȡ��ƺ����
	if (plant == NULL)
	{
		return;
	}
	//plant��Ϊ��  ��ʾ��ѡ�е�ֲ��	��������������ƶ�
	plant->SetPosition(x - plant->GetWidth()/2, y - plant->GetHeight()/2);
}
//������¼�
void Level1::mouseClick(int x, int y)
{
	int plantType = pcb.MenuMouseClick(x, y);	//���ֲ���ʱ����ȡֲ������
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
		plant->SetPosition(x-plant->GetWidth()/2, y - plant->GetHeight()/2);
		plant->setType(plantType);
		plant->SetLayerTypeID(LAYER_PLY);
	}
	else if (plantType >= 0 && !pcb.getSelected())
	{
		plant = NULL;
	}
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

//��ȡ������Ĳ�ƺ����
int Level1::getClickBlock(int x, int y)
{
	int Index = -1;
	POINT pt;
	pt.x = x;
	pt.y = y;

	RECT rec;

	int iCount = 0;
	for (int i = 0; i < LEVEL1_VALID_BLOCKNUMBER; i++)
	{
		rec.left = LEVEL1_VALID_BLOCKPOS[i][0];
		rec.top = LEVEL1_VALID_BLOCKPOS[i][1];
		rec.right = rec.left + LEVEL1_VALID_BLOCKPOS[i][2];
		rec.bottom = rec.top + LEVEL1_VALID_BLOCKPOS[i][3];
		if (PtInRect(&rec, pt))
		{
			return iCount;
		}
		iCount++;
	}
	return Index;
}
 
//��һ���Ƿ��ʤ
bool Level1::Win()
{
	if (curentZombieNumber == 5)
	{
		if (zombies.size() == 0)
		{
			gameBgm_buffer.Stop();
			return true;
		}
	}
	return false;
}
// �ؿ��Ƿ�ʧ��
bool Level1::Lose()
{
	// �����ʬ��Ϊ�ղ��ж�
	if (!zombies.empty())
	{
		// �������еĽ�ʬ���Ƿ񴥼���
		vector<Zombie*>::iterator p;
		for ( p = zombies.begin(); p != zombies.end(); p++)
		{
			// ���ͻ�Ʒ��ߣ���ʧ��
			if ((*p)->GetX() + (*p)->GetRatioSize().cx < 0 )
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

//��ʬ����
void Level1::activeZombieToAppear()
{
	if (curentZombieNumber < 5)
	{
		zombiesCount[curentZombieNumber]++;
		if (curentZombieNumber == 0 && zombiesCount[curentZombieNumber] > 1000)
		{
			addZombie(NORMAL_ZOMBIE);
			curentZombieNumber++;
		}
		else if (zombiesCount[curentZombieNumber] > 1000 || (zombies.size() == 0 && zombiesCount[curentZombieNumber] > 200))
		{
			addZombie(NORMAL_ZOMBIE);
			curentZombieNumber++;
		}
	}
}

void Level1::clearLevel()
{
	// �����ʬ
	if (!zombies.empty())
	{
		zombies.clear();
		return;
	}
	if (!zombieLayers.empty())
	{
		zombieLayers.clear();
	}

	//vector<Zombie*>::iterator p;
	/*for (p = zombies.begin(); p != zombies.end(); ++p)
	{
		zombies.erase(p);
	}*/
}

//�����ɫ������״̬
void Level1::handlleSpriteDead()
{
	handlePlantDead();
	handleZombieDead();
}
void Level1::handlePlantDead()
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
void Level1::handleZombieDead()
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
//��������
void Level1::makeSun()
{
	sunCount++;
	if ((sunCount % 900 == 250 + rand() % 400 && zombies.size() == 0) || (sunCount % 900 == 400 && zombies.size() > 0))
	{
		suns.push_back(new Sun(SUNPIC.img, SUNPIC.frameWidth, SUNPIC.frameHeight));
		Sun *sun = suns.back();
		sun->setEndY(rand() % 240 + 200);
		sun->SetPosition(rand()%500 + 100, -rand() % 100 - 70);
		GAMELAYER layer;
		layer.layer = sun;
		layer.z_order = sceneLayers.size() + 1;
		layer.type_id = LAYER_BONUS;
		Append(layer);
		this->sunPower += 50;
		sunCount = 0;
	}
}

//�õ�̫��   ������
void Level1::getSun()
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
			if (ratioCount % int(5000 + (1-ratio)*5000) == 0)
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

void Level1::addPlant()
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
		plant->SetPosition(LEVEL1_VALID_BLOCKPOS[blockIndex][0] +
			(LEVEL1_VALID_BLOCKPOS[blockIndex][2] - plant->GetWidth()) / 2, LEVEL1_VALID_BLOCKPOS[blockIndex][1]);
		plant->init(plant->getType());	//��ʼ��ʼ��ֲ��
		plants.push_back(plant);		//�����ֲ����
		plant->setValidY(3);
		plant->initSound(hwnd);
		plant->setState(PLANT_STAND_STATE);
		plantLayer.layer = plants.back();
		plantLayer.type_id = LAYER_MAP_BARR;
		plantLayers.push_back(plantLayer);
		plantLayer.z_order = this->getSceneLayers()->size() + 1;
		this->Insert(plantLayer, 2);//��ӽ�����
		plantsCount++;				//ֲ��������1
		pcb.setSelected(false);		//����ֲ���Ϊδѡ��
		dirt->SetPosition(LEVEL1_VALID_BLOCKPOS[blockIndex][0] +
			(LEVEL1_VALID_BLOCKPOS[blockIndex][2] - plant->GetWidth()) / 2 + 8,
			LEVEL1_VALID_BLOCKPOS[blockIndex][1] + plant->GetHeight());
		dirt->SetVisible(true);
		this->sunPower -= plant->getCostSun();
		pcb.addSunPower(-plant->getCostSun());
		pcb.setState(plant->getType(), 0);
		plant = NULL;				//ѡ��ֲ��Ҳ���
	}
}

//��Ϸ��ʼʱ�������ƶ�
void Level1::sceneMove()
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
				canActiveGrass = true;
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

//���Ƴ���
void Level1::Draw(HDC hdc, int x, int y)
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

//�жϵ�ǰ�����Ƿ�����ƶ�   Ĭ�Ͽ��ƶ�   �ڳ���ͷ��β��ͣ��һ��ʱ��
bool Level1::judgeCanMove()
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


