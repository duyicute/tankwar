#include "TankApp.h"

DECLARE(CTankApp)
CTankApp::CTankApp(void)
{
}


CTankApp::~CTankApp(void)
{
}

void CTankApp::OnCreateGame()
{
	//1.背景初始化
	back.LoadMap(); 
	back.InitBack(m_hIns);
	foetankbox.CreateFoePlane(m_hIns);
	//2.玩家坦克初始化
	player.InitPlayer(m_hIns);
	
	//3.启动所有定时器
	::SetTimer(m_hWnd,PLAYER_MOVE_TIMER_ID,100,0);	//玩家坦克启动
	::SetTimer(m_hWnd,PLANER_SENGGUNNER_TIMER_ID,1000,0);	//玩家坦克350ms发射一次炮弹
	::SetTimer(m_hWnd,FOETANK_SENDGUNNER_TIMER_ID,2000,0);	//敌人坦克发射炮弹
	::SetTimer(m_hWnd,FOETANK_MOVE_TIMER_ID,100,0);	//敌人坦克移动
	::SetTimer(m_hWnd,GUNNER_MOVE_TIMER_ID,100,0);	//炮弹10ms移动一次
	
}
void CTankApp::OnGameDraw()
{
	PAINTSTRUCT ps = {0};
	HDC hdc = ::BeginPaint(m_hWnd,&ps);
	HDC hMemDC = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hdc,600,600);
	::SelectObject(hMemDC,hBitmap);

	//================================================
	back.ShowBack(hMemDC);
	gunnerbox.AllGunnerShow(hMemDC);
	gunnerFoebox.AllGunnerShow(hMemDC);
	foetankbox.AllFoePlaneShow(hMemDC);
	player.ShowPlayer(hMemDC);
	
	
	
	//====================================================

	::BitBlt(hdc,0,0,600,600,hMemDC,0,0,SRCCOPY);

	::DeleteObject(hBitmap);
	::DeleteDC(hMemDC);
	::EndPaint(m_hWnd,&ps);
}
void CTankApp::OnGameRun(WPARAM TimerID)
{

	if(TimerID == FOETANK_SENDGUNNER_TIMER_ID)
	{	
		foetankbox.SendGunnerFoePlane(m_hIns,gunnerFoebox);

	}
	if(TimerID == FOETANK_MOVE_TIMER_ID)
	{
		foetankbox.AllFoePlaneMove(back);		
	}
	if(TimerID == PLANER_SENGGUNNER_TIMER_ID)
	{player.SendGunner(m_hIns,gunnerbox);
	}
	if(TimerID == GUNNER_MOVE_TIMER_ID)
	{gunnerbox.AllGunnerMove(back);
	gunnerFoebox.AllGunnerMove(back);
	int a = this->GunnerHitPlane();
	int b = this->IsFoeGunnerHitPlayer();
	
	if(this->IsGameOver()==true ||a==1||b==1)
		{
		
			::KillTimer(m_hWnd,PLAYER_MOVE_TIMER_ID);
			::KillTimer(m_hWnd,PLANER_SENGGUNNER_TIMER_ID);//玩家飞机350ms发射一次炮弹
			::KillTimer(m_hWnd,GUNNER_MOVE_TIMER_ID);	//炮弹10ms移动一次
			::KillTimer(m_hWnd,FOETANK_SENDGUNNER_TIMER_ID);	//创建敌人飞机
			::KillTimer(m_hWnd,FOETANK_MOVE_TIMER_ID);	//敌人飞机移动
		
			MessageBox(m_hWnd,"gameover","message",MB_OK);
		}
	
	}
		if(TimerID == PLAYER_MOVE_TIMER_ID)
	{
		if(GetAsyncKeyState(VK_RIGHT))	//GetAsyncKeyState:按一下动一下；GetKeyState：按一下不会停
			player.MovePlayer(VK_RIGHT,back);
		if(GetAsyncKeyState(VK_LEFT))
			player.MovePlayer(VK_LEFT,back);
		if(GetAsyncKeyState(VK_UP))
			player.MovePlayer(VK_UP,back);
		if(GetAsyncKeyState(VK_DOWN))
			player.MovePlayer(VK_DOWN,back);
		
	}			
	//重绘
	RECT rect = {0,0,600,600};
	::InvalidateRect(m_hWnd,&rect,FALSE);
}
//void CTankApp::OnKeyDown(WPARAM nKey)
//{
//
//}

int CTankApp::GunnerHitPlane()	//炮弹撞击敌人坦克
{
	
	list<CGunner*>::iterator iteGun = gunnerbox.m_lstGunner.begin();
	bool bflag = false;

	while(iteGun != gunnerbox.m_lstGunner.end())
	{
		list<CFoeTank*>::iterator iteFoe = foetankbox.m_lstFoePlane.begin();
		while(iteFoe != foetankbox.m_lstFoePlane.end())
		{
			if((*iteFoe)->IsGunnerHitFoxPlane(*iteGun) ==true)	//敌人坦克被玩家炮弹打中
			{
				//打到敌人坦克
				bflag = true;
				//1.删除炮弹
				delete(*iteGun);
				iteGun = gunnerbox.m_lstGunner.erase(iteGun);
				//2.敌人坦克掉血
				(*iteFoe)->DownBlood();
				if((*iteFoe)->IsBoom() == true)
				{					
					//1.删除敌人坦克
					foetankbox.m_lstFoePlane.erase(iteFoe);

				}	
				break;
			}
			++iteFoe;
		}
		
		if(bflag == false)
		{
			//2.判断玩家炮弹击中home
			if((*iteGun)->GunnerHitHome(back)==true)
			{
				return true;
			}
			++iteGun;
		}
		else
			bflag = false;
	}
	return false;
}

bool CTankApp::IsFoeGunnerHitPlayer()	//炮弹撞击玩家坦克
{
	
	list<CGunner*>::iterator iteGun = gunnerFoebox.m_lstGunner.begin();
	bool bflag = false;

	while(iteGun != gunnerFoebox.m_lstGunner.end())
	{
			if(player.IsGunnerHitPlayer(*iteGun) ==true)	//玩家坦克被炮弹打中
			{
				//打到玩家坦克
				bflag = true;
				//1.删除炮弹
				delete(*iteGun);
				iteGun = gunnerFoebox.m_lstGunner.erase(iteGun);
				//2.玩家坦克掉血
				player.DownBlood();
				
				if(player.m_blood == 0)
				{					
					//1.删除玩家坦克，游戏结束
					return true;
				}	
			}
		
		if(bflag == false)
		{//2.判断敌人炮弹击中home
			if((*iteGun)->GunnerHitHome(back))
				return true;
				++iteGun;
		}
		else
			bflag = false;
	}
	return false;
}

bool CTankApp::IsGameOver()
{
	list<CFoeTank*>::iterator ite = foetankbox.m_lstFoePlane.begin();

	while(ite != foetankbox.m_lstFoePlane.end())
	{
		if((*ite)->IsFoeHitPlayer(player)==true )
			return true;
		++ite;
	}
	if(player.m_blood==0)
		return true;

	return false;
}
