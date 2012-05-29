#pragma once
#ifndef __CERRORCODE_H__
#define __CERRORCODE_H__

//错误码定义
static int ERROR_CODE_SUM = 4;
static char * ERRORCODE[] = {
	"正常",												//  0
	"创建主窗口失败",									//  1
	"创建MsgBox窗口失败",								//  2
	"错误码不存在"										//  3
};

class CErrorCode
{
public:
	CErrorCode(void);
	~CErrorCode(void);
	char * GetErrorByCode(int code);
};

#endif // __CERRORCODE_H__