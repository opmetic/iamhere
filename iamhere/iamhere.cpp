#pragma once

#include "iamhere.h"
#include "Control.h"

//extern CControl mControl;

//#include "IamHereWindowWnd.h"

static CControl * pControl = new CControl(); //全局控制

void MsgBox(CStdString msg)
{
	pControl->MsgBox(msg);
}

//发送命令或消息
void SendMC(targetModular tm, commandAction ca, int param, void * lParam, void * WParam)
{
	switch(tm)
	{
	case MOD_UI:
		pControl->ManageMC(ca, param, lParam, WParam);
		break;
	case MOD_INDEX:
		break;
	}
}

// 程序入口及Duilib初始化部分
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	int ret = 0;
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	
	ret = pControl->InitMainFrame(_T("skin.xml"));

	if (ret == 0)
	{
		CPaintManagerUI::MessageLoop();
	}

    return 0;
}
