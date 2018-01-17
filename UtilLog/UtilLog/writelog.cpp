#include "writelog.h"

#include <io.h>
#include <atlstr.h>
#include <time.h>
#include <stdio.h>
#include <sys/timeb.h>  
#include <fcntl.h>

writelog::writelog()
{
}


writelog::~writelog()
{
}

void writelog::Run(const char* buffer)
{
	this->write(getFileName(TYPERUN), buffer, TYPERUN);
}

void writelog::Info(const char* buffer)
{
	this->write(getFileName(TYPEINFO), buffer, TYPEINFO);
}

void writelog::Debug(const char* buffer)
{
	this->write(getFileName(TYPEDBG), buffer, TYPEDBG);
}

void writelog::Warn(const char* buffer)
{
	this->write(getFileName(TYPEWARN), buffer, TYPEWARN);
}

void writelog::Error(const char* buffer)
{
	this->write(getFileName(TYPEERR), buffer, TYPEERR);
}

void writelog::NetworkPackage(const char* buffer)
{
	this->write(getFileName(TYPERUN), buffer, TYPERUN);
}

std::string writelog::getFileName(int type)
{
	char szapipath[MAX_PATH];
	memset(szapipath, 0, MAX_PATH);
	GetModuleFileNameA(NULL, szapipath, MAX_PATH);

	//获取应用程序名称
	char szExe[MAX_PATH] = {0x0};
	char *pbuf = NULL;
	char* szLine = strtok_s(szapipath, "\\", &pbuf);
	while (NULL != szLine)
	{
		strcpy_s(szExe, szLine);
		szLine = strtok_s(NULL, "\\", &pbuf);
	}

	strncpy_s(szapipath, szExe, strlen(szExe) - 4);

	switch (type)
	{
	case TYPERUN:
		strcat(szapipath, "_run");
		break;

	case TYPEERR:
		strcat(szapipath, "_error");
		break;

	case TYPEDBG:
		strcat(szapipath, "_debug");
		break;

	case TYPEINFO:
		strcat(szapipath, "_info");
		break;

	case TYPEWARN:
		strcat(szapipath, "_warn");
		break;

	}
	return makeFileDate(szapipath);
}

char* LogFileTime(bool isDate = true)
{
	struct  tm      *ptm;
	struct  timeb   stTimeb;
	static  char    szTime[9] = {0x0};

	ftime(&stTimeb);
	ptm = localtime(&stTimeb.time);
	if (isDate)
	{
		sprintf(szTime, "_%04d%02d%02d", ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday);
	}
	else
	{
		sprintf(szTime, "_%02d%02d%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
	}
	
	return szTime;
}

// 
std::string writelog::makeFileDate(const string &filename)
{
	//TODO
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // 删除程序名，只获得路径字串
	string strLogFilePath = szFilePath;  // strLogFilePath==e:\program\Debug\

	strLogFilePath += "log\\" + filename + LogFileTime() + ".log";

	FILE* file = fopen(strLogFilePath.c_str(), "a+");
	if (file->_bufsiz >= MAX_FILE_SIZE)
	{
		string strNewLogFile = strLogFilePath + LogFileTime(false);
		rename(strLogFilePath.c_str(), strNewLogFile.c_str());

		strLogFilePath = strNewLogFile;		
	}
	
	fclose(file);
	return strLogFilePath;
}

void writelog::write(const string &filename, const char* buffer, int type)
{
	switch (type)
	{
	case TYPERUN:
	{
		if (NULL == m_pRunFile)
		{
			m_pRunFile = fopen(filename.c_str(), "a+");
		}
		write(filename, buffer, m_pRunFile);
		break;
	}

	case TYPEERR:
	{
		if (NULL == m_pErrFile)
		{
			m_pErrFile = fopen(filename.c_str(), "a+");
		}
		write(filename, buffer, m_pErrFile);
		break;
	}

	case TYPEDBG:
	{
		if (NULL == m_pDebugFile)
		{
			m_pDebugFile = fopen(filename.c_str(), "a+");
		}
		write(filename, buffer, m_pDebugFile);
		break;
	}

	case TYPEINFO:
	{
		if (NULL == m_pInfoFile)
		{
			m_pInfoFile = fopen(filename.c_str(), "a+");
		}
		write(filename, buffer, m_pInfoFile);
		break;
	}

	case TYPEWARN:
	{
		if (NULL == m_pWarnFile)
		{
			m_pWarnFile = fopen(filename.c_str(), "a+");
		}
		write(filename, buffer, m_pWarnFile);
		break;
	}

	default:
		break;
	}
}

void writelog::write(const string &filename, const char* buffer, FILE *&pFile)
{
	string _buffer = buffer;
	_buffer.append("\n");
	int size = _buffer.size();
	char *pBuffer = new char[size + 1];
	memset(pBuffer, 0x0, size + 1);
	memcpy(pBuffer, _buffer.data(), size);
	fwrite(pBuffer, size, sizeof(char), pFile);
	fflush(pFile);
	delete[] pBuffer;

	FILE* file = fopen(filename.c_str(), "a+");
	if (file->_bufsiz >= MAX_FILE_SIZE)
	{
		fclose(pFile);
		pFile = NULL;
	}
}
