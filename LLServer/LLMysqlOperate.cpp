#include "stdafx.h"
#include "LLMysqlOperate.h"
#include "Utils.h"
#include "XMLOperate.h"

template<> CLLMysqlOperate* CSingleton<CLLMysqlOperate>::ms_Singleton = nullptr;
CLLMysqlOperate::CLLMysqlOperate()
{
	SQLInfo info = CUtils::GetSqlInfo();
	int nError = InitDataBase(CUtils::w2a(info.strIp), CUtils::w2a(info.strUserName), CUtils::w2a(info.strUserPassWord), CUtils::w2a(info.strSqlName));
	if (nError != ERROR_SUCESS)
	{
		AfxMessageBox(_T("初始化数据库失败"));
	}
}


CLLMysqlOperate::~CLLMysqlOperate()
{
}

vector<DepartmentInfo> CLLMysqlOperate::GetDepartmentVecByParentId(int nParentId)
{
	vector<DepartmentInfo> vecDep;
	CString strSql;
	strSql.Format(_T("SELECT * FROM tb_department WHERE parentId=%d"),nParentId);

	sql::ResultSet* pRes = nullptr;
	int nError = ExecuteQuery(CUtils::w2a(strSql.GetBuffer()), &pRes);
	if (nError == ERROR_SUCESS)
	{
		while (pRes->next())
		{
			DepartmentInfo info;
			info.nDepartID = pRes->getInt("departId");
			info.nParentId = pRes->getInt("parentId");
			sql::SQLString strName = pRes->getString("departName");
			info.strDepartName = strName.c_str();
			vecDep.push_back(info);
		}
	}

	return vecDep;
}

DepartmentInfo CLLMysqlOperate::GetDepartmentInfoById(int nDepartId)
{
	DepartmentInfo info;
	CString strSql;
	strSql.Format(_T("SELECT * FROM tb_department WHERE departId=%d"), nDepartId);

	sql::ResultSet* pRes = nullptr;
	int nError = ExecuteQuery(CUtils::w2a(strSql.GetBuffer()), &pRes);
	if (nError == ERROR_SUCESS)
	{
		while (pRes->next())
		{
			info.nDepartID = pRes->getInt("departId");
			info.nParentId = pRes->getInt("parentId");
			sql::SQLString strName = pRes->getString("departName");
			info.strDepartName = strName.c_str();
		}
	}

	return info;
}

int CLLMysqlOperate::InitDataBase(string strIP, string strName, string strPW, string strDbName)
{
	int nErrorCode = OpenCon(strIP, strName, strPW);
	if (nErrorCode == ERROR_SUCESS)
	{
		nErrorCode = SetSchema(strDbName);
	}
	return nErrorCode;
}

vector<AccountInfo> CLLMysqlOperate::GetAccountVecAllItem()
{
	vector<AccountInfo> vecAccount;
	CStringA strSql = "SELECT * FROM tb_account";
	sql::ResultSet* pRes = nullptr;
	int nError = ExecuteQuery(strSql.GetString(), &pRes);
	if (nError == ERROR_SUCESS)
	{
		while (pRes->next())
		{
			AccountInfo accountInfo;
			accountInfo.nAccountId = pRes->getInt("accountId");
			sql::SQLString strName = pRes->getString("accountName");
			accountInfo.strName = strName.c_str();
			sql::SQLString strPassWord = pRes->getString("accountPassWord");
			accountInfo.strPassword = strPassWord.c_str();
			sql::SQLString strSex = pRes->getString("Sex");
			accountInfo.strSex = strSex.c_str();
			accountInfo.nAge = pRes->getInt("Age");
			accountInfo.nDepartmentId = pRes->getInt("departmentId");
			sql::SQLString strDepName = pRes->getString("departmentName");
			accountInfo.strDepartmentName = strDepName.c_str();
			sql::SQLString strHeadShip = pRes->getString("headerShip");
			accountInfo.strHeaderShip = strHeadShip.c_str();
			vecAccount.push_back(accountInfo);
		}
	}
	return vecAccount;
}

vector<AccountInfo> CLLMysqlOperate::GetAccountVecByDepartId(int nDepartId)
{
	vector<AccountInfo> vecAccount;
	CStringA strSql;
	strSql.Format("SELECT * FROM tb_account WHERE departId=%d",nDepartId);
	sql::ResultSet* pRes = nullptr;
	int nError = ExecuteQuery(strSql.GetString(), &pRes);
	if (nError == ERROR_SUCESS)
	{
		while (pRes->next())
		{
			AccountInfo accountInfo;
			accountInfo.nAccountId = pRes->getInt("accountId");
			sql::SQLString strName = pRes->getString("accountName");
			accountInfo.strName = strName.c_str();
			sql::SQLString strPassWord = pRes->getString("passWord");
			accountInfo.strPassword = strPassWord.c_str();
			sql::SQLString strSex = pRes->getString("sex");
			accountInfo.strSex = strSex.c_str();
			accountInfo.nAge = pRes->getInt("age");
			accountInfo.nDepartmentId = pRes->getInt("departId");
			sql::SQLString strDepName = pRes->getString("departName");
			accountInfo.strDepartmentName = strDepName.c_str();
			sql::SQLString strHeadShip = pRes->getString("headerShip");
			accountInfo.strHeaderShip = strHeadShip.c_str();
			vecAccount.push_back(accountInfo);
		}
	}
	return vecAccount;
}

AccountInfo CLLMysqlOperate::GetAccountInfoById(int nAccountId)
{
	AccountInfo accountInfo;
	CStringA strSql;
	strSql.Format("SELECT * FROM tb_account WHERE accountId=%d", nAccountId);
	sql::ResultSet* pRes = nullptr;
	int nError = ExecuteQuery(strSql.GetString(), &pRes);
	if (nError == ERROR_SUCESS)
	{
		while (pRes->next())
		{
			accountInfo.nAccountId = pRes->getInt("accountId");
			sql::SQLString strName = pRes->getString("accountName");
			accountInfo.strName = strName.c_str();
			sql::SQLString strPassWord = pRes->getString("passWord");
			accountInfo.strPassword = strPassWord.c_str();
			sql::SQLString strSex = pRes->getString("sex");
			accountInfo.strSex = strSex.c_str();
			accountInfo.nAge = pRes->getInt("age");
			accountInfo.nDepartmentId = pRes->getInt("departId");
			sql::SQLString strDepName = pRes->getString("departName");
			accountInfo.strDepartmentName = strDepName.c_str();
			sql::SQLString strHeadShip = pRes->getString("headerShip");
			accountInfo.strHeaderShip = strHeadShip.c_str();
		}
	}
	return accountInfo;
}

int CLLMysqlOperate::InsertDepartmentInfo(DepartmentInfo info)
{
	int nErrorCode = ERROR_SUCESS;
	CString strSql;
	strSql.Format(_T("INSERT INTO tb_department (departId,departName,parentId) VALUES (%d,'%s',%d)"),info.nDepartID,info.strDepartName,info.nParentId);
	nErrorCode = Execute(CUtils::w2a(strSql.GetString()));
	if (nErrorCode == ERROR_SUCESS)
	{
		CXMLOperate::getSingletonPtr()->UpdateXml();
	}
	return nErrorCode;
}

int CLLMysqlOperate::InsertAccountInfo(AccountInfo info)
{
	int nErrorCode = ERROR_SUCESS;
	CString strSql;
	strSql.Format(_T("INSERT INTO tb_account (accountId,accountName,passWord,sex,age,departId,departName,headerShip) VALUES (%d,'%s','%s','%s',%d,%d,'%s','%s')"), 
		info.nAccountId, info.strName, info.strPassword, info.strSex, info.nAge, info.nDepartmentId, info.strDepartmentName, info.strHeaderShip);
	nErrorCode = Execute(CUtils::w2a(strSql.GetString()));
	if (nErrorCode == ERROR_SUCESS)
	{
		CXMLOperate::getSingletonPtr()->UpdateXml();
	}
	return nErrorCode;
}

int CLLMysqlOperate::DeleteDepartmentById(int nDepartId)
{
	int nErrorCode = ERROR_SUCESS;
	CStringA strSql;
	strSql.Format("DELETE FROM tb_department WHERE departId=%d", nDepartId);
	nErrorCode = Execute(strSql.GetString());
	if (nErrorCode == ERROR_SUCESS)
	{
		CXMLOperate::getSingletonPtr()->UpdateXml();
	}
	return nErrorCode;
}


int CLLMysqlOperate::GetNewDepartId()
{
	int nId=0;
	CStringA strSql = "SELECT MAX(departId) FROM tb_department";
	sql::ResultSet* pRes = nullptr;
	ExecuteQuery(strSql.GetString(),&pRes);
	while (pRes->next())
	{
		nId = pRes->getInt("max(departId)");
	}
	return (nId+1);
}


int CLLMysqlOperate::DeleteAccountById(int nAccountId)
{
	int nErrorCode = ERROR_SUCESS;
	CStringA strSql;
	strSql.Format("DELETE FROM tb_account WHERE accountId=%d", nAccountId);
	nErrorCode = Execute(strSql.GetString());
	if (nErrorCode == ERROR_SUCESS)
	{
		CXMLOperate::getSingletonPtr()->UpdateXml();
	}
	return nErrorCode;
}
