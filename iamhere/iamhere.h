#ifndef __IAMHERE_H__
#define __IAMHERE_H__

#pragma once

#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <objbase.h>
#include <shellapi.h>
#include <typeinfo.h>

#include ".\include\DuiLib\UIlib.h"
#include "ErrorCode.h"

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

//��󴰿�Ψһ��ʶ
#define MAX_INDEXWND 65536

//Ŀ��ģ��ö��
enum targetModular {
	MOD_UI,  //UI ģ��
	MOD_INDEX, // ����ģ��
	MOD_MAX
};

//�����ö��
enum commandAction {
	ACT_CANCEL_WIN, // �� UI ģ��ע�� ����Ψһ��ʶ 
	ACT_SHOW_ALL_WIN, //��ʾ���д���
	ACT_HIDE_ALL_WIN, //�������д���
	ACT_SHOW_ASSIGN_WIN, //��ʾָ������
	ACT_HIDE_ASSIGN_WIN, //����ָ������
	ACT_TEST, 
	ACT_MAX
};

// ȫ�ֺ���
void MsgBox(CStdString msg); //  
void SendMC(targetModular tm, commandAction ca, int param, void * lParam, void * WParam); //�����������Ϣ

#endif // __IAMHERE_H__