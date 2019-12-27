// Sample.cpp : 定义控制台应用程序的入口点。
//
#include "DocParser.h"
#include <stdio.h>
#ifndef OS_LINUX

#ifndef WIN64
#pragma comment(lib, "../../../bin/DocParser/DocParser.lib")
#else
#pragma comment(lib, "../../../bin/DocParser/x64/DocParser.lib")
#endif
#endif

int main(int argc,char *argv[])
{
	if (!DP_Init())
	{
		printf("DocParser Init failed! Reason is %s\n",DP_GetLastErrorMsg());
		return -1;
	}
	if (argc<2)
	{
		printf("Usage: %s [filename_list]",argv[0]);
	}
	for (int i = 1; i < argc; i++)
	{
		DP_HANDLE handle;
		handle=DP_Parse(argv[i]);
		const char *pText = DP_GetText(handle);
		const char *pTextE = DP_GetTextE(handle);
		const char *pTable = DP_GetTables(handle);
		const char *pFigures = DP_GetFigures(handle);
		DP_ReleaseHandle(handle);
	}
    return 0;
}

