#include "Game.h"
#include "MyConfig.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	LPCTSTR WinTitle = L"植物大战僵尸";
	Game* game = new Game(hInstance, WIN_CLASS, WinTitle, NULL, NULL, WIN_WIDTH, WIN_HEIGHT);
	T_Engine::pEngine = game;
	game->SetFrame(1000);
	game->StartEngine();
	return true;
}


Game::Game(HINSTANCE h_instance, LPCTSTR sz_winclass, LPCTSTR sz_title,
	WORD icon, WORD sm_icon, int winWidth, int winHeight) : T_Engine(h_instance, sz_winclass,
		sz_title, icon, sm_icon, winWidth, winHeight)
{
	wndWidth = winWidth;
	wndHeight = winHeight;
	clickMenuIndex = -1;
}

Game::~Game()
{
}
//资源初始化
void Game::GameInit()
{
	srand(GetTickCount());
	this->initSound();			//加载需要的音效资源
	this->initMenu();			//加载菜单
	this->initRole();			//加载角色
	this->initLevels();			//加载所有的关卡
	bgm_buffer.Play(true);		//循环播放背景音乐
	GameState = GAME_START;
}

void Game::GameLogic()
{
	if (GameState == GAME_WAIT)
	{
		if (readyToGameAdventure())
		{
			GameState = GAME_ADVENTURE;
		}
	}

	else if (GameState == GAME_ADVENTURE && LEVEL_1 == LevelState)
	{
		level1->loopLevelFrame();
		level1->changeSpriteState();
		level1->updateLevelSpriteState();
		level1->activeZombieToAppear();
		if (level1->Win())
		{
			win_buffer.Play(false);
			LevelState = LEVEL_1_2;
		}
	}

	else if (GameState == GAME_ADVENTURE && LEVEL_2 == LevelState)
	{
		level2->loopLevelFrame();
		level2->changeSpriteState();
		level2->updateLevelSpriteState();
		level2->activeZombieToAppear();
		if (level2->Win())
		{
			win_buffer.Play(false);
			LevelState = LEVEL_2_3;
		}
	}

	else if (GameState == GAME_ADVENTURE && LEVEL_3 == LevelState)
	{
		level3->loopLevelFrame();
		level3->changeSpriteState();
		level3->updateLevelSpriteState();
		level3->activeZombieToAppear();
		if (level3->Win())
		{
			win_buffer.Play(false);
			LevelState = LEVEL_2_3;
		}
	}
}

void Game::GameEnd()
{ 
}

void Game::GamePaint(HDC hdc)
{
	if (GameState == GAME_START)
	{
		startMenu->DrawMenu(hdc);
	}
	else if (GameState == GAME_WAIT)
	{
		startMenu->DrawMenu(hdc);
		zombieHand->Draw(hdc);
	}
	else if (GameState == GAME_QUIT)
	{
		startMenu->DrawMenu(hdc);
		quitMenu->DrawMenu(hdc);
	}
	else if (GameState == GAME_HELP)
	{
		helpMenu->DrawMenu(hdc);
	}
	else if (GameState == GAME_ABOUT)
	{
		aboutMenu->DrawMenu(hdc);
	}
	else if (GameState == GAME_ADVENTURE && LEVEL_1 == LevelState)
	{
		level1->start(hdc);
	}
	else if (GameState == GAME_ADVENTURE && LevelState == LEVEL_1_2)
	{
		passGameMenu->initCard(SUNFLOWER_CARD);
		passGameMenu->DrawMenu(hdc);
	}
	else if (GameState == GAME_ADVENTURE && LevelState == LEVEL_2)
	{
		level2->start(hdc);
	}
	else if (GameState == GAME_ADVENTURE && LevelState == LEVEL_2_3)
	{
		passGameMenu->initCard(WALLNUT_CARD);
		passGameMenu->DrawMenu(hdc);
	}
	else if (GameState == GAME_ADVENTURE && LevelState == LEVEL_3)
	{
		level3->start(hdc);
	}
}

void Game::GameKeyAction(int Action)
{
}

void Game::GameMouseAction(int x, int y, int Action)
{
	MouseMoveHandle(x, y, Action, GameState);
	if (Action == MOUSE_LCLICK)
	{
		if (GameState == GAME_START)
		{
			int index = startMenu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					activeZombieHand();
					clickMenuIndex = 0;
					break;
				case 1:
					activeZombieHand();
					clickMenuIndex = 1;
					break;
				case 2:
					activeZombieHand();
					clickMenuIndex = 2;
					break;
				case 3:
				
					
					break;
				case 4:
					GameState = GAME_ABOUT;
					break;
				case 5:
					GameState = GAME_HELP;
					break;
				case 6:
					GameState = GAME_QUIT;
					break;
				}
			}
		}

		else if (GameState == GAME_QUIT)
		{
			int index = quitMenu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				switch (index)
				{
				case 0:
					SendMessage(m_hWnd, WM_SYSCOMMAND, SC_CLOSE, 0);
					break;
				case 1:
					GameState = GAME_START;
					break;
				}
			}
		}

		else if (GameState == GAME_HELP)
		{
			int index = helpMenu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				GameState = GAME_START;
			}
		}
		else if (GameState == GAME_ABOUT)
		{
			int index = aboutMenu->MenuMouseClick(x, y);
			if (index >= 0)
			{
				GameState = GAME_START;
			}
		}
		else if (GameState == GAME_ADVENTURE)
		{
			if (LEVEL_1 == LevelState)
			{
				level1->mouseClick(x, y);
			}
			else if (LEVEL_2 == LevelState)
			{
				level2->mouseClick(x, y);
			}
			else if (LEVEL_3 == LevelState)
			{
				level3->mouseClick(x, y);
			}
			else if (LevelState == LEVEL_1_2)
			{
				int index = passGameMenu->MenuMouseClick(x, y);
				if (index >= 0)
				{
					GameState = GAME_ADVENTURE;
					LevelState = LEVEL_2;	// TODO 跳关预览，但是有问题
				}
			}
			else if (LevelState == LEVEL_2_3)
			{
				int index = passGameMenu->MenuMouseClick(x, y);
				if (index >= 0)
				{
					GameState = GAME_ADVENTURE;
					LevelState = LEVEL_3;
				}
			}
			else if (LevelState == level_3_4)
			{
				int index = passGameMenu->MenuMouseClick(x, y);
				if (index >= 0)
				{
					GameState = GAME_ADVENTURE;
					LevelState = LEVEL_4;
				}
			}
		}
	}
}

//激活僵尸手动画
void Game::activeZombieHand()
{
	GameState = GAME_WAIT;
	LevelState = LEVEL_1;			//进入第一关												
	zombieHand->SetVisible(true);
	zombieHand->SetActive(true);
	enter_buffer.Play(false);
	loseGame_buffer.Play(false);
	bgm_buffer.Stop();
}

//准备进入游戏
bool Game::readyToGameAdventure()
{
	zombieHand->LoopFrameOnce(true);
	startMenu->SetMenuIndex(clickMenuIndex);
	startMenu->changeMenuFocusd();
	if (startMenu->countNum >= ZOMBIEHAND_REMAIN_TIME)
	{
		startMenu->reset();
		zombieHand->reset();
		clickMenuIndex = -1;
		return true;
	}
	return false;
}

void Game::initRole()
{
	/************************************************************************/
	//初始化僵尸手角色
	zombieHand = new ZombieHand(ZOMBIEHAND, 330, 330);
	zombieHand->init();
	/************************************************************************/

}

void Game::initMenu()
{
	/************************************************************************/
	//开始菜单相关设置
	startMenu = new StartMenu(); //创建开始菜单对象
	/*	startMenu->SetMenuBkg(L".\\res\\startMenu\\Surface.png");*/
	startMenu->init();		//初始化开始菜单
	startMenu->SetMoveSound(&startMenuMouseMove_buffer);		//设置开始菜单移动音效
	startMenu->SetClickSound(&startMenuMouseClick_buffer);		//设置开始菜单点击音效
	/*************************************************************************/

	/*************************************************************************/
	//退出游戏菜单相关设置
	quitMenu = new QuitMenu();
	quitMenu->init();
	quitMenu->SetMoveSound(&startMenuMouseMove_buffer);
	quitMenu->SetClickSound(&graveMenu_buffer);
	/*************************************************************************/

	/*************************************************************************/
	//帮助菜单相关设置
	helpMenu = new HelpMenu();
	helpMenu->init();
	helpMenu->SetMoveSound(&startMenuMouseMove_buffer);
	helpMenu->SetClickSound(&startMenuMouseClick_buffer);
	/************************************************************************/
	passGameMenu = new PassGameMenu();
	passGameMenu->init();
	passGameMenu->SetMoveSound(&startMenuMouseMove_buffer);
	passGameMenu->SetClickSound(&startMenuMouseClick_buffer);

	aboutMenu = new AboutMenu();
	aboutMenu->init();
	aboutMenu->SetMoveSound(&startMenuMouseMove_buffer);
	aboutMenu->SetClickSound(&startMenuMouseClick_buffer);
}

//加载音乐资源
void Game::initSound()
{
	if (!ds.CreateDS(m_hWnd))
	{
		return;
	}
	startMenuMouseMove_buffer.LoadWave(ds, START_MENU_MOVE_MUSIC.c_str());
	startMenuMouseClick_buffer.LoadWave(ds, START_MENU_CLICK_MUSIC.c_str());
	bgm_buffer.LoadWave(ds, START_MENU_BGM_MUSIC.c_str());
	enter_buffer.LoadWave(ds, ENTERGAME_MUSIC.c_str());
	graveMenu_buffer.LoadWave(ds, QUITGAME_MENU_CLICK_MUSIC.c_str());
	loseGame_buffer.LoadWave(ds, LOSEGAME_MUSIC.c_str());
	win_buffer.LoadWave(ds, WIN_MUSIC.c_str());
}

void Game::initLevels()
{
	level1 = new Level1();
	level1->init(m_hWnd);
	level2 = new Level2();
	level2->init(m_hWnd);
 	level3 = new Level3();
	level3->init(m_hWnd);
}



void Game::MouseMoveHandle(int x, int y, int Action, int theGameState)
{
	if (Action == MOUSE_MOVE && theGameState == GAME_START)
	{
		startMenu->MenuMouseMove(x, y);
	}
	else if (Action == MOUSE_MOVE && theGameState == GAME_QUIT)
	{
		quitMenu->MenuMouseMove(x, y);
	}
	else if (Action == MOUSE_MOVE && theGameState == GAME_HELP)
	{
		helpMenu->MenuMouseMove(x, y);
	}
	else if (Action == MOUSE_MOVE && theGameState == GAME_ABOUT)
	{
		aboutMenu->MenuMouseMove(x, y);
	}
	else if (Action == MOUSE_MOVE && theGameState == GAME_ADVENTURE)
	{
		if (LevelState == LEVEL_1)
		{
			level1->mouseMove(x, y);
		}
		else if (LevelState == LEVEL_2)
		{
			level2->mouseMove(x, y);
		}
		else if (LevelState == LEVEL_3)
		{
			level3->mouseMove(x, y);
		}
		else if (LevelState == LEVEL_1_2 || LevelState == LEVEL_2_3 || LevelState == level_3_4)
		{
			passGameMenu->MenuMouseMove(x, y);
		}
	}
}