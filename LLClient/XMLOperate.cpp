#include "stdafx.h"
#include "XMLOperate.h"
#include "Utils.h"

template<> CXMLOperate* CSingleton<CXMLOperate>::ms_Singleton = nullptr;
CXMLOperate::CXMLOperate()
{
	m_strPath = CUtils::GetAppPath() + _T("\\xml\\");
	if (_access(CUtils::w2a(m_strPath.GetString()).c_str(), 0) == -1)
	{
		CreateDirectoryA(CUtils::w2a(m_strPath).c_str(), nullptr);
	}
	m_strPath += _T("data.xml");
}

CXMLOperate::~CXMLOperate()
{
}
