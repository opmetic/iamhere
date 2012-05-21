#include "IamHereWindowWnd.h"

CIamHereWindowWnd::CIamHereWindowWnd(void)
{
	//���캯��
	m_className = _T((typeid(*this)).name());
	m_size.cx = 540;
	m_size.cy = 450;
}

CIamHereWindowWnd::CIamHereWindowWnd(CStdString skinName) 
{
	//���캯��
	//m_className = _T("CIamHereWindowWnd");
	m_className = _T((typeid(*this)).name());
	m_size.cx = 540;
	m_size.cy = 450;

	SetSkinName(skinName);
}


CIamHereWindowWnd::~CIamHereWindowWnd(void)
{
}

void CIamHereWindowWnd::Init()
{
	//����
	InitNotify();
	InitHotKey();

	//��ʼ��ָ��
	pControlKey = static_cast<CRichEditUI*>(m_paintManager.FindControl(_T("rememberKey")));
	pControlValue = static_cast<CRichEditUI*>(m_paintManager.FindControl(_T("rememberValue")));
	pControlKey->SetFocus();
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

//Alt + q ���
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
		HWND focusHWnd = GetFocus(); 
		if (focusHWnd != this->m_hWnd) 
		{
			//���ڱ��������ڵ�ס�ˣ���ǰ̨
			SetForegroundWindow(this->m_hWnd);//��ǰ̨	
		}
		else
		{
			//���ڿɼ���������
			this->ShowWindow(false);
			pControlValue->SetFocus();
		}
	}
	else
	{
		//���ڲ��ɼ�������ʾ
		this->ShowWindow(true);
		SetForegroundWindow(this->m_hWnd);//��ǰ̨

		pControlKey->SetFocus();
		pControlKey->SetSelAll();
	}
}

LRESULT CIamHereWindowWnd::DoSearch(void) //ִ�в���
{
	CStdString strKey = pControlKey->GetText();
	if (strKey == _T("exit"))
	{
		this->Close();
	}
	pControlValue->SetText(strKey + _T(" ����"));
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////

//�¼���Ӧ��·��
void CIamHereWindowWnd::Notify(TNotifyUI& msg)
{
    //�رհ�ť
    if( msg.pSender->GetName() == _T("closeBtn") ) 
	{
		if( msg.sType == _T("click") ) //����
		{
			OncloseBtnClick();
        }
    }
	
	// ��searchBtn����ť
	if (msg.pSender->GetName() == _T("searchBtn") )
	{
		if (msg.sType == _T("click")) //����
		{
			OnSearchBtnClick();
		}
	}

	// addBtn ��ť
	if (msg.pSender->GetName() == _T("addBtn") )
	{
		if (msg.sType == _T("click"))
		{
			OnAddBtnClick();
		}
	}

	// key ����
	if (msg.pSender->GetName() == _T("rememberKey") )
	{
		if (msg.sType == _T("return"))
		{
			OnRememberKeyReturn();
		}
	}

	//pasteBtn ճ��
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



//��Ϣ��Ӧ ·��
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

/////////////////////////////////////////////////////////////////////////////////////////////
//��Ϣ��Ӧ
LRESULT CIamHereWindowWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CBaseWindowWnd::OnCreate(uMsg, wParam, lParam, bHandled); //����base����䱾����

	Init();
	return 0;
}
/*
//�رմ���
LRESULT CIamHereWindowWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	ShowOrHideWindow();
	return 0;
}*/

//���ٴ��ڣ���������
LRESULT CIamHereWindowWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	Shell_NotifyIcon(NIM_DELETE, &m_nid);//ɾ������ͼ��
	UnregisterHotKey(this->m_hWnd, WM_HOTKEY); //ɾ���ȼ�
	CBaseWindowWnd::OnDestroy(uMsg, wParam, lParam, bHandled); //����base����䱾����
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

/////////////////////////////////////////////////////////////////////////////////////////////
//�¼���Ӧ
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

//����ϵͳճ����
LRESULT CIamHereWindowWnd::OnPasteBtnClick(void)
{
	CStdString fromClipboard;
	if ( OpenClipboard(this->m_hWnd) )
	{
		if (IsClipboardFormatAvailable(CF_TEXT)) //�鿴ճ�������ǲ����ı�
		{
			HANDLE hData = GetClipboardData(CF_TEXT);
			char * buffer = (char*)GlobalLock(hData);
			fromClipboard = buffer;
			GlobalUnlock(hData);
		}

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
	CIamHereWindowWnd* pFrame = new CIamHereWindowWnd(_T("messageBox.xml"));

    if( pFrame == NULL ) 
	{
		return 0;
	}
    pFrame->Create(NULL, _T("��ʾ"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pFrame->ShowWindow(true);
	return 0;
}