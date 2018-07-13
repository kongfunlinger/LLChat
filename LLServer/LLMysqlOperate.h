#pragma once
#include "MysqlConn.h"
class CLLMysqlOperate :
	public CMysqlConn
{
public:
	CLLMysqlOperate();
	~CLLMysqlOperate();
	//�Բ������ݱ�Ĳ���
	vector<DepartmentInfo>  GetDepartmentVecByParentId(int nParentId);
	int                     InsertDepartmentInfo(DepartmentInfo info);
	int                     DeleteDepartmentById(int nDepartId);

	//���û����ݱ�Ĳ���
	vector<AccountInfo>		GetAccountVecAllItem();
	int                     InsertAccountInfo(AccountInfo info);
	int                     DeleteAccountById(int nAccountId);
protected:
	int InitDataBase(string strIP,string strName,string strPW,string strDbName);
};

