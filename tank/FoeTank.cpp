#include "FoeTank.h"
#define H 30
#define L 30

CFoeTank::CFoeTank(void)
{
	h_nBitFoeTankmapUp = 0;
	h_nBitFoeTankmapDown = 0;
	h_nBitFoeTankmapRight = 0;
	h_nBitFoeTankmapLeft = 0;
	m_nBlood = 3;
	m_nFX = 0;
	x = 0;
	y = 0;
}


CFoeTank::~CFoeTank(void)
{
	::DeleteObject(h_nBitFoeTankmapUp);
	::DeleteObject(h_nBitFoeTankmapDown);
	::DeleteObject(h_nBitFoeTankmapRight);
	::DeleteObject(h_nBitFoeTankmapLeft);
}

bool CFoeTank::IsBoom()
{
	if(m_nBlood==0)
		return true;
	return false;
}
void CFoeTank::DownBlood()
{
	m_nBlood = m_nBlood--;
}

bool CFoeTank::IsFoeHitPlayer(CPlayer &player)
{
	if(player.x+15 >= this->x && player.x <= this->x+30 
		&& player.y >= this->y && player.y <= this->y+30)
		return true;
	if(player.x >= this->x && player.x <= this->x+30
		&& player.y+15 >= this->y && player.y+15 <= this->y+30)
		return true;
	if(player.x >= this->x && player.x<= this->x+30 
		&& player.y+15 >= this->y && player.y+15 <= this->y+30)
		return true;
	return false;
}
bool CFoeTank::IsGunnerHitFoxPlane(CGunner* pGunner)	//敌人坦克是否中弹
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


void CFoeTank::SendGunner(HINSTANCE hIns,CGunnerBox &gunBox)	
{
	//1.创建炮弹对象
	CGunner* pGunner = new CGunner;
	//2.初始化炮弹
	pGunner->InitGunner(hIns,x,y,m_nFX);
	//3.添加到链表中
	gunBox.m_lstGunner.push_back(pGunner);
}

bool CFoeTank::CheckFoeTank(int FX,CBack& back)	//检测坦克前方有无障碍，无障碍返回真
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



void CFoeTank::IsFoxPlaneMove(CBack&back)	//敌人坦克移动
{

	if(m_nFX == VK_UP && y>0)	//up
	{y-=1;if(this->CheckFoeTank(m_nFX,back)) return;}
	if(m_nFX == VK_DOWN && y<570)	//down
	{y+=1;if(this->CheckFoeTank(m_nFX,back)) return;}
	if(m_nFX == VK_LEFT && x>0)	//left
	{x-=1;if(this->CheckFoeTank(m_nFX,back)) return;}
	if(m_nFX == VK_RIGHT && x<570)	//right
	{x+=1;if(this->CheckFoeTank(m_nFX,back)) return;}
}
void CFoeTank::ShowFoxPlane(HDC hdc)
{
	HDC hMemDC = ::CreateCompatibleDC(hdc);
	int n= rand()%200;
	switch(n)
	{
	case 0:
			m_nFX = VK_DOWN;//0;
		break;
	case 1:
			m_nFX = VK_UP;//1;
		break;
	case 2:
			m_nFX = VK_RIGHT;//2;
		break;
	case 3:
			m_nFX = VK_LEFT;//3;
		break;
	}
	if(m_nFX == VK_UP)
		::SelectObject(hMemDC,h_nBitFoeTankmapUp);
	if(m_nFX == VK_DOWN)
		::SelectObject(hMemDC,h_nBitFoeTankmapDown);
	if(m_nFX == VK_RIGHT)
		::SelectObject(hMemDC,h_nBitFoeTankmapRight);
	if(m_nFX == VK_LEFT)
		::SelectObject(hMemDC,h_nBitFoeTankmapLeft);
	::BitBlt(hdc,x,y,30,30,hMemDC,0,0,SRCAND);
	::DeleteDC(hMemDC);
}

