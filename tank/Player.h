#pragma once
#include"sys.h"
#include"Back.h"
#include"GuunerBox.h"

class CPlayer
{
public:
	HBITMAP m_hBmpUp;
	HBITMAP m_hBmpDown;
	HBITMAP m_hBmpRight;
	HBITMAP m_hBmpLeft;
	int x;
	int y;
	int pFX;
	int m_blood;
private:
	int oldX;
	int oldY;
public:
	CPlayer(void);
	~CPlayer(void);
public:
	bool CheckTank(int FX,CBack& back);
	void InitPlayer(HINSTANCE hIns);
	void MovePlayer(int FX,CBack& back);
	void SendGunner(HINSTANCE hIns,CGunnerBox &gunBox);
	void ShowPlayer(HDC hdc);
	bool IsGunnerHitPlayer(CGunner* pGunner);
	bool IsGunnerHitFoeTank(CGunnerBox &gunnerbox);
	void DownBlood();
};

