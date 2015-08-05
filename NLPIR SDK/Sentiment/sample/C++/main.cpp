#ifdef _WIN64
#pragma comment(lib, "../lib/win64/LJSentiment.lib")
#else
#pragma comment(lib, "../lib/win32/LJSentiment.lib")
#endif

#include <cstdio>
#include <string>
#include "LJSentiment.h"

using namespace std;

const string rootDir = "../";

int main(void)
{
	if (!ST_Init(rootDir.c_str(), 0, ""))
	{
		printf("初始化失败");
		printf("按任意键继续...");
		getchar();
		return 0;
	}

	/**
	* 测试导出情感词典
	*/
	if (ST_SentiDictIO((rootDir + "test/positive.txt").c_str(), (rootDir + "test/negative.txt").c_str(), false) == 1)
	{
		printf("词典导出成功，请到对应的目录查找");
	}
	else
	{
		printf("词典导出失败");
	}

	/**
	* 测试导入情感词典
	*/
	if (ST_SentiDictIO((rootDir + "test/pos.txt").c_str(), (rootDir + "test/neg.txt").c_str(), true) == 1)
	{
		printf("恭喜，词典导入成功");
	}
	else
	{
		printf("词典导入失败");
	}

	printf("=====================================================================================");
	string sTitle = "郭德纲需反思：观众如水，能载舟亦能覆舟";
	string sContent = "据《法制晚报》报道，警方已经证实1月9号在首都国际机场打人的均是德云社员工，且德云社三名员工因打人被警方处以行政拘留并罚款。目前德云社已申请行政复议，而郭德纲与“打人”字眼再次引起人们的热议。\n德云社为什么会频频出现打人事件，这是一个让我们很难理解的事情。在舞台上，郭德纲把自己的身段放的那么低，与观众是那样的亲，为什么一到舞台下面就似乎完全是换了一个人呢?\n郭德纲不在体制内，按他的话说自己就是一个“非著名相声演员”，而那些在体质内的则统一被他戏称为“主流的”，而且在一切场合尽自己的最大的可能来讽刺和挖苦这些所谓的“主流”相声演员。郭德纲成名，靠的不是哪个政府部门，靠的是自己坚持不懈的努力，靠的是观众们的力捧，靠的是电视台网络的大力宣传。所以，他在唱经典段子《大实话》的时候会一直唱“要说亲，观众们亲，观众演员心连着心!”";

	printf("标题为：\n%s\n", sTitle.c_str());
	printf("内容为：\n%s\n", sContent.c_str());

	printf(ST_GetOneObjectResult(sTitle.c_str(), sContent.c_str(), "郭德纲"));
	printf(ST_GetMultiObjectResult(sTitle.c_str(), sContent.c_str(), "stConduct.xml"));


	ST_Exit();

	printf("结束");
	printf("按任意键继续...");
	getchar();
	return 0;
}