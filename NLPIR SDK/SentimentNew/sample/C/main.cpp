#include <cstdio>
#include <string>
#include <fstream>

#include "Sentiment.h"
#ifdef WIN64
#pragma comment(lib, "..\\..\\..\\bin\\SentimentNew\\x64\\SentimentNew.lib")
#elif WIN32 
#pragma comment(lib, "..\\..\\..\\bin\\SentimentNew\\SentimentNew.lib")
#endif
const std::string path = "D:\\NLPIR\\bin\\SentimentNew\\";

int main(int argc, char *argv[])
{
	int flag = ST_Init(path.c_str(), 0, "");
	if (flag == 0)
	{
		printf("初始化失败\n");
		getchar();
		return 0;
	}

	const std::string destDict3 = path + "test/dict/negation.txt";
	const std::string destDict4 = path + "test/dict/transition.txt";
	const std::string destDict5 = path + "test/dict/sentilexicon.txt";
	/*
	int i = 0;

	// 	i += ST_AddWordFromTxt(destDict1.c_str());
	// 	i += ST_AddWordFromTxt(destDict2.c_str());
	i += ST_ImportUserDict(destDict3.c_str(), 1);
	i += ST_ImportUserDict(destDict4.c_str(), 1);
	i += ST_ImportUserDict(destDict5.c_str(), 1);
	printf("共导入单词数：%d\n\n", i);
	*/

//	const std::string sTitle = "范冰冰很豪爽";
//	const std::string sContent = "范冰冰很漂亮，而且更好爽。郭德纲嘴太毒了。";
	const std::string sObject = "郭德纲";
	const std::string sTitle = "郭德纲需反思：观众如水，能载舟亦能覆舟";
	const std::string sContent = "据《法制晚报》报道，警方已经证实1月9号在首都国际机场打人的均是德云社员工，且德云社三名员工因打人被警方处以行政拘留并罚款。目前德云社已申请行政复议，而郭德纲与“打人”字眼再次引起人们的热议。\n\
		　　    德云社为什么会频频出现打人事件，这是一个让我们很难理解的事情。在舞台上，郭德纲把自己的身段放的那么低，与观众是那样的亲，为什么一到舞台下面就似乎完全是换了一个人呢?\n\
		  　　  郭德纲不在体制内，按他的话说自己就是一个“非著名相声演员”，而那些在体质内的则统一被他戏称为“主流的”，而且在一切场合尽自己的最大的可能来讽刺和挖苦这些所谓的“主流”相声演员。郭德纲成名，靠的不是哪个政府部门，靠的是自己坚持不懈的努力，靠的是观众们的力捧，靠的是电视台网络的大力宣传。所以，他在唱经典段子《大实话》的时候会一直唱“要说亲，观众们亲，观众演员心连着心!”";

	printf("【标题】：%s\n【正文】：%s\n", sTitle.c_str(), sContent.c_str());


/*
	const std::string filePath = path + "/test/gbk.txt";
	std::ifstream ifs(filePath, std::ios::binary | std::ios::in); // 创建个文件流对象
	std::string sTitle;
	std::string sContent;
	getline(ifs, sTitle);
	getline(ifs, sContent);
	ifs.close();
*/

	const char *result = ST_GetOneObjectResult(sTitle.c_str(), sContent.c_str(), sObject.c_str());
	printf("%s\n\n", result);


	const std::string sConfig = path + "test/gbkconfig.xml";
	result = ST_GetMultiObjectResult(sTitle.c_str(), sContent.c_str(), sConfig.c_str());
	printf("%s\n\n", result);

	result = ST_GetSentencePoint(sContent.c_str());
 	printf("%s\n\n", result);
	/*
	const std::string sFilePath = path + "result.xml";
	std::ofstream ofs(sFilePath, std::ios::binary | std::ios::out);
	ofs << result;
	ofs.close();
	*/
	getchar();

	ST_Exit();

	return 0;
}