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
		printf("��ʼ��ʧ��");
		printf("�����������...");
		getchar();
		return 0;
	}

	printf("���࿪ʼ��");

	string title = "�������ֻ�����E600";
	string content = "ȫ�����бر�:�������ֻ�����E600 ���� 2011-9-26 15:53�ֻ�������������ʹ������ߵĵ��Ӳ�Ʒ,����»����ٶȸ��ǿ���޷�������ô�������������߶���,Ӧ�����ѡ����? ��Ȼ,Ƶ���Ļ����Ƿǳ��������,�����������֧,ƽ����������������,�����ڹ���֮����Ӧ��ѡ��һ����������������ֻ���...";

	printf("�ı����ݣ�\n%s\n", content.c_str());

	string sResult = classifier_exec(title.c_str(), content.c_str(), 0);


	printf("���˽����\n%s\n", sResult.c_str());

	string results = classifier_detail(sResult.c_str());
	printf("���˽����\n%s\n", results.c_str());

	classifier_exit();

	printf("�������");
	printf("�����������...");
	getchar();

	return 0;
}