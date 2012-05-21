#pragma once

#include "iamhere.h"
#include "IamHereWindowWnd.h"



// 程序入口及Duilib初始化部分
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
    pFrame->Create(NULL, _T("在这里"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
    pFrame->ShowWindow(true);
    CPaintManagerUI::MessageLoop();

    return 0;
}
