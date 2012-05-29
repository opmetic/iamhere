#include "BaseWindowWnd.h"

CBaseWindowWnd::CBaseWindowWnd(void)
{
	SetLocalStyleValue(WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	m_className = _T((typeid(*this)).name());
	m_indexWnd = 0;
}


CBaseWindowWnd::~CBaseWindowWnd(void)
{
}

void CBaseWindowWnd::SetSkinName(CStdString skinName)
{
	if (!skinName.IsEmpty())
	{
		m_skinName = _T(skinName);
	}
}

//得到自己的类名，在创建窗口前就调用，很重要
LPCTSTR CBaseWindowWnd::GetWindowClassName() const 
{

	if (!m_className.IsEmpty())
	{
		return _T(m_className); 
	}
	else
	{
		return _T("CBaseWindowWnd");
	}
	
}

UINT CBaseWindowWnd::GetClassStyle() const 
{ 
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; 
}

LONG CBaseWindowWnd::GetLocalStyleVaule()
{
	return m_localStyleValue;
}

LRESULT CBaseWindowWnd::SetLocalStyleValue(LONG styleValue) //
{
	m_localStyleValue = styleValue;
	return 0;
}

//最后一个消息
void CBaseWindowWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	delete this; 
}

//消息响应
LRESULT CBaseWindowWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | m_localStyleValue);

	m_paintManager.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T(this->m_skinName.GetData()), (UINT)0, NULL, &m_paintManager);

	ASSERT(pRoot && "解析XML皮肤文件失败");

	m_paintManager.AttachDialog(pRoot);

	m_paintManager.AddNotifier(this);
	return 0;
}

//关闭窗口
LRESULT CBaseWindowWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostMessage(WM_DESTROY, wParam, lParam); //发送 WM_DESTROY 消息，销毁窗口 
	return 0;
}

//销毁窗口，除出程序
LRESULT CBaseWindowWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0);
	return 0;
}

LRESULT CBaseWindowWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CBaseWindowWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CBaseWindowWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

//窗口圆角处理
LRESULT CBaseWindowWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CBaseWindowWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

//
LRESULT CBaseWindowWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
    if( wParam == SC_CLOSE ) {
        ::PostQuitMessage(0L);
        bHandled = TRUE;
        return 0;
    }

	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam); //处理默认的命令，没有这句，将不能拖动

	/*

    BOOL bZoomed = ::IsZoomed(*this); //确定窗口是否是最大化的窗口
    
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
	*/
    return lRes;
}