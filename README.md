# UtilLog
纯C++ log库，参考qDebug实现，比spdlog好用

实现方法：
1、在程序exe目录下手动新建一个log文件夹即可

////////////////////////实现demo///////////////////
#include "UtilLogShell.h"

#pragma comment(lib,"UtilLog.lib")

int main()
{
	LOG_RUN << "1hellow world!";

	LOG_RUN << "2hellow world!";

	LOG_RUN << "3hellow world!";

	system("pause");
	return 0;
}

////////////log文件名////////////////////////
程序名_run_20180117.log

/////////////////////打印效果////////////////
[<2018-01-17 10:21:08.000 test.cpp line: 7 >] 1hellow world! 
[<2018-01-17 10:21:08.000 test.cpp line: 9 >] 2hellow world! 
[<2018-01-17 10:21:08.000 test.cpp line: 11 >] 3hellow world! 
