#include "AboutMenu.h"



AboutMenu::AboutMenu()
{
}


AboutMenu::~AboutMenu()
{

}

void AboutMenu::init()
{
	this->SetMenuBkg(ABOUT_MENU_BG);
	initBackToMainMenu();
}

void AboutMenu::initBackToMainMenu()
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(HELP_MENU_MAINMANU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = (WIN_WIDTH - info.width) / 2;
	info.pos.y = WIN_HEIGHT - info.btn->GetImageHeight() - 20;
	myMenuItems.push_back(info);
}

void AboutMenu::MenuMouseMove(int x, int y)
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

int AboutMenu::MenuMouseClick(int x, int y)
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

int AboutMenu::GetMenuIndex(int x, int y)
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

void AboutMenu::DrawMenu(HDC hdc, BYTE btnTrans, bool startState)
{
	if (&gm_menuBkg != NULL && startState == true)
	{
		HBITMAP tBmp = T_Graph::CreateBlankBitmap(WIN_WIDTH, WIN_HEIGHT, bkColor);
		SelectObject(hdc, tBmp);

		gm_menuBkg.PaintImage(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, bkImageAlpha);

		DeleteObject(tBmp);
		tBmp = NULL;
	}
	else
	{
		T_Graph::PaintBlank(hdc, 0, 0, WIN_WIDTH, WIN_HEIGHT, MENU_BKCLR, MENU_ALPHA);
	}


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