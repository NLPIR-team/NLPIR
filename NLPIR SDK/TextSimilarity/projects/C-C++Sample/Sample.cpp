// Sample.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include "TextSimilarity.h"

#ifndef OS_LINUX
#ifndef WIN64
#pragma comment(lib, "../../../bin/TextSimilarity/TextSimilarity.lib")
#else
#pragma comment(lib, "../../../bin/TextSimilarity/x64/TextSimilarity.lib")
#endif
#endif

int main()
{

	if (!TS_Init("D:\\NLPIR", UTF8_CODE))//数据在上一层目录下，设置为UTF8编码，默认为GBK编码的分词
	{
		printf("KS  INIT FAILED!\n");
		return 1;
	}
	char sFiles[2][100] = { "a.txt", "b.txt" };
	double dSim = TS_ComputeSimFile(sFiles[0], sFiles[1], SIM_MODEL_CHAR);
	//采用字符相似度模型，优点速度快，缺点是语义不足，比较两个文件相似度，如果是内存比较，则直接调用TS_ComputeSim即可
	printf("Using Char model, Sim between file %s and file %s is %.2lf\n", sFiles[0],sFiles[1],dSim);

	dSim = TS_ComputeSimFile(sFiles[0], sFiles[1], SIM_MODEL_WORD);
	printf("Using Word model, Sim between file %s and file %s is %.2lf\n", sFiles[0], sFiles[1], dSim);
	//采用词相似度模型，介于字与语义之间，比较两个文件相似度，如果是内存比较，则直接调用TS_ComputeSim即可

	dSim = TS_ComputeSimFile(sFiles[0], sFiles[1], SIM_MODEL_KEY);
	printf("Using Keyword model, Sim between file %s and file %s is %.2lf\n", sFiles[0], sFiles[1], dSim);
	//采用主题相似度模型，优点是语义考虑较多，效果好，缺点是速度慢。比较两个文件相似度，如果是内存比较，则直接调用TS_ComputeSim即可

	TS_Exit();
	//不使用了，全局需要退出
	return 0;
}

