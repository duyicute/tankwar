#pragma once
#include"FoeTank.h"

class CFoeTankBox
{
public:
	list<CFoeTank*>  m_lstFoePlane;

public:
	CFoeTankBox(void);
	~CFoeTankBox(void);
public:
	void AllFoePlaneMove(CBack&back);
	void AllFoePlaneShow(HDC hdc);
	void CreateFoePlane(HINSTANCE hIns);
	void SendGunnerFoePlane(HINSTANCE hIns,CGunnerBox &gunBox);
	//void IsGunnerHitPlayer(CGunnerBox &gunBox,CPlayer &player);
};

