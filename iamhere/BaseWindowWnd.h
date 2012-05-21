#ifndef __BASEWINDOWWND_H__
#define __BASEWINDOWWND_H__

#include "iamhere.h"

class CBaseWindowWnd : public CWindowWnd, public INotifyUI
{
public:
	CBaseWindowWnd(void);
	~CBaseWindowWnd(void);
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void SetSkinName(CStdString skinName); //设置界面样式文件名
	LONG GetLocalStyleVaule();
	LRESULT SetLocalStyleValue(LONG styleValue); //

	void OnFinalMessage(HWND /*hWnd*/);

	//消息响应
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	CStdString m_className; //窗口类名
	CRect m_rcWnd; //本窗口矩形
	CSize m_size; //本窗口大小
	CStdString m_skinName; //界面样式文件名
	LONG m_localStyleValue; //窗口样式
	CPaintManagerUI m_paintManager; //窗口指针
};

#endif // __BASEWINDOWWND_H__