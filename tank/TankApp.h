#pragma once
#include "gameapp.h"
#include"Back.h"
#include"Player.h"
#include"GuunerBox.h"
#include"FoeTankBox.h"

class CTankApp :
	public CGameApp
{
public:
	CTankApp(void);
	~CTankApp(void);
public:
	CBack back;
	CPlayer player;
	CGunnerBox  gunnerbox;
	CGunnerBox  gunnerFoebox;
	CFoeTankBox foetankbox;

public:
	virtual void OnCreateGame();
	virtual void OnGameDraw();
	virtual void OnGameRun(WPARAM TimerID);
	//virtual void OnKeyDown(WPARAM nKey);
	int GunnerHitPlane();
	bool IsGameOver();
	
	bool IsFoeGunnerHitPlayer();
	
};

