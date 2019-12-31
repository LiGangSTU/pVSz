#include "PlantCardBoard.h"



PlantCardBoard::PlantCardBoard()
{
	srand(GetTickCount());
	m_index = -1;
	key_index = 0;
	isItemFocused = false;
	bkImageAlpha = 255;
	bkColor = RGB(0, 0, 0);
	m_MoveSound = NULL;
	m_ClickSound = NULL;
	board = new T_Graph(CARDBOARD);
	textBg = new T_Graph(TEXTBG);
	visible = false;
	dynamicY = -board->GetImageWidth();
	sunNumRect.X = 15;
	sunNumRect.Width = 50;
	sunNumRect.Height = 40;
	sunNumRect.Y = dynamicY + 40;
	sunPower = 50;
	selected = false;
	startTime = GetTickCount();
}


PlantCardBoard::~PlantCardBoard()
{
}

void PlantCardBoard::addCardItem(MYSTARTMENUINFO info)
{
	myMenuItems.push_back(info);
}

void PlantCardBoard::changeFocus(int index)
{
	vector<MYSTARTMENUINFO>::iterator p;
	int indexCount = 0;
	for (p = myMenuItems.begin(); p != myMenuItems.end(); p++, index++)
	{
		if (index == indexCount)
		{
			p->isFocused = true;
		}
	}
}

void PlantCardBoard::DrawMenu(HDC hdc, BYTE btnTrans, bool startState)
{
	if (visible == true)
	{
		dynamicY += 10;
		if (dynamicY >= 0)
		{
			dynamicY = 0;
		}
		sunNumRect.Y = dynamicY + 40;
		wsprintf(sunNum, L"%d", sunPower);
		board->PaintImage(hdc, 10, dynamicY, board->GetImageWidth(), board->GetImageHeight(), 255);
		T_Graph::PaintText(hdc, sunNumRect, sunNum, 12, L"微软雅黑", Color::Black);
		int mIndex = 0;
		vector<MYSTARTMENUINFO>::iterator p;
		for (p = myMenuItems.begin(); p != myMenuItems.end(); p++)
		{
			if (p->costPower > sunPower || p->state == 0) p->isFocused = true;
			else if(p->costPower <= sunPower && p->state == 1) p->isFocused = false;
			if (!p->isFocused)  
			{
				int x = p->pos.x;
				int y = p->pos.y;
				int w = p->width;
				int h = p->height;
				// 绘制卡片图像
				if (&p->btn != NULL)
				{
					p->btn->PaintRegion(p->btn->GetBmpHandle(), hdc, x, dynamicY + y, 0, 0, w, h, 1, 0, btnTrans);
				}
			}
			else    //绘制冷却时卡片
			{
				int x = p->pos.x;
				int y = p->pos.y;
				int w = p->width;
				int h = p->height;
				if (&p->btn != NULL)
				{
					p->btn->PaintRegion(p->btn->GetBmpHandle(), hdc, x, dynamicY + y, 0, h, w, h, 1, 0, btnTrans);
					endTime = GetTickCount();
					if (p->state == 0)
					{
						p->quiteCount++;
						if (endTime - startTime >= 1000)
						//if (p->quiteCount % 100 == 0)
						{
							startTime = endTime;
							p->waitTime -= 1;
							p->quiteCount = 0;
							if (p->waitTime <= 0)
							{
								p->quiteCount = 0;
								p->state = 1;
								p->waitTime = WAITTIME[p->type];
								p->isFocused = !p->isFocused;
							}
						}
						RectF rec;
						rec.Width = 85;
						rec.Height = 30;
						rec.X = p->pos.x;
						rec.Y = p->pos.y + dynamicY + p->height/3;
						wsprintf(remainTime, L"%d", p->waitTime);
						T_Graph::PaintText(hdc, rec, remainTime, 18, L"宋体", Color::Red);
					}
				}
			}
			//当鼠标悬浮时  显示文字
			if (mIndex == m_index && !selected)
			{
				RectF rec;
				rec.Width = 85;
				rec.Height = 45;
				rec.X = p->pos.x;
				rec.Y = p->pos.y + dynamicY + board->GetImageHeight() + 2;
				//文字的背景图片
				textBg->PaintImage(hdc, rec.X, rec.Y, textBg->GetImageWidth(), textBg->GetImageHeight(), btnTrans);
				if (p->state == 0)
				{	//状态为冷却时
					T_Graph::PaintText(hdc, rec, L"冷却中...\n" + p->name, 8, L"宋体", Color::Red);
				}
				else 
				{	//状态为非冷却时
					if (sunPower >= p->costPower)
					{	//  阳光足够
						T_Graph::PaintText(hdc, rec, p->name, 8, L"宋体", Color::Black);
					}
					else
					{
						T_Graph::PaintText(hdc, rec, L"没有足够的阳光...\n" + p->name, 8, L"宋体", Color::Red);
					}
				}
			}
			mIndex++;
		}
	}
}

void PlantCardBoard::MenuMouseMove(int x, int y)
{
	lastIndex = m_index;//记录前一次的索引值
	m_index = GetMenuIndex(x, y);
}

int PlantCardBoard::GetMenuIndex(int x, int y)
{
	int Index = -1;
	POINT pt;
	pt.x = x;
	pt.y = y;

	RECT rec;

	int iCount = 0;
	vector<MYSTARTMENUINFO>::iterator iter;
	for (iter = myMenuItems.begin(); iter != myMenuItems.end(); iter++)
	{
		int w = iter->width;
		int h = iter->height;
		rec.left = iter->pos.x;
		rec.top = iter->pos.y;
		rec.right = rec.left + w;
		rec.bottom = rec.top + h;

		if (PtInRect(&rec, pt))
		{
			return iCount;
		}
		iCount++;
	}
	return Index;
}

int PlantCardBoard::MenuMouseClick(int x, int y)
{
	m_index = GetMenuIndex(x, y);
	if (m_index >= 0)
	{
		int iCount = -1;
		if (!selected)			//没有选植物时  可以选中植物
		{
			vector<MYSTARTMENUINFO>::iterator iter;
			for (iter = myMenuItems.begin(); iter != myMenuItems.end(); iter++)
			{
				iCount++;
				if (iCount == m_index)
				{
					if (sunPower >= iter->costPower && iter->state != 0)
					{
						selected = !selected;	// 当选中植物时，设置为选中
						plantSelected_buffer.Play(false);
						return iter->type;		//点击植物槽  返回对应的植物类型
					}
				}
			}
		}
		else
		{
			selected = !selected;			//当选中植物时  再次点击植物槽  恢复原样
			gameMenu_buffeer.Play(false);
		}
	}

	return m_index;
}

//初始化音乐素材
void PlantCardBoard::initSound(HWND m_hWnd)
{
	if (!ds.CreateDS(m_hWnd))
	{
		return;
	}
	plantSelected_buffer.LoadWave(ds, SEED_SELECT.c_str());
	gameMenu_buffeer.LoadWave(ds, GAME_MENU_CLICK_MUSIC.c_str());
}

// 增加  或  减少阳光数量
void PlantCardBoard::addSunPower(int power)
{
	this->sunPower += power;
}

//按照卡片类型不同 设置卡片冷却状态
void PlantCardBoard::setState(int type, int state)
{
	vector<MYSTARTMENUINFO>::iterator p;
	for (p = myMenuItems.begin(); p != myMenuItems.end(); p++)
	{
		if (p->type == type)
		{
			p->state = state;
		}
	}
}

