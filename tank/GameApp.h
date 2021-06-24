#pragma once
#include <windows.h>

#define DECLARE(ThisClass) \
	CGameApp* CreateObject()\
	{\
		return new ThisClass;\
	}


class CGameApp
{
protected:
	HINSTANCE m_hIns;
	HWND m_hWnd;
public:
	CGameApp()
	{
		m_hIns = 0;
		m_hWnd = 0;
	}
	virtual ~CGameApp()
	{
	
	}
public:
	void SetHandle(HINSTANCE hIns,HWND hwnd)
	{
		m_hIns = hIns;
		m_hWnd = hwnd;
	}
public:
	virtual void OnCreateGame(){}   //  需要  HINSTANCE
	virtual void OnGameDraw(){}      //  需要 HWND
	virtual void OnGameRun(WPARAM nTimerID){}        //  需要  WPARAM 这个定时器编号
	virtual void OnKeyDown(WPARAM nKey){}         // 需要  WPARAM 这个具体的按键
	virtual void OnKeyUp(WPARAM nKey){}			// 需要  WPARAM 这个具体的按键
	virtual void OnLButtonDown(POINT point){}     //  需要一个坐标点  坐标的获取是通过 LPARAM
	virtual void OnLButtonUp(POINT point){}		//  需要一个坐标点  坐标的获取是通过 LPARAM
	virtual void OnMouseMove(POINT point){}		//  需要一个坐标点  坐标的获取是通过 LPARAM
};