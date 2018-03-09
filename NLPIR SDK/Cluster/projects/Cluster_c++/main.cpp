#ifdef _WIN64
#pragma comment(lib, "../lib/win64/LJCluster.lib")
#else
#pragma comment(lib, "../lib/win32/LJCluster.lib")
#endif

#include <cstdio>
#include <string>
#include <sstream>
#include "LJCluster.h"

using namespace std;

int main(void)
{

	if (!CLUS_Init("../", "", 0))
	{
		printf("初始化失败：%s\n" ,CLUS_GetLastErrMsg());
		printf("按任意键继续...");
		getchar();
		return 0;
	}



	/**
	* 根据文本内容聚类
	*/
	CLUS_SetParameter(10, 20);
	string content = "周公恐惧流言日，王莽谦恭下士时。假使当年身便死，一生真伪有谁知。";
	ostringstream ss;
	for (int i = 0; i < 7; ++i)
	{
		ss.str("");
		ss << "文章" << i;
		CLUS_AddContent(content.c_str(), ss.str().c_str());
	}
	// 打印结果
	if (CLUS_GetLatestResult("../ClusterResultByContent.xml"))
	{
		printf("根据【内容】聚类结果已经保存到文件，请到项目根目录下查看\n");
	}

	CLUS_Exit();

	printf("结束\n");
	printf("按任意键继续...\n");
	getchar();

	return 0;
}