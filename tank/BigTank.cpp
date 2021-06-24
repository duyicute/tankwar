#include "BigTank.h"


CBigTank::CBigTank(void)
{
	x = 30;
	y = 0;
}


CBigTank::~CBigTank(void)
{

}

void CBigTank::InitFoxPlane(HINSTANCE hIns)
{
	h_nBitFoeTankmapUp = ::LoadBitmap(hIns,MAKEINTRESOURCE(silveryup));
	h_nBitFoeTankmapDown = ::LoadBitmap(hIns,MAKEINTRESOURCE(silverydown));
	h_nBitFoeTankmapRight = ::LoadBitmap(hIns,MAKEINTRESOURCE(silveryright));
	h_nBitFoeTankmapLeft = ::LoadBitmap(hIns,MAKEINTRESOURCE(silveryleft));
}
