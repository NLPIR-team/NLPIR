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
		printf("��ʼ��ʧ��");
		printf("�����������...");
		getchar();
		return 0;
	}


	/**
	* �������ݻ����з���
	*/
	// sentimentAnalysis.LJST_ImportUserDict(sentimentAnalysis.RootDir + "test.txt", true);//����ʵ�
	char *result = new char[1024];//�������
	memset(result, 0, sizeof(char) * 1024);
	string content = "�����7��֮��ȫ�����BT��վ�������塱�����»������ | Pirate Bay�������壩��ȫ������ BT ���ӷ���������վ��ȥ�� 12 ����Ϊ�⵽��䵱�ֲ��رշ��񳤴� 7 ��ʱ�䡣���պ���������Ϥ��thepiratebay.se���������������У�������վ���÷��ȡ���˺����졣";
	//�������ݻ����з���
	LJST_GetParagraphSent(content.c_str(), result);
	printf("�����ı����ݷ��������\n%s", result);//����������
	delete[] result;

	/**
	* �����ı��ļ������з���
	*/
	//result = new StringBuilder();
	//sentimentAnalysis.LJST_GetFileSent(sentimentAnalysis.RootDir + "content.txt", result);
	// printf("�����ı��ļ����������\n" + result);//����������

	LJST_Exits();

	printf("����");
	printf("�����������...");
	getchar();
	return 0;
}