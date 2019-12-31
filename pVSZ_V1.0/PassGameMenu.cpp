#include "PassGameMenu.h"



PassGameMenu::PassGameMenu()
{
	m_index = -1;
	key_index = 0;
	isItemFocused = false;
	bkImageAlpha = 255;
	bkColor = RGB(0, 0, 0);
	m_MoveSound = NULL;
	m_ClickSound = NULL;
}


PassGameMenu::~PassGameMenu()
{

}


void PassGameMenu::init()
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(PASSMENU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = (WIN_WIDTH - info.width) / 2;
	info.pos.y = WIN_HEIGHT - info.btn->GetImageHeight() - 80;
	myMenuItems.push_back(info);
	bg = new T_Graph(PASSMENUBG);
}

void PassGameMenu::initCard(wstring card)
{
	plantCard = new T_Graph(card);
}

//���ݵ�ǰ����������˵���������
int PassGameMenu::GetMenuIndex(int x, int y)
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
//�˵�����ƶ��¼�����
void PassGameMenu::MenuMouseMove(int x, int y)
{
	lastIndex = m_index;//��¼ǰһ�ε�����ֵ
	m_index = GetMenuIndex(x, y);
	if (m_index >= 0)
	{
		isItemFocused = true;
		//��֤����ƹ���ťֻ����һ������
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

int PassGameMenu::MenuMouseClick(int x, int y)
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


//�˵�����
void PassGameMenu::DrawMenu(HDC hdc, BYTE btnTrans, bool startState)
{
	bg->PaintImage(hdc, (WIN_WIDTH - bg->GetImageWidth()) / 2, (WIN_HEIGHT - bg->GetImageHeight()) / 2,
		bg->GetImageWidth(), bg->GetImageHeight(), btnTrans);
	plantCard->PaintRegion(plantCard->GetBmpHandle(), hdc, (WIN_WIDTH - plantCard->GetImageWidth()) / 2,
		200, 0, 0, plantCard->GetImageWidth(), plantCard->GetImageHeight() / 2, 1);
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
			// ���ư�ťͼ��
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