#ifndef __CCONTROL_H__
#define __CCONTROL_H__

#include "iamhere.h"
#include "IamHereWindowWnd.h"
#include "MsgBox.h"


//窗口列表 单元Node
struct WndList {
	int m_indexWnd; //窗口唯一标识
	CBaseWindowWnd * m_Wnd;  //窗口指针
	struct WndList * pNext; //下一个结点指针
};

// 控制中心，兼故UI控制攻能
class CControl
{
public:
	CControl(void);
	~CControl(void);
	LRESULT InitMainFrame(CStdString skinPath);
	LRESULT MsgBox(CStdString info); // MessageBox 窗口
	void ShowOrHideAllWindows(bool flag);//true: show | false: hidden
	int IndexWndGenerator(); //  窗口唯一标识正成器
	void ManageMC(commandAction ca, int param, void * lParam, void * WParam);

public:
	CIamHereWindowWnd* pMainFrame;
	CMsgBox* pMsgBox;
	int indexWnd; //窗口唯一标识

public:
	//窗口列表相关操作
	struct WndList * m_WndList; //窗口列表头指针
	int AddWnd(CBaseWindowWnd * wnd); //注册窗口管理
	int DelWnd(int indexWnd); //注销窗口管理
};

#endif // __CCONTROL_H__