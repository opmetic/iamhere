#include "StdAfx.h"
#include "manageSearch.h"


manageSearch::manageSearch(void)
{
	::GetCurrentDirectory(256, m_pathDbFile);
	memset(m_pathDbFile, '\0', 256);
	strcpy(m_pathDbFile, "db.imh");                       //���Ե�ַ
	CFile RecFile;
	if (GetFileAttributes(m_pathDbFile) == -1 )                          //�ж��ļ��Ƿ����
	{
		RecFile.Open(m_pathDbFile, CFile::modeCreate);              //�����ھʹ���
		RecFile.Close();
	}
}


manageSearch::~manageSearch(void)
{
}

//ִ�в���
CString manageSearch::ExecuteSearch(CString tag)
{
	int lenTag = 0;
	CFile RecFile;
	CString sourceData, info = "";//����һ��ʱ��������һ����¼
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

//����������
int manageSearch::InsetInfo(CString tag, CString info)
{
	int ret = 0;
	CString sourceData;//����һ��ʱ��������һ����¼
	CFile RecFile;
	CFileException ex;
	RecFile.Open(m_pathDbFile, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite, &ex);        //���ļ�
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