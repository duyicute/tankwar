#pragma once
#include"sys.h"
#include"Back.h"

class CGunner
{
public:
	HBITMAP m_hBmpGunnerup;
	HBITMAP m_hBmpGunnerdown;
	HBITMAP m_hBmpGunnerright;
	HBITMAP m_hBmpGunnerleft;
	int m_nFX;
	int x;
	int y;
public:
	CGunner(void);
	~CGunner(void);
public:
	void InitGunner(HINSTANCE hIns, int x, int y,int FX);
	bool MoveGunner(CBack&back);
	void ShowGunner(HDC hdc);
	bool GunnerHitWall(CBack &back);
	bool GunnerHitHome(CBack &back);
};

