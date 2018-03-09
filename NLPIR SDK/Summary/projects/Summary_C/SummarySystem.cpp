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
#define makeDirectory(x) mkdir(x, 0777)    // �ⲽ����룬�����ļ���ֻ��
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

//bool fn_vScanFiles(std::string& sFolderName, std::vector<std::string>& vsFileName,tstring& sFilter);
bool gfn_bReadFile(const char* lpszFilename, string& sFileText);
bool fn_vScanFiles(const char* sFolderName, std::vector<std::string>& vsFileName,const char* sFilter);
int main(int argc, char* argv[])
{

	if (argc != 2){
		printf("usage: SummarySystem <CorpusDir>\n");
		return 1;
	}
	FILE *fp=fopen("result.txt","wb");
	// ��ʼ��	
	//if(!DS_Init("../../Data/Summary/")) {
	if(!DS_Init("D:/NLPIR",GBK_CODE)) {//UTF8
		printf("%s\n", DS_GetLastErrMsg());
		return 1;
	}

	// ɨ��
	int nRealCount;
	vector<string> vsFileName;
	fn_vScanFiles(argv[1], vsFileName,"txt");

	//fn_vScanFiles(std::string& sFolderName, std::vector<std::string>& vsFileName,tstring& sFilter)
	string sOutput = "";

	// ����
	printf("�������£�Total %d��...\n",vsFileName.size());
	int i;
	clock_t tStart,tEnd;
	long lTime,lTotalTime=0,lTotalSize=0;
	float fTime;

	for(i=0; i<vsFileName.size(); i++) {

		string sContent;
		gfn_bReadFile(vsFileName[i].c_str(), sContent);
		tStart=clock();
		const char* pResult;
		/*
		pResult = DS_SingleDoc(sContent.c_str(), 0, 400, 0);
		
		fprintf(fp,"800summary--%s\n",pResult);
		
		pResult = DS_SingleDoc(sContent.c_str(), 0, 50,true);

		fprintf(fp,"50summary---%s\n",pResult);
*/
		pResult = DS_SingleDoc(sContent.c_str(), 0,50,true);
		printf("50: %s\n", pResult);
		pResult = DS_SingleDoc(sContent.c_str(), 0,100,true);
		printf("100: %s\n", pResult);

		pResult = DS_SingleDoc(sContent.c_str(), 0,200,true);
		printf("200: %s\n", pResult);

		pResult = DS_SingleDoc(sContent.c_str(), 0,300,true);
		printf("300: %s\n", pResult);

		fprintf(fp,"50summary---%s\n",pResult);
		fflush(fp);
		tEnd=clock();
		lTime=tEnd-tStart;
		lTotalTime+=lTime;
		lTotalSize+=sContent.size();
		if(!pResult) {
			printf("%s\n", DS_GetLastErrMsg());
			continue;
		}	
		printf("-------------------------------------\n�ļ�:%s\n���ݣ�\n%s\n\n------------------------------------\nժҪ��\n%s\n", vsFileName[i].c_str(), sContent.c_str(), pResult);
		//sOutput += pResult;
		//sOutput += "\n";
		fTime=(float)lTime/(float)CLOCKS_PER_SEC;//Time cost
		printf("Size=%d Bytes,time=%.2f s,speed=%.2fKB/s\n",sContent.size(),fTime,sContent.size()/fTime/1000);
		//getchar();
	}
	fclose(fp);
	// �˳�
	DS_Exit();
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
	sDirFiles+="*.";
	sDirFiles +=sFilter;

#ifndef OS_LINUX

	int iNoFile, hFoundFile=-1;
	struct _finddata_t stFileStat;

	hFoundFile = _findfirst(sDirFiles.c_str(), &stFileStat);
	iNoFile =  (hFoundFile == -1);

	while (!iNoFile)
	{
		if (stFileStat.name[0] == '.')
		{
			iNoFile = _findnext(hFoundFile, &stFileStat);
		}
		else if(stFileStat.attrib & _A_SUBDIR)
		{	//	�˵�"."��".."	
		}
		else {
			tstring sFullFilePath =  sNoSuffixDir + stFileStat.name;
			vsFileName.push_back(sFullFilePath);
		}
		iNoFile = _findnext(hFoundFile, &stFileStat);
	};
	if (hFoundFile!=-1)
		_findclose(hFoundFile);

#else

	DIR * dirp;  //Ŀ¼ָ�� 
	char sFileName[2048];
	char sFilterExt[1024]=".";
	strcpy(sFilterExt,sFilter);
	dirp = opendir(sFolderName);
	if(dirp==NULL) { 	
		//cerr<<" Failure to open the directory " << lpszDir<<endl;
		return false;
	} 

	struct dirent* direntp;                //ָ�������ҵ����ļ���ָ��
	struct stat st;                        //ȡ�ص��ļ���״̬ 

	while((direntp = readdir(dirp)) != NULL)   //ѭ����ȡһ���ļ�,ÿ��ȡһ��dirpָ�������ƶ�
	{
		if((strcmp(direntp->d_name,".")!=0) && (strcmp(direntp->d_name,"..")!=0))
		{		        
			strcpy(sFileName, sNoSuffixDir.c_str());
			strcat(sFileName, direntp->d_name);			
			if(stat(sFileName,&st) == -1) {
				//cerr<<"Error:stat " <<sFileName<<endl;
				continue;                        
			}			
			if((st.st_mode& S_IFMT) == S_IFDIR) {     //�ж��ǲ���һ��Ŀ¼ 
			}else {
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

