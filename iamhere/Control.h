#ifndef __CCONTROL_H__
#define __CCONTROL_H__

#include "iamhere.h"
#include "IamHereWindowWnd.h"
#include "MsgBox.h"


//�����б� ��ԪNode
struct WndList {
	int m_indexWnd; //����Ψһ��ʶ
	CBaseWindowWnd * m_Wnd;  //����ָ��
	struct WndList * pNext; //��һ�����ָ��
};

// �������ģ����UI���ƹ���
class CControl
{
public:
	CControl(void);
	~CControl(void);
	LRESULT InitMainFrame(CStdString skinPath);
	LRESULT MsgBox(CStdString info); // MessageBox ����
	void ShowOrHideAllWindows(bool flag);//true: show | false: hidden
	int IndexWndGenerator(); //  ����Ψһ��ʶ������
	void ManageMC(commandAction ca, int param, void * lParam, void * WParam);

public:
	CIamHereWindowWnd* pMainFrame;
	CMsgBox* pMsgBox;
	int indexWnd; //����Ψһ��ʶ

public:
	//�����б���ز���
	struct WndList * m_WndList; //�����б�ͷָ��
	int AddWnd(CBaseWindowWnd * wnd); //ע�ᴰ�ڹ���
	int DelWnd(int indexWnd); //ע�����ڹ���
};

#endif // __CCONTROL_H__