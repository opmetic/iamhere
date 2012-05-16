#include "IamHereWindowWnd.h"

CIamHereWindowWnd::CIamHereWindowWnd(void)
{
	//���캯��
	m_className = _T("CIamHereWindowWnd");
}

CIamHereWindowWnd::~CIamHereWindowWnd(void)
{
}

LPCTSTR CIamHereWindowWnd::GetWindowClassName() const 
{ 
	return _T(m_className); 
};

UINT CIamHereWindowWnd::GetClassStyle() const 
{ 
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; 
};

//���һ����Ϣ
void CIamHereWindowWnd::OnFinalMessage(HWND /*hWnd*/) 
{ 
	delete this; 
};

//��������
void CIamHereWindowWnd::Notify(TNotifyUI& msg)
{
    //�رհ�ť
    if( msg.pSender->GetName() == _T("closeBtn") ) 
	{
		if( msg.sType == _T("click") ) //����
		{
            Close();
        }
    }
	
	// ��searchBtn����ť
	if (msg.pSender->GetName() == _T("searchBtn") )
	{
		if (msg.sType == _T("click")) //����
		{
			
			CRichEditUI* pControl = static_cast<CRichEditUI*>(m_paintManager.FindControl(_T("rememberKey")));
			pControl->GetText();
			//MessageBox(NULL, pControl->GetText(), "HH", MB_OK);
			CContainerUI* pCon = static_cast<CContainerUI *>(m_paintManager.FindControl(_T("rememberValue")));
			pCon->SetText(pControl->GetText() + _T(" ����"));

		}
	}
}


void CIamHereWindowWnd::InitNotify() //��ʼ������
{
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = WM_SHOWTASK;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;
	m_nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	strcpy(m_nid.szTip, _T("��������(�Ҽ��ر�)"));
	if (Shell_NotifyIcon(NIM_ADD, &m_nid) == 0)
	{
		//����ʧ��
	}
}

void CIamHereWindowWnd::InitHotKey() //��ʼ��ȫ�ּ���hook
{
	if (!RegisterHotKey(this->m_hWnd, WM_HOTKEY, MOD_ALT, 'Q'))
	{
		//����hookʧ��
	}
}

void CIamHereWindowWnd::ShowOrHideWindow() //��ʾ�����ش���
{
	if (IsWindowVisible(this->m_hWnd))
	{
		//���ڿɼ���������
		this->ShowWindow(false);
	}
	else
	{
		//���ڲ��ɼ�������ʾ
		SetForegroundWindow(this->m_hWnd);//��ǰ̨
		this->ShowWindow(true);
	}
}





//�¼���Ӧ ·��
LRESULT CIamHereWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
    BOOL bHandled = TRUE; //�Ƿ���Ϣֹ����������
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
		case WM_HOTKEY:				lRes = OnHotKey(uMsg, wParam, lParam, bHandled); break; //�ȼ�
		case WM_SHOWTASK:			lRes = OnShowTask(uMsg, wParam, lParam, bHandled); break; //��������Ϣ
		
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


//�¼���Ӧ
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

	//����
	InitNotify();
	InitHotKey();
	return 0;
}

//�رմ���
LRESULT CIamHereWindowWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//PostMessage(WM_DESTROY, wParam, lParam); //���� WM_DESTROY ��Ϣ�����ٴ��� 
	ShowOrHideWindow();
	return 0;
}

//���ٴ��ڣ���������
LRESULT CIamHereWindowWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Shell_NotifyIcon(NIM_DELETE, &m_nid);//ɾ������ͼ��
	UnregisterHotKey(this->m_hWnd, WM_HOTKEY); //ɾ���ȼ�
	::PostQuitMessage(0);
	return 0;
}

LRESULT CIamHereWindowWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
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

LRESULT CIamHereWindowWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CIamHereWindowWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

//ʵ���϶�Ч��
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
				return HTCAPTION; //���б����������ǿ����϶�
	}

	return HTCLIENT;
}

//����Բ�Ǵ���
LRESULT CIamHereWindowWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SIZE szRoundCorner = m_paintManager.GetRoundCorner();
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
		CRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
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
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
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

//����Ӧ�û�˫��������ȥ��˫���������Ǵ�����󻯹���
LRESULT CIamHereWindowWnd::OnNcLButtonDBLclk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CIamHereWindowWnd::OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) //�ȼ�
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
	case WM_RBUTTONUP: //�Ҽ�
		PostMessage(WM_DESTROY, wParam, lParam); //���� WM_DESTROY ��Ϣ�����ٴ��� 
		break;

	case WM_LBUTTONDBLCLK:
		ShowOrHideWindow(); //��ʾ�����ش���
		break;
	}
	return 0;
}