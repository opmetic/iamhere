#include "MsgBox.h"

CMsgBox::CMsgBox(void)
{
	//构造函数
	m_className = _T((typeid(*this)).name());
}

CMsgBox::CMsgBox(CStdString skinName, int indexWnd) 
{
	//构造函数
	m_className = _T((typeid(*this)).name());
	SetSkinName(skinName);

	m_indexWnd = indexWnd;
}

CMsgBox::~CMsgBox(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////

//事件响应　路由
void CMsgBox::Notify(TNotifyUI& msg)
{
    //关闭按钮
    if( msg.pSender->GetName() == _T("closeBtn") ) 
	{
		if( msg.sType == _T("click") ) //单击
		{
			Close();
        }
    }
}

//消息响应 路由
LRESULT CMsgBox::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
    BOOL bHandled = TRUE; //是否将消息止步于在这里
    switch( uMsg ) {
		case WM_CREATE:				lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
		case WM_NCACTIVATE:			lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
		case WM_NCCALCSIZE:			lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
		case WM_NCPAINT:			lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
		case WM_NCHITTEST:			lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
		case WM_SIZE:				lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
		case WM_GETMINMAXINFO:		lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
		case WM_SYSCOMMAND:			lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
		case WM_NCLBUTTONDBLCLK:	lRes = OnNcLButtonDBLclk(uMsg, wParam, lParam, bHandled); break;
		case WM_DESTROY:			lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;

		
		default:
			{
				bHandled = FALSE;
			}
    }
    if( bHandled ) 
	{
		return lRes;
	}

    if( m_paintManager.MessageHandler(uMsg, wParam, lParam, lRes) ) 
	{
		return lRes;
	}
    
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////////////////////
//实现拖动效果
LRESULT CMsgBox::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	RECT rcCaption = m_paintManager.GetCaptionRect();
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
			CControlUI* pControl = static_cast<CControlUI*>(m_paintManager.FindControl(pt));
			if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 && 
							_tcscmp(pControl->GetClass(), _T("ComboUI")) != 0 &&
							_tcscmp(pControl->GetClass(), _T("EditUI")) != 0 &&
							_tcscmp(pControl->GetClass(), _T("TextUI")) != 0  &&
							_tcscmp(pControl->GetClass(), _T("RichEditUI")) != 0 &&
							_tcscmp(pControl->GetClass(), _T("ScrollBarUI")) != 0 )
				return HTCAPTION; //命中标题栏，就是可以拖动
	}

	return HTCLIENT;
}

//空响应用户双击动作，去除双击标题栏是窗口最大化功能
LRESULT CMsgBox::OnNcLButtonDBLclk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

//销毁窗口，退出程序
LRESULT CMsgBox::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SendMC(MOD_UI, ACT_CANCEL_WIN, this->m_indexWnd, NULL, NULL);
	bHandled = false;
	return 0;
}


//消息响应
LRESULT CMsgBox::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CBaseWindowWnd::OnCreate(uMsg, wParam, lParam, bHandled); //调用base类的其本操作
	return 0;
}


void CMsgBox::SetMsgInfo(CStdString msg)
{
	CControlUI* pMsgArea = static_cast<CControlUI*>(m_paintManager.FindControl(_T("msgArea")));
	pMsgArea->SetText(_T(msg));
}