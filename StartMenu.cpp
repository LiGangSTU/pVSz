#include "StartMenu.h"



StartMenu::StartMenu()
{
	m_index = -1;
	key_index = 0;
	isItemFocused = false;
	bkImageAlpha = 255;
	bkColor = RGB(0, 0, 0);
	countNum = 0;
	m_MoveSound = NULL;
	m_ClickSound = NULL;
	this->adventureShadow = new T_Graph(ADVENTURE_MENU_SHADOW);
	this->mini = new T_Graph(MINI_MENU_SHADOW);
	this->quiz = new T_Graph(QUIZ_MENU_SHADOW);
}


StartMenu::~StartMenu()
{
}

//��ʼ�˵���ʼ��
void StartMenu::init()
{
	this->SetMenuBkg(STARTMENU_BACK);		//���ò˵�����
	this->initAdventure();
	this->initMini();
	this->initQuiz();
	this->initHandBook();
	this->initOption();
	this->initHelp();
	this->initQuit();
}

//��ʼ���˳��˵���
void StartMenu::initQuit()
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(QUIT_MENU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = 813;
	info.pos.y = 520;
	myMenuItems.push_back(info);
}

void StartMenu::reset()
{
	countNum = 0;
	isItemFocused = false;
	m_index = -1;
}



//��ʼ��ѡ��˵���
void StartMenu::initOption() 
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(OPTION_MENU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = 650;
	info.pos.y = 498;
	myMenuItems.push_back(info);
}
//��ʼ������ѡ��
void StartMenu::initHelp()
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(HELP_MENU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = 727;
	info.pos.y = 528;
	myMenuItems.push_back(info);
}
//��ʼ��ͼ��
void StartMenu::initHandBook() 
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(HANDBOOK_MENU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = 374;
	info.pos.y = 428;
	myMenuItems.push_back(info);
}
//��ʼ��������Ϸ�˵���
void StartMenu::initQuiz() 
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(QUIZ_MENU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = 478;
	info.pos.y = 303;
	myMenuItems.push_back(info);
}
//��ʼ��������Ϸ�˵���
void StartMenu::initMini() 
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(MINI_MENU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = 474;
	info.pos.y = 203;
	myMenuItems.push_back(info);
}
//��ʼ��ð�ղ˵���
void StartMenu::initAdventure()
{
	MYSTARTMENUINFO info;
	info.btn = new T_Graph(ADVANTURE_MENU);
	info.width = info.btn->GetImageWidth();
	info.height = info.btn->GetImageHeight() / 2;
	info.pos.x = 474;
	info.pos.y = 80;
	myMenuItems.push_back(info);
}


//�˵�����
void StartMenu::DrawMenu(HDC hdc, BYTE btnTrans, bool startState)
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
	//����ð�ղ˵���Ŀ����Ӱ����
	adventureShadow->PaintImage(hdc, 468, 82, 350, 150, btnTrans);
	//����������Ϸ�˵�����Ӱ����
	mini->PaintImage(hdc, 476, 208, 318, 136, btnTrans);
	//����������Ϸ�˵�����Ӱ����
	quiz->PaintImage(hdc, 480, 307, 289, 127, btnTrans);
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


//���ݵ�ǰ����������˵���������
int StartMenu::GetMenuIndex(int x, int y)
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

void StartMenu::changeMenuFocusd()
{
	if (countNum % 5 == 0)
	{
		isItemFocused = !isItemFocused;
	}
	countNum++;
}

//�˵�����ƶ��¼�����
void StartMenu::MenuMouseMove(int x, int y)
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

int StartMenu::MenuMouseClick(int x, int y)
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
