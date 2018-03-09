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
		printf("��ʼ��ʧ�ܣ�%s\n" ,CLUS_GetLastErrMsg());
		printf("�����������...");
		getchar();
		return 0;
	}



	/**
	* �����ı����ݾ���
	*/
	CLUS_SetParameter(10, 20);
	string content = "�ܹ��־������գ���çǫ����ʿʱ����ʹ�����������һ����α��˭֪��";
	ostringstream ss;
	for (int i = 0; i < 7; ++i)
	{
		ss.str("");
		ss << "����" << i;
		CLUS_AddContent(content.c_str(), ss.str().c_str());
	}
	// ��ӡ���
	if (CLUS_GetLatestResult("../ClusterResultByContent.xml"))
	{
		printf("���ݡ����ݡ��������Ѿ����浽�ļ����뵽��Ŀ��Ŀ¼�²鿴\n");
	}

	CLUS_Exit();

	printf("����\n");
	printf("�����������...\n");
	getchar();

	return 0;
}