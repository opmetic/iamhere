#pragma once
#ifndef __MSGBOX_H__
#define __MSGBOX_H__

#include "BaseWindowWnd.h"

class CMsgBox : public CBaseWindowWnd 
{
public:
	CMsgBox(void);
	CMsgBox(CStdString skinName, int indexWnd);
	~CMsgBox(void);

	void Notify(TNotifyUI& msg); //事件响应　路由
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam); //消息响应 路由
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcLButtonDBLclk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	void SetMsgInfo(CStdString msg);
};

#endif // __MSGBOX_H__
