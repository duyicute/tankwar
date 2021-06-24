#include "Player.h"

#define H 30
#define L 30
#define TankH 30
#define TankL 30

CPlayer::CPlayer(void)
{
	pFX = VK_UP;
	m_hBmpUp = 0;
	m_hBmpDown = 0;
	m_hBmpRight = 0;
	m_hBmpLeft = 0;
	x = 360;
	y = 570;
	m_blood = 5;
}


CPlayer::~CPlayer(void)
{
	DeleteObject(m_hBmpUp);
	DeleteObject(m_hBmpDown);
	DeleteObject(m_hBmpRight);
	DeleteObject(m_hBmpLeft);
}


void CPlayer::InitPlayer(HINSTANCE hIns)
{
	m_hBmpUp = LoadBitmap(hIns,MAKEINTRESOURCE(yellowup));
	m_hBmpDown = LoadBitmap(hIns,MAKEINTRESOURCE(yellowdown));
	m_hBmpRight = LoadBitmap(hIns,MAKEINTRESOURCE(yellowright));
	m_hBmpLeft = LoadBitmap(hIns,MAKEINTRESOURCE(yellowleft));
}

bool CPlayer::CheckTank(int FX,CBack& back)	//检测坦克前方有无障碍，无障碍返回真
{
	switch(FX)
	{
		case VK_RIGHT:
		{		
			if(this->y%H==0)
			{
				if(Wall == back.GetTypeOfMap((this->x)/H+1,(this->y)/L)||Stone == back.GetTypeOfMap((this->x)/H+1,(this->y)/L)||River == back.GetTypeOfMap((this->x)/H+1,(this->y)/L))
				{x=((this->x)/30)*30;return false;	}
			}
			else if(Wall == back.GetTypeOfMap((this->x)/H+1,(this->y)/L)|| Wall == back.GetTypeOfMap((this->x)/H+1,(this->y)/L+1)
				||Stone == back.GetTypeOfMap((this->x)/H+1,(this->y)/L)||Stone == back.GetTypeOfMap((this->x)/H+1,(this->y)/L+1)
				||River == back.GetTypeOfMap((this->x)/H+1,(this->y)/L)||River == back.GetTypeOfMap((this->x)/H+1,(this->y)/L+1))
				{x=((this->x)/30)*30;return false;}
			else
				return true;			
				
		}
		break;
	case VK_LEFT:
		{
			
				if(this->y%H==0)
				{
					if(Wall == back.GetTypeOfMap((this->x)/H,(this->y)/L)||Stone == back.GetTypeOfMap((this->x)/H,(this->y)/L)||River == back.GetTypeOfMap((this->x)/H,(this->y)/L))
					{x=((this->x)/30+1)*30;return false;}
				}
				else if(Wall == back.GetTypeOfMap((this->x)/H,(this->y)/L)|| Wall == back.GetTypeOfMap((this->x)/H,(this->y)/L+1)
					||Stone == back.GetTypeOfMap((this->x)/H,(this->y)/L)||Stone == back.GetTypeOfMap((this->x)/H,(this->y)/L+1)
					||River == back.GetTypeOfMap((this->x)/H,(this->y)/L)||River == back.GetTypeOfMap((this->x)/H,(this->y)/L+1))
					{x=((this->x)/30+1)*30;return false;}
				else
					return true;
			
		}
		break;
	case VK_UP:
		{
			
				if(this->x%L == 0){
					if(Wall == back.GetTypeOfMap((this->x)/H,(this->y)/L)||Stone == back.GetTypeOfMap((this->x)/H,(this->y)/L)||River == back.GetTypeOfMap((this->x)/H,(this->y)/L))
					{y=((this->y)/30+1)*30;;return false;}
					}
				else if(Wall == back.GetTypeOfMap((this->x)/H,(this->y)/L)|| Wall == back.GetTypeOfMap((this->x)/H+1,(this->y)/L)
					 ||Stone == back.GetTypeOfMap((this->x)/H,(this->y)/L)||Stone == back.GetTypeOfMap((this->x)/H+1,(this->y)/L)
					 ||River == back.GetTypeOfMap((this->x)/H,(this->y)/L)||River == back.GetTypeOfMap((this->x)/H+1,(this->y)/L))
						{y=((this->y)/30+1)*30;return false;}		
				else 
					return true;
			
		}
		break;
	case VK_DOWN:
		{
			
				if(this->x%L == 0){
					if(Wall == back.GetTypeOfMap((this->x)/H,(this->y)/L+1)||Stone == back.GetTypeOfMap((this->x)/H,(this->y)/L+1)||River == back.GetTypeOfMap((this->x)/H,(this->y)/L+1))
					{y=((this->y)/30)*30;return false;}
				}
				else if(Wall == back.GetTypeOfMap((this->x)/H,(this->y)/L+1)|| Wall == back.GetTypeOfMap((this->x)/H+1,(this->y)/L+1)
				 ||Stone == back.GetTypeOfMap((this->x)/H,(this->y)/L+1)||Stone == back.GetTypeOfMap((this->x)/H+1,(this->y)/L+1)
				 ||River == back.GetTypeOfMap((this->x)/H,(this->y)/L+1)||River == back.GetTypeOfMap((this->x)/H+1,(this->y)/L+1))
				{y=((this->y)/30)*30;return false;	}																								  
				else
					return true;
					
		}
		break;	
	}	
	return true;
}

void CPlayer::MovePlayer(int FX,CBack& back)
{
	pFX = FX;
	if(FX == VK_UP && y>0)	//up
	{y-=5;if(this->CheckTank(FX,back)) return;}
	if(FX == VK_DOWN && y<570)	//down
	{y+=5;if(this->CheckTank(FX,back)) return;}
	if(FX == VK_LEFT && x>0)	//left
	{x-=5;if(this->CheckTank(FX,back)) return;}
	if(FX == VK_RIGHT && x<570)	//right
	{x+=5;if(this->CheckTank(FX,back)) return;}
}

void CPlayer::ShowPlayer(HDC hdc)
{
	HDC hMemDC = CreateCompatibleDC(hdc);
	if(pFX == VK_UP)
		::SelectObject(hMemDC,m_hBmpUp);
	if(pFX == VK_DOWN)
		::SelectObject(hMemDC,m_hBmpDown);
	if(pFX == VK_RIGHT)
		::SelectObject(hMemDC,m_hBmpRight);
	if(pFX == VK_LEFT)
		::SelectObject(hMemDC,m_hBmpLeft);
	::BitBlt(hdc,x,y,TankH,TankL,hMemDC,0,0,SRCAND);
	::DeleteDC(hMemDC);
}
void CPlayer::SendGunner(HINSTANCE hIns,CGunnerBox &gunBox)
{
	//1.创建炮弹对象
	CGunner* pGunner = new CGunner;
	//2.初始化炮弹
	pGunner->InitGunner(hIns,x,y,pFX);
	//3.添加到链表中
	gunBox.m_lstGunner.push_back(pGunner);

}

bool CPlayer::IsGunnerHitPlayer(CGunner* pGunner)
{
	if(pGunner->x+15 >= this->x &&pGunner->x <= this->x+30 
		&& pGunner->y >= this->y && pGunner->y <= this->y+30)
		return true;
	if(pGunner->x >= this->x && pGunner->x <= this->x+30
		&& pGunner->y+15 >= this->y && pGunner->y+15 <= this->y+30)
		return true;
	if(pGunner->x >= this->x &&pGunner->x<= this->x+30 
		&& pGunner->y+15 >= this->y && pGunner->y+15 <= this->y+30)
		return true;
	return false;
}


void CPlayer::DownBlood()
{
	m_blood--;
}