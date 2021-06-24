#pragma once
#include "foetank.h"
class CSmallTank :
	public CFoeTank
{
public:
	CSmallTank(void);
	~CSmallTank(void);
public:
	virtual void InitFoxPlane(HINSTANCE hIns);
};

