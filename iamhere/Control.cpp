#include "Control.h"

CControl::CControl(void)
{
	pMsgBox = NULL;
	m_WndList = NULL;
	indexWnd = 0; //��ʼ����Ψһ��ʶ
}

CControl::~CControl(void)
{
	pMsgBox = NULL;
}

//������
LRESULT CControl::InitMainFrame(CStdString skinPath)
{
	pMainFrame = new CIamHereWindowWnd(_T(skinPath), IndexWndGenerator());

    if( pMainFrame == NULL ) 
	{
		return 1; //����������ʧ��
	}
    pMainFrame->Create(NULL, _T("������"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pMainFrame->CenterWindow();
    pMainFrame->ShowWindow(true);
	return 0;
}

// MessageBox ����
LRESULT CControl::MsgBox(CStdString msg)
{
	pMsgBox = new CMsgBox(_T("messageBox.xml"), IndexWndGenerator());
	AddWnd(pMsgBox); //ע�ᴰ�ڹ���

    if( pMsgBox == NULL ) 
	{
		return 2; //����MsgBox����ʧ��
	}
	pMsgBox->Create(pMainFrame->GetHWND(), _T("��ʾ"), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
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

//  ����Ψһ��ʶ������
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
	case ACT_CANCEL_WIN: //ע������Ψһ��ʶ 
		DelWnd(param);
		break;
	case ACT_SHOW_ALL_WIN: //��ʾ���д���
		ShowOrHideAllWindows(true);
		break;
	case ACT_HIDE_ALL_WIN: //�������д���
		ShowOrHideAllWindows(false);
		break;
	case ACT_TEST: //������
		//this->ResizeClient(
		break;
	}
}



///////////////////////////////////////////////////////////////////////////////////
//�����б���ز���
WndList * m_WndList; //�����б�ͷָ��
//ע�ᴰ�ڹ���
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


//ע�����ڹ���
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