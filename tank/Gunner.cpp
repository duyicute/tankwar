#include "Gunner.h"


CGunner::CGunner(void)
{
	m_nFX = VK_UP;
	m_hBmpGunnerup = 0;
	m_hBmpGunnerdown = 0;
	m_hBmpGunnerright = 0;
	m_hBmpGunnerleft = 0;
	x = 0;
	y = 0;
}


CGunner::~CGunner(void)
{
	::DeleteObject(m_hBmpGunnerup);
	::DeleteObject(m_hBmpGunnerdown);
	::DeleteObject(m_hBmpGunnerright);
	::DeleteObject(m_hBmpGunnerleft);
}

void CGunner::InitGunner(HINSTANCE hIns, int x1, int y1,int FX)
{
	m_hBmpGunnerup = LoadBitmap(hIns,MAKEINTRESOURCE(gunnerup));
	m_hBmpGunnerdown = LoadBitmap(hIns,MAKEINTRESOURCE(gunnerdown));
	m_hBmpGunnerright = LoadBitmap(hIns,MAKEINTRESOURCE(gunnerright));
	m_hBmpGunnerleft = LoadBitmap(hIns,MAKEINTRESOURCE(gunnerleft));
	
	m_nFX = FX;
	switch(m_nFX)
	{
	case VK_RIGHT:
		{x = x1+30;y = y1+15-3;}
		break;
	case VK_LEFT:
		{x = x1-9;y = y1+15-3;}
		break;
	case VK_UP:
		{x = x1+15-3;y = y1-9;}
		break;
	case VK_DOWN:
		{x = x1+15-3;y = y1+30+9;}
		break;
	}	
}


void CGunner::ShowGunner(HDC hdc)
{
	HDC hMemDC = CreateCompatibleDC(hdc);

	switch (m_nFX)
	{
	case VK_RIGHT:
		{
			::SelectObject(hMemDC,m_hBmpGunnerright);
			::BitBlt(hdc,x,y,9,6,hMemDC,0,0,SRCCOPY);
		}
		break;
	case VK_LEFT:
		{
			::SelectObject(hMemDC,m_hBmpGunnerleft);
			::BitBlt(hdc,x,y,9,6,hMemDC,0,0,SRCCOPY);
		}
		break;
	case VK_DOWN:
		{
			::SelectObject(hMemDC,m_hBmpGunnerdown);
			::BitBlt(hdc,x,y,6,9,hMemDC,0,0,SRCCOPY);
		}
		break;
	case VK_UP:
		{
			::SelectObject(hMemDC,m_hBmpGunnerup);
			::BitBlt(hdc,x,y,6,9,hMemDC,0,0,SRCCOPY);
		}
		break;
	}

	DeleteDC(hMemDC);
}
bool CGunner::MoveGunner(CBack&back)
{
	if(m_nFX == VK_UP&&y>-9)
	{
		if(Stone == back.GetTypeOfMap((this->x+3)/30,(this->y-4.5)/30)||River == back.GetTypeOfMap((this->x+3)/30,(this->y-4.5)/30))
			return true;
		else
			y-=10;
	}
	if(m_nFX == VK_DOWN&&y<609)
	{
		if(Stone == back.GetTypeOfMap((this->x+3)/30,(this->y+4.5)/30)||River == back.GetTypeOfMap((this->x+3)/30,(this->y+4.5)/30))
			return true;
		else
			y+=10;
	}
	if(m_nFX == VK_LEFT&&x>-9)
	{
		if(Stone == back.GetTypeOfMap((this->x+3)/30,(this->y+4.5)/30)||River == back.GetTypeOfMap((this->x+3)/30,(this->y+4.5)/30))
			return true;
		else
			x-=10;
	}
	if(m_nFX == VK_RIGHT&&x<609)
	{
		if(Stone == back.GetTypeOfMap((this->x+4.5)/30,(this->y+3)/30)||River == back.GetTypeOfMap((this->x+4.5)/30,(this->y+3)/30))
			return true;
		else
			x+=10;
	}
}

bool CGunner::GunnerHitWall(CBack &back)
{
	if(Wall == back.GetTypeOfMap((this->x)/30,(this->y)/30))
	{
		//Ïû³ýÇ½
		back.SetTypeOfMap((this->x)/30,(this->y)/30,0);
		return true;
	}
	return false;
}

bool CGunner::GunnerHitHome(CBack &back)
{
	if(this->x<600 && this->x>0 && this->y<600 && this->y>0 && 5 == back.GetTypeOfMap((this->x)/30,(this->y)/30))
	{
		back.SetTypeOfMap((this->x)/30,(this->y)/30,0);
		return true;
	}
	return false;
}