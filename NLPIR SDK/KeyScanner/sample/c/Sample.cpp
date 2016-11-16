// Sample.cpp : 定义控制台应用程序的入口点。
//

#include "KeyScanAPI.h"
#ifndef OS_LINUX
#ifndef WIN64
#pragma comment(lib, "../../../bin/KeyScanner/KeyScanAPI.lib")
#else
#pragma comment(lib, "../../../bin/KeyScanner/x64/KeyScanAPI.lib")
#endif
#endif
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	//Usage
	if (argc<5)
	{
		printf("Usage1-import User Dictionary: %s i <dict_path> <encoding:0-GBK,1-UTF8,2-BIG5,3-GBK+Fanti> <dictioanry_text_file>\n",argv[0]);
		printf("Usage1-Testing: %s t <dict_path> <encoding:0-GBK,1-UTF8,2-BIG5,3-GBK+Fanti> <testing_text_file>\n",argv[0]);
		return -2;
	}
	//"D:/NLPIR/Data/KeyScanner/" "D:/NLPIR/Data/KeyScanner/Dict/KeyList.txt"
	//"D:/NLPIR/Data/KeyScanner/Dict/Sample.txt"
	//t D:/NLPIR/Data/KeyScanner/ 3  D:/NLPIR/Data/KeyScanner/Dict/Sample.txt
	if (!KS_Init(argv[2], atoi(argv[3])))
	{//Init Failed!
		printf("KS_Init Failed! Reason is %s\n", KS_GetLastErrorMsg());
		return -1;
	}
	int nCount = 0;
	const char *pResult = 0;
	switch (argv[1][0])
	{
	case 'i':
	case 'I':
		nCount = KS_ImportUserDict(argv[4]);
		printf("Successfully imported %d entries.\n",nCount);
	default:
		pResult = KS_ScanFile(argv[4]);
		printf("KS_ScanFile Result=%s\n", pResult);
		pResult = KS_ScanFileDetail(argv[4]);
		printf("KS_ScanFileDetail Result=%s\n", pResult);
		break;
	}
	/*//词典的加载过程程序，已经测试通过
	KS_Exit();//Delete and Release
	return 0;
	*/
	KS_Exit();//Delete and Release
	return 0;
}

