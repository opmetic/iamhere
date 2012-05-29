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

//�õ��Լ����������ڴ�������ǰ�͵��ã�����Ҫ
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

//���һ����Ϣ
void CBaseWindowWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	delete this; 
}

//��Ϣ��Ӧ
LRESULT CBaseWindowWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | m_localStyleValue);

	m_paintManager.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T(this->m_skinName.GetData()), (UINT)0, NULL, &m_paintManager);

	ASSERT(pRoot && "����XMLƤ���ļ�ʧ��");

	m_paintManager.AttachDialog(pRoot);

	m_paintManager.AddNotifier(this);
	return 0;
}

//�رմ���
LRESULT CBaseWindowWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostMessage(WM_DESTROY, wParam, lParam); //���� WM_DESTROY ��Ϣ�����ٴ��� 
	return 0;
}

//���ٴ��ڣ���������
LRESULT CBaseWindowWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0);
	return 0;
}

LRESULT CBaseWindowWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) )
	{
		//����δ��С��
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

//����Բ�Ǵ���
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
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
    if( wParam == SC_CLOSE ) {
        ::PostQuitMessage(0L);
        bHandled = TRUE;
        return 0;
    }

	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam); //����Ĭ�ϵ����û����䣬�������϶�

	/*

    BOOL bZoomed = ::IsZoomed(*this); //ȷ�������Ƿ�����󻯵Ĵ���
    
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