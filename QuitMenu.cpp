#include "QuitMenu.h"



QuitMenu::QuitMenu()
{
	m_index = -1;
	key_index = 0;
	isItemFocused = false;
	bkImageAlpha = 255;
	bkColor = RGB(0, 0, 0);

	m_MoveSound = NULL;
	m_ClickSound = NULL;

	this->bg = new T_Graph(QUITGAME_BG);
}


QuitMenu::~QuitMenu()
{
}

void QuitMenu::initCancelMenu()
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(CANCEL_MENU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = 467;
	info.pos.y = 355;
	myMenuItems.push_back(info);
}

void QuitMenu::initQuitMenu()
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(QUITGAME_MENU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = 320;
	info.pos.y = 355;
	myMenuItems.push_back(info);
}

void QuitMenu::init()
{
	initQuitMenu();
	initCancelMenu();
}

void QuitMenu::DrawMenu(HDC hdc, BYTE btnTrans, bool startState)
{
	//绘制墓碑
	bg->PaintImage(hdc, (WIN_WIDTH - bg->GetImageWidth()) / 2, (WIN_HEIGHT - bg->GetImageHeight()) / 2, 
		bg->GetImageWidth(), bg->GetImageHeight(), btnTrans);

	if (isItemFocused == FALSE)
	{
		Gdiplus::RectF Rec;
		vector<MYSTARTMENUINFO>::iterator iter;
		for (iter = myMenuItems.begin(); iter != myMenuItems.end(); iter++)
		{
			int x = iter->pos.x;
			int y = iter->pos.y;
			int w = iter->width;
			int h = iter->height;
			// 绘制按钮图像
			if (&iter->btn != NULL)
			{
				iter->btn->PaintRegion(iter->btn->GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnTrans);
			}
		}
	}
	if (isItemFocused == TRUE)
	{
		int mIndex = 0;
		Gdiplus::RectF Rec;
		vector<MYSTARTMENUINFO>::iterator iter;
		for (iter = myMenuItems.begin(); iter != myMenuItems.end(); iter++)
		{
			int x = iter->pos.x;
			int y = iter->pos.y;
			int w = iter->width;
			int h = iter->height;
			if (mIndex != m_index)
			{
				if (&iter->btn != NULL)
				{
					iter->btn->PaintRegion(iter->btn->GetBmpHandle(), hdc, x, y, 0, 0, w, h, 1, 0, btnTrans);
				}
			}
			if (mIndex == m_index)
			{
				if (&iter->btn != NULL)
				{
					iter->btn->PaintRegion(iter->btn->GetBmpHandle(), hdc, x, y, 0, h, w, h, 1, 0, btnTrans);
				}
			}
			mIndex = mIndex + 1;
		}
	}
}

int QuitMenu::MenuMouseClick(int x, int y)
{
	m_index = GetMenuIndex(x, y);
	if (m_index >= 0)
	{
		if (m_MoveSound && m_ClickSound)
		{
			m_MoveSound->Restore();
			m_ClickSound->Restore();
			m_ClickSound->Play(false);
		}
	}
	isItemFocused = false;
	return m_index;
}

void QuitMenu::MenuMouseMove(int x, int y)
{
	lastIndex = m_index;//记录前一次的索引值
	m_index = GetMenuIndex(x, y);
	if (m_index >= 0)
	{
		isItemFocused = true;
		//保证鼠标移过按钮只播放一次声音
		if (lastIndex != m_index)
		{
			if (m_MoveSound && m_ClickSound)
			{
				m_ClickSound->Restore();
				m_MoveSound->Restore();
				m_MoveSound->Play(false);
			}
		}
	}
	else
	{
		isItemFocused = false;
	}
}

int QuitMenu::GetMenuIndex(int x, int y)
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
