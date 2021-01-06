// ClusterSystem.cpp : Defines the entry point for the console application.
//
#include "../API/LJSummary.h"
#include <vector>
#include <string>
#include <time.h>
#ifndef OS_LINUX
#include <io.h>
#include <direct.h>
#include <assert.h>
#include <conio.h>
#include <string.h>
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
//#pragma comment(lib, "LJSummary.lib")
#ifndef OS_LINUX
#ifndef WIN64
#pragma comment(lib, "../../../bin/Summary/LJSummary.lib")
#else
#pragma comment(lib, "../../../bin/Summary/x64/LJSummary.lib")
#endif
#endif

bool gfn_bReadFile(const char* lpszFilename, string& sFileText);
bool gfn_vScanFiles(const char* sFolderName, std::vector<std::string>& vsFileName, const char* sFilter);
int main(int argc, char* argv[])
{//D:/NLPIR D:/NLPIR/test/test.txt  D:/NLPIR/test/test.txt  D:/NLPIR/test/test2.txt 
	if (argc <3)
	{
		printf("usage: %s <Data_Path> <Input_File1> ... \n",argv[0]);
		return 1;
	}
	if(!DS_Init(argv[1],UTF8_CODE)) 
	{//UTF8
		printf("DS_Init(%s) failed! reason is %s\n", argv[1], DS_GetLastErrMsg());
		return 1;
	}
	printf("DS_Init(%s) success!\n", argv[1]);
	clock_t tStart, tEnd;
	long lTime, lTotalTime = 0, lTotalSize = 0;
	float fTime;
	int lengs[6] = {50,100,200,300,400,500};
	string sResult;
	for (int i = 2; i < argc; i++)
	{
		sResult = argv[i];
		sResult += "_summary.txt";
		string sContent;
		gfn_bReadFile(argv[i], sContent);
		if (sContent.empty())
		{//
			printf("Error read file %s\n", argv[i]);
			continue;
		}
		FILE *fp = fopen(sResult.c_str(), "wb");
		if (fp==NULL)
		{
			printf("Error writing file %s\n", sResult.c_str());
			continue;
		}
		const char* pResult;
		for (size_t j = 0; j < 6; j++)
		{
			tStart = clock();
			pResult = DS_SingleDoc(sContent.c_str(), 0, lengs[j], true);
			tEnd = clock();
			lTime = tEnd - tStart;
			fTime = (float)lTime / (float)CLOCKS_PER_SEC;//Time cost
			fprintf(fp, "%d bytes summary(Size=%d Bytes,time=%.2f s,speed=%.2fKB/s): %s\n", lengs[j], sContent.size(), fTime, sContent.size() / fTime / 1000,pResult);
			printf("%d bytes summary(Size=%d Bytes,time=%.2f s,speed=%.2fKB/s): %s\n", lengs[j],  sContent.size(), fTime, sContent.size() / fTime / 1000, pResult);
		}
		printf("%s summary finished!\n", argv[i]);
		fclose(fp);
	}
	DS_Exit();
	return 0;
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

