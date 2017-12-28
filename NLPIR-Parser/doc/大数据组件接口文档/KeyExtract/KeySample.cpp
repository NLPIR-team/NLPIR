// KeySample.cpp : 定义控制台应用程序的入口点。
//
#include <stdio.h>
#include "KeyExtract.h"
int main(int argc, const char * argv[])
{

	if(!KeyExtract_Init("D:\\NLPIR",GBK_CODE,""))//数据在上一层目录下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return 1;
	}
	const char *pKeys=KeyExtract_GetKeyWords("去年开始，打开百度李毅吧，满屏的帖子大多含有“屌丝”二字，一般网友不仅不懂这词什么意思，更难理解这个词为什么会这么火。然而从下半年开始，“屌丝”已经覆盖网络各个角落，人人争说屌丝，人人争当屌丝。",50,true);
	//从文本中分析关键词
	printf("Keywords are:\n%s\n",pKeys);
	pKeys=KeyExtract_GetFileKeyWords("D:\\NLPIR\\test\\十八大报告.txt",50,true);
	//从文本文件中分析关键词
	printf("Keywords are:\n%s\n",pKeys);
	KeyExtract_Exit();
	return 0;
}

