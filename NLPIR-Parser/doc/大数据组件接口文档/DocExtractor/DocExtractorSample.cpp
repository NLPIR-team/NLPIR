// ClusterSystem.cpp : Defines the entry point for the console application.
//
#include "../API/DocExtractor.h"
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

	// 初始化	
	if(!DE_Init("../../")) {
		printf("%s\n", DE_GetLastErrMsg());
		return 1;
	}

	// 扫描
	int nRealCount;
	vector<string> vsFileName;
	fn_vScanFiles(argv[1], vsFileName,"txt");

	//fn_vScanFiles(std::string& sFolderName, std::vector<std::string>& vsFileName,tstring& sFilter)
	string sOutput = "";

	// 加载
	printf("分析文章（Total %d）...\n",vsFileName.size());
	int i;
	clock_t tStart,tEnd;
	long lTime,lTotalTime=0,lTotalSize=0;
	float fTime;
	_tDocExtractResult result;
	for(i=0; i<vsFileName.size(); i++) {
		string sContent;
		gfn_bReadFile(vsFileName[i].c_str(), sContent);
		tStart=clock();
		DE_ParseDoc(sContent.c_str(),result,true);//,LOCATION_REQUIRED|ORGANIZATION_REQUIRED|PERSON_REQUIRED
		tEnd=clock();
		lTime=tEnd-tStart;
		lTotalTime+=lTime;
		lTotalSize+=sContent.size();
		printf("-------------------------------------\n文件:%s\n内容：\n%s\n\n------------------------------------\n分析结果：\n", vsFileName[i].c_str(), sContent.c_str());
		printf("Person list:%s\n",result.entity_list[DOC_EXTRACT_TYPE_PERSON]);
		printf("Loc list:%s\n",result.entity_list[DOC_EXTRACT_TYPE_LOCATION]);
		printf("Org list:%s\n",result.entity_list[DOC_EXTRACT_TYPE_ORGANIZATION]);
		printf("Abstract list:%s\n",result.entity_list[DOC_EXTRACT_TYPE_ABSTRACT]);
		printf("Keyword list:%s\n",result.entity_list[DOC_EXTRACT_TYPE_KEYWORD]);
		printf("Media list:%s\n",result.entity_list[DOC_EXTRACT_TYPE_MEDIA]);
		printf("Author list:%s\n",result.entity_list[DOC_EXTRACT_TYPE_AUTHOR]);
		printf("Country:%s\n",result.entity_list[DOC_EXTRACT_TYPE_COUNTRY]);
		printf("Province:%s\n",result.entity_list[DOC_EXTRACT_TYPE_PROVINCE]);
		printf("Food:%s\n",result.entity_list[DOC_EXTRACT_TYPE_FOOD]);
		printf("Transportation:%s\n",result.entity_list[DOC_EXTRACT_TYPE_TRANS]);
		printf("Apps:%s\n",result.entity_list[DOC_EXTRACT_TYPE_APPS]);
		printf("SENTIMENT:%d\n",result.sentiment_score);


		//sOutput += pResult;
		//sOutput += "\n";
		fTime=(float)lTime/(float)CLOCKS_PER_SEC;//Time cost
		printf("Size=%d Bytes,time=%.2f s,speed=%.2fKB/s\n",sContent.size(),fTime,sContent.size()/fTime/1000);
		getchar();
	}

	// 退出
	DE_Exit();
	fTime=(float)lTotalTime/(float)CLOCKS_PER_SEC;//Time cost
	printf("Total Size=%d bytes,total time=%.2fs,average speed=%.2fKB/s\n",lTotalSize,fTime,lTotalSize/fTime/1000);

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
				newPath+=stFileStat.name;
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

