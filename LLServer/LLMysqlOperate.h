#pragma once
#include "MysqlConn.h"
class CLLMysqlOperate :
	public CMysqlConn
{
public:
	CLLMysqlOperate();
	~CLLMysqlOperate();
	//对部门数据表的操作
	vector<DepartmentInfo>  GetDepartmentVecByParentId(int nParentId);
	int                     InsertDepartmentInfo(DepartmentInfo info);
	int                     DeleteDepartmentById(int nDepartId);

	//对用户数据表的操作
	vector<AccountInfo>		GetAccountVecAllItem();
	int                     InsertAccountInfo(AccountInfo info);
	int                     DeleteAccountById(int nAccountId);
protected:
	int InitDataBase(string strIP,string strName,string strPW,string strDbName);
};

