#ifndef __IAMHEREWINDOWWND_H__
#define __IAMHEREWINDOWWND_H__

#include "BaseWindowWnd.h"

class CIamHereWindowWnd : public CBaseWindowWnd
{
public:
	CIamHereWindowWnd(void);
	CIamHereWindowWnd(CStdString skinName);
	~CIamHereWindowWnd(void);
	void Init();
	
	
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void InitNotify(); //初始化托盘
	void InitHotKey(); //初始化全局键盘hook
	void ShowOrHideWindow(); //显示、隐藏窗口

	LRESULT DoSearch(void); //执行查找

	//消息响应
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
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
	NOTIFYICONDATA m_nid;//托盘

	CRichEditUI* pControlKey;
	CRichEditUI* pControlValue;

	
};


#endif // __IAMHEREWINDOWWND_H__