#pragma once

#include "iamhere.h"
#include "IamHereWindowWnd.h"

CIamHereWindowWnd* pFrame = new CIamHereWindowWnd();

// ������ڼ�Duilib��ʼ������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));

    if( pFrame == NULL ) 
	{
		return 0;
	}
    pFrame->Create(NULL, _T("������"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pFrame->ShowWindow(true);
    CPaintManagerUI::MessageLoop();

    return 0;
}
