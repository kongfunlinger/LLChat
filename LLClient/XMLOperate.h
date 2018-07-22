#pragma once
#include "Markup.h"
#include "Singleton.h"
class CXMLOperate :public CSingleton<CXMLOperate>
{
public:
	CXMLOperate();
	~CXMLOperate();
public:

protected:
	
	CString			  m_strPath;
};

