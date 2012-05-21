#ifndef __IAMHEREWINDOWWND_H__
#define __IAMHEREWINDOWWND_H__

#include "BaseWindowWnd.h"

class CIamHereWindowWnd : public CBaseWindowWnd
{
public:
	CIamHereWindowWnd(void);
	CIamHereWindowWnd(CStdString skinName);
	~CIamHereWindowWnd(void);
	void Init();
	
	
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void InitNotify(); //��ʼ������
	void InitHotKey(); //��ʼ��ȫ�ּ���hook
	void ShowOrHideWindow(); //��ʾ�����ش���

	LRESULT DoSearch(void); //ִ�в���

	//��Ϣ��Ӧ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	
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
	NOTIFYICONDATA m_nid;//����

	CRichEditUI* pControlKey;
	CRichEditUI* pControlValue;

	
};


#endif // __IAMHEREWINDOWWND_H__