#include "stdafx.h"
#include "XMLOperate.h"
#include "LLMysqlOperate.h"
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

bool CXMLOperate::UpdateXml(CString strPath)
{
	CMarkup xml;
	xml.AddElem(XML::ROOT);
	xml.IntoElem();
	xml.AddElem(XML::DEPART);
	xml.SetAttrib(XML::DEPARTID, 0);
	xml.SetAttrib(XML::PARENTID, 0);
	xml.SetAttrib(XML::DEPARTNAME, _T("部门组织"));
	xml.IntoElem();
	
	vector<DepartmentInfo> departVec = CLLMysqlOperate::getSingletonPtr()->GetDepartmentVecByParentId(0);
	for (int i = 0; i < departVec.size();++i)
	{
		InsertDepart(xml,departVec.at(i));
	}
	

	xml.OutOfElem();
	xml.OutOfElem();

	return xml.Save(strPath);
}

void CXMLOperate::UpdateXml()
{
	UpdateXml(m_strPath);
}

void CXMLOperate::InsertAccount(CMarkup& xml, AccountInfo info)
{
	xml.AddElem(XML::ACCOUNT);
	xml.SetAttrib(XML::ACCOUNTID, info.nAccountId);
	xml.SetAttrib(XML::ACCOUNTNAME, info.strName);
	xml.SetAttrib(XML::SEX, info.strSex);
	xml.SetAttrib(XML::DEPARTID, info.nDepartmentId);
}

void CXMLOperate::InsertDepart(CMarkup& xml, DepartmentInfo info)
{
	xml.AddElem(XML::DEPART);
	xml.SetAttrib(XML::DEPARTID, info.nDepartID);
	xml.SetAttrib(XML::PARENTID, info.nParentId);
	xml.SetAttrib(XML::DEPARTNAME, info.strDepartName);
	xml.IntoElem();

	vector<AccountInfo> accountVec = CLLMysqlOperate::getSingletonPtr()->GetAccountVecByDepartId(info.nDepartID);
	for (int i = 0; i < accountVec.size(); ++i)
	{
		InsertAccount(xml,accountVec.at(i));
	}

	//递归
	vector<DepartmentInfo> departVec = CLLMysqlOperate::getSingletonPtr()->GetDepartmentVecByParentId(info.nDepartID);
	for (int i = 0; i < departVec.size();++i)
	{
		InsertDepart(xml,departVec.at(i));
	}

	xml.OutOfElem();
}
