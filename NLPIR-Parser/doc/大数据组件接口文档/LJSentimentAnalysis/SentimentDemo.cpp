#include "LJSentimentAnalysis.h"
#include <vector>
#include <list>
#include <fstream>
using namespace std;
#ifndef OS_LINUX
#pragma comment(lib,"LJSentimentAnalysis.lib")
#endif



int main(int argc, char* argv[])
{

	//��ʼ��
	int values = LJST_Inits("",GBK_CODE);
	if(!values)
	{
		printf("��ʼ��ʧ�ܣ�\n");
		return -1;
	}

	char szRes[40] = {0};
	bool bResult= LJST_GetFileSent("./Input/test.txt", szRes);
	if(!bResult)
	{
		printf("get feel info failed!\n");
		return -1;
	}
	printf("��ƪ���µ����������: %s\n", szRes);

	LJST_Exits();
	system("pause");
	return 0;
}

