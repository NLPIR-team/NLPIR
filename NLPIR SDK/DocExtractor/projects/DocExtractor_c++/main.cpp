#ifdef _WIN64
#pragma comment(lib, "../lib/win64/DocExtractor.lib")
#else
#pragma comment(lib, "../lib/win32/DocExtractor.lib")
#endif

#include <cstdio>
#include <string>
#include <vector>
#include "DocExtractor.h"

using namespace std;

int main(void)
{

	if (DE_Init("../", 0, "") == 0)
	{
		printf("初始化失败");
		printf("按任意键继续...");
		getchar();
		return 0;
	}

	string content = "<td width=\"92%\"><font color=\"red\">新华网</font>天安门广场10月1日电（记者李大伟、李宣良）陆军铁骑可蹈海，在《战车进行曲》的昂扬旋律中，两栖突击车方队滚滚而来。装备05式...</td>";

	printf("内容为：\n%s\n", content.c_str());

	int score = DE_ComputeSentimentDoc(content.c_str());
	printf("--->score--->%d\n", score);
	DOC_PARSER_HANDLE handle = DE_ParseDocE(content.c_str(), "mgc#ngd", true, ALL_REQUIRED);

	printf("抽取的人名为-->%s\n", DE_GetResult(handle, 0));
	printf("抽取的地名为-->%s\n", DE_GetResult(handle, 1));
	printf("抽取的机构名为-->%s\n", DE_GetResult(handle, 2));
	printf("抽取的关键词为-->%s\n", DE_GetResult(handle, 3));
	printf("抽取的文章作者为-->%s\n", DE_GetResult(handle, 4));
	printf("抽取的媒体为-->%s\n", DE_GetResult(handle, 5));
	printf("抽取的文章对应的所在国别为-->%s\n", DE_GetResult(handle, 6));
	printf("抽取的文章对应的所在省份为-->%s\n", DE_GetResult(handle, 7));
	printf("抽取的文章摘要为-->%s\n", DE_GetResult(handle, 8));
	printf("输出文章的正面情感词为-->%s\n", DE_GetResult(handle, 9));
	printf("输出文章的副面情感词-->%s\n", DE_GetResult(handle, 10));
	printf("输出文章去除网页等标签后的正文-->%s\n", DE_GetResult(handle, 11));

	// printf("去除空格:" + Regex.Replace(docExtractor.DE_GetResult(handle, 11), "[　*| *| *|//s*]*", ""));

	printf("自定义词(mgc)-->%s\n", DE_GetResult(handle, 12));
	printf("情感值---->%d\n", DE_GetSentimentScore(handle));
	DE_ReleaseHandle(handle);


	DE_Exit();

	printf("结束");
	printf("按任意键继续...");
	getchar();

	return 0;
}