#ifdef _WIN32
#ifdef _WIN64
#pragma comment(lib, "../lib/win64/NLPIR.lib")
#else
#pragma comment(lib, "../lib/win32/NLPIR.lib")
#endif
#endif

#include <cstdio>
#include <string>
#include "../include/NLPIR.h"

using namespace std;

const string DataPath = "..\\";

int main(void)
{
	if (NLPIR_Init(DataPath.c_str(), 0, ""))
	{
		printf("初始化成功");
		printf("\n\n");
	}
	else
	{
		printf("初始化失败\n");
		printf("按任意键退出...\n");
		getchar();
		return 0;
	}

	string sSrc = "\n坐标原点，全球旅行必备话中蒙友好合作，谈中国周边外交，论亚洲国家相处之道，强调互尊互信、聚同化异、守望相助、合作共赢，共创中蒙关系发展新时代，共促亚洲稳定繁荣";

	printf("原文: \n%s", sSrc.c_str());
	printf("\n");

	// 分词测试
	string cutWord = NLPIR_ParagraphProcess(sSrc.c_str(), 1);
	printf("\n");
	printf("分词结果：%s", cutWord.c_str());
	printf("\n\n");
	
	int count = 0;
	const result_t * result = NLPIR_ParagraphProcessA(sSrc.c_str(), &count);
	for (size_t i = 0; i < count; i++)
	{
		printf("%d %d %s %d %d %d %d\n", result[i].start, result[i].length, result[i].sPOS, 
			result[i].iPOS, result[i].word_ID, result[i].word_type, result[i].weight);
	}

	// 获取新词测试
	string newWord = NLPIR_GetNewWords(sSrc.c_str(), 10, false);
	printf("获取新词：%s", newWord.c_str());
	printf("\n\n");

	// 词频统计
	string wordFreq = NLPIR_WordFreqStat(sSrc.c_str());
	printf("词频结果如下：%s", wordFreq.c_str());
	printf("\n\n");

	// 关键词
	string keyWords = NLPIR_GetKeyWords(sSrc.c_str(), 10, true);
	printf("关键词：%s", keyWords.c_str());
	printf("\n\n");

	// 添加用户词典测试
	int addDictNum = NLPIR_ImportUserDict("./test/dict.txt", true);
	printf("导入用户词典单词个数：%d", addDictNum);
	printf("\n\n");

	// 删除单词测试
	string sDelWord = "中蒙";
	NLPIR_DelUsrWord(sDelWord.c_str());
	printf("该词已经被删除：%s", sDelWord.c_str());
	printf("\n\n");

	getchar();
}