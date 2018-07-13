#include "stdafx.h"
#include "LLMysqlOperate.h"
#include "Utils.h"

CLLMysqlOperate::CLLMysqlOperate()
{
	int nError = InitDataBase("127.0.0.1", "root", "wangluling!012", "liaoliaodb");
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
	CString strSql;
	strSql.Format(_T("SELECT * FROM tb_account"));
	sql::ResultSet* pRes = nullptr;
	int nError = ExecuteQuery(CUtils::w2a(strSql.GetString()), &pRes);
	if (nError == ERROR_SUCESS)
	{
		while (pRes->next())
		{
			AccountInfo accountInfo;
			accountInfo.nAccountId = pRes->getInt("accountId");
			sql::SQLString strName = pRes->getString("accountName");
			accountInfo.strName = strName->c_str();
			sql::SQLString strPassWord = pRes->getString("accountPassWord");
			accountInfo.strPassword = strPassWord->c_str();
			sql::SQLString strSex = pRes->getString("Sex");
			accountInfo.strSex = strSex->c_str();
			accountInfo.nAge = pRes->getInt("Age");
			accountInfo.nDepartmentId = pRes->getInt("departmentId");
			sql::SQLString strDepName = pRes->getString("departmentName");
			accountInfo.strDepartmentName = strDepName->c_str();
			sql::SQLString strHeadShip = pRes->getString("headerShip");
			accountInfo.strHeaderShip = strHeadShip->c_str();
			vecAccount.push_back(accountInfo);
		}
	}
	return vecAccount;
}

int CLLMysqlOperate::InsertDepartmentInfo(DepartmentInfo info)
{
	int nErrorCode = ERROR_SUCESS;
	CStringA strSql;
	strSql.Format("INSERT INTO tb_department (departId,departName,parentId) VALUES (%d,'%s',%d)",info.nDepartID,CUtils::GBKToUTF8(info.strDepartName),info.nParentId);
	nErrorCode = Execute(strSql.GetString());
	return nErrorCode;
}

int CLLMysqlOperate::InsertAccountInfo(AccountInfo info)
{
	int nErrorCode = ERROR_SUCESS;
	return nErrorCode;
}

int CLLMysqlOperate::DeleteDepartmentById(int nDepartId)
{
	int nErrorCode = ERROR_SUCESS;
	CString strSql;
	strSql.Format(_T("DELETE FROM tb_department WHERE departId=%d"), nDepartId);
	nErrorCode = Execute(CUtils::w2a(strSql.GetString()));
	return nErrorCode;
}

int CLLMysqlOperate::DeleteAccountById(int nAccountId)
{
	int nErrorCode = ERROR_SUCESS;
	return nErrorCode;
}
