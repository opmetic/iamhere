#include "IamHereWindowWnd.h"

CIamHereWindowWnd::CIamHereWindowWnd(void)
{
	//构造函数
	m_className = _T("CIamHereWindowWnd");
	m_size.cx = 540;
	m_size.cy = 450;
}

CIamHereWindowWnd::~CIamHereWindowWnd(void)
{
}

void CIamHereWindowWnd::Init()
{
	//托盘
	InitNotify();
	InitHotKey();

	//初始化指针
	pControlKey = static_cast<CRichEditUI*>(m_paintManager.FindControl(_T("rememberKey")));
	pControlValue = static_cast<CRichEditUI*>(m_paintManager.FindControl(_T("rememberValue")));
	pControlKey->SetFocus();
}

LPCTSTR CIamHereWindowWnd::GetWindowClassName() const 
{ 
	return _T(m_className); 
};

UINT CIamHereWindowWnd::GetClassStyle() const 
{ 
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; 
};

//最后一个消息
void CIamHereWindowWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	delete this; 
};




void CIamHereWindowWnd::InitNotify() //初始化托盘
{
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = WM_SHOWTASK;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;
	m_nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	strcpy(m_nid.szTip, _T("我在这里(右键关闭)"));
	if (Shell_NotifyIcon(NIM_ADD, &m_nid) == 0)
	{
		//托盘失败
	}
}

void CIamHereWindowWnd::InitHotKey() //初始化全局键盘hook
{
	if (!RegisterHotKey(this->m_hWnd, WM_HOTKEY, MOD_ALT, 'Q'))
	{
		//键盘hook失败
	}
}

void CIamHereWindowWnd::ShowOrHideWindow() //显示、隐藏窗口
{
	if (IsWindowVisible(this->m_hWnd))
	{
		HWND f = GetFocus(); 
		if (f != this->m_hWnd) 
		{
			//窗口被其它窗口挡住了，置前台
			SetForegroundWindow(this->m_hWnd);//置前台	
		}
		else
		{
			//窗口可见，作隐藏
			this->ShowWindow(false);
			pControlValue->SetFocus();
		}
	}
	else
	{
		//窗口不可见，作显示
		this->ShowWindow(true);
		SetForegroundWindow(this->m_hWnd);//置前台

		pControlKey->SetFocus();
		pControlKey->SetSelAll();
	}
}

LRESULT CIamHereWindowWnd::DoSearch(void) //执行查找
{
	CStdString strKey = pControlKey->GetText();
	if (strKey == _T("exit"))
	{
		this->Close();
	}
	pControlValue->SetText(strKey + _T(" 哈哈"));
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//事件响应　路由
void CIamHereWindowWnd::Notify(TNotifyUI& msg)
{
    //关闭按钮
    if( msg.pSender->GetName() == _T("closeBtn") ) 
	{
		if( msg.sType == _T("click") ) //单击
		{
			OncloseBtnClick();
        }
    }
	
	// 　searchBtn　按钮
	if (msg.pSender->GetName() == _T("searchBtn") )
	{
		if (msg.sType == _T("click")) //单击
		{
			OnSearchBtnClick();
		}
	}

	// addBtn 按钮
	if (msg.pSender->GetName() == _T("addBtn") )
	{
		if (msg.sType == _T("click"))
		{
			OnAddBtnClick();
		}
	}

	// key 窗口
	if (msg.pSender->GetName() == _T("rememberKey") )
	{
		if (msg.sType == _T("return"))
		{
			OnRememberKeyReturn();
		}
	}

	//pasteBtn 粘贴
	if (msg.pSender->GetName() == _T("pasteBtn") )
	{
		if (msg.sType == _T("click"))
		{
			OnPasteBtnClick();
		}
	}

	//historyBtn
	if (msg.pSender->GetName() == _T("historyBtn") )
	{
		if (msg.sType == _T("click"))
		{
			OnHistoryBtnClick();
		}
	}
}



//消息响应 路由
LRESULT CIamHereWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
    BOOL bHandled = TRUE; //是否将消息止步于在这里
    switch( uMsg ) {
		case WM_CREATE:				lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
		case WM_CLOSE:				lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
		case WM_DESTROY:			lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
		case WM_NCACTIVATE:			lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
		case WM_NCCALCSIZE:			lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
		case WM_NCPAINT:			lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
		case WM_NCHITTEST:			lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
		case WM_SIZE:				lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
		case WM_GETMINMAXINFO:		lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
		case WM_SYSCOMMAND:			lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
		case WM_NCLBUTTONDBLCLK:	lRes = OnNcLButtonDBLclk(uMsg, wParam, lParam, bHandled); break;
		case WM_HOTKEY:				lRes = OnHotKey(uMsg, wParam, lParam, bHandled); break; //热键
		case WM_SHOWTASK:			lRes = OnShowTask(uMsg, wParam, lParam, bHandled); break; //自字义消息
		
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
//消息响应
LRESULT CIamHereWindowWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_paintManager.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("skin.xml"), (UINT)0, NULL, &m_paintManager);
	ASSERT(pRoot && "Failed to parse XML");
	m_paintManager.AttachDialog(pRoot);


	m_paintManager.AddNotifier(this);

	Init();
	return 0;
}

//关闭窗口
LRESULT CIamHereWindowWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostMessage(WM_DESTROY, wParam, lParam); //发送 WM_DESTROY 消息，销毁窗口 
	//ShowOrHideWindow();
	return 0;
}

//销毁窗口，除出程序
LRESULT CIamHereWindowWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Shell_NotifyIcon(NIM_DELETE, &m_nid);//删除托盘图标
	UnregisterHotKey(this->m_hWnd, WM_HOTKEY); //删除热键
	::PostQuitMessage(0);
	return 0;
}

LRESULT CIamHereWindowWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) )
	{
		//窗口未最小化
		bHandled = FALSE;
	}

    return (wParam == 0) ? TRUE : FALSE;

	/*
	bHandled = false;
	if( !::IsIconic(m_hWnd) ) 
	{
        return (wParam == 0) ? TRUE : FALSE;
    }
	return 0;
	*/
}

LRESULT CIamHereWindowWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CIamHereWindowWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

//实现拖动效果
LRESULT CIamHereWindowWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

//窗口圆角处理
LRESULT CIamHereWindowWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_paintManager.GetRoundCorner();
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) 
	{
		::GetWindowRect(*this, &m_rcWnd);
		m_rcWnd.Offset(-m_rcWnd.left, -m_rcWnd.top);
		m_rcWnd.right++; m_rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(m_rcWnd.left, m_rcWnd.top, m_rcWnd.right, m_rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CIamHereWindowWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CIamHereWindowWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
    if( wParam == SC_CLOSE ) {
        ::PostQuitMessage(0L);
        bHandled = TRUE;
        return 0;
    }
    BOOL bZoomed = ::IsZoomed(*this);
    LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
    if( ::IsZoomed(*this) != bZoomed ) {
        if( !bZoomed ) {
            CControlUI* pControl = static_cast<CControlUI*>(m_paintManager.FindControl(_T("maxbtn")));
            if( pControl ) pControl->SetVisible(false);
            pControl = static_cast<CControlUI*>(m_paintManager.FindControl(_T("restorebtn")));
            if( pControl ) pControl->SetVisible(true);
        }
        else {
            CControlUI* pControl = static_cast<CControlUI*>(m_paintManager.FindControl(_T("maxbtn")));
            if( pControl ) pControl->SetVisible(true);
            pControl = static_cast<CControlUI*>(m_paintManager.FindControl(_T("restorebtn")));
            if( pControl ) pControl->SetVisible(false);
        }
    }
    return lRes;
}

//空响应用户双击动作，去除双击标题栏是窗口最大化功能
LRESULT CIamHereWindowWnd::OnNcLButtonDBLclk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CIamHereWindowWnd::OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) //热键
{
	bHandled = false;
	ShowOrHideWindow();
	return 0;
}

LRESULT CIamHereWindowWnd::OnShowTask(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{

	if (wParam != WM_SHOWTASK)
	{
		return 1;
	}

	switch(lParam)
	{
	case WM_RBUTTONUP: //右键
		PostMessage(WM_DESTROY, wParam, lParam); //发送 WM_DESTROY 消息，销毁窗口 
		break;

	case WM_LBUTTONDBLCLK:
		ShowOrHideWindow(); //显示、隐藏窗口
		break;
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//事件响应
LRESULT CIamHereWindowWnd::OncloseBtnClick()
{
	Close();
	return 0;
}

LRESULT CIamHereWindowWnd::OnSearchBtnClick()
{
	return DoSearch();
}

LRESULT CIamHereWindowWnd::OnAddBtnClick()
{
	MessageBox(NULL, pControlValue->GetText(), "HH", MB_OK);
	return 0;
}

LRESULT CIamHereWindowWnd::OnRememberKeyReturn()
{
	return DoSearch();
}

//操作系统粘贴板
LRESULT CIamHereWindowWnd::OnPasteBtnClick(void)
{
	CStdString fromClipboard;
	if ( OpenClipboard(this->m_hWnd) )
	{
		HANDLE hData = GetClipboardData(CF_TEXT);
		char * buffer = (char*)GlobalLock(hData);
		fromClipboard = buffer;
		GlobalUnlock(hData);
		CloseClipboard();
	}
	if (!fromClipboard.IsEmpty())
	{
		pControlKey->SetText(fromClipboard);
	}
	return 0;
}

LRESULT CIamHereWindowWnd::OnHistoryBtnClick(void)
{
	return DoSearch();
}