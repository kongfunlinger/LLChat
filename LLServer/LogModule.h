#pragma once
#include <fstream>
#include <sstream>  
#include "Singleton.h"
#include <time.h>  
class CLogModule : public CSingleton<CLogModule>
{
public:
	CLogModule(string strLogPath);
	CLogModule();
	~CLogModule();

public:
	void            StartWriteLog();
	void            WriteLog(string strLog);
	void            EndWriteLog();
protected:
	string          GetCurDay();
private:
	time_t          m_tStartTime;
	time_t          m_tEndTime;
	fstream			m_logFile;
	string          m_strLogPath;
};

