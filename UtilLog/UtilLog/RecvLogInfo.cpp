#include "RecvLogInfo.h"
#include "writelog.h"

writelog g_writeLog;
RecvLogInfo RecvLogInfo::m_instance;

RecvLogInfo::RecvLogInfo()
{
}


RecvLogInfo::~RecvLogInfo()
{
}

void RecvLogInfo::write(int logLevel, const char* buffer)
{
	if (buffer)
	{
		switch (logLevel)
		{
		case RecvLogInfo::RUN:
			g_writeLog.Run(buffer);
			break;

		case RecvLogInfo::ERROR:
			g_writeLog.Error(buffer);
			break;

		case RecvLogInfo::DEBUG:
			g_writeLog.Debug(buffer);
			break;

		case RecvLogInfo::INFO:
			g_writeLog.Info(buffer);
			break;

		case RecvLogInfo::WARN:
			g_writeLog.Warn(buffer);
			break;

		case RecvLogInfo::NETPACKAGE:
			g_writeLog.NetworkPackage(buffer);
			break;

		default:
			break;
		}
	}
}
