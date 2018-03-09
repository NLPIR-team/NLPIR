#include "SplitSentence.h"
#include "../Utility/ReadFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef OS_LINUX
#ifndef WIN64
#pragma comment(lib, "../../../bin/SplitSentence/SplitSentence.lib")
#else
#pragma comment(lib, "../../../bin/SplitSentence/x64/SplitSentence.lib")
#endif
#endif
int main(int argc, char*argv[])
{
	if (!SS_Init("D:/NLPIR/"))//
	{
		printf("Init Failed. Reason is %s\n", SS_GetLastErrorMsg());
		return 1;
	}
	char *pText = 0;
	size_t nSize = ReadFile("D:/NLPIR/Test/test.TXT", &pText);
	if (nSize==0)
	{
		printf("Read file D:/NLPIR/Test/test.TXT Failed. \n");
		return 2;
	}
	int i = 1;
	int encode = GBK_CODE;
	const char *pSentence = SS_GetSentence(pText, encode);//设置输入的文本，以及编码，默认为ANSI/GBK
	while (pSentence != 0 && pSentence[0] != 0)//为空字符串，则表示句子已经分析完毕
	{
		printf("No. %d Sentence: %s\n", i++, pSentence);
		pSentence = SS_GetSentence();//剩下的句子，不需要输入参数
	}
	delete [] pText;


	nSize = ReadFile("D:/NLPIR/Test/testUTF8.TXT", &pText);
	if (nSize == 0)
	{
		printf("Read file D:/NLPIR/Test/test.TXT Failed. \n");
		return 2;
	}
	i = 1;
	encode = UTF8_CODE;
	pSentence = SS_GetSentence(pText, encode);//设置输入的文本，以及编码，默认为ANSI/GBK
	while (pSentence!=0&&pSentence[0] != 0)
	{
		printf("No. %d Sentence: %s\n", i++, pSentence);
		pSentence = SS_GetSentence();//第二句
	}
	delete[] pText;

	SS_Exit();
	return 0;
}