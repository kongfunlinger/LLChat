#define SAFE_DELETE(a) {if (a){delete (a);a=nullptr;}}


#define COLOR_WHITE RGB(255,255,255)

#define COLOR_RED RGB(255,0,0)

#define COLOR_BLACK RGB(0,0,0)
#define COLOR_TITLE_BK RGB(14,133,233)

#define DRAW_FONT_NAME _T("Arial")

#define TITLE_BAR_COLOR_TOP				CLR2ARGB(RGB(210,233,255))
#define TITLE_BAR_COLOR_BOTTOM		CLR2ARGB(RGB(153,204,255))
//定义两个消息
//const UINT MSG_CHILD2FATHER_DEPARTMENT = RegisterWindowMessage(_T("User+100"));
#define  MSG_CHILD2FATHER_ACCOUNT (WM_USER+101)
#define  MSG_CHILD2FATHER_DEPARTMENT (WM_USER + 102)

//部门信息结构体
struct DepartmentInfo
{
	int		nDepartID = 0;
	int		nParentId = 0;
	CString strDepartName;
};

//账户信息结构体
struct AccountInfo
{
	int     nAccountId = 0;
	int     nDepartmentId = 0;
	CString strName;
	CString strPassword;
	CString strSex;
	int     nAge = 0;
	CString strDepartmentName;
	CString strHeaderShip;

};

//数据库信息
struct SQLInfo
{
	CString strIp;
	CString strPort;
	CString strUserName;
	CString strUserPassWord;
	CString strSqlName;
};
//服务器信息
struct ServerInfo
{
	CString strIp;
	CString strPort;
};

//账户信息
struct UserInfo
{
	CString strName;
	CString strPW;
};

namespace XML
{
	static  CString ROOT = _T("root");
	static  CString DEPART = _T("depart");
	static  CString DEPARTID = _T("departId");
	static  CString DEPARTNAME = _T("departName");
	static  CString PARENTID = _T("parentId");
	static  CString ACCOUNT = _T("account");
	static  CString ACCOUNTID = _T("accountId");
	static  CString ACCOUNTNAME = _T("accountName");
	static  CString SEX = _T("sex");


};

namespace LLSERVERINI
{
	static CString SQLCONFIG = _T("sqlconfig");
	static CString SQLIP = _T("sqlip");
	static CString SQLPORT = _T("sqlport");
	static CString SQLUSERPASSWORD = _T("sqluserpassword");
	static CString SQLUSERNAME = _T("sqlusername");
	static CString SQLNAME = _T("sqlname");

	
}

namespace LLCLIENTINI
{
	static CString USERCONFIG = _T("userconfig");
	static CString USERNAME = _T("username");
	static CString USERPASSWORD = _T("userpassword");
	static CString USERAUTOLOGIN = _T("userautologin");
	static CString USERREMEMBERPW = _T("userrememberpw");
	static CString SERVERIP = _T("serverip");
	static CString SERVERPORT = _T("serverport");
}
