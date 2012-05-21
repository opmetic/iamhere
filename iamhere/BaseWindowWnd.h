#ifndef __BASEWINDOWWND_H__
#define __BASEWINDOWWND_H__

#include "iamhere.h"

class CBaseWindowWnd : public CWindowWnd, public INotifyUI
{
public:
	CBaseWindowWnd(void);
	~CBaseWindowWnd(void);
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void SetSkinName(CStdString skinName); //���ý�����ʽ�ļ���
	LONG GetLocalStyleVaule();
	LRESULT SetLocalStyleValue(LONG styleValue); //

	void OnFinalMessage(HWND /*hWnd*/);

	//��Ϣ��Ӧ
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

public:
	CStdString m_className; //��������
	CRect m_rcWnd; //�����ھ���
	CSize m_size; //�����ڴ�С
	CStdString m_skinName; //������ʽ�ļ���
	LONG m_localStyleValue; //������ʽ
	CPaintManagerUI m_paintManager; //����ָ��
};

#endif // __BASEWINDOWWND_H__