#pragma once
#include"sys.h"

#define MAP_HIGH 20
#define MAP_WIDTH 20

#define Grassland 1
#define River 2
#define Stone 3
#define Wall 4

class CBack
{
public:
	HBITMAP m_hBmpgrassland;
	HBITMAP m_hBmpriver;
	HBITMAP m_hBmpstone;
	HBITMAP m_hBmpperson;
	HBITMAP m_hBmpwall;
	int ArrBackMap[MAP_HIGH][MAP_WIDTH];
public:
	CBack(void);
	~CBack(void);
public:
	BOOL LoadMap();
	void InitBack(HINSTANCE hIns);
	void ShowBack(HDC hdc);
	int GetTypeOfMap(int posX, int posY);
	void CBack::SetTypeOfMap(int x, int y, int type);
};

