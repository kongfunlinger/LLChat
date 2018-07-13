#define SAFE_DELETE(a) {if (a){delete (a);a=nullptr;}}


#define COLOR_WHITE RGB(255,255,255)

#define COLOR_RED RGB(255,0,0)

#define COLOR_BLACK RGB(0,0,0)
#define COLOR_TITLE_BK RGB(14,133,233)

#define DRAW_FONT_NAME _T("Arial")


//定义两个消息
//const UINT MSG_CHILD2FATHER_DEPARTMENT = RegisterWindowMessage(_T("User+100"));
#define  MSG_CHILD2FATHER_ACCOUNT (WM_USER+101)
#define  MSG_CHILD2FATHER_DEPARTMENT (WM_USER + 102)

//部门信息结构体
struct DepartmentInfo
{
	int		nDepartID = 0;
	int		nParentId = 0;
	string  strDepartName;
};

//账户信息结构体
struct AccountInfo
{
	int     nAccountId = 0;
	int     nDepartmentId = 0;
	string  strName;
	string  strPassword;
	string  strSex;
	int     nAge = 0;
	string  strDepartmentName;
	string  strHeaderShip;

};