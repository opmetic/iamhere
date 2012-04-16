
// iamhereDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "manageSearch.h"

#define WM_SHOWTASK WM_USER + 107

// CiamhereDlg �Ի���
class CiamhereDlg : public CDialogEx
{
// ����
public:
	CiamhereDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IAMHERE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_info;
	CEdit m_tagCtrl;
	CString m_tag;
	CFont m_tagFontValue; //tag �ı�������
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedSearch();
	afx_msg void OnBnClickedMore();

	void ExecuteSearch();
	manageSearch m_manageSearch;

	//����
	NOTIFYICONDATA m_nid;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);

	void ShowIAmDialog();
	void HideIAmDialog();
	afx_msg void OnClose();
};
