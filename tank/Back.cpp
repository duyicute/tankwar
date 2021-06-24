#include "Back.h"


CBack::CBack(void)
{
	m_hBmpgrassland = 0;
	m_hBmpriver = 0;
	m_hBmpstone = 0;
	m_hBmpperson = 0;
	m_hBmpwall = 0;
}


CBack::~CBack(void)
{
	::DeleteObject(m_hBmpgrassland);
	::DeleteObject(m_hBmpriver);
	::DeleteObject(m_hBmpstone);
	::DeleteObject(m_hBmpperson);
	::DeleteObject(m_hBmpwall);
}

#define size 30

void CBack::InitBack(HINSTANCE hIns)
{
	m_hBmpgrassland = ::LoadBitmap(hIns,MAKEINTRESOURCE(grassland));
	m_hBmpriver = ::LoadBitmap(hIns,MAKEINTRESOURCE(river));
	m_hBmpstone = ::LoadBitmap(hIns,MAKEINTRESOURCE(stone));
	m_hBmpperson = ::LoadBitmap(hIns,MAKEINTRESOURCE(person));
	m_hBmpwall = ::LoadBitmap(hIns,MAKEINTRESOURCE(wall));
}

BOOL CBack::LoadMap()
{
	FILE* pf = NULL;
	fopen_s(&pf,"../map.txt","rb");

	if(pf == 0)
		return FALSE;

	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			char c = fgetc(pf);
			ArrBackMap[i][j] = c - '0';
		}
		fgetc(pf);
		fgetc(pf);
	}
	fclose(pf);
	pf=0;
	return TRUE;
}
void CBack::ShowBack(HDC hdc)
{
	
	Rectangle(hdc,0,0,600,600);
	HDC hMemDC = CreateCompatibleDC(hdc);

	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			/*if(ArrBackMap[i][j] == 1)
			{
				SelectObject(hMemDC,hBack);
				BitBlt(hdc,30*j,30*i,30,30,hMemDC,0,0,SRCCOPY);
			}*/
			switch(ArrBackMap[i][j])
			{
			case Grassland:
				SelectObject(hMemDC,m_hBmpgrassland);
				BitBlt(hdc,30*j,30*i,size,size,hMemDC,0,0,SRCCOPY);
				break;
			case River:
				SelectObject(hMemDC,m_hBmpriver);
				BitBlt(hdc,30*j,30*i,size,size,hMemDC,0,0,SRCCOPY);
				break;
			case Stone:
				SelectObject(hMemDC,m_hBmpstone);
				BitBlt(hdc,30*j,30*i,size,size,hMemDC,0,0,SRCCOPY);
				break;
			case Wall:
				SelectObject(hMemDC,m_hBmpwall);
				BitBlt(hdc,30*j,30*i,size,size,hMemDC,0,0,SRCCOPY);
				break;
			case 5:
				SelectObject(hMemDC,m_hBmpperson);
				BitBlt(hdc,270,540,60,60,hMemDC,0,0,SRCCOPY);
				break;

			}
			//SelectObject(hMemDC,m_hBmpperson);
			//BitBlt(hdc,270,540,60,60,hMemDC,0,0,SRCCOPY);
		}	
	}
	DeleteDC(hMemDC);
}
int CBack::GetTypeOfMap(int posX, int posY)
{ 
	return ArrBackMap[posY][posX];
}

void CBack::SetTypeOfMap(int x, int y, int type)
{
	ArrBackMap[y][x] = type;
}