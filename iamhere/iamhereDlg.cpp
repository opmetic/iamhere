
// iamhereDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "iamhere.h"
#include "iamhereDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CiamhereDlg �Ի���




CiamhereDlg::CiamhereDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CiamhereDlg::IDD, pParent)
	, m_info(_T(""))
	, m_tag(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CiamhereDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INFO, m_info);
	DDX_Control(pDX, IDC_TAG, m_tagCtrl);
	DDX_Text(pDX, IDC_TAG, m_tag);
}

BEGIN_MESSAGE_MAP(CiamhereDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SEARCH, &CiamhereDlg::OnBnClickedSearch)
	ON_BN_CLICKED(IDC_MORE, &CiamhereDlg::OnBnClickedMore)
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_HOTKEY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CiamhereDlg ��Ϣ�������

BOOL CiamhereDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//��ʼ������
	m_tagFontValue.CreateFont(40, // nHeight �ı�߶ȺͿ�Ⱥ����޷��ı������С����Ȼһ����С��ֻ��ѡ��ʱ����ռ�ø߶�ȷʵ�ߣ�����������ʾ���ߡ�
			18, // nWidth
			0, // nEscapement
			0, // nOrientation
			FW_HEAVY, // nWeight
			FALSE, // bItalic
			FALSE, // bUnderline
			0, // cStrikeOut
			ANSI_CHARSET, // nCharSet
			OUT_DEFAULT_PRECIS, // nOutPrecision
			CLIP_DEFAULT_PRECIS, // nClipPrecision
			DEFAULT_QUALITY, // nQuality
			DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
			_T("Arial")
			);
	m_tagCtrl.SetFont(&m_tagFontValue); //����tag�ı�������

	//���̲���
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	m_nid.uCallbackMessage = WM_SHOWTASK; // �Զ������Ϣ����
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy (m_nid.szTip, "��������"); // ��Ϣ��ʾ��Ϊ"��������" ʹ��
	Shell_NotifyIcon(NIM_ADD, &m_nid); // �����������ͼ��

	//ȫ�ּ���hook
	if(!RegisterHotKey(this->m_hWnd, WM_HOTKEY, MOD_ALT, 'Q')) 
	{ 
		AfxMessageBox( _T("ע���ȼ�ʧ�ܣ����ȼ���Ͻ������ã� ")); 
	} 

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CiamhereDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CiamhereDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CiamhereDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)  
	{
		HWND hWnd = ::GetFocus(); 
		int iID = ::GetDlgCtrlID(hWnd); 
		if (iID == IDC_INFO) //��Ϣ���û��༭������
		{
			return CDialogEx::PreTranslateMessage(pMsg);
		}
		else 
		{
			ExecuteSearch();
		}
		
		return TRUE;
	}

	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE)  
	{
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CiamhereDlg::OnBnClickedSearch()
{
	// TODO:
	ExecuteSearch();
}


void CiamhereDlg::OnBnClickedMore()
{
	// TODO: 
	UpdateData(TRUE);
	m_manageSearch.InsetInfo(m_tag, m_info);
}

void CiamhereDlg::ExecuteSearch()
{
	UpdateData(TRUE);
	m_info = m_manageSearch.ExecuteSearch(m_tag);
	UpdateData(FALSE);
}

//��Ӧ�Զ����¼������̲���
LRESULT CiamhereDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME)
	{
		return 1;
	}

	switch(lParam)
	{
		case WM_RBUTTONUP: // �Ҽ�����ʱ�����˵�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint); // �õ����λ��
			CMenu menu;
			menu.CreatePopupMenu(); // ����һ������ʽ�˵�
			menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�ر�"));
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
		case WM_LBUTTONDBLCLK: // ˫������Ĵ���
		{
			ShowIAmDialog();
		}
		break;
	}
	return 0;
}

void CiamhereDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 
	if(nType == SIZE_MINIMIZED)
	{
		HideIAmDialog();// ����С��ʱ������������
	}
}


void CiamhereDlg::OnDestroy()
{
	// ��������ɾ��ͼ��
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	UnregisterHotKey(m_hWnd, WM_HOTKEY); // ɾ���ȼ�

	CDialogEx::OnDestroy();

	// TODO:
}


void CiamhereDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 
	if (!IsWindowVisible())
	{
		ShowIAmDialog();
	}
	else
	{
		HideIAmDialog();
	}
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void CiamhereDlg::ShowIAmDialog()
{
	SetForegroundWindow(); //�ú���������ָ�����ڵ��߳����õ�ǰ̨
	ShowWindow(SW_SHOWNORMAL); // ��ʾ������	
	m_tagCtrl.SetSel(0, -1); //tag�ı���ȫѡ
	::SetFocus(m_tagCtrl.m_hWnd); //tag�����õ�����
}

void CiamhereDlg::HideIAmDialog()
{
	ShowWindow(SW_HIDE);
}

/**
 * ��д�رհ���
 */
void CiamhereDlg::OnClose()
{
	// TODO: 
	HideIAmDialog();
//	CDialogEx::OnClose();
}
