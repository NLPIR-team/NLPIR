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
	if (!KS_Init(argv[2], atoi(argv[3])))
	{//Init Failed!
		printf("KS_Init Failed! Reason is %s\n", KS_GetLastErrorMsg());
		return -1;
	}
	int nCount = 0;
	int nThreadCount = 10;
	const char *pResult = 0;
	bool nOverwrite = true;
	int  nEncript = true;
	float fThreshold;
	switch (argv[1][0])
	{
	case 'i':
	case 'I'://i D:\NLPIR 1 D:\NLPIR\Data\KeyScanner\dict/keylistUTF8.txt
			// i D:\NLPIR\LJKeyScannerInstall 1 D:\NLPIR\LJKeyScannerInstall\dict\keylist.txt
		if (argc>5)
		{
			if (argv[5][0] == 'f' ||argv[5][0] == 'F' || argv[5][0] == '0')
			{
				nOverwrite = false;
			}
		}
		nCount = KS_ImportUserDict(argv[4], nOverwrite);
		printf("Successfully imported %d entries.\n",nCount);
		break;
	case 'l':
	case 'L'://l D:\NLPIR 0 D:\NLPIR\LJKeyScannerInstall\baidu\test.txt  D:\NLPIR\LJKeyScannerInstall\baidu\testResult.txt  D:\NLPIR\LJKeyScannerInstall\baidu\BaiduStatResult.xls 
		nCount = KS_ScanLine(argv[4],argv[5]);
		KS_ScanStat(argv[6]);
		printf("Successfully Scan %d entries.\n",nCount);
		break;
	case 'e':
	case 'E'://e D:\NLPIR\LJKeyScannerInstall 1 D:\NLPIR\LJKeyScannerInstall\output D:\NLPIR\LJKeyScannerInstall\result
		
		nCount = KS_Decrypt(argv[4], argv[5]);
		printf("Successfully Scan %d entries.\n", nCount);
		break;
	case 'p':
	case 'P':
		//p D:\NLPIR 0 D:\LJParser\LJParser_release\NLPIR_Packet\演示语料 D:\LJParser\LJParser_release\NLPIR_Packet\result 9
		//p D:\NLPIR\LJKeyScannerInstall 1 D:\NLPIR\LJKeyScannerInstall\test D:\NLPIR\LJKeyScannerInstall\output 9 t
		//p D:\NLPIR\LJKeyScannerInstall 0 D:\LJParser\LJParser_release\NLPIR_Packet\演示语料 D:\NLPIR\LJKeyScannerInstall\output 9 f
		if (argc>6)
		{
			nThreadCount = atoi(argv[6]);
		}
		nEncript = 0;
		if (argc>7)
		{
			if (argv[7][0] == 't' ||argv[7][0] == 'T' || argv[7][0] == '1')
			{
				nEncript = 1;
			}
		}
		if (nThreadCount == 0)
		{
			nThreadCount = 10;
		}
		nCount = KS_ScanDir(argv[4], argv[5], nThreadCount,nEncript);
		printf("Successfully Scan %d entries.\n", nCount);
		break;
	case 'd':
	case 'D'://d D:\NLPIR\Data\KeyScanner\ 1 D:\NLPIR\Data\KeyScanner\dict/deletekeyUTF8.txt
		nCount = KS_DeleteUserDict(argv[4]);
		printf("Successfully deleted %d entries.\n",nCount);
		break;
	case 's':
	case 'S'://s  D:\NLPIR\LJKeyScannerInstall 1 D:\NLPIR\LJKeyScannerInstall\output\KeyStat.xls D:\NLPIR\LJKeyScannerInstall\output\KeyStatFilter.xls  5.0
		fThreshold = 5.0;
		if (argc>6)
		{
			fThreshold = atof(argv[6]);
		}
		nCount = KS_StatResultFilter(argv[4], argv[5], fThreshold);
		printf("KS_StatResultFilter result has been saved to %s.\n", argv[5]);
		break;
	case 'r':
	case 'R'://r  D:\NLPIR\LJKeyScannerInstall 1 D:\NLPIR\LJKeyScannerInstall\output\Result.xls D:\NLPIR\LJKeyScannerInstall\output\ResultFilter.xls  9.0
		fThreshold = 9.0;
		if (argc>6)
		{
			fThreshold = atof(argv[6]);
		}
		nCount = KS_ScanResultFilter(argv[4], argv[5], fThreshold);
		printf("KS_StatResultFilter result has been saved to %s.\n", argv[5]);
		break;
	default:
		//t D:\NLPIR\Data\KeyScanner\ 0 D:\NLPIR\Data\KeyScanner\dict/sample.TXT
		//t D:\NLPIR\Data\KeyScanner\ 1 D:\NLPIR\Data\KeyScanner\dict/sampleUTF8.TXT
		pResult = KS_ScanDetail("孙中山东习近平");
		printf("KS_ScanDetail Result=%s\n", pResult);
		pResult = KS_ScanDetail("毛泽东");
		printf("KS_ScanDetail Result=%s\n", pResult);

		pResult = KS_ScanFile(argv[4]);
		printf("KS_ScanFile Result=%s\n", pResult);
		FILE *fp = fopen("debug.txt", "wb");
		fprintf(fp, "%s\n", pResult);

		pResult = KS_ScanFileDetail(argv[4]);
		printf("KS_ScanFileDetail Result=%s\n", pResult);
		fprintf(fp, "%s\n", pResult);
		fclose(fp);
		break;
	}
	KS_Exit();//Delete and Release
	system("pause");
	return 0;
}

