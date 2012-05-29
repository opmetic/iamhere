#include "ErrorCode.h"

CErrorCode::CErrorCode(void)
{
}

CErrorCode::~CErrorCode(void)
{
}

char * CErrorCode::GetErrorByCode(int code)
{
	if (code > 0 && code < ERROR_CODE_SUM) 
	{
		return ERRORCODE[code];
	}
	else
	{
		return ERRORCODE[ERROR_CODE_SUM - 1];
	}
}