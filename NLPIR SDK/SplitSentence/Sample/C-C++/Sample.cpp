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
	const char *pSentence = SS_GetSentence(pText, encode);//����������ı����Լ����룬Ĭ��ΪANSI/GBK
	while (pSentence != 0 && pSentence[0] != 0)//Ϊ���ַ��������ʾ�����Ѿ��������
	{
		printf("No. %d Sentence: %s\n", i++, pSentence);
		pSentence = SS_GetSentence();//ʣ�µľ��ӣ�����Ҫ�������
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
	pSentence = SS_GetSentence(pText, encode);//����������ı����Լ����룬Ĭ��ΪANSI/GBK
	while (pSentence!=0&&pSentence[0] != 0)
	{
		printf("No. %d Sentence: %s\n", i++, pSentence);
		pSentence = SS_GetSentence();//�ڶ���
	}
	delete[] pText;

	SS_Exit();
	return 0;
}