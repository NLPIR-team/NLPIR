// win_cDemo.cpp : 定义控制台应用程序的入口点。
//
#include "NewWordFinder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef OS_LINUX
#ifdef NLPIR_STATIC
#pragma comment(lib, "../../../bin/NewWordFinder/NLPIRStatic.lib")
#else

#ifndef WIN64
#pragma comment(lib, "../../../bin/NewWordFinder/NewWordFinder.lib")
#else
#pragma comment(lib, "../../../bin/NewWordFinder/x64/NewWordFinder.lib")
#endif
#endif

#else
#include<pthread.h>
#endif


#include <string>
#include <vector>
#include <list>
#include <deque>
#include <map>
#include <time.h>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef OS_LINUX
#include <io.h>
#include <process.h>
#include <direct.h>
#include <assert.h>
#include <conio.h>
#define makeDirectory _mkdir
#pragma warning(disable:4786)
#define PATH_DELEMETER  "\\"
#define LONG64U __int64
#define DATE_DELEMETER  "/"
//#include <windows.h>
#define SLEEP(x) Sleep(x*1000)
#else
#include <dirent.h>
#include <ctype.h>
#include <unistd.h> 
#include <pthread.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <semaphore.h>
#define makeDirectory(x) mkdir(x, 0777)    // 这步骤必须，否则文件夹只读
//#define stricmp strcasecmp
//#define strnicmp strncasecmp
#define Sleep(x) sleep(x/1000)
#define _stricmp(X,Y) strcasecmp((X),(Y))
#define stricmp(X,Y) strcasecmp((X),(Y))
#define strnicmp(X,Y,Z) strncasecmp((X),(Y),(Z))
#define _fstat(X,Y)     fstat((X),(Y))
#define _fileno(X)     fileno((X))
#define _stat           stat
#define _getcwd         getcwd
#define _off_t          off_t
#define PATH_DELEMETER  "/"
#define DATE_DELEMETER  "/"
#define LONG64U long long
#include <unistd.h>
#define SLEEP(x) sleep(x)
#endif

void testNewWord(int code);
long ReadFile(const char *sFilename,char **pBuffer);

/*********************************************************************
 *
 *  Func Name  : Read(const char *sFilename,char *pBuffer)
 *  Description: 
 *        Read file to a buffer and return the file size
 *              
 *
 *  Parameters : 
 *               sFilename: filename;
 *               pBuffer: buffer
 *
 *  Returns    : _off_t file size
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2003-11-28
 *********************************************************************/
long ReadFile(const char *sFilename,char **pBuffer)
{
	FILE *fp;
    struct _stat buf;
    if((fp=fopen(sFilename,"rb"))==NULL)
	   return 0;//read file false
    int nRet=_fstat( _fileno(fp), &buf );//Get file information
    if(nRet != 0)//File length of the lexicon file
	{
	   return 0;
	}
    *pBuffer = new char[buf.st_size+1];
    //The buffer for file
    if(*pBuffer == 0)
	{
	   return 0;
	}
    fread(*pBuffer, buf.st_size, 1, fp);//Read 
	(*pBuffer)[buf.st_size]=0;
    fclose(fp);
	return buf.st_size;
}


void testNewWord(int nCode)
{
	//初始化分词组件
	if(!NWF_Init("../../",nCode))//数据在上一层目录下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	char sInputFile[1024]="../../test/test.TXT",sResultFile[1024];
	if (nCode==UTF8_CODE)
	{
		strcpy(sInputFile,"../../test/test-utf8.TXT");
	}

		const char *sResult=NWF_GetFileNewWords(sInputFile,50,true);//从文本文件中提取关键词
	FILE *fp=0;
	//////////////////////////////////////////////////////////////////////////
	//下面开始测试从单个文件中提取新词的功能
	//////////////////////////////////////////////////////////////////////////
	sResult=NWF_GetFileNewWords(sInputFile);//从文本文件中提取新词
	fp=fopen("ResultNew.txt","wb");//将结果写入文件
	fprintf(fp,sResult);
	fclose(fp);
	
	//////////////////////////////////////////////////////////////////////////
	//下面开始测试从单个文件中提取新词的功能
	//////////////////////////////////////////////////////////////////////////
	NWF_Batch_Start();//新词识别开始
	NWF_Batch_AddFile(sInputFile);//批量增加输入文件，可以不断循环调用NLPIR_NWI_AddFile或者NLPIR_NWI_AddMem
	NWF_Batch_Complete();//新词识别导入文件结束
	const char *pNewWordlist=NWF_Batch_GetResult();//获取本次批量导入文本文件中识别的新词结果
	printf("识别出的新词为：%s\n",pNewWordlist);//打印输出新词识别结果
	
	strcpy(sResultFile,sInputFile);
	strcat(sResultFile,"_result1.txt");
	clock_t  lStart,lEnd;
	long lTime=0;
	int nLine=0;
		
	NWF_Result2UserDict();//将上次新词识别的结果作为用户词典导入系统中，导入后的分词结果为自适应分词结果

	NWF_Exit();//识别完成，系统退出，释放资源

}

int main(int argc,char *argv[])
{
	char *pFile;
	testNewWord(0);
	return 0;
}	