#include "stdafx.h"
#include "Utils.h"
#include <memory>

CUtils::CUtils()
{
}


CUtils::~CUtils()
{
}

std::wstring CUtils::GetAppPath()
{
	wchar_t chFullName[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, chFullName, MAX_PATH);
	wstring strPath(chFullName);
	strPath = strPath.substr(0,strPath.find_last_of(_T("\\")));
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