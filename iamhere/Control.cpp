#include "Control.h"

CControl::CControl(void)
{
	pMsgBox = NULL;
	m_WndList = NULL;
	indexWnd = 0; //初始窗口唯一标识
}

CControl::~CControl(void)
{
	pMsgBox = NULL;
}

//主窗口
LRESULT CControl::InitMainFrame(CStdString skinPath)
{
	pMainFrame = new CIamHereWindowWnd(_T(skinPath), IndexWndGenerator());

    if( pMainFrame == NULL ) 
	{
		return 1; //创建主窗口失败
	}
    pMainFrame->Create(NULL, _T("在这里"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pMainFrame->CenterWindow();
    pMainFrame->ShowWindow(true);
	return 0;
}

// MessageBox 窗口
LRESULT CControl::MsgBox(CStdString msg)
{
	pMsgBox = new CMsgBox(_T("messageBox.xml"), IndexWndGenerator());
	AddWnd(pMsgBox); //注册窗口管理

    if( pMsgBox == NULL ) 
	{
		return 2; //创建MsgBox窗口失败
	}
	pMsgBox->Create(pMainFrame->GetHWND(), _T("提示"), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
    pMsgBox->CenterWindow();

	pMsgBox->SetMsgInfo(msg);

    pMsgBox->ShowModal();
	
	return 0;
}

void CControl::ShowOrHideAllWindows(bool flag)//true: show | false: hidden
{
	struct WndList * per = m_WndList;
	while(per != NULL)
	{
		per->m_Wnd->ShowWindow(flag);
		per = per->pNext;
	}
	/*
	if (flag)
	{
		//show all windows
	}
	else
	{
		//hidden all windows
	}
	*/
}

//  窗口唯一标识正成器
int CControl::IndexWndGenerator()
{
	if (++indexWnd >= MAX_INDEXWND)
	{
		indexWnd = 1;
	}
	return indexWnd;
}

void CControl::ManageMC(commandAction ca, int param, void * lParam, void * WParam)
{
	switch(ca)
	{
	case ACT_CANCEL_WIN: //注销窗口唯一标识 
		DelWnd(param);
		break;
	case ACT_SHOW_ALL_WIN: //显示所有窗口
		ShowOrHideAllWindows(true);
		break;
	case ACT_HIDE_ALL_WIN: //隐藏所有窗口
		ShowOrHideAllWindows(false);
		break;
	case ACT_TEST: //测试用
		//this->ResizeClient(
		break;
	}
}



///////////////////////////////////////////////////////////////////////////////////
//窗口列表相关操作
WndList * m_WndList; //窗口列表头指针
//注册窗口管理
int CControl::AddWnd(CBaseWindowWnd * wnd)
{
	struct WndList ** per = &m_WndList;
	while ((*per) != NULL)
	{
		per = &((*per)->pNext);		
	}
	(*per) = (struct WndList *)malloc(sizeof(struct WndList));
	(*per)->m_indexWnd = wnd->m_indexWnd;
	(*per)->m_Wnd = wnd;
	(*per)->pNext = NULL;

	return 0;
}


//注销窗口管理
int CControl::DelWnd(int indexWnd)
{
	struct WndList * perDel = NULL;
	struct WndList ** per = &m_WndList;
	if ((*per) != NULL)
	{
		do {
			if ((*per)->m_indexWnd == indexWnd)
			{
				perDel = (*per);
				break;
			}
			per = &((*per)->pNext);
		} while((*per) != NULL);
	}

	if (perDel != NULL)
	{
		(*per) = perDel->pNext;
		free(perDel);
	}
	return 0;
}