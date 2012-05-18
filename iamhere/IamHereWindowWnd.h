#ifndef __IAMHEREWINDOWWND_H__
#define __IAMHEREWINDOWWND_H__

#include "iamhere.h"

class CIamHereWindowWnd : public CWindowWnd, public INotifyUI
{
public:
	CIamHereWindowWnd(void);
	~CIamHereWindowWnd(void);
	void Init();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/);
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void InitNotify(); //初始化托盘
	void InitHotKey(); //初始化全局键盘hook
	void ShowOrHideWindow(); //显示、隐藏窗口

	LRESULT DoSearch(void); //执行查找

	//消息响应
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcLButtonDBLclk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); //热键
	LRESULT OnShowTask(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); //自定义

	//事件响应
	LRESULT OncloseBtnClick(void);
	LRESULT OnSearchBtnClick(void);
	LRESULT OnAddBtnClick(void);
	LRESULT OnRememberKeyReturn(void);
	LRESULT OnPasteBtnClick(void);
	LRESULT OnHistoryBtnClick(void);
	

public:
	CPaintManagerUI m_paintManager; //窗口指针
	CStdString m_className; //窗口类名
	NOTIFYICONDATA m_nid;//托盘

	CRichEditUI* pControlKey;
	CRichEditUI* pControlValue;

	CRect m_rcWnd; //本窗口矩形
	CSize m_size; //本窗口大小
};


#endif // __IAMHEREWINDOWWND_H__