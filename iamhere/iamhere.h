#ifndef __IAMHERE_H__
#define __IAMHERE_H__


#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <objbase.h>
#include <shellapi.h>
#include <typeinfo.h>

#include ".\include\DuiLib\UIlib.h"

using namespace DuiLib;

#ifdef _DEBUG
#   ifdef _UNICODE
#       pragma comment(lib, ".\\libs\\DuiLib_ud.lib")
#   else
#       pragma comment(lib, ".\\libs\\DuiLib_d.lib")
#   endif
#else
#   ifdef _UNICODE
#       pragma comment(lib, ".\\libs\\DuiLib_u.lib")
#   else
#       pragma comment(lib, ".\\libs\\DuiLib.lib")
#   endif
#endif

#define WM_SHOWTASK WM_USER + 779

/*
class CIamHereProxy 
{
public:
	CIamHereWindowWnd * pFrame;
};

CIamHereProxy IamHere;
*/
#endif // __IAMHERE_H__