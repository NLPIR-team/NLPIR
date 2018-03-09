#ifdef _WIN64
#pragma comment(lib, "../lib/win64/LJClassifier.lib")
#else
#pragma comment(lib, "../lib/win32/LJClassifier.lib")
#endif

#include <cstdio>
#include <string>
#include "LJClassifier.h"

using namespace std;

int main(void)
{

	if (!classifier_init("../data/rulelist.xml", "../data/DataFile"))
	{
		printf("初始化失败");
		printf("按任意键继续...");
		getchar();
		return 0;
	}

	printf("分类开始：");

	string title = "天翼定制手机天语E600";
	string content = "全球旅行必备:天翼定制手机天语E600 新浪 2011-9-26 15:53手机——这项人们使用率最高的电子产品,其更新换代速度更是快得无法想象。那么对于我们消费者而言,应当如何选择呢? 显然,频繁的换机是非常不划算的,更会增加生活开支,平白增添生活负担。因此,我们在购机之初就应当选择一款满足自身需求的手机。...";

	printf("文本内容：\n%s\n", content.c_str());

	string sResult = classifier_exec(title.c_str(), content.c_str(), 0);


	printf("过滤结果：\n%s\n", sResult.c_str());

	string results = classifier_detail(sResult.c_str());
	printf("过滤结果：\n%s\n", results.c_str());

	classifier_exit();

	printf("分类结束");
	printf("按任意键继续...");
	getchar();

	return 0;
}