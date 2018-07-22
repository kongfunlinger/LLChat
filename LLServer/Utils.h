#pragma once
class CUtils
{
public:
	CUtils();
	~CUtils();
public:
	static CString GetAppPath();
	static std::string  w2a(const wchar_t* pText);
	static std::wstring a2w(const char* pText);
	static string GBKToUTF8(const string strGBK);
	static string UTF8ToGBK(const string strUTF8);
	static string UnicodeToAnsi(const wchar_t* wstr);
	static wstring AnsiToUnicode(const char* cstr);

	//iniÎÄ¼þ²Ù×÷
	static SQLInfo GetSqlInfo();
};

