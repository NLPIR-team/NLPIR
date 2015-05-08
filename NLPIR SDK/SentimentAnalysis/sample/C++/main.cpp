#ifdef _WIN64
#pragma comment(lib, "../lib/win64/LJSentimentAnalysis.lib")
#else
#pragma comment(lib, "../lib/win32/LJSentimentAnalysis.lib")
#endif

#include <cstdio>
#include <string>
#include <vector>
#include <io.h>
#include <fstream>
#include <sstream>
#include "LJSentimentAnalysis.h"

using namespace std;

const string rootDir = "../";

int main(void)
{
	if (LJST_Inits(rootDir.c_str(), 0, "") == 0)
	{
		printf("初始化失败");
		printf("按任意键继续...");
		getchar();
		return 0;
	}


	/**
	* 根据内容获得情感分析
	*/
	// sentimentAnalysis.LJST_ImportUserDict(sentimentAnalysis.RootDir + "test.txt", true);//导入词典
	char *result = new char[1024];//分析结果
	memset(result, 0, sizeof(char) * 1024);
	string content = "被查封7周之后，全球最大BT网站“海盗湾”又重新活过来了 | Pirate Bay（海盗湾）是全球最大的 BT 种子分享下载网站，去年 12 月因为遭到瑞典当局查封关闭服务长达 7 周时间。近日海盗湾以熟悉的thepiratebay.se域名继续上线运行，并在网站上用凤凰取代了海盗旗。";
	//根据内容获得情感分析
	LJST_GetParagraphSent(content.c_str(), result);
	printf("根据文本内容分析结果：\n%s", result);//输出分析结果
	delete[] result;

	/**
	* 根据文本文件获得情感分析
	*/
	//result = new StringBuilder();
	//sentimentAnalysis.LJST_GetFileSent(sentimentAnalysis.RootDir + "content.txt", result);
	// printf("根据文本文件分析结果：\n" + result);//输出分析结果

	LJST_Exits();

	printf("结束");
	printf("按任意键继续...");
	getchar();
	return 0;
}