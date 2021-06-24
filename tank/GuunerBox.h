#pragma once
#include"sys.h"
#include"Gunner.h"

class CGunnerBox
{
public:
	list<CGunner*> m_lstGunner; 
public:
	CGunnerBox(void);
	~CGunnerBox(void);

public:
	void AllGunnerMove(CBack &back);
	void AllGunnerShow(HDC hdc);
};

