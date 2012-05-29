#include "MsgBox.h"

CMsgBox::CMsgBox(void)
{
	//���캯��
	m_className = _T((typeid(*this)).name());
}

CMsgBox::CMsgBox(CStdString skinName, int indexWnd) 
{
	//���캯��
	m_className = _T((typeid(*this)).name());
	SetSkinName(skinName);

	m_indexWnd = indexWnd;
}

CMsgBox::~CMsgBox(void)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////

//�¼���Ӧ��·��
void CMsgBox::Notify(TNotifyUI& msg)
{
    //�رհ�ť
    if( msg.pSender->GetName() == _T("closeBtn") ) 
	{
		if( msg.sType == _T("click") ) //����
		{
			Close();
        }
    }
}

//��Ϣ��Ӧ ·��
LRESULT CMsgBox::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
    BOOL bHandled = TRUE; //�Ƿ���Ϣֹ����������
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
//ʵ���϶�Ч��
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
				return HTCAPTION; //���б����������ǿ����϶�
	}

	return HTCLIENT;
}

//����Ӧ�û�˫��������ȥ��˫���������Ǵ�����󻯹���
LRESULT CMsgBox::OnNcLButtonDBLclk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

//���ٴ��ڣ��˳�����
LRESULT CMsgBox::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	SendMC(MOD_UI, ACT_CANCEL_WIN, this->m_indexWnd, NULL, NULL);
	bHandled = false;
	return 0;
}


//��Ϣ��Ӧ
LRESULT CMsgBox::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CBaseWindowWnd::OnCreate(uMsg, wParam, lParam, bHandled); //����base����䱾����
	return 0;
}


void CMsgBox::SetMsgInfo(CStdString msg)
{
	CControlUI* pMsgArea = static_cast<CControlUI*>(m_paintManager.FindControl(_T("msgArea")));
	pMsgArea->SetText(_T(msg));
}