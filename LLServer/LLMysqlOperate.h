#pragma once
#include "MysqlConn.h"
#include "Singleton.h"
class CLLMysqlOperate :
	public CMysqlConn,
	public CSingleton<CLLMysqlOperate>
{
public:
	CLLMysqlOperate();
	~CLLMysqlOperate();
	//对部门数据表的操作
	vector<DepartmentInfo>  GetDepartmentVecByParentId(int nParentId);
	DepartmentInfo			GetDepartmentInfoById(int nDepartId);
	int                     InsertDepartmentInfo(DepartmentInfo info);
	int                     DeleteDepartmentById(int nDepartId);
	int                     GetNewDepartId();

	//对用户数据表的操作
	vector<AccountInfo>		GetAccountVecAllItem();
	vector<AccountInfo>     GetAccountVecByDepartId(int nDepartId);
	AccountInfo				GetAccountInfoById(int nAccountId);
	int                     InsertAccountInfo(AccountInfo info);
	int                     DeleteAccountById(int nAccountId);
protected:
	int InitDataBase(string strIP,string strName,string strPW,string strDbName);
};

