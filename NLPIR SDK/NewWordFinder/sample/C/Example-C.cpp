// win_cDemo.cpp : �������̨Ӧ�ó������ڵ㡣
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
#define makeDirectory(x) mkdir(x, 0777)    // �ⲽ����룬�����ļ���ֻ��
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
	//��ʼ���ִ����
	if(!NWF_Init("../../",nCode))//��������һ��Ŀ¼�£�Ĭ��ΪGBK����ķִ�
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	char sInputFile[1024]="../../test/test.TXT",sResultFile[1024];
	if (nCode==UTF8_CODE)
	{
		strcpy(sInputFile,"../../test/test-utf8.TXT");
	}

		const char *sResult=NWF_GetFileNewWords(sInputFile,50,true);//���ı��ļ�����ȡ�ؼ���
	FILE *fp=0;
	//////////////////////////////////////////////////////////////////////////
	//���濪ʼ���Դӵ����ļ�����ȡ�´ʵĹ���
	//////////////////////////////////////////////////////////////////////////
	sResult=NWF_GetFileNewWords(sInputFile);//���ı��ļ�����ȡ�´�
	fp=fopen("ResultNew.txt","wb");//�����д���ļ�
	fprintf(fp,sResult);
	fclose(fp);
	
	//////////////////////////////////////////////////////////////////////////
	//���濪ʼ���Դӵ����ļ�����ȡ�´ʵĹ���
	//////////////////////////////////////////////////////////////////////////
	NWF_Batch_Start();//�´�ʶ��ʼ
	NWF_Batch_AddFile(sInputFile);//�������������ļ������Բ���ѭ������NLPIR_NWI_AddFile����NLPIR_NWI_AddMem
	NWF_Batch_Complete();//�´�ʶ�����ļ�����
	const char *pNewWordlist=NWF_Batch_GetResult();//��ȡ�������������ı��ļ���ʶ����´ʽ��
	printf("ʶ������´�Ϊ��%s\n",pNewWordlist);//��ӡ����´�ʶ����
	
	strcpy(sResultFile,sInputFile);
	strcat(sResultFile,"_result1.txt");
	clock_t  lStart,lEnd;
	long lTime=0;
	int nLine=0;
		
	NWF_Result2UserDict();//���ϴ��´�ʶ��Ľ����Ϊ�û��ʵ䵼��ϵͳ�У������ķִʽ��Ϊ����Ӧ�ִʽ��

	NWF_Exit();//ʶ����ɣ�ϵͳ�˳����ͷ���Դ

}

int main(int argc,char *argv[])
{
	char *pFile;
	testNewWord(0);
	return 0;
}	