#pragma once

#include "iamhere.h"
#include "IamHereWindowWnd.h"



// ������ڼ�Duilib��ʼ������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    CPaintManagerUI::SetInstance(hInstance);
    CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin"));
	
	CIamHereWindowWnd* pFrame = new CIamHereWindowWnd(_T("skin.xml"));
	//pFrame->SetSkinName(_T("skin.xml"));

    if( pFrame == NULL ) 
	{
		return 0;
	}
    pFrame->Create(NULL, _T("������"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pFrame->ShowWindow(true);
    CPaintManagerUI::MessageLoop();

    return 0;
}
