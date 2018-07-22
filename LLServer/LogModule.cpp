#include "stdafx.h"
#include "LogModule.h"
#include "Utils.h"
#include "time.h"
#define TIME_MAX 32
template<> CLogModule* CSingleton<CLogModule>::ms_Singleton = nullptr;
CLogModule::CLogModule(string strLogPath) :m_strLogPath(strLogPath)
{
	m_logFile.open(strLogPath, std::fstream::in | std::fstream::out | std::fstream::app);
}


CLogModule::CLogModule()
{
	m_strLogPath = CUtils::GetAppPath() + "\\LLlogs\\";
	if (_access(m_strLogPath.c_str(), 0) == -1)
	{
		CreateDirectoryA(m_strLogPath.c_str(), nullptr);
	}
	m_strLogPath += GetCurDay() + ".log";
	m_logFile.open(m_strLogPath, std::fstream::in | std::fstream::out | std::fstream::app);
}

CLogModule::~CLogModule()
{
	if (m_logFile.is_open())
	{
		m_logFile.close();
	}
}


void CLogModule::StartWriteLog()
{
	if (!m_logFile.is_open())
	{
		m_logFile.open(m_strLogPath);
	}
	tm timep;
	localtime_s(&timep, &m_tStartTime);
	char stTime[TIME_MAX];
	asctime_s(stTime, &timep);
	m_logFile <<"-----------------start-----------------------------------"<< 
		stTime<<"---------------------------------------------------------" << endl;
}

void CLogModule::WriteLog(string strLog)
{
	if (!m_logFile.is_open())
	{
		m_logFile.open(m_strLogPath);
	}

	m_logFile <<strLog << endl;
}

void CLogModule::EndWriteLog()
{
	if (!m_logFile.is_open())
	{
		m_logFile.open(m_strLogPath);
	}
	tm timep;
	localtime_s(&timep, &m_tStartTime);
	char stTime[TIME_MAX];
	asctime_s(stTime, &timep); 

	char strCost[TIME_MAX];
	sprintf_s(strCost, "%f", difftime(m_tEndTime, m_tStartTime));

	m_logFile <<"used time: "<< strCost <<"s"<< endl;
	m_logFile <<  "-----------------end------------------------------------" << endl
		<<stTime<<"--------------------------------------------------------" << endl;
}

string CLogModule::GetCurDay()
{
	time_t timep;
	time(&timep);
	tm curtime;
	localtime_s(&curtime, &timep);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d", &curtime);
	return tmp;
}