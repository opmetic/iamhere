#pragma once
#ifndef __CERRORCODE_H__
#define __CERRORCODE_H__

//�����붨��
static int ERROR_CODE_SUM = 4;
static char * ERRORCODE[] = {
	"����",												//  0
	"����������ʧ��",									//  1
	"����MsgBox����ʧ��",								//  2
	"�����벻����"										//  3
};

class CErrorCode
{
public:
	CErrorCode(void);
	~CErrorCode(void);
	char * GetErrorByCode(int code);
};

#endif // __CERRORCODE_H__