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
	pBarrier = NULL;		//碰撞图层指针
	pMask = NULL;			//遮罩层指针
	LayerChanged = false;
	timeCount = 0;

	//自己定义的变量
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
//所有资源初始化
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
//初始化地图
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
//初始化草坪
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

//初始化音乐
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

//设置开场 右侧摆动僵尸
void Level1::initZombie()
{
	for (int i = 0; i < LEVEL1_ZOMBIE_NUMBER; i++)
	{
		// TODO 根据僵尸类型随机数字，导入不同的僵尸静态数据
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
//初始化植物槽
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
	info.name = L"豌豆射手";
	info.costPower = 100;
	info.waitTime = WAITTIME[info.type];
	info.quiteCount = 0;
	info.pos.x = 75;
	info.pos.y = 1;
	pcb.addCardItem(info);
}

//激活草坪铺开动画
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

//添加僵尸
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

//控制阳光的停留一段时间 然后消失
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

//场景开始
void Level1::start(HDC hdc)
{
	//绘制场景
	this->Draw(hdc, this->SceneX, this->SceneY);
/*	pcb.DrawMenu(hdc);*/
	dirt->Draw(hdc);
	//绘制透明植物
	if (blockIndex >= 0 && plant != NULL)
	{
		plant->PaintPic(hdc, LEVEL1_VALID_BLOCKPOS[blockIndex]);
	}
	//绘制选中植物
	if (plant != NULL)
	{
		plant->Draw(hdc);
	}
	//播放一次开场音乐
	if (canPlayPre)
	{
		startTime = GetTickCount();
		canPlayPre = false;
		adventureGamePre_buffer.Play(false);
	}
	//移动一次场景
	if (judgeCanMove())
	{
		//场景移动
		sceneMove();

		return;
	}
	//铺开草坪
	if (canActiveGrass)
	{
		//激活草坪卷开动画
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

//改变场景所有角色帧数
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

//根据场景中所有角色的状态  进而改变角色的行为
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
//根据场景中的现象  改变场景中的角色的状态  进而表现不同的行为
void Level1::changeSpriteState()
{
	//  改变植物的状态
	vector<Zombie*>::iterator p;
	for (p=zombies.begin(); p!=zombies.end(); p++)
	{
		//if((*p)->CollideWith(this->getBarrier())) (*p)->setState(ATTACK_STATE);
		vector<Plant*>::iterator p2;
		for (p2 = plants.begin(); p2 != plants.end(); p2++)
		{
			//当僵尸碰撞到 植物  僵尸攻击植物
			if ((*p)->CollideWith(*p2) && (*p)->getRemianLive()>0)
			{
				(*p)->setState(ATTACK_STATE);
				(*p)->attack(*p2);
			}
			// 当僵尸出现、并且在同一行有植物时，植物类型为射手时，进行射击
			if ((*p2)->getValidY() == (*p)->getValidY() && (*p)->getState() != DIE_STATE)
			{
				if ((*p2)->getType() == PEASHOOTER)
				{
					if ((*p)->GetX() <= 810 && (*p2)->getPlantX()+(*p2)->GetWidth() <= (*p)->GetX()+135
						&& (*p)->getValidY() == (*p2)->getValidY())
					{
						(*p2)->setState(PLANT_SHOOT_STATE);	//射手的进攻状态
					}
				}
			}
		}
	}
}

//鼠标移动事件
void Level1::mouseMove(int x, int y)
{
	pcb.MenuMouseMove(x, y);			//植物槽鼠标移动事件
	blockIndex = getClickBlock(x, y);	//鼠标移动时 获取草坪索引
	if (plant == NULL)
	{
		return;
	}
	//plant不为空  表示有选中的植物	设置其随着鼠标移动
	plant->SetPosition(x - plant->GetWidth()/2, y - plant->GetHeight()/2);
}
//鼠标点击事件
void Level1::mouseClick(int x, int y)
{
	int plantType = pcb.MenuMouseClick(x, y);	//点击植物槽时，获取植物类型
	if (plantType >= 0 && pcb.getSelected())	//当获取到了植物类型   并且  植物槽的状态为选中时  才进行创建植物  但是并没有添加进场景中
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
	//当  植物槽为选中状态时并且点击了草坪   将植物添加进场景
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

//获取点击到的草坪索引
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
 
//第一关是否获胜
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
// 关卡是否失败
bool Level1::Lose()
{
	// 如果僵尸不为空才判断
	if (!zombies.empty())
	{
		// 遍历所有的僵尸，是否触及线
		vector<Zombie*>::iterator p;
		for ( p = zombies.begin(); p != zombies.end(); p++)
		{
			// 如果突破防线，则失败
			if ((*p)->GetX() + (*p)->GetRatioSize().cx < 0 )
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

//僵尸出现
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
	// 清除僵尸
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

//处理角色的死亡状态
void Level1::handlleSpriteDead()
{
	handlePlantDead();
	handleZombieDead();
}
void Level1::handlePlantDead()
{
	//处理植物的死亡
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
	//处理僵尸死亡
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
//制造阳光
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

//得到太阳   加能量
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
				(*p)->SetRatio(ratio);		//将太阳逐渐变小   小到一定程度时  删除
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
		//设置为种植的位置
		int random = rand() % 2;		//随机播放种植音乐
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
		plant->init(plant->getType());	//开始初始化植物
		plants.push_back(plant);		//保存进植物类
		plant->setValidY(3);
		plant->initSound(hwnd);
		plant->setState(PLANT_STAND_STATE);
		plantLayer.layer = plants.back();
		plantLayer.type_id = LAYER_MAP_BARR;
		plantLayers.push_back(plantLayer);
		plantLayer.z_order = this->getSceneLayers()->size() + 1;
		this->Insert(plantLayer, 2);//添加进场景
		plantsCount++;				//植物数量加1
		pcb.setSelected(false);		//设置植物槽为未选中
		dirt->SetPosition(LEVEL1_VALID_BLOCKPOS[blockIndex][0] +
			(LEVEL1_VALID_BLOCKPOS[blockIndex][2] - plant->GetWidth()) / 2 + 8,
			LEVEL1_VALID_BLOCKPOS[blockIndex][1] + plant->GetHeight());
		dirt->SetVisible(true);
		this->sunPower -= plant->getCostSun();
		pcb.addSunPower(-plant->getCostSun());
		pcb.setState(plant->getType(), 0);
		plant = NULL;				//选中植物也清空
	}
}

//游戏开始时场景的移动
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

//绘制场景
void Level1::Draw(HDC hdc, int x, int y)
{
	// 计算场景当前坐标与场景上一次坐标的差值
	int offsetX = 0;
	int offsetY = 0;
	offsetX = (abs(lastSceneX) - abs(SceneX));
	offsetY = (abs(lastSceneY) - abs(SceneY));
// 	// 如果图层发生过任何变化
// 	if (LayerChanged == true)
// 	{
// 		SortLayers();//对图层重新排序
// 	}

	int pX, pY;
	// 遍历全部图层
	SCENE_LAYERS::iterator p;
	for (p = sceneLayers.begin(); p != sceneLayers.end(); p++)
	{
		// 计算每个图层要平移的步长
		pX = (*p).layer->GetX();
		pX += offsetX;
		pY = (*p).layer->GetY();
		pY += offsetY;
		(*p).layer->SetPosition(pX, pY);
		// 如果图层可见,将其绘制出来
		if ((*p).layer->IsVisible() == true)
		{
			if (p - sceneLayers.begin() == 1)
			{
				pcb.DrawMenu(hdc);
			}
			(*p).layer->Draw(hdc);//调用图层自己的绘制方法
		}
	}

	//将数据复位
	lastSceneX = SceneX;
	lastSceneY = SceneY;
}

//判断当前场景是否可以移动   默认可移动   在场景头和尾部停留一点时间
bool Level1::judgeCanMove()
{
	//保证场景只移动两次  来回各一次
	if (scnMoveCount < 2 && !canMove)
	{
		//让场景停留170个循环单位
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


