// KeySample.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include <stdio.h>
#include "KeyExtract.h"
int main(int argc, const char * argv[])
{

	if(!KeyExtract_Init("D:\\NLPIR",GBK_CODE,""))//��������һ��Ŀ¼�£�Ĭ��ΪGBK����ķִ�
	{
		printf("ICTCLAS INIT FAILED!\n");
		return 1;
	}
	const char *pKeys=KeyExtract_GetKeyWords("ȥ�꿪ʼ���򿪰ٶ�����ɣ����������Ӵ�ຬ�С���˿�����֣�һ�����Ѳ����������ʲô��˼��������������Ϊʲô����ô��Ȼ�����°��꿪ʼ������˿���Ѿ���������������䣬������˵��˿������������˿��",50,true);
	//���ı��з����ؼ���
	printf("Keywords are:\n%s\n",pKeys);
	pKeys=KeyExtract_GetFileKeyWords("D:\\NLPIR\\test\\ʮ�˴󱨸�.txt",50,true);
	//���ı��ļ��з����ؼ���
	printf("Keywords are:\n%s\n",pKeys);
	KeyExtract_Exit();
	return 0;
}

