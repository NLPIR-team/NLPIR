
#include "iEncoder.h"
#include <stdio.h>

#ifndef OS_LINUX
#ifndef WIN64
#pragma comment(lib, "../../../bin/iEncoder/iEncoder.lib")
#else
#pragma comment(lib, "../../../bin/iEncoder/x64/iEncoder.lib")
#endif
#endif
int main(int argc, char *argv[])
{// [dataPath] [input_file] [outputfile] [encode=1:UTF8; encode=2:GBK;8:Unicode]
	//参数候选
 // D:\NLPIR D:\NLPIR\test\gbk\sample.txt  D:\NLPIR\test\gbk\sample-utf.txt 1
 // D:\NLPIR D:\NLPIR\test\gbk\sample.txt  D:\NLPIR\test\gbk\sample-utf.txt 0
 // D:\NLPIR D:\NLPIR\test\utf8\testUTF8.txt  D:\NLPIR\test\utf8\testUTF8-GBK.txt 2
 // D:\NLPIR D:\NLPIR\test\utf8\testUTF8.txt  D:\NLPIR\test\utf8\testUTF8-GBK.txt 1
	if (argc<4)
	{
		printf("Usage: %s [dataPath] [input_file] [outputfile] [encode=1:UTF8; encode=2:GBK;8:Unicode]\n",argv[0]);
		return -1;
	}
	if (IE_Init(argv[1]) != 1)//初始化，加载授权和数据文件
	{//初始化失败
		printf("IE_Init Init from %s failed. Reseason: %s\n", argv[1],IE_GetLastErrorMsg());
		IE_Exit();
		return -2;
	}
	printf("IE_Init Init from %s Sucss!\n", argv[1]);
	int encode=1;
	if (argc>4)
	{
		sscanf(argv[4], "%d", &encode);
	}
	size_t nRtn=1;
	switch (encode)
	{
	case IE_UTF8_CODE:
		nRtn=IE_ToUtf8File(argv[2], argv[3]);
		break;
	case IE_GBK_CODE:
		nRtn=IE_ToGBKFile(argv[2], argv[3]);
		break;
	case IE_UNICODE_CODE:
		nRtn=IE_ToUnicodeFile(argv[2], argv[3]);
		break;
	default:
		break;
	}
	if (nRtn!=(size_t)-1)
	{
		printf("%s convert encoding to %s successfully!\n", argv[2], argv[3]);
	}
	else
	{
		printf("%s convert encoding to %s failed! Reason is %s\n", argv[2], argv[3],IE_GetLastErrorMsg());
	}
	IE_Exit();
	return 1;
}