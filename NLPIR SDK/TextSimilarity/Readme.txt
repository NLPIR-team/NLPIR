				          Readme
文本相似度计算系统，支持多类编码，支持文本文件与内存文本计算，支持三种模型：字模型、词模型、语义主题模型
具体事例如下：

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

采用test提供的a.txt与b.txt输出结果应该为：
Using Char model, Sim between file a.txt and file b.txt is 0.24
Using Word model, Sim between file a.txt and file b.txt is 0.20
Using Keyword model, Sim between file a.txt and file b.txt is 0.77


联系方式
	张华平 博士 副教授
北京理工大学大数据搜索与挖掘实验室 主任
地址：北京海淀区中关村南大街5号 100081
电话：+86-10-68918642
Email:kevinzhang@bit.edu.cn
MSN:  pipy_zhang@msn.com;
官网: http://ictclas.nlpir.org (NLPIR/ICTCLAS官网)
微博:http://www.weibo.com/drkevinzhang/
 
Dr. Kevin Zhang  (张华平，Zhang Hua-Ping)
Associate Professor, Graduate Supervisor
Director, Big Data Search and Mining Lab.
Beijing Institute of Technology 
Add: No.5, South St.,Zhongguancun,Haidian District,Beijing,P.R.C  PC:100081
Tel: +86-10-68918642
Email:kevinzhang@bit.edu.cn
MSN:  pipy_zhang@msn.com;
Website: http://ictclas.nlpir.org (NLPIR/ICTCLAS Official Website)
Microblog: http://www.weibo.com/drkevinzhang/