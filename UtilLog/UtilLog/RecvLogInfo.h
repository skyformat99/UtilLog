#ifndef RECVLOGINFO_H
#define RECVLOGINFO_H

class RecvLogInfo
{
public:
	explicit RecvLogInfo();
	static RecvLogInfo* instance() { return &m_instance; }

	~RecvLogInfo();

	typedef enum Log_Level
	{
		RUN = 1,
		ERROR, 
		DEBUG, 
		INFO, 
		WARN, 
		NETPACKAGE
	}LOG_LEVEL;

//private:
	static RecvLogInfo m_instance;
	static void write(int logLevel, const char* buffer);
};

#endif