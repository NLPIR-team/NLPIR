#ifdef _WIN64
#pragma comment(lib, "../lib/win64/DocExtractor.lib")
#else
#pragma comment(lib, "../lib/win32/DocExtractor.lib")
#endif

#include <cstdio>
#include <string>
#include <vector>
#include "DocExtractor.h"

using namespace std;

int main(void)
{

	if (DE_Init("../", 0, "") == 0)
	{
		printf("��ʼ��ʧ��");
		printf("�����������...");
		getchar();
		return 0;
	}

	string content = "<td width=\"92%\"><font color=\"red\">�»���</font>�찲�Ź㳡10��1�յ磨�������ΰ����������½������ɵ������ڡ�ս�����������İ��������У�����ͻ�������ӹ���������װ��05ʽ...</td>";

	printf("����Ϊ��\n%s\n", content.c_str());

	int score = DE_ComputeSentimentDoc(content.c_str());
	printf("--->score--->%d\n", score);
	DOC_PARSER_HANDLE handle = DE_ParseDocE(content.c_str(), "mgc#ngd", true, ALL_REQUIRED);

	printf("��ȡ������Ϊ-->%s\n", DE_GetResult(handle, 0));
	printf("��ȡ�ĵ���Ϊ-->%s\n", DE_GetResult(handle, 1));
	printf("��ȡ�Ļ�����Ϊ-->%s\n", DE_GetResult(handle, 2));
	printf("��ȡ�Ĺؼ���Ϊ-->%s\n", DE_GetResult(handle, 3));
	printf("��ȡ����������Ϊ-->%s\n", DE_GetResult(handle, 4));
	printf("��ȡ��ý��Ϊ-->%s\n", DE_GetResult(handle, 5));
	printf("��ȡ�����¶�Ӧ�����ڹ���Ϊ-->%s\n", DE_GetResult(handle, 6));
	printf("��ȡ�����¶�Ӧ������ʡ��Ϊ-->%s\n", DE_GetResult(handle, 7));
	printf("��ȡ������ժҪΪ-->%s\n", DE_GetResult(handle, 8));
	printf("������µ�������д�Ϊ-->%s\n", DE_GetResult(handle, 9));
	printf("������µĸ�����д�-->%s\n", DE_GetResult(handle, 10));
	printf("�������ȥ����ҳ�ȱ�ǩ�������-->%s\n", DE_GetResult(handle, 11));

	// printf("ȥ���ո�:" + Regex.Replace(docExtractor.DE_GetResult(handle, 11), "[��*| *| *|//s*]*", ""));

	printf("�Զ����(mgc)-->%s\n", DE_GetResult(handle, 12));
	printf("���ֵ---->%d\n", DE_GetSentimentScore(handle));
	DE_ReleaseHandle(handle);


	DE_Exit();

	printf("����");
	printf("�����������...");
	getchar();

	return 0;
}