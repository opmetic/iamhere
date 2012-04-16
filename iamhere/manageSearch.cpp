#include "StdAfx.h"
#include "manageSearch.h"


manageSearch::manageSearch(void)
{
	::GetCurrentDirectory(256, m_pathDbFile);
	memset(m_pathDbFile, '\0', 256);
	strcpy(m_pathDbFile, "db.imh");                       //绝对地址
	CFile RecFile;
	if (GetFileAttributes(m_pathDbFile) == -1 )                          //判断文件是否存在
	{
		RecFile.Open(m_pathDbFile, CFile::modeCreate);              //不存在就创建
		RecFile.Close();
	}
}


manageSearch::~manageSearch(void)
{
}

//执行查找
CString manageSearch::ExecuteSearch(CString tag)
{
	int lenTag = 0;
	CFile RecFile;
	CString sourceData, info = "";//定义一临时变量保存一条记录
	CFileException ex;
	RecFile.Open(m_pathDbFile, CFile::modeRead , &ex); 
	CArchive ar(&RecFile, CArchive::load);  

	tag += "=";
	lenTag = tag.GetLength();
	if (lenTag > 1)
	{
		while (ar.ReadString(sourceData))
		{

			if (sourceData.Left(lenTag) == tag )
			{
				info += sourceData.Mid(tag.GetLength());
				info += "\r\n\r\n";
			}
			sourceData.Empty();
		}
	}
	ar.Close();
	RecFile.Close();
	info.Replace("<<RETRUN>>", "\r\n");
	return info;
}

//增加新数据
int manageSearch::InsetInfo(CString tag, CString info)
{
	int ret = 0;
	CString sourceData;//定义一临时变量保存一条记录
	CFile RecFile;
	CFileException ex;
	RecFile.Open(m_pathDbFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &ex);        //打开文件
	info.Replace("\r\n", "<<RETRUN>>");
	sourceData = tag + '=' + info;
	sourceData += "\r\n";
	CArchive ar(&RecFile, CArchive::store);  
	RecFile.SeekToEnd();
	ar.WriteString(sourceData);
	ar.Close();
	RecFile.Close();
	//MessageBox(NULL, tag, info, MB_OK);
	return ret;
}