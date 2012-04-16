#pragma once
class manageSearch
{
private:
	char m_pathDbFile[256];
public:
	manageSearch(void);
	~manageSearch(void);

	CString ExecuteSearch(CString tag); //执行查找
	int InsetInfo(CString tag, CString info);//增加新数据
};

