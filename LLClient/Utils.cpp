#include "stdafx.h"
#include "Utils.h"
#include <memory>

CUtils::CUtils()
{
}


CUtils::~CUtils()
{
}

CString CUtils::GetAppPath()
{
	wchar_t chFullName[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, chFullName, MAX_PATH);
	CString strPath(chFullName);
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	return strPath;
}

std::string CUtils::w2a(const wchar_t* pText)
{
	long len = WideCharToMultiByte(CP_OEMCP, NULL, pText, -1, NULL, 0, NULL, FALSE);
	if (len == 0) return "";

	unique_ptr<char[]>pBuff(new char[len]);
	ZeroMemory(pBuff.get(), sizeof(char)*len);
	std::string cstr;
	if (pBuff.get())
	{
		WideCharToMultiByte(CP_OEMCP, NULL, pText, -1, pBuff.get(), len, NULL, FALSE);
		cstr = pBuff.get();
	}
	return cstr;
}

std::wstring CUtils::a2w(const char* pText)
{
	int len = ::MultiByteToWideChar(CP_ACP, 0, pText, -1, NULL, 0);
	if (len == 0) return L"";

	std::wstring strUnicode;
	unique_ptr<wchar_t[]>pBuff(new wchar_t[len]);
	ZeroMemory(pBuff.get(), sizeof(wchar_t)*len);
	if (pBuff.get())
	{
		::MultiByteToWideChar(CP_ACP, 0, pText, -1, pBuff.get(), len);
		strUnicode = pBuff.get();
	}

	return strUnicode;
}


std::string CUtils::GBKToUTF8(const string strGBK)
{
	std::string strOutUTF8;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	WCHAR * strTemp = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, strTemp, n);
	n = WideCharToMultiByte(CP_UTF8, 0, strTemp, -1, NULL, 0, NULL, NULL);
	char * strDst = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, strTemp, -1, strDst, n, NULL, NULL);
	strOutUTF8 = strDst;
	delete[]strTemp;
	strTemp = NULL;
	delete[]strDst;
	strDst = NULL;
	return strOutUTF8;
}

std::string CUtils::UTF8ToGBK(const string strUTF8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	wchar_t * wszGBK = new wchar_t[len + 1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, wszGBK, len);

	len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
	std::string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
}

std::string CUtils::UnicodeToAnsi(const wchar_t* wstr)
{
	int nlne = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	if (nlne == 0)
	{
		return NULL;
	}
	char* sztr = new char[nlne];
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, sztr, nlne, NULL, NULL);
	string strOut = sztr;
	delete[] sztr;
	return strOut;
}

std::wstring CUtils::AnsiToUnicode(const char* cstr)
{
	int nLen = MultiByteToWideChar(CP_ACP, 0, cstr, -1, NULL, 0);
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* wcstr = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, 0, cstr, -1, wcstr, nLen);
	wstring strOut = wcstr;
	delete[] wcstr;
	return strOut;
}

SQLInfo CUtils::GetSqlInfo()
{
	SQLInfo info;
	CString strPath = GetAppPath() + _T("\\LLServer.ini");
	TCHAR szBuf[MAX_PATH];
	GetPrivateProfileString(LLSERVERINI::SQLCONFIG, LLSERVERINI::SQLIP, _T("127.0.0.1"), szBuf, MAX_PATH, strPath);
	info.strIp = szBuf;

	GetPrivateProfileString(LLSERVERINI::SQLCONFIG, LLSERVERINI::SQLPORT, _T("3306"), szBuf, MAX_PATH, strPath);
	info.strPort = szBuf;

	GetPrivateProfileString(LLSERVERINI::SQLCONFIG, LLSERVERINI::SQLUSERNAME, _T("root"), szBuf, MAX_PATH, strPath);
	info.strUserName = szBuf;

	GetPrivateProfileString(LLSERVERINI::SQLCONFIG, LLSERVERINI::SQLUSERPASSWORD, _T("root"), szBuf, MAX_PATH, strPath);
	info.strUserPassWord = szBuf;

	GetPrivateProfileString(LLSERVERINI::SQLCONFIG, LLSERVERINI::SQLNAME, _T("liaoliaodb"), szBuf, MAX_PATH, strPath);
	info.strSqlName = szBuf;
	return info;
}

bool CUtils::WriteServerInfo(ServerInfo info)
{
	CString strPath = GetAppPath() + _T("\\LLClient.ini");
	BOOL bRetIp = WritePrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::SERVERIP, info.strIp, strPath);
	BOOL bRetPort = WritePrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::SERVERPORT, info.strPort, strPath);
	
	return bRetPort && bRetIp;

}

ServerInfo CUtils::ReadServerInfo()
{
	CString strPath = GetAppPath() + _T("\\LLClient.ini");
	ServerInfo info;
	TCHAR szBuf[MAX_PATH];
	GetPrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::SERVERIP, _T("127.0.0.1"), szBuf, MAX_PATH, strPath);
	info.strIp = szBuf;

	GetPrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::SERVERPORT, _T("3306"), szBuf, MAX_PATH, strPath);
	info.strPort = szBuf;
	return info;
}

bool CUtils::WriteUserInfo(UserInfo info)
{
	CString strPath = GetAppPath() + _T("\\LLClient.ini");
	BOOL bRetNAME = WritePrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::USERNAME, info.strName, strPath);
	BOOL bRetPW = TRUE;
	int nRememberPw = GetPrivateProfileInt(LLCLIENTINI::USERCONFIG, LLCLIENTINI::USERREMEMBERPW, 0, strPath);
	if (nRememberPw == 1)
	{
		bRetPW = WritePrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::USERPASSWORD, info.strPW, strPath);
	}
	return bRetPW && bRetNAME;
}

UserInfo CUtils::ReadUserInfo()
{
	CString strPath = GetAppPath() + _T("\\LLClient.ini");
	UserInfo info;
	TCHAR szBuf[MAX_PATH];
	GetPrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::USERNAME, _T(""), szBuf, MAX_PATH, strPath);
	info.strName = szBuf;

	GetPrivateProfileString(LLCLIENTINI::USERCONFIG, LLCLIENTINI::USERPASSWORD, _T(""), szBuf, MAX_PATH, strPath);
	info.strPW = szBuf;
	return info;
}
