#pragma once
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
enum DB_Error_Code
{
	ERROR_SUCESS = 0,
	ERROR_UNKNOWN = -1000,
	ERROR_INIT = -1001,
	ERROR_CONNECT = -1002,
	ERROR_STATEMENT = -1003,
	ERROR_EXECUTE =-1004,


};
class CMysqlConn
{
public:
	CMysqlConn();
	~CMysqlConn();
public:
	int                         OpenCon(string strIP,string strName,string password);
	int                         CloseCon();
	int                         SetSchema(string strDB);
	int                         Execute(string strSql);

	int							ExecuteQuery(string strSql,sql::ResultSet** pRes);



	//int                         GetTables(vector<string>& vecTab);
protected:
	
private:
	sql::Driver*                 m_pDriver = nullptr;
	sql::Connection*             m_pConnect = nullptr; 
};

