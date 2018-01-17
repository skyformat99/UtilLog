#include <string>

using namespace std;

const int TYPERUN	= 0x0001;
const int TYPEERR	= 0x0002;
const int TYPEDBG	= 0x0003;
const int TYPEINFO	= 0x0004;
const int TYPEWARN	= 0X0005;
const long long int MAX_FILE_SIZE = (1024 * 1024 * 5); // 5M

class writelog
{
public:
	writelog();
	~writelog();

	void Run(const char* buffer);
	void Info(const char* buffer);
	void Debug(const char* buffer);
	void Warn(const char* buffer);
	void Error(const char* buffer);
	void NetworkPackage(const char* buffer);

private:
	string getFileName(int type);
	string makeFileDate(const string &filename);
	void write(const string &filename, const char* buffer, int type);
	void write(const string &filename, const char* buffer, FILE *&pFile);

private:
	string m_fileName;
	FILE *m_pRunFile;
	FILE *m_pErrFile;
	FILE *m_pDebugFile;
	FILE *m_pInfoFile;
	FILE *m_pWarnFile;

};

