// win_cDemo.cpp : 定义控制台应用程序的入口点。
//
#include "../include/NLPIR.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef OS_LINUX
#ifdef NLPIR_STATIC
#pragma comment(lib, "../../../bin/ICTCLAS2013/NLPIRStatic.lib")
#else

#ifndef WIN64
#pragma comment(lib, "../../../bin/ICTCLAS2013/NLPIR.lib")
#else
#pragma comment(lib, "../../../bin/ICTCLAS2013/x64/NLPIR.lib")
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

void SplitGBK(const char *sInput);
void SplitBIG5();
void SplitUTF8();
void testNewWord(int code);
long ReadFile(const char *sFilename,char **pBuffer);
void testRandomString()
{
	if (!NLPIR_Init("../../", UTF8_CODE)) 
	{ 
		return ; 
	} 
	unsigned char buf[15] = {0}; 
	srand((unsigned)time(NULL)); 
	for (int i = 0; i < 1000000; i++) 
	{ 
		memset(buf, '\0', 15); 
		printf("%d\n", sizeof(buf)); 
		for (int j = 0; j < sizeof(buf) - 2; j++) 
		{ 
			unsigned int nt = abs(rand()%254); 
			buf[j] = nt; 
		} 
		printf("content[%s], len[%d]\n", buf, strlen((const char*)buf)); 
		NLPIR_ParagraphProcess((char*)buf, 0); 
	} 

	NLPIR_Exit();
}
int testBug()
{
	if(NLPIR_Init("../../")) 
	{ 
		for(int j=0; j<3000; ++j) 
		{ 
			if (j==1963)
			{
				int nDebug=1;
			}
			std::string str = "携号转网拟扩大试验范围，各方不积极形同鸡肋。"; 
			int nCount = 0; 
			const result_t *pVecResult = NLPIR_ParagraphProcessA(str.c_str(), &nCount); 
			//根据pVecResult和nCount处理关键词等 
			for(int i=0; i<nCount; ++i) 
			{ 
				char szKey[16] = { 0 }; 
				memcpy(szKey, str.c_str() + pVecResult[i].start, (pVecResult[i].length < 16) ? pVecResult[i].length : 16 - 1); 
				//cout<<szKey<<endl; 
			} 

			printf("%d\r",j);
		} 
		NLPIR_Exit(); 
	} 
	else 
	{ 
		//cout<<"nlpir init failed."<<endl; 
		printf("nlpir init failed.\n");
	} 

	return 0; 
}
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


void testStrSplitSpeed()
{
	//初始化分词组件
	printf("按照单篇文章进行处理！\n");
	if(!NLPIR_Init("../../",GBK_CODE))//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	printf("Success Init!\n");
	char sInput[1000] = "先登机第一劝业银行【环球时报记者朱晓磊】据越南《青年日报》等媒体2月18日报道";


	clock_t  lStart,lEnd;
	long lTime=0;
	int nLine=0;


	int nSize=strlen(sInput),nTotalSize=0;
	int i=1;
	double fTimeTotal=0.0,fTime=0.0;//Time cost
	double fSpeed,fSpeendMin=100000000.0;
	lStart=clock();//Record the time
	for (int i=0;i<10000;i++)
	{
		const char *pResult=NLPIR_ParagraphProcess(sInput);
	}

	lEnd=clock();//Record the time
	lTime=lEnd-lStart;
	fTime=(double)lTime/(double)CLOCKS_PER_SEC;//Time cost
	fSpeed=(double)nSize*10000/(double)fTime;
		
	printf("speed=%.2lfBytes/sec,length=%ld,time=%.6f\n",fSpeed,nSize*10000,fTime);

	NLPIR_Exit();
}
void testBatchSpeed(const char *sListFilename)
{
	//初始化分词组件
	printf("按照单篇文章进行处理！\n");
	if(!NLPIR_Init("../../",UTF8_CODE))//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	printf("Success Init!\n");

	FILE *fpListFile=fopen(sListFilename,"rb");
	char sInputFile[1025]="../test/test.TXT",sResultFile[1024];

	if (fpListFile==NULL)
	{
		printf("Error open %s\n",sListFilename);
		return ;
	}
	clock_t  lStart,lEnd;
	long lTime=0;
	int nLine=0;

	
	int nSize=0,nTotalSize=0;
	int i=1;
	double fTimeTotal=0.0,fTime=0.0;//Time cost
	double fSpeed,fSpeendMin=100000000.0;

	while(fgets(sInputFile,1024,fpListFile))
	{
		nLine=strlen(sInputFile);
		while(nLine>0&&(sInputFile[nLine-1]=='\r'||sInputFile[nLine-1]=='\n'))
		{
			nLine--;
		}
		sInputFile[nLine]=0;
		//sscanf(sResultFile,sInputFile)
		char *pText=0;
		nSize=ReadFile(sInputFile,&pText);
		if (nSize<=0)
		{
			printf("Error open %s\n",sInputFile);
			continue ;
		}
		nTotalSize+=nSize;
		lStart=clock();//Record the time
		int nCount=NLPIR_GetParagraphProcessAWordCount(pText);

		if (nCount>0)
		{
			result_t *pResult=new result_t[nCount];
			NLPIR_ParagraphProcessAW(nCount,pResult);
			
			//for (int i=0;i<nCount;i++)
			{
				//printf("\nstart=%d length=%d\n",pResult[i].start,pResult[i].length);
			}
			delete [] pResult;
		}
		lEnd=clock();//Record the time
		lTime=lEnd-lStart;
		fTime=(double)lTime/(double)CLOCKS_PER_SEC;//Time cost
		fTimeTotal+=lTime;
		fSpeed=(double)nSize/(double)fTime;
		if (nSize>0&&fSpeed<fSpeendMin)
		{
			fSpeendMin=fSpeed;
			strcpy(sResultFile,sInputFile);
		}
		printf("%d\r",i++);
	}
	
	fclose(fpListFile);
	fTimeTotal=fTimeTotal/CLOCKS_PER_SEC;
	fSpeed=(double)nTotalSize/fTimeTotal;
	printf("speed=%.2lfBytes/sec,length=%ld,time=%.6f\n",fSpeed,nTotalSize,fTimeTotal);
	fSpeed=(double)i/(double)fTimeTotal;
	printf("speed=%.2lfdocs/sec,docs=%ld,time=%.6f\n",fSpeed,i,fTimeTotal);

	printf("MinSpeed=%.2lfBytes/sec,file=%s\n",fSpeendMin,sResultFile);
	NLPIR_Exit();
}
void testSpeed(int nCode)
{
	//初始化分词组件
	printf("按照单篇文章进行处理！\n");
	if(!NLPIR_Init("../../",nCode))//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	printf("Success Init!\n");
	char sInputFile[1024]="../test/test.TXT",sResultFile[1024];
	if (nCode==UTF8_CODE)
	{
		strcpy(sInputFile,"../test/test-utf8.TXT");
	}
	strcpy(sResultFile,sInputFile);
	strcat(sResultFile,"_result.txt");
	clock_t  lStart,lEnd;
	long lTime=0;
	int nLine=0;
	FILE *fpResult=fopen(sResultFile,"wt");
	if (fpResult==NULL)
	{
		printf("Error open %s\n",sResultFile);
	}
	lStart=clock();//Record the time
	char *pText=0;
	int nSize=ReadFile(sInputFile,&pText);
	if (nSize<=0)
	{
		printf("Error open %s\n",sInputFile);
		return ;
	}
	int nCount=NLPIR_GetParagraphProcessAWordCount(pText);
	
	if (nCount>0)
	{
			result_t *pResult=new result_t[nCount];
			NLPIR_ParagraphProcessAW(nCount,pResult);
			lEnd=clock();//Record the time
			for (int i=0;i<nCount;i++)
			{
				fprintf(fpResult,"\"\nstart=%d length=%d word=\"",pResult[i].start,pResult[i].length);
				fwrite(pText+pResult[i].start,sizeof(char),pResult[i].length,fpResult);
			}
			fclose(fpResult);
			delete [] pResult;
	}
	lTime=lEnd-lStart;

	double fTime=(double)lTime/(double)CLOCKS_PER_SEC;//Time cost
	double fSpeed=(double)nSize/(double)fTime;
	printf("speed=%.2lfBytes/s,length=%ld,time=%.2f\n",fSpeed,nSize,fTime);


	strcat(sResultFile,"_file");
	lStart=clock();//Record the time
	NLPIR_FileProcess(sInputFile,sResultFile,0);
	lEnd=clock();//Record the time
	lTime=lEnd-lStart;
	fTime=(double)lTime/(double)CLOCKS_PER_SEC;//Time cost
	fSpeed=(double)nSize/(double)fTime;

	printf("NLPIR_FileProcess speed=%.2lfBytes/s,length=%ld,time=%.2f\n",fSpeed,nSize,fTime);

	NLPIR_Exit();
}

void testNewWord(int nCode)
{
	//初始化分词组件
	if(!NLPIR_Init("../../",nCode))//数据在上一层目录下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	char sInputFile[1024]="../test/test.TXT",sResultFile[1024];
	if (nCode==UTF8_CODE)
	{
		strcpy(sInputFile,"../test/test-utf8.TXT");
	}

	//////////////////////////////////////////////////////////////////////////
	//下面开始测试关键词提取功能
	//////////////////////////////////////////////////////////////////////////
	const char *sResult=NLPIR_GetFileKeyWords(sInputFile,50,true);//从文本文件中提取关键词
	FILE *fp=fopen("Result.txt","wb");
	fprintf(fp,sResult);//将结果写入文件
	fclose(fp);
	//////////////////////////////////////////////////////////////////////////
	//下面开始测试从单个文件中提取新词的功能
	//////////////////////////////////////////////////////////////////////////
	sResult=NLPIR_GetFileNewWords(sInputFile);//从文本文件中提取新词
	fp=fopen("ResultNew.txt","wb");//将结果写入文件
	fprintf(fp,sResult);
	fclose(fp);



	//////////////////////////////////////////////////////////////////////////
	//下面开始测试从单个文件中提取新词的功能
	//////////////////////////////////////////////////////////////////////////
	NLPIR_NWI_Start();//新词识别开始
	NLPIR_NWI_AddFile(sInputFile);//批量增加输入文件，可以不断循环调用NLPIR_NWI_AddFile或者NLPIR_NWI_AddMem
	NLPIR_NWI_Complete();//新词识别导入文件结束
	const char *pNewWordlist=NLPIR_NWI_GetResult();//获取本次批量导入文本文件中识别的新词结果
	printf("识别出的新词为：%s\n",pNewWordlist);//打印输出新词识别结果
	
	strcpy(sResultFile,sInputFile);
	strcat(sResultFile,"_result1.txt");
	clock_t  lStart,lEnd;
	long lTime=0;
	int nLine=0;

	lStart=clock();//Record the time
	double speed=NLPIR_FileProcess(sInputFile,sResultFile,0);//普通的文本文件分词功能
	lEnd=clock();//Record the time
	lTime+=lEnd-lStart;

	float fTime=(float)lTime/(float)CLOCKS_PER_SEC;//Time cost
	printf("speed=%.2lfKB/s,time=%.2f\n",speed,fTime);
	
	NLPIR_NWI_Result2UserDict();//将上次新词识别的结果作为用户词典导入系统中，导入后的分词结果为自适应分词结果

	strcpy(sResultFile,sInputFile);
	strcat(sResultFile,"_result2.txt");
	NLPIR_FileProcess(sInputFile,sResultFile);//再次调用同样的函数，但是分词结果将自动适应新词结果
	
	NLPIR_Exit();//识别完成，系统退出，释放资源
}

void SplitEnglish(const char *sInput)
{//分词演示

	//初始化分词组件
	if(!NLPIR_Init("../../"))//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	//对文件进行分词

	const char *sResult = ICTCLAS_ParagraphProcess(sInput, 1); 
	printf("%s\n", sResult); 

	int nCount1=ICTCLAS_ImportUserDict("userdictgbk.txt");
	sResult = ICTCLAS_ParagraphProcess(sInput, 1); 
	printf("%s\n", sResult); 
	sResult = NLPIR_GetKeyWords(sInput,100,true); 
	printf("%s\n", sResult); 
	NLPIR_Exit();
	return ;
//	NLPIR_ReleaseBuf(sResult);
	NLPIR_FileProcess("D:\\NLPIR\\test\\english\\sample3.txt","D:\\NLPIR\\test\\english\\sample3_result.txt",1);
	NLPIR_FileProcess("D:\\NLPIR\\test\\english\\sample4.txt","D:\\NLPIR\\test\\english\\sample4_result.txt",1);
	NLPIR_FileProcess("D:\\NLPIR\\test\\english\\input_test.txt","D:\\NLPIR\\test\\english\\input_test_result.txt",1);
	NLPIR_FileProcess("D:\\NLPIR\\test\\english\\sample1.txt","D:\\NLPIR\\test\\english\\sample1_result.txt",1);
	NLPIR_FileProcess("D:\\NLPIR\\test\\english\\sample2.txt","D:\\NLPIR\\test\\english\\sample2_result.txt",1);
	NLPIR_FileProcess("D:\\NLPIR\\test\\english\\sample5.txt","D:\\NLPIR\\test\\english\\sample5_result.txt",1);
	//////////////////////////////////////////////////////////////////////////
	//下面开始测试NLPIR_ParagraphProcessA功能
	//////////////////////////////////////////////////////////////////////////
	int nCount;
	const result_t *pResult=NLPIR_ParagraphProcessA(sInput,&nCount);
	//分词的高级功能
	//该函数功能为：输入字符串，输出分词结果的result_t结构体数组，nCout为数组大小
	//返回的数组结果由系统自行维护，用户直接调用即可

	printf("nCount=%d\n",nCount);//分词结果数目

	int i=1;
	char *sWhichDic;
	char sWord[100];
	for(i=0;i<nCount;i++)
	{//逐个答应分词结果的内容
		strncpy(sWord,sInput+pResult[i].start,pResult[i].length);
		sWord[pResult[i].length]=0;
		printf("No.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d, UserDefine:%d, Word:%s\n",
			i+1, pResult[i].start, pResult[i].length, pResult[i].iPOS, pResult[i].word_ID, pResult[i].word_type,
			sWord);
	}


	//释放分词组件资源
	NLPIR_Exit();
}
void SplitGBK(const char *sInput)
{//分词演示

	//初始化分词组件
	if(!NLPIR_Init("d:/nlpir"))//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	printf("ICTCLAS INIT Success!\n");
	FILE *fp=fopen("result.txt","wt");
	const char *pKey=NLPIR_GetFileKeyWords("D:\\BIT\\项目\\2015\\anq\\张灵甫\\content\\content.txt",200,true);
	fprintf(fp,"Key is:\n%s\n",pKey);
	printf("NLPIR_GetFileKeyWords Success!\n");
	fflush(fp);

	pKey=NLPIR_FileWordFreqStat("D:\\BIT\\项目\\2015\\anq\\张灵甫\\content\\content.txt");
	fprintf(fp,"Freq is:%s\n",pKey);
	printf("NLPIR_FileWordFreqStat Success!\n");
	fflush(fp);
	fclose(fp);


	/*
	char sWord[100]="高兴";
	const char* pResult,*pFinerResult;
	int bExit=NLPIR_IsWord(sWord);
	pResult=NLPIR_GetWordPOS(sWord);
	pFinerResult=NLPIR_FinerSegment(sWord);
	printf("sWord=%s,NLPIR_IsWord=%d,NLPIR_GetWordPOS=%s,NLPIR_FinerSegment=%s\n",sWord,bExit,pResult,pFinerResult);
	
	strcpy(sWord,"工作的");
	bExit=NLPIR_IsWord(sWord);
	pResult=NLPIR_GetWordPOS(sWord);
	pFinerResult=NLPIR_FinerSegment(sWord);
	printf("sWord=%s,NLPIR_IsWord=%d,NLPIR_GetWordPOS=%s,NLPIR_FinerSegment=%s\n",sWord,bExit,pResult,pFinerResult);


	strcpy(sWord,"中华人民共和国");
	bExit=NLPIR_IsWord(sWord);
	pResult=NLPIR_GetWordPOS(sWord);
	pFinerResult=NLPIR_FinerSegment(sWord);
	printf("sWord=%s,NLPIR_IsWord=%d,NLPIR_GetWordPOS=%s,NLPIR_FinerSegment=%s\n",sWord,bExit,pResult,pFinerResult);
	
	strcpy(sWord,"中华人民共和国1949年成立了");
	pFinerResult=NLPIR_ParagraphProcess(sWord);
	printf("%s",pFinerResult);

	//NLPIR_Exit();
	//return ;
	*/
	//char sSentence[5000]="尊敬的全球通客户，您好！欢迎登录江苏移动短信营业厅， 请直接回复序号：\r\n0.已开通业务查询\n1.话费与积分\n2.促销优惠\n3.热门业务\n4.流量查询与办理\n5.家庭和集团业务\n6.全球通语音套餐\n7.客户服务与帮助\n快捷通道：DHLL（积分兑换流量）；3305（开通5元包30MB流量叠加包，立即生效）；111（查话费）；192（查流量）；113（查套餐）。中国移动";//"Bill Clinton是美国总统，好像没来过北京理工大学，喜欢吃小尾羊！";
	char sSentence[5000]="113（查套餐）。中国移动";//"Bill Clinton是美国总统，好像没来过北京理工大学，喜欢吃小尾羊！";
	strcpy(sSentence,"Waitingforyousolongtime!600056!\n");
	const char * sResult;
	//ICTCLAS_AddUserWord("。中 ns");
	sResult=ICTCLAS_ParagraphProcess(sSentence, 1); 
	printf("%s",sResult);
	sResult=NLPIR_FinerSegment(sSentence); 
	printf("%s",sResult);


	sResult = NLPIR_FileWordFreqStat("testGBK.txt");
	printf("%s\n", sResult);

	sResult = NLPIR_GetEngWordOrign("driving");
	printf("%s\n", sResult);
	sResult = NLPIR_GetEngWordOrign("drove");
	printf("%s\n", sResult);
	sResult = NLPIR_GetEngWordOrign("drives");
	printf("%s\n", sResult);
	sResult = NLPIR_GetEngWordOrign("driven");
	printf("%s\n", sResult);
/*
	NLPIR_Exit();
	return ;

	

	NLPIR_SetPOSmap(ICT_POS_MAP_SECOND);//设置词性标注集合的类型，默认为计算所二级标注体系
	NLPIR_FileProcess("D:/NLPIR/feedback/1.txt","D:/NLPIR/feedback/1-result.txt");
	const char* sample1 ="据悉，质检总局已将最新有关情况再次通报美方，要求美方加强对输华玉米的产地来源、运输及仓储等环节的管控措施，有效避免输华玉米被未经我国农业部安全评估并批准的转基因品系污染。";// "开心成长的烦恼学习深造中国证券市场";
	const char* sResult1 = ICTCLAS_ParagraphProcess(""); 
	printf("%s\n", sResult1); 
	for (int i=0;i<100;i++)
	{
		sResult1 = ICTCLAS_ParagraphProcess(sample1); 
		printf("%d,%s\n", i,sResult1); 
	}

	printf("%d\n", ICTCLAS_AddUserWord("要求美方加强对输 n"));
	printf("%d\n", ICTCLAS_AddUserWord("华玉米的产地来源  n"));



	sResult1 = ICTCLAS_ParagraphProcess(sample1, 1); 
	 printf("%s\n", sResult1); 
	 printf("%d\n", ICTCLAS_DelUsrWord("要求美方加强对输"));
	 sResult1 = ICTCLAS_ParagraphProcess(sample1, 1); 
	 printf("%s\n", sResult1); 
	 printf("%d\n", ICTCLAS_AddUserWord("要求美方加强对输 n"));
	 sResult1 = ICTCLAS_ParagraphProcess(sample1, 1); 
	 printf("%s\n", sResult1); 
	 
	 sResult1 = NLPIR_GetFileKeyWords("D:\\NLPIR\\feedback\\keyword2.txt",50,false); 
	 printf("%s\n", sResult1); 
	
	 char *pText=0;
	 ReadFile("D:\\NLPIR\\feedback\\keyword2.txt",&pText);
	 sResult1 = NLPIR_GetKeyWords(pText,50,false); 
	 printf("%s\n", sResult1); 
	 delete [] pText;

	 sResult1 = NLPIR_GetKeyWords(sample1,10,false); 
	 printf("%s\n", sResult1); 


	 const char* sample2 = "不雅视频网上流传";
	 const char* sResult2 = ICTCLAS_ParagraphProcess(sample2);
	 printf("%s\n", sResult2); 
	 printf("%d\n", ICTCLAS_AddUserWord("不雅 ag")); 
	 sResult2 = ICTCLAS_ParagraphProcess(sample2, 1); 
	 printf("%s\n", sResult2);



	 */
	//////////////////////////////////////////////////////////////////////////
	//下面开始测试NLPIR_ParagraphProcessA功能
	//////////////////////////////////////////////////////////////////////////
	int nCount;
	//strcpy(sSentence,"张长虹指出，中国证券市场的下跌有特殊的原因，例如经济发展方向的调整和非流通股的消化问题，以及市场情绪的变化等。");
//	strcpy(sSentence,"drivingmotor The fuel for which gas and oil are used in general is determined at the same time as determination of the driving motor , taking into account the supplying condition, environmental properties, cost, etc.");
	strcpy(sSentence,"driving  motor , Bill  Clinton taking into account the supplying condition, environmental properties, cost, etc.");

	

	const result_t *pResult=NLPIR_ParagraphProcessA(sSentence,&nCount);
	//分词的高级功能
	//该函数功能为：输入字符串，输出分词结果的result_t结构体数组，nCout为数组大小
	//返回的数组结果由系统自行维护，用户直接调用即可
	printf("nCount=%d\n",nCount);//分词结果数目

	int i=1;
	char *sWhichDic;
	char sWord[100];
	for(i=0;i<nCount;i++)
	{//逐个答应分词结果的内容
		sWhichDic="";
		switch (pResult[i].word_type)
		{
		case 0:
			sWhichDic = "核心词典";
			break;
		case 1:
			sWhichDic = "用户词典";
			break;
		case 2:
			sWhichDic = "专业词典";
			break;
		default:
			break;
		}
		strncpy(sWord,sSentence+pResult[i].start,pResult[i].length);
		sWord[pResult[i].length]=0;
		printf("No.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d, UserDefine:%s, Word:%s,Weight:%d\n",
			i+1, pResult[i].start, pResult[i].length, pResult[i].iPOS, pResult[i].word_ID, sWhichDic,
			sWord,pResult[i].weight );
	}
	//////////////////////////////////////////////////////////////////////////
	//下面开始测试用户词典功能
	//////////////////////////////////////////////////////////////////////////
	//导入用户词典前
	
	printf("未导入用户词典：\n");
	sResult = NLPIR_ParagraphProcess(sSentence, 1);
	printf("%s\n", sResult);

	//导入用户词典后
	printf("\n导入用户词典后：\n");
	nCount = NLPIR_ImportUserDict("userdictgbk.txt");//userdic.txt覆盖以前的用户词典
	//保存用户词典
	printf("导入%d个用户词。\n", nCount);
	sResult = NLPIR_ParagraphProcess(sSentence, 1);
	printf("%s\n", sResult);
	NLPIR_Exit();
	return;
	//导入第二个用户词典后
	printf("\n导入用户词典后：\n");
	nCount = NLPIR_ImportUserDict("userdictgbk.txt",false);//userdictgbk.txt补充以前的用户词典
	//保存用户词典
	printf("导入%d个用户词。\n", nCount);
	sResult = NLPIR_ParagraphProcess(sSentence, 1);
	printf("%s\n", sResult);

	strcpy(sSentence,"不雅视频东莞聚众淫乱");
	sResult = NLPIR_ParagraphProcess(sSentence, 1);
	printf("%s\n", sResult);

	//动态添加用户词
	printf("\n动态添加用户词后：\n");
	NLPIR_AddUserWord("不雅   ag");
	sResult = NLPIR_ParagraphProcess(sSentence, 1);
	printf("%s\n", sResult);


	//////////////////////////////////////////////////////////////////////////
	//下面开始测试对文件进行分词功能
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//下面开始测试基本的常用功能NLPIR_ParagraphProcess功能
	//////////////////////////////////////////////////////////////////////////
	while(_stricmp(sSentence,"q")!=0)
	{
		sResult = NLPIR_ParagraphProcess(sSentence);
		//测试最基本的功能，输入一个字符串，输出分词结果字符串，
		//如果不需要标注，调用的时候可以为： NLPIR_ParagraphProcess(sSentence,0)
		printf("%s\nInput string now('q' to quit)!\n", sResult);// 
		gets(sSentence);
	}
	//对文件进行分词
	NLPIR_FileProcess("test2.txt","test2_result.txt",1);
	NLPIR_FileProcess("testGBK.txt","testGBK_result.txt",1);

	sResult=NLPIR_GetFileNewWords("D:\\NLPIR\\test\\屌丝，一个字头的诞生.TXT");
	//释放分词组件资源
	NLPIR_Exit();
}

void SplitGBK_Fanti(const char *sInput)
{//分词演示

	//初始化分词组件
	if(!NLPIR_Init("",GBK_FANTI_CODE))//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}

	NLPIR_SetPOSmap(ICT_POS_MAP_SECOND);

	char sSentence[5000]="ICTCLAS在国内专家组组织的评测中活动获得了第一名，在第一届国际中文处理研究机构SigHan组织的评测中都获得了多项第一名。ICTCLAS在國內專家組組織的評測中活動獲得了第一名，在第一屆國際中文處理研究機構SigHan組織的評測中都獲得了多項第一名。";
	const char * sResult;


	int nCount;
	NLPIR_ParagraphProcessA(sSentence,&nCount);
	printf("nCount=%d\n",nCount);
	int count = NLPIR_GetParagraphProcessAWordCount(sSentence);
	const result_t *pResult=NLPIR_ParagraphProcessA(sSentence,&nCount);

	int i=1;
	char *sWhichDic;
	for(i=0;i<nCount;i++)
	{
		sWhichDic="";
		switch (pResult[i].word_type)
		{
		case 0:
			sWhichDic = "核心词典";
			break;
		case 1:
			sWhichDic = "用户词典";
			break;
		case 2:
			sWhichDic = "专业词典";
			break;
		default:
			break;
		}
		printf("No.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d, UserDefine:%s, Word:%s\n",
			i+1, pResult[i].start, pResult[i].length, pResult[i].iPOS, pResult[i].word_ID, sWhichDic,sSentence+pResult[i].start );
	}
	while(_stricmp(sSentence,"q")!=0)
	{
		sResult = NLPIR_ParagraphProcess(sSentence,0);
		printf("%s\nInput string now('q' to quit)!\n", sResult);// 
		scanf("%s",sSentence);
	}
	
	//导入用户词典前
	printf("未导入用户词典：\n");
	sResult = NLPIR_ParagraphProcess(sInput, 0);
	printf("%s\n", sResult);

	//导入用户词典后
	printf("\n导入用户词典后：\n");
	nCount = NLPIR_ImportUserDict("userdic.txt");//userdic.txt覆盖以前的用户词典
	//保存用户词典
	NLPIR_SaveTheUsrDic();
	printf("导入%d个用户词。\n", nCount);
	
	sResult = NLPIR_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);

	//动态添加用户词
	printf("\n动态添加用户词后：\n");
	NLPIR_AddUserWord("计算机学院   xueyuan");
	NLPIR_SaveTheUsrDic();
	sResult = NLPIR_ParagraphProcess(sInput, 1);
	printf("%s\n", sResult);


	//对文件进行分词
	NLPIR_FileProcess("test2.txt","test2_result.txt",1);
	NLPIR_FileProcess("testGBK.txt","testGBK_result.txt",1);


	//释放分词组件资源
	NLPIR_Exit();
}
void SplitBIG5()
{
	//初始化分词组件
	if(!NLPIR_Init("../../",BIG5_CODE))//数据在当前路径下，设置为BIG5编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	NLPIR_FileProcess("testBIG.txt","testBIG_result.txt");
	NLPIR_Exit();
}

void SplitFantiUTF8()
{
	//初始化分词组件
	if(!NLPIR_Init("../../",UTF8_FANTI_CODE))//数据在当前路径下，设置为BIG5编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	NLPIR_FileProcess("testFantiUTF.txt","testFantiUTF_result.txt");
	NLPIR_Exit();
}
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
void SplitUTF8()
{
	/*if(!NLPIR_Init("D:/NLPIR",UTF8_CODE))//数据在当前路径下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	NLPIR_FileProcess("testUTF.txt","testUTF_result.txt");
	NLPIR_FileProcess("luan.txt","luan_result.txt");
	NLPIR_FileProcess("ting.txt","ting_result.txt");
	//NLPIR_
	NLPIR_Exit();
	return;
	int nnCount=0;
	ifstream fin("weibo2.csv");
	string strInput;

	while(getline(fin,strInput))
	{
		nnCount++;
		const char *sResult = NLPIR_ParagraphProcess(strInput.c_str());
		//if (nnCount%1000==0)
		{
			printf("nCount=%d\r",nnCount);
		}
	}
	NLPIR_Exit();
	return ;*/
	/*
	FILE *fpSource,*fpResult;//The file pointer of read and write
	char sLine[4097];

	fpSource=fopen("D:/NLPIR/feedback/weibo1.txt","rb");
	fpResult=fopen("D:/NLPIR/feedback/weibo1_result.txt","wb");
	
	//m_bEnglishText=IsEnglishTextFile(sSrcFilename);
	clock_t  lStart,lEnd;
	long lTime=0;
	int nLine=0;
	const char *pResult;
	;
	while (fgets(sLine,4096,fpSource))
	{
		fputs(sLine,fpResult);
		//fwrite(sLine,strlen(sLine),1,fpResult);
		nLine+=1;
#ifdef _DEBUG
		printf("%d\r",nLine);
#endif
	}
	//printf("Size=%ldBytes,Time=%6fs,Speed=%6fKB/s\n",buf.st_size,fTime,fSpeed/1000);
	fclose(fpSource);
	fclose(fpResult);
	*/
	//初始化分词组件
	if(!NLPIR_Init("D:/NLPIR",UTF8_CODE))//数据在当前路径下，设置为UTF8编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	//NLPIR_FileProcess("D:\\NLPIR\\feedback\\huawei\\microBlog.txt","D:\\NLPIR\\feedback\\huawei\\microBlogLicense.txt");
	NLPIR_FileProcess("D:\\NLPIR\\test\\1.txt","D:\\NLPIR\\test\\1-result.res");
	const char *sResult=NLPIR_GetFileNewWords("D:\\NLPIR\\test\\testNewwordUTF8.TXT");
	//释放分词组件资源

	NLPIR_Exit();
	return ;


	/**
	std::cout << NLPIR_ParagraphProcess("^^", 0) << std::endl; 
	std::cout << NLPIR_ParagraphProcess("^^a", 0) <<std::endl; 
	std::cout << NLPIR_ParagraphProcess("b^^a", 0) <<std::endl; 
	std::cout << NLPIR_ParagraphProcess("b^^^a", 0) <<std::endl; 
	std::cout << NLPIR_ParagraphProcess("bcd^^^a", 0) <<std::endl; 

	std::cout << NLPIR_ParagraphProcess("A B C D", 0) << std::endl;
	std::cout << NLPIR_ParagraphProcess("def", 0) << std::endl;
	std::cout << NLPIR_ParagraphProcess("A B C D", 0) << std::endl;
	std::cout << NLPIR_ParagraphProcess("def", 0) << std::endl;
	std::cout << NLPIR_ParagraphProcess("   ", 0) << std::endl;
	std::cout << NLPIR_ParagraphProcess("ghi", 0) << std::endl;
	std::cout << NLPIR_ParagraphProcess("a1 b1 c1", 0) << std::endl;
	//NLPIR_FileProcess("D:/NLPIR/feedback/weibo2.txt","D:/NLPIR/feedback/weibo2.csv.txt");
	printf("Start now!\n");
、*/
	int nCount=NLPIR_ImportUserDict("dict.txt");

	NLPIR_FileProcess("testUtf.txt","testUtf8-result.txt");

	printf("Start now!\n");
	//const char *sResult=NLPIR_GetFileKeyWords("D:\\NLPIR\\feedback\\huawei\\5341\\5341\\《女职工劳动保护特别规定》特刊\\2012\\6\\18951.txt");
	//const char *sResultNew=NLPIR_GetFileNewWords("D:\\NLPIR\\feedback\\huawei\\5341\\5341\\《女职工劳动保护特别规定》特刊\\2012\\6\\18951.txt");
	FILE *fpResult=fopen("Result.txt","wb");
	//const char *sResult;	
	sResult=NLPIR_GetFileKeyWords("testUtf.txt",1000,true);
	fprintf(fpResult,"Key Result is\n%s\n",sResult);
	nCount=NLPIR_ImportKeyBlackList("keyblack.txt");
	sResult=NLPIR_GetFileKeyWords("testUtf.txt",1000,true);
	fprintf(fpResult,"Key Result （after blacklist imported） is\n%s\n",sResult);
	//const char *sResultNew=NLPIR_GetFileNewWords("weibo.txt",1000,true);
	//fprintf(fpResult,"New Result is\n%s\n",sResultNew);
	fclose(fpResult);

	//NLPIR_FileProcess("D:/NLPIR/feedback/weibo1.txt","D:/NLPIR/feedback/weibo1-result.txt");
	//NLPIR_FileProcess("D:/NLPIR/feedback/weibo1.txt","D:/NLPIR/feedback/weibo1-result.txt");
	NLPIR_FileProcess("D:/NLPIR/feedback/input-utf8.txt","D:/NLPIR/feedback/input-utf8-result.txt");
/*	
	const char *pMessage=NLPIR_GetLastErrorMsg();
	char *pText=0;
    int nSize=ReadFile("testUTF.txt",&pText);
 	const char *pKeyResult=NLPIR_GetKeyWords(pText);
	const char *pNewResult=NLPIR_GetNewWords(pText);
	const char *pResult=NLPIR_ParagraphProcess(pText,1);
	delete [] pText;
	//NLPIR_Exit();
	//return ;
	FILE *fpU=fopen("testUTF_result2.txt","wt");
	if (fpU==NULL)
	{
		printf("Error Open TestUTF8-bigfile.txt\n");
		NLPIR_Exit();
		return ;
	}
	fprintf(fpU,"%s",pResult);
	fclose(fpU);
//	NLPIR_ReleaseBuf(pResult);
	//return;

	FILE *fp=fopen("D:\\NLPIR\\test\\utf-8-offset.txt","rb");
	if (fp==NULL)
	{
		printf("Error Open TestUTF8-bigfile.txt\n");
		NLPIR_Exit();
		return ;
	}
	FILE *fpResult=fopen("utf-8-offset-result.txt","wt");
	char sLine[10241];
	int i,nCount,nDocID=1;
	result_t res[1000];
	//while (fgets(sLine,10240,fp))
	{
		CICTCLAS *pICTCLAS=new CICTCLAS;
		fseek(fp,0,SEEK_END);
		int nSize=ftell(fp);

		fseek(fp,0,SEEK_SET);
		fread(sLine,nSize,1,fp);
		sLine[nSize]=0;
		const result_t *pResult=pICTCLAS->ParagraphProcessA(sLine,&nCount);
	    i=1;

		for(i=0;i<500&&i<nCount;i++)
		{
 			fprintf(fpResult,"\nNo.%d:start:%d, length:%d,POS_ID:%d,Word_ID:%d\n",
 				i+1, pResult[i].start, pResult[i].length, pResult[i].iPOS, pResult[i].word_ID);
			fwrite(sLine+pResult[i].start,sizeof(char),pResult[i].length,fpResult);
		}
		delete pICTCLAS;
		fclose(fpResult);
		printf("Processed docs %d\r",nDocID++);
	}
	*/
	NLPIR_Exit();
}
void ImportUserDict(const char *sFilename)
{
	//初始化分词组件
	if(!NLPIR_Init("../../"))//数据在上一层目录下，默认为GBK编码的分词
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}
	int nCount=NLPIR_ImportUserDict(sFilename);//再次调用同样的函数，但是分词结果将自动适应新词结果
	printf("Import %d user defined items from file %s\n",nCount,sFilename);
	NLPIR_Exit();//识别完成，系统退出，释放资源
}
void testLinuxMac()
{

	int	m_length=0;
	char sMacAddr[255][13];
	char sTemp[13];	
	int i,j,nMacCount=0;


	char *pText=0,*pCur,*pStart;//,sChar[4]
	int nLen=ReadFile("temp.mac",&pText);
	//sChar[3]=0;
	i=0;
	if (nLen>0)
	{//HWaddr 00:30:48:24:21:AB
		//sChar[3]=0;
		i=0;
		if (nLen>0)
		{//HWaddr 00:30:48:24:21:AB
			pStart=strstr(pText,":");
			while (pStart!=0&&pStart-pText>3&&pStart+3-pText<nLen)
			{
				while (pStart!=0&&pStart-pText>3&&pStart+12-pText<nLen&&
						(*(pStart+12)!=':'||*(pStart+3)!=':'||*(pStart+6)!=':'||*(pStart+9)!=':')
					   )
				{//Lookup the start position:00:0C:29:BF:F0:85
					pStart=strstr(pStart+3,":");
				}
				if (pStart!=0&&pStart-pText>3&&pStart+3-pText<nLen&&*(pStart+3)==':')
				{//Locate a mac address
					pCur=pStart-2;
					//printf("pCur=%s\n",pCur);
					for (j=0;j<6;j++)
					{
						sMacAddr[i][j*2]=pCur[j*3];
						sMacAddr[i][j*2+1]=pCur[j*3+1];
					}
					sMacAddr[i][12]=0;
					i++;
				}
				if (pStart!=0)
				{
					pStart=strstr(pCur+17,":");
				}
			}	
		}
	}


}
int main(int argc,char *argv[])
{
//	testLinuxMac();
//	testRandomString();
//	return 1;
	//SplitFantiUTF8();
	char *pFile;
	if (argc<2)
	{
		SplitGBK("");
		return 1;
	}
	switch(argv[1][0])
	{

	case 'b'://thread
	case 'B'://thread
		testBatchSpeed(argv[1]);
		break;
	case 'e'://thread
	case 'E'://thread
		SplitEnglish("Beijing Institute of Technology from the year of 2010 in China!");//Dr. Kevin Zhang worked in 
		break;
	case 'f'://thread
	case 'F'://thread
		SplitBIG5();
		break;
	case 'g'://thread
	case 'G'://thread
		SplitGBK("Test");
		break;
	case 'i'://import user dictionary
	case 'I'://
		pFile="../../Data/Userdict.txt";
		if (argc>2)
		{
			pFile=argv[2];
		}
		ImportUserDict(pFile);
		break;
	case 's'://thread
	case 'S'://thread
		testSpeed(0);
		break;
	case 'm'://thread
	case 'M'://thread
		//testThread();
		break;
	case 'n'://thread
	case 'N'://thread
		testNewWord(0);
		break;
	case 'u'://thread
	case 'U'://thread
		SplitUTF8();
		break;
	}
	return 0;
}	