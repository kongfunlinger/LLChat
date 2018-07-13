#include "stdafx.h"
#include "MysqlConn.h"


CMysqlConn::CMysqlConn()
{
	m_pConnect = nullptr;
	m_pDriver = nullptr;
}


CMysqlConn::~CMysqlConn()
{
}

int CMysqlConn::OpenCon(string strIP, string strName, string password)
{
	m_pDriver = get_driver_instance();
	if (m_pDriver == nullptr)
	{
		return ERROR_INIT;
	}
	try
	{
		m_pConnect = m_pDriver->connect(strIP.c_str(), strName.c_str(), password.c_str());
		if (m_pConnect == nullptr)
		{
			return ERROR_CONNECT;
		}
	
	}
	catch (sql::SQLException& e)
	{
		return ERROR_CONNECT;
	}
	catch (std::runtime_error& e)
	{
		return ERROR_CONNECT;
	}
	catch (CException* e)
	{
		return ERROR_UNKNOWN;
	}
	
	return ERROR_SUCESS;
}

int CMysqlConn::CloseCon()
{
	if (m_pConnect != nullptr)
	{
		try
		{
			m_pConnect->close();
		}
		catch (sql::SQLException&e)
		{
			return ERROR_CONNECT;
		}
		catch (std::exception&e)
		{
			return ERROR_UNKNOWN;
		}
		SAFE_DELETE(m_pConnect);
		return ERROR_SUCESS;
	}
	return ERROR_UNKNOWN;
}

int CMysqlConn::SetSchema(string strDBName)
{
	if (m_pConnect == nullptr)
	{
		return ERROR_CONNECT;
	}
	try
	{
		//选择要连接的数据库
		m_pConnect->setSchema(strDBName.c_str());
		boost::scoped_ptr<sql::Statement> pst(m_pConnect->createStatement());
		pst->execute("SET NAMES 'GBK'");

	}
	catch (sql::SQLException&e)
	{
		return ERROR_CONNECT;
	}
	catch (std::exception&e)
	{
		return ERROR_UNKNOWN;
	}
	return ERROR_SUCESS;
}

//int CMysqlConn::GetTables(vector<string>& vecTab)
//{
//	int nErrorcode = ERROR_SUCESS;
//	sql::ResultSet* pSet = nullptr;
//	string strSQL = "show tables;";
//	nErrorcode = ExecuteQuery(strSQL, &pSet);
//	if (pSet != nullptr)
//	{
//		while (pSet->next())
//		{
//			sql::ResultSetMetaData* pDat = pSet->getMetaData();
//			if (pDat != nullptr)
//			{
//				sql::SQLString str = pDat->getTableName(0);
//				CString strt;
//				strt= str.c_str();
//				OutputDebugString(strt);
//			}
//			/*int n = pSet->getInt("Id");
//			CString strt;
//			sql::SQLString s=pSet->getString("name");
//			strt = s.c_str();
//			CString str;
//			str.Format(_T("%d"), n);
//			OutputDebugString(str);
//			OutputDebugString(strt);*/
//		}
//	}
//	return ERROR_SUCESS;
//}

int CMysqlConn::Execute(string strSql)
{
	if (m_pConnect == nullptr)
	{
		return ERROR_CONNECT;
	}
	sql::Statement* pst = m_pConnect->createStatement();

	if (pst == nullptr)
	{
		return ERROR_STATEMENT;
	}
	try
	{
		pst->execute(strSql.c_str());
	}
	catch (sql::SQLException&e)
	{
		CString str(e.getSQLStateCStr());
		CString strInfo(e.what());
		OutputDebugString(str+strInfo);
		return ERROR_EXECUTE;
	}
	catch (std::exception&e)
	{
		return ERROR_UNKNOWN;
	}
	return ERROR_SUCESS;
	
}

int CMysqlConn::ExecuteQuery(string strSql, sql::ResultSet** pRes)
{
	if (m_pConnect == nullptr)
	{
		return ERROR_CONNECT;
	}
	sql::Statement* pst = m_pConnect->createStatement();
	if (pst == nullptr)
	{
		return ERROR_STATEMENT;
	}
	try
	{
		*pRes = pst->executeQuery(strSql.c_str());
	}
	catch (sql::SQLException&e)
	{
		return ERROR_EXECUTE;
	}
	catch (std::exception&e)
	{
		return ERROR_UNKNOWN;
	}
	return ERROR_SUCESS;

}
