#pragma once
class manageSearch
{
private:
	char m_pathDbFile[256];
public:
	manageSearch(void);
	~manageSearch(void);

	CString ExecuteSearch(CString tag); //ִ�в���
	int InsetInfo(CString tag, CString info);//����������
};

