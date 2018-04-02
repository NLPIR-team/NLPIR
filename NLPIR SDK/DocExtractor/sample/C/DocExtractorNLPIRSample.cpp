// ClusterSystem.cpp : Defines the entry point for the console application.
//
#include "../API/DocExtractor.h"
//#include "../../ICTCLAS2013/include/NLPIR.h"
#ifdef WIN64
#pragma comment(lib, "../../../bin/DocExtractor/x64/DocExtractor.lib")
#else
#pragma comment(lib, "../../../bin/DocExtractor/DocExtractor.lib")
#endif
#include <vector>
#include <string>
#include <time.h>
#ifndef OS_LINUX
#include <io.h>
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
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h> 
#define makeDirectory(x) mkdir(x, 0777)    // 这步骤必须，否则文件夹只读
#define _stricmp strcasecmp
#define stricmp strcasecmp
#define strnicmp strncasecmp
#define Sleep(x) sleep(x/1000)
#define min(a,b) (((a)<(b)) ? (a) : (b))
#define _fstat(X,Y)     fstat((X),(Y))
#define _fileno(X)     fileno((X))
#define _getcwd         getcwd
#define _off_t          off_t
#define PATH_DELEMETER  "/"
#define DATE_DELEMETER  "/"
#define LONG64U long long
#define __int64 long long
#define _atoi64(val) strtoll(val, NULL, 10)
#define _fseeki64(stream,offset,whence) fseeko((stream),(offset),(whence))
#include <unistd.h>
#define SLEEP(x) sleep(x)
#endif
using namespace::std;
typedef  std::string tstring;
//#pragma comment(lib, "../bin/LJSummary.lib")

//bool fn_vScanFiles(std::string& sFolderName, std::vector<std::string>& vsFileName,tstring& sFilter);
bool gfn_bReadFile(const char* lpszFilename, string& sFileText);
bool fn_vScanFiles(const char* sFolderName, std::vector<std::string>& vsFileName,const char* sFilter);
int main(int argc, char* argv[])
{

	if (argc != 2){
		printf("usage: %s <CorpusDir>\n",argv[0]);
		return 1;
	}

	//for (int k=0;k<10;k++)
	{
		//printf("Round %d:",k);
		// 初始化	
		//if(!DE_Init("../../",GBK_CODE)) 
		if (!DE_Init("E:\\NLPIR\\NLPIR SDK\\DocExtractor\\", UTF8_CODE))
		{//UTF8_CODE
			printf("%s\n", DE_GetLastErrMsg());
				return 1;
		}
		else
		{
			printf("Success!\n");
		}
	}
	/*
	//_tDocExtractResult result;
	DOC_PARSER_HANDLE handle2=DE_ParseDocE(">endobj54 0 obj<<67581BC655958B4394F7B770C72FDF99>]/Index[36 47]/Info 35 0 R/Length 97/Prev 201454/Root 37 0 R/Size 83/Type/XRef/W[1 3 1]>>streamh辀bd```b``?梹?@$??\"?傎?捙L偵*?X讃?\"?力)I?N 耳 鵲鯱&爫汚\"@鵄J`乎","",true);
	//outPut(result);
	DE_Exit();
	return 1;*/
	/*
		if(!NLPIR_Init("../../",UTF8_CODE)) {//UTF8_CODE
			printf("%s\n", DE_GetLastErrMsg());
				return 1;
		}*/

	// 扫描
	//int nRealCount;
	vector<string> vsFileName;
	vsFileName.push_back("D:\\NLPIR\\feedback\\DocExtractor\\xicheng-utf\\test.TXT");
	//fn_vScanFiles(argv[1], vsFileName,"txt");

	//fn_vScanFiles(std::string& sFolderName, std::vector<std::string>& vsFileName,tstring& sFilter)
	string sOutput = "";

	// 加载
	printf("分析文章（Total %d）...\n",vsFileName.size());
	int i;
	clock_t tStart,tEnd;
	long lTime,lTotalTime=0,lTotalSize=0;
	float fTime;
	FILE *fp=fopen("nlpir_result.txt","wt");
	const char *sResult=0;
	i=0;
	for(i=0; i<vsFileName.size(); i++)
	{

		string sContent;
		gfn_bReadFile(vsFileName[i].c_str(), sContent);
	///	sResult=NLPIR_ParagraphProcess(sContent.c_str());
//		fprintf(fp,"paper %d result is:\n[%s]\n",i,sResult);
	//	fflush(fp);
		tStart=clock();
		//DE_ParseDoc(sContent.c_str(),result,true);//,LOCATION_REQUIRED|ORGANIZATION_REQUIRED|PERSON_REQUIRED
		//中间位自定义的三个输出词性，
		//第二个参数：sUserDefPos:用户自定义的词性标记，最多三种（人名、地名、机构名、媒体等内置，无需设置），不同词类之间采用#分割，如"gms#gjtgj#g"
		
		size_t pHandle=DE_ParseDocE(sContent.c_str(),"a#v#gms",true);//
		tEnd=clock();
		lTime=tEnd-tStart;
		lTotalTime+=lTime;
		lTotalSize+=sContent.size();

		fprintf(fp,"-------------------------------------\nfile:%s\ncontent：\n%s\n\n------------------------------------\n分析结果：\n", vsFileName[i].c_str(), sContent.c_str());
		/*
		for(int k=0;k<=DOC_EXTRACT_TYPE_USER+2;k++)
		{
			fprintf(fp,"%d:%s\n",k+1,DE_GetResult(pHandle,k));
		}*/
		
		fprintf(fp,"Person list:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_PERSON));
		fprintf(fp,"Loc list:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_LOCATION));//,result.entity_list[]);
		fprintf(fp,"Org list:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_ORGANIZATION));//,result.entity_list[DOC_EXTRACT_TYPE_ORGANIZATION]);
		fprintf(fp, "Time:%s\n", DE_GetResult(pHandle, DOC_EXTRACT_TYPE_TIME));//,result.entity_list[DOC_EXTRACT_TYPE_ABSTRACT]);
		fprintf(fp,"Abstract list:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_ABSTRACT));//,result.entity_list[DOC_EXTRACT_TYPE_ABSTRACT]);
		fprintf(fp,"Keyword list:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_KEYWORD));//,result.entity_list[DOC_EXTRACT_TYPE_KEYWORD]);
		fprintf(fp,"Media list:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_MEDIA));//,result.entity_list[DOC_EXTRACT_TYPE_MEDIA]);
		fprintf(fp,"Author list:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_AUTHOR));//,result.entity_list[DOC_EXTRACT_TYPE_AUTHOR]);
		fprintf(fp,"Country:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_COUNTRY));//,result.entity_list[DOC_EXTRACT_TYPE_COUNTRY]);
		fprintf(fp,"Province:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_PROVINCE));//,result.entity_list[DOC_EXTRACT_TYPE_PROVINCE]);
		fprintf(fp,"User1:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_USER));//,result.entity_list[DOC_EXTRACT_TYPE_FOOD]);
		fprintf(fp,"User2:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_USER+1));//,result.entity_list[DOC_EXTRACT_TYPE_TRANS]);
		fprintf(fp,"User3:%s\n",DE_GetResult(pHandle,DOC_EXTRACT_TYPE_USER+2));//,result.entity_list[DOC_EXTRACT_TYPE_APPS]);
		fprintf(fp,"SENTIMENT:%d\n",DE_GetSentimentScore(pHandle));//,result.sentiment_score);
		
		DE_ReleaseHandle(pHandle);

		fTime=(float)lTime/(float)CLOCKS_PER_SEC;//Time cost
		fprintf(fp,"Size=%d Bytes,time=%.2f s,speed=%.2fKB/s\n",sContent.size(),fTime,sContent.size()/fTime/1000);
		//getchar();
	}
	
	// 退出
	DE_Exit();
	fTime=(float)lTotalTime/(float)CLOCKS_PER_SEC;//Time cost
	printf("Total Size=%d bytes,total time=%.2fs,average speed=%.2fKB/s\n",lTotalSize,fTime,lTotalSize/fTime/1000);
	fclose(fp);
//	NLPIR_Exit();
	//getchar();

	return 0;
}

bool fn_vScanFiles(const char* sFolderName, std::vector<std::string>& vsFileName,const char* sFilter)
{//sFilter: "*.txt"
	tstring sDirFiles = sFolderName;	
	sDirFiles += "/";
	tstring sNoSuffixDir = sDirFiles;
	sDirFiles+="*.*";
	//sDirFiles +=sFilter;

#ifndef OS_LINUX

	int iNoFile, hFoundFile=-1;
	struct _finddata_t stFileStat;

	hFoundFile = _findfirst(sDirFiles.c_str(), &stFileStat);
	iNoFile =  (hFoundFile == -1);

	while (!iNoFile)
	{
		if (stFileStat.name[0] == '.')
		{//break;
			//iNoFile = _findnext(hFoundFile, &stFileStat);
		}
		else if(stFileStat.attrib & _A_SUBDIR) 
		{//	滤掉"."和".."	子目录
			tstring newPath=sFolderName;
			newPath+="/";
			newPath+=stFileStat.name;
			fn_vScanFiles(newPath.c_str(),vsFileName,sFilter);
		}
		else if (stricmp(stFileStat.name+strlen(stFileStat.name)-strlen(sFilter),sFilter)==0)
		{
			tstring sFullFilePath =  sNoSuffixDir + stFileStat.name;
			vsFileName.push_back(sFullFilePath);
		}
		iNoFile = _findnext(hFoundFile, &stFileStat);
	};
	if (hFoundFile!=-1)
		_findclose(hFoundFile);

#else

	DIR * dirp;  //目录指针 
	char sFileName[2048];
	char sFilterExt[1024]=".";
	strcpy(sFilterExt,sFilter);
	dirp = opendir(sFolderName);
	if(dirp==NULL) { 	
		//cerr<<" Failure to open the directory " << lpszDir<<endl;
		return false;
	} 

	struct dirent* direntp;                //指向所有找到的文件的指针
	struct stat st;                        //取回的文件的状态 

	while((direntp = readdir(dirp)) != NULL)   //循环读取一个文件,每读取一次dirp指针往后移动
	{
		if((strcmp(direntp->d_name,".")!=0) && (strcmp(direntp->d_name,"..")!=0))
		{		        
			strcpy(sFileName, sNoSuffixDir.c_str());
			strcat(sFileName, direntp->d_name);			
			if(stat(sFileName,&st) == -1) {
				//cerr<<"Error:stat " <<sFileName<<endl;
				continue;                        
			}			
			if((st.st_mode& S_IFMT) == S_IFDIR)
			{//判断是不是一个目录 
				tstring newPath=sFolderName;
				newPath+="/";
				newPath+=direntp->d_name;
				fn_vScanFiles(newPath.c_str(),vsFileName,sFilter);
			}
			else
			{
				tstring sFullFilePath =  sNoSuffixDir + direntp->d_name;
				if(sFullFilePath.rfind(sFilterExt) == sFullFilePath.size()-strlen(sFilterExt))
					vsFileName.push_back(sFullFilePath);
			}

		}//if
	}//while        

	if(dirp != NULL) closedir(dirp);

#endif
	return true;	
}

bool gfn_bReadFile(const char* lpszFilename, string& sFileText) {

	if(!lpszFilename || (strlen(lpszFilename)==0)) {
		return false;
	}

	sFileText = "";

	FILE* fp = fopen(lpszFilename, "rb");

	try{
		if(!fp) {
			return false;
		}//if

		fseek(fp, 0L, SEEK_END);
		long lSize = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		if(lSize>0){
			char* lpszFileText = (char*)calloc(lSize+1, sizeof(char));
			if(!lpszFileText) {
				fclose(fp);
				return false;
			}

			fread(lpszFileText, sizeof(char), lSize, fp);

			sFileText = lpszFileText;
			free(lpszFileText);
		}//if

		fclose(fp);

	}catch(...) {
		if(fp)
			fclose(fp);	
	}//try

	return true;
}//gfn_bReadFile

