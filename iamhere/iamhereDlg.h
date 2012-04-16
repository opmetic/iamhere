
// iamhereDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "manageSearch.h"

#define WM_SHOWTASK WM_USER + 107

// CiamhereDlg 对话框
class CiamhereDlg : public CDialogEx
{
// 构造
public:
	CiamhereDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IAMHERE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_info;
	CEdit m_tagCtrl;
	CString m_tag;
	CFont m_tagFontValue; //tag 文本框字体
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedMore();

	void ExecuteSearch();
	manageSearch m_manageSearch;

	//托盘
	NOTIFYICONDATA m_nid;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);

	void ShowIAmDialog();
	void HideIAmDialog();
	afx_msg void OnClose();
};
