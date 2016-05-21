#include "Log.h"
#include <datetimeapi.h>

Log * Log::s_pLog = 0;

Log::Log()
{
	if (countString() > 100000)
	{
		m_fileLog.open("log.txt", std::ios::trunc);
	}
	else
	{
		m_fileLog.open("log.txt", std::ios::app);
	}
	m_tpNow = std::chrono::system_clock::now();
	m_fileLog << asString(m_tpNow).c_str() << "  Application start." << std::endl;
	m_fileLog << std::string(asString(m_tpNow) + ".txt").c_str() << std::endl;
	m_fileLog.close();
}

Log::~Log()
{
}

void Log::write(const std::string & _writeLog)
{
	m_fileLog.open("log.txt", std::ios::app);
	m_tpNow = std::chrono::system_clock::now();
	m_fileLog << asString(m_tpNow).c_str() << "  " << _writeLog.c_str() << std::endl;
	m_fileLog.close();
}

int Log::countString()
{
	std::ifstream fin;
	fin.open("log.txt", std::ios_base::in);
	if (!fin.good())
	{
		return 0;
	}
	int n_countStr = 0;
	std::string strRead;
	while (std::getline(fin, strRead))
		++n_countStr;
	fin.close();
	return n_countStr;
}

Log * Log::Instance()
{
	if (!s_pLog)
	{
		s_pLog = new Log();
	}
	return s_pLog;
}

void Log::release()
{
	if (s_pLog)
		delete s_pLog;
}

std::string Log::asString(const std::chrono::system_clock::time_point & _timePoint)
{
	char      TimeBuffer[26] = {};
	time_t    RawTime = 0;
	time(&RawTime);
	ctime_s(TimeBuffer, 26 * sizeof(char), &RawTime);
	std::string currentTime(TimeBuffer);
	currentTime.resize(currentTime.size() - 1);
	return currentTime;
}