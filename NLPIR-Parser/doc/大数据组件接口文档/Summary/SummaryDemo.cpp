#include "LJSummary.h"
#include <io.h>
#include <direct.h>
#include <assert.h>
#include <conio.h>
#include <string>
#include <vector>
using namespace::std;
#pragma comment(lib, "LJSummary.lib")

typedef string tstring;
bool gfn_bReadFile(const char* lpszFilename, string& sFileText);
bool fn_vScanFiles(const char* sFolderName, std::vector<std::string>& vsFileName,const char* sFilter);

int main(int argc,char* argv[])
{
		if(!DS_Init("",GBK_CODE))
		{
			printf("sErrorMsg : %s \n", DS_GetLastErrMsg());
			return -1;
		}

		vector<string> vsFileName;
		fn_vScanFiles(argv[1], vsFileName,"txt");

		string sOutput = "";

		// ����
		printf("�������£�Total %d��...\n",vsFileName.size());

		for(int i=0; i<vsFileName.size(); i++) {
			string sContent;
			gfn_bReadFile(vsFileName[i].c_str(), sContent);
			const char* sSummary = DS_SingleDoc(sContent.c_str());
			printf("[1]��ƪ���µ�ժҪ��SingleDoc��%s \n", sSummary);

			char szSummary[1024] = {0};
			const char* sRes = DS_SingleDocE(szSummary,sContent.c_str());
			printf("[2]��ƪ���µ�ժҪ��SingleDocE��%s \n, [3]%s\n", sRes,szSummary);
		}
		//const char* DS_SingleDoc(const char *sText, float fSumRate=0.00, int iSumLen=250);
		DS_Exit();
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
		{//	�˵�"."��".."	��Ŀ¼
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
			if((st.st_mode& S_IFMT) == S_IFDIR)
			{//�ж��ǲ���һ��Ŀ¼ 
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

