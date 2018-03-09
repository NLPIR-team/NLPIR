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
		printf("��ʼ��ʧ��\n");
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
	printf("�����뵥������%d\n\n", i);
	*/

//	const std::string sTitle = "�������ܺ�ˬ";
//	const std::string sContent = "��������Ư�������Ҹ���ˬ�����¸���̫���ˡ�";
	const std::string sObject = "���¸�";
	const std::string sTitle = "���¸��跴˼��������ˮ�����������ܸ���";
	const std::string sContent = "�ݡ��������������������Ѿ�֤ʵ1��9�����׶����ʻ������˵ľ��ǵ�����Ա�����ҵ���������Ա������˱����������������������Ŀǰ�������������������飬�����¸��롰���ˡ������ٴ��������ǵ����顣\n\
		����    ������Ϊʲô��ƵƵ���ִ����¼�������һ�������Ǻ����������顣����̨�ϣ����¸ٰ��Լ�����ηŵ���ô�ͣ���������������ף�Ϊʲôһ����̨������ƺ���ȫ�ǻ���һ������?\n\
		  ����  ���¸ٲ��������ڣ������Ļ�˵�Լ�����һ����������������Ա��������Щ�������ڵ���ͳһ����Ϸ��Ϊ�������ġ���������һ�г��Ͼ��Լ������Ŀ�������̺��ڿ���Щ��ν�ġ�������������Ա�����¸ٳ��������Ĳ����ĸ��������ţ��������Լ���ֲ�и��Ŭ���������ǹ����ǵ������������ǵ���̨����Ĵ������������ԣ����ڳ�������ӡ���ʵ������ʱ���һֱ����Ҫ˵�ף��������ף�������Ա��������!��";

	printf("�����⡿��%s\n�����ġ���%s\n", sTitle.c_str(), sContent.c_str());


/*
	const std::string filePath = path + "/test/gbk.txt";
	std::ifstream ifs(filePath, std::ios::binary | std::ios::in); // �������ļ�������
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