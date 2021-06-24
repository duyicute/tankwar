#pragma once
#include "foetank.h"
class CBigTank :
	public CFoeTank
{
public:
	CBigTank(void);
	~CBigTank(void);

public:
	virtual void InitFoxPlane(HINSTANCE hIns);
};

