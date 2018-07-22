#pragma once
#include "Markup.h"
#include "Singleton.h"
class CXMLOperate :public CSingleton<CXMLOperate>
{
public:
	CXMLOperate();
	~CXMLOperate();
public:
	void			  UpdateXml();
protected:
	bool			  UpdateXml(CString strPath);
	bool			  LoadXml(CString strPath);
	void			  InsertAccount(CMarkup& xml,AccountInfo info);
	void			  InsertDepart(CMarkup& xml, DepartmentInfo info);
	CString			  m_strPath;
};

