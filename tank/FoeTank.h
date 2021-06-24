#pragma once
#include"sys.h"
#include"Player.h"
#include"Gunner.h"

class CFoeTank
{
public:
	HBITMAP h_nBitFoeTankmapUp;
	HBITMAP h_nBitFoeTankmapDown;
	HBITMAP h_nBitFoeTankmapRight;
	HBITMAP h_nBitFoeTankmapLeft;
	int m_nBlood;
	int m_nFX;
	int x;
	int y;

public:
	CFoeTank(void);
	virtual ~CFoeTank(void);

public:
	virtual void InitFoxPlane(HINSTANCE hIns)=0;
	//virtual =0;
	
public:
	bool CheckFoeTank(int FX,CBack& back);
	bool IsBoom();
	void DownBlood();
	bool IsGunnerHitFoxPlane(CGunner* pGunner);
	void SendGunner(HINSTANCE hIns,CGunnerBox &gunBox) ;
	bool IsFoeHitPlayer(CPlayer &player);
	void IsFoxPlaneMove(CBack&back);
	void ShowFoxPlane(HDC hdc);

};

