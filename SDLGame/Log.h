#ifndef LOG_H_
#define LOG_H_

#include "stdafx.h"

class Log
{
private:
	std::ofstream m_fileLog;
	std::chrono::system_clock::time_point m_tpNow;
	int countString();
	std::string asString(const std::chrono::system_clock::time_point & _timePoint);

	Log();
	Log(const Log & _logCopy);
	Log * operator=(const Log & _logCopy);
	~Log();

	static Log * s_pLog;
public:
	void write(const std::string & _writeLog);
	static Log * Instance();
	void release();

};

#endif // LOG_H_