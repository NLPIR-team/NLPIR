// win_cDemo.cpp : 定义控制台应用程序的入口点。
//
#include "../include/NLPIR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef OS_LINUX
#pragma comment(lib, "../../../bin/ICTCLAS2013/NLPIR.lib")
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
#include <afxmt.h>
#pragma warning(disable:4786)
#define PATH_DELEMETER  "\\"
#define LONG64U __int64
#define DATE_DELEMETER  "/"
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
#define Sleep(x) sleep(x/1000)
#define min(a,b) (((a)<(b)) ? (a) : (b))
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
//互斥锁宏定义

#ifndef OS_LINUX
#define		MUTEXDEFX(x)		HANDLE x 
#define		MUTEXINITX(x)		x = CreateMutex (NULL, FALSE, NULL)  
#define		MUTEXLOCKX(x)		WaitForSingleObject(x , INFINITE)
#define		MUTEXUNLOCKX(x)		ReleaseMutex(x)
#define     MUTEXDESDROYX(x)    CloseHandle(x)
#else
#define		MUTEXDEFX(x)	    pthread_mutex_t x
#define		MUTEXINITX(x)		pthread_mutex_init(& x, NULL)
#define		MUTEXLOCKX(x)		pthread_mutex_lock(& x)
#define		MUTEXUNLOCKX(x)	    pthread_mutex_unlock(& x)
#define     MUTEXDESDROYX(x)	pthread_mutex_destroy(& x)
#endif

MUTEXDEFX(m_mutex);


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
#ifdef _WIN32
static void FileWordSegThread(void* lpParam)
#else
static void* FileWordSegThread(void* lpParam)
#endif
{
	//printf("FileWordSegThread entering!\n");
	int *nThreadId=(int*)lpParam;//Thread ID
	printf("Thread %d started!\n",nThreadId);
	while(!NLPIR_Init("../..",1))//UTF8 encoding
	{//NLPIR_Init maybe fail because other thread is initialization 
		printf("ICTCLAS INIT FAILED!\n");
		continue;
#ifdef _WIN32
		return ;
#else
		return NULL;
#endif
	}
	
	//printf("Thread %d ReadFile entering!\n",nThreadId);
	/*char *pText=0;
	int nSize=ReadFile("testUTF.txt",&pText);//Read UTF8 text file to memory
	if (nSize==0)
	{
		printf("Error open testUTF8.txt\n");
#ifdef _WIN32
		return ;
#else
		return NULL;
#endif
	}*/
	FILE *fp=fopen("testUTF.txt","rb");
	if (fp==0)
	{
		printf("Error open testUTF8.txt\n");
#ifdef _WIN32
		return ;
#else
		return NULL;
#endif
	}
	char sLine1[1024],sUserWord[1024],sLine2[1024];
	fgets(sLine1,1024,fp);
	fgets(sLine2,1024,fp);
	fgets(sUserWord,1024,fp);

	fclose(fp);
	for (int i=0;i<100;i++)
	{
		Sleep(20);
		const char *pResult=NLPIR_ParagraphProcess(sLine1,1);
		printf("%d\t--%d start!\n",nThreadId,i);
		//unsigned long nFinger=NLPIR_FingerPrint(sLine1);
		//printf("%d\t--%d--%ld\n",nThreadId,i,nFinger);
		pResult=NLPIR_ParagraphProcess(sLine2,1);
		//printf("%d\t--%d sLine2:before adding user word--%ld\n",nThreadId,i,nFinger);
		int nAddId=NLPIR_AddUserWord(sUserWord);
		//printf("%d\t--%d sLine2:adding user word--%ld\n",nThreadId,i,nFinger);
		pResult=NLPIR_ParagraphProcess(sLine2,1);
		//printf("%d\t--%d sLine2:after adding user word--%ld\n",nThreadId,i,nFinger);
		//nAddId=NLPIR_DelUsrWord(sUserWord);
		//pResult=NLPIR_ParagraphProcess(sLine2,1);
		printf("%d\t--%d sLine2:after adding user word\n",nThreadId,i);
	}
	//delete [] pText;
	printf("%d\tDone!\n",nThreadId);
#ifdef _WIN32
	return ;
#else
	return NULL;
#endif
}

void testMultiThread(int nThreadCount)
{
	//初始化分词组件

	printf("start testMultiThread\n ");
	if(!NLPIR_Init("../..",1))//UTF8 encoding
	{//NLPIR_Init maybe fail because other thread is initialization 
		printf("ICTCLAS INIT FAILED!\n");
#ifdef _WIN32
		return ;
#else
		return ;
#endif
	}
	printf("ICTCLAS INIT Success!\n");
	//int nThreadCount=50;
	if (nThreadCount<=0)
	{
		nThreadCount=50;
	}
	int i;

#if defined(_WIN32)||defined(WIN32)

	HANDLE *handles=new HANDLE[nThreadCount];
	unsigned long myID;
	for(i=0; i<nThreadCount; ++i)
	{
		handles[i] = CreateThread(NULL, 0,	(LPTHREAD_START_ROUTINE)FileWordSegThread,(LPVOID)i, 0, &myID);
		if (handles[i] == NULL)  
		{   
			ExitProcess(i); 
		} 
	}
	int err = WaitForMultipleObjects(nThreadCount, handles,	TRUE, INFINITE);
	printf("Last thread to finish was thread #%d\n", err);
	for(i=0; i<nThreadCount; i++) 
	{   
		CloseHandle(handles[i]); 
	} 
#else		
	pthread_t *handles=new pthread_t[nThreadCount];
/*	pthread_attr_t stThreadAttr;

	pthread_attr_init(&stThreadAttr);
	pthread_attr_setdetachstate(&stThreadAttr, PTHREAD_CREATE_DETACHED);*/
	for(i=0; i<nThreadCount; ++i)
	{
		if(int err=pthread_create(&handles[i], NULL, &FileWordSegThread,(void *)i) != 0) 
		{	
			printf("can't create thread: %s\n", strerror(err));
			return ;
		}
		else
		{
			printf("create thread : %d\n", i);
		}
	}
	for(i=0; i<nThreadCount; ++i)
	{
		pthread_join(handles[i], NULL);
		//return ;
	}
#endif		
	printf("Mutilthread Main Exits!\n");
	delete [] handles;
	NLPIR_Exit();

}

int main(int argc,char *argv[])
{
	/**
	NLPIR_Init("../..",1);
	char *pText=0;
	int nSize=ReadFile("testUTF.txt",&pText);//Read UTF8 text file to memory
	if (nSize==0)
	{
		printf("Error open testUTF8.txt\n");
#ifdef _WIN32
		return 0;
#else
		return NULL;
#endif
	}
	for (int i=0;i<1;i++)
	{
		const char *pResult=NLPIR_ParagraphProcess(pText,1);
		printf("%d\t--%d\n",0,i);
	}
	delete [] pText;
	NLPIR_Exit();

	return 1;*/
	int nThreadCount=50;
	if (argc>1)
	{
		nThreadCount=atoi(argv[1]);
	}
	testMultiThread(nThreadCount);

	return 0;
}
