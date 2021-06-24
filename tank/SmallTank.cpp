#include "SmallTank.h"


CSmallTank::CSmallTank(void)
{
	x = 540;
	y = 0;
}


CSmallTank::~CSmallTank(void)
{
}

void CSmallTank::InitFoxPlane(HINSTANCE hIns)
{
	h_nBitFoeTankmapUp = ::LoadBitmap(hIns,MAKEINTRESOURCE(greenup));
	h_nBitFoeTankmapDown = ::LoadBitmap(hIns,MAKEINTRESOURCE(greendown));
	h_nBitFoeTankmapRight = ::LoadBitmap(hIns,MAKEINTRESOURCE(greenright));
	h_nBitFoeTankmapLeft = ::LoadBitmap(hIns,MAKEINTRESOURCE(greenleft));
}

