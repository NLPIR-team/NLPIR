// KeySample.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include "KeyExtract.h"

#ifndef OS_LINUX
#ifndef WIN64
#pragma comment(lib, "../../../bin/KeyExtract/KeyExtract.lib")
#else
#pragma comment(lib, "../../../bin/KeyExtract/x64/KeyExtract.lib")
#endif
#endif

int main(int argc, const char * argv[])
{

	if(!KeyExtract_Init("D:\\NLPIR",GBK_CODE,""))//数据在上一层目录下，默认为GBK编码的分词
	{
		printf("KeyExtract  INIT FAILED!\n");
		return 1;
	}
	//int nCount = KeyExtract_ImportKeyBlackList(NULL, "#nr#ns#");
	int nCount;// = KeyExtract_ImportUserDict("keywords.txt");
	const char *pKeys;//=KeyExtract_GetKeyWords("为提高工程建设施工现场设备和工业金属管道焊接工程的施工水平，加强焊接工程施工过程的质量控制。",50,true);
	//从文本中分析关键词
	pKeys = KeyExtract_GetFileKeyWords("d:/nlpir/test/The Farmer in the Dell.txt");
	printf("%s", pKeys);
	
	pKeys = KeyExtract_GetKeyWords("为提高工程建设施工现场设备和工业金属管道焊接工程的施工水平，加强焊接工程施工过程的质量控制。", 50, true);;
	printf("Before ImportUserDict Keywords are:\n%s\n", pKeys);
	const char *pUserDict = "质量控制 key";
	KeyExtract_AddUserWord(pUserDict);
	//nCount = KeyExtract_ImportUserDict("keywords.txt");
	pKeys = KeyExtract_GetKeyWords("为提高工程建设施工现场设备和工业金属管道焊接工程的施工水平，加强焊接工程施工过程的质量控制。", 50, true);;
	printf("After KeyExtract_AddUserWord %s Keywords are:\n%s\n", pUserDict, pKeys);
	//nCount = KeyExtract_ImportUserDict("keywords2.txt");
	pUserDict = "施工过程 key";
	KeyExtract_AddUserWord(pUserDict);
	//nCount = KeyExtract_ImportUserDict("keywords.txt");
	pKeys = KeyExtract_GetKeyWords("为提高工程建设施工现场设备和工业金属管道焊接工程的施工水平，加强焊接工程施工过程的质量控制。", 50, true);;
	printf("After KeyExtract_AddUserWord %s Keywords are:\n%s\n", pUserDict, pKeys);
	
	KeyExtract_Exit();
	return 0;
}

