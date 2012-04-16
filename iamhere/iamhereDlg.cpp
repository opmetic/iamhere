
// iamhereDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "iamhere.h"
#include "iamhereDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CiamhereDlg 对话框




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


// CiamhereDlg 消息处理程序

BOOL CiamhereDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	//初始代字体
	m_tagFontValue.CreateFont(40, // nHeight 改变高度和宽度好像无法改变字体大小，仍然一样大小，只是选中时发现占用高度确实高，但是字体显示不高。
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
	m_tagCtrl.SetFont(&m_tagFontValue); //设置tag文本框字体

	//托盘参数
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	m_nid.uCallbackMessage = WM_SHOWTASK; // 自定义的消息名称
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy (m_nid.szTip, "我在这里"); // 信息提示条为"我在这里" 使用
	Shell_NotifyIcon(NIM_ADD, &m_nid); // 在托盘区添加图标

	//全局键盘hook
	if(!RegisterHotKey(this->m_hWnd, WM_HOTKEY, MOD_ALT, 'Q')) 
	{ 
		AfxMessageBox( _T("注册热键失败，该热键组合将不可用！ ")); 
	} 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CiamhereDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
		if (iID == IDC_INFO) //信息框，用户编辑新增用
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

//响应自定义事件　托盘操作
LRESULT CiamhereDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME)
	{
		return 1;
	}

	switch(lParam)
	{
		case WM_RBUTTONUP: // 右键起来时弹出菜单
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint); // 得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu(); // 声明一个弹出式菜单
			menu.AppendMenu(MF_STRING, WM_DESTROY, _T("关闭"));
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
		case WM_LBUTTONDBLCLK: // 双击左键的处理
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
		HideIAmDialog();// 当最小化时，隐藏主窗口
	}
}


void CiamhereDlg::OnDestroy()
{
	// 在托盘区删除图标
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
	UnregisterHotKey(m_hWnd, WM_HOTKEY); // 删除热键

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
	SetForegroundWindow(); //该函数将创建指定窗口的线程设置到前台
	ShowWindow(SW_SHOWNORMAL); // 显示主窗口	
	m_tagCtrl.SetSel(0, -1); //tag文本框　全选
	::SetFocus(m_tagCtrl.m_hWnd); //tag输入框得到焦点
}

void CiamhereDlg::HideIAmDialog()
{
	ShowWindow(SW_HIDE);
}

/**
 * 重写关闭按键
 */
void CiamhereDlg::OnClose()
{
	// TODO: 
	HideIAmDialog();
//	CDialogEx::OnClose();
}
