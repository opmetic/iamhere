#ifndef __IAMHEREWINDOWWND_H__
#define __IAMHEREWINDOWWND_H__

#include "iamhere.h"

class CIamHereWindowWnd : public CWindowWnd, public INotifyUI
{
public:
	CIamHereWindowWnd(void);
	~CIamHereWindowWnd(void);
	void Init();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/);
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void InitNotify(); //��ʼ������
	void InitHotKey(); //��ʼ��ȫ�ּ���hook
	void ShowOrHideWindow(); //��ʾ�����ش���

	LRESULT DoSearch(void); //ִ�в���

	//��Ϣ��Ӧ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcLButtonDBLclk(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); //�ȼ�
	LRESULT OnShowTask(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled); //�Զ���

	//�¼���Ӧ
	LRESULT OncloseBtnClick(void);
	LRESULT OnSearchBtnClick(void);
	LRESULT OnAddBtnClick(void);
	LRESULT OnRememberKeyReturn(void);
	LRESULT OnPasteBtnClick(void);
	LRESULT OnHistoryBtnClick(void);
	

public:
	CPaintManagerUI m_paintManager; //����ָ��
	CStdString m_className; //��������
	NOTIFYICONDATA m_nid;//����

	CRichEditUI* pControlKey;
	CRichEditUI* pControlValue;

	CRect m_rcWnd; //�����ھ���
	CSize m_size; //�����ڴ�С
};


#endif // __IAMHEREWINDOWWND_H__