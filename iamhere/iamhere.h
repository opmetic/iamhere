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

//最大窗口唯一标识
#define MAX_INDEXWND 65536

//目标模块枚举
enum targetModular {
	MOD_UI,  //UI 模块
	MOD_INDEX, // 索引模块
	MOD_MAX
};

//命令动作枚举
enum commandAction {
	ACT_CANCEL_WIN, // 发 UI 模块注销 窗口唯一标识 
	ACT_SHOW_ALL_WIN, //显示所有窗口
	ACT_HIDE_ALL_WIN, //隐藏所有窗口
	ACT_SHOW_ASSIGN_WIN, //显示指定窗口
	ACT_HIDE_ASSIGN_WIN, //隐藏指定窗口
	ACT_TEST, 
	ACT_MAX
};

// 全局函数
void MsgBox(CStdString msg); //  
void SendMC(targetModular tm, commandAction ca, int param, void * lParam, void * WParam); //发送命令或消息

#endif // __IAMHERE_H__