#include "../API/LJHtmlParser.h"
#include <stdio.h>

#ifndef OS_LINUX
//#pragma comment(lib, "../../../bin/HtmlParser/LJHtmlParser.lib")
#endif
int main(int argc, char *argv[])
{
	if(argc != 3){
		printf("Usage: %s <html_file> <result_file>\n", argv[0]);
		return -1;
	}
	if(!HPR_Init("","LingjoinHtmlParse*~!@#$%&*(^^^)*&%$#@!~*"))
	{
		printf("HPR_Init failed");
		return -1;
	}
	FILE *fp = fopen(argv[2], "wt");
	if(fp == NULL){
		printf("fopen failed: %s\n", argv[2]);
		return -1;
	}

	//CHtmlParser hp;
	HPR_ParseFile(argv[1]);

	//提取标题
	fprintf(fp, "<title>%s</title>\n", HPR_GetTitle());
	
	//提取正文
	fprintf(fp, "<content>%s</content>\n", HPR_GetContent());
		
	fclose(fp);
	HPR_Exit();
	return 0;
}

