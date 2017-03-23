#include "JZSearchAPI.h"
#include <vector>
#include <string>
#include <io.h>
#include <direct.h>
#include <assert.h>
#include <conio.h>
#include <iostream>
#include <iterator>
using namespace std;

#pragma comment(lib,"JZSearchAPI.lib")
typedef string tstring;

bool gfn_bReadFile(const char* lpszFilename, string& sFileText);
bool fn_vScanFiles(const char* sFolderName, std::vector<std::string>& vsFileName,const char* sFilter);
int JZSearch();
void JZSearchIndex(char *szParagma);
int main(int argc, char* argv[])
{
	//JZSearchIndex(argv[1]);
	if(argc >= 2)
	{
		JZSearchIndex(argv[1]);
	}
	else
	{
		int i = JZSearch();
		if(i <0)
		{
			return -1;
		}
	}


	return 0;
}

int JZSearch()
{
	if (!JZSearch_Init(".\\output\\", ".\\Data\\JZSearch","Field.dat", 512000000, INDEX_ENCODING_GBK_FANTI,0,false,1,"9aFI2|P#5hT`94VK(@LjK("))
	{
		printf("初始化失败");
		return -1;		
	}

	CJZSearcher *pSearcher=new CJZSearcher(SORT_TYPE_RELEVANCE);//按照相关度排序

	if(!pSearcher) {
		return -1;
	}

	string sQuery = "";
	printf("请输入查询内容:\n");
	printf("1: title; 2: content; 3: title+content;\n");
	int n = 0;
	scanf("%d",&n);
	switch(n)
	{
	case 1:
		{
			sQuery += "[FIELD] title [AND] ";
			printf("请输入要查询的title:");
			char szBuff[128] = {0};
			scanf("%s",szBuff);
			sQuery += szBuff;
		}
		break;
	case 2:
		{
			sQuery += "[FIELD] content [AND] ";
			printf("请输入要查询的content:");
			char szBuff[128] = {0};
			scanf("%s",szBuff);
			sQuery += szBuff;
		}
		break;
	case 3:
		{
			sQuery += "[FIELD] title [AND] ";
			printf("请输入要查询的title:");
			char szBuff[128] = {0};
			scanf("%s",szBuff);
			sQuery += szBuff;
			sQuery += "[FIELD] content [AND] ";
			printf("请输入要查询的content:");
			char szBuffstr[128] = {0};
			scanf("%s",szBuffstr);
			sQuery += szBuffstr;
		}
		break;
	}

	string m_sSearchPath = "result.xml";
	//pSearcher->Search(sQuery.c_str(), 0, 1000, m_sSearchPath.c_str());
	vector<int> vIndex;
	pSearcher->Search(sQuery.c_str(), vIndex);
	printf("查询的最终结果是 \n");
	copy (vIndex.begin(), vIndex.end(), ostream_iterator<int>(cout));
	
	//string sResult;
	//gfn_bReadFile(m_sSearchPath.c_str(), sResult);	

//	printf("查询的最终结果是: %s \n", sResult.c_str());

//	printf("394 doc的content is :%s \n" , pSearcher->GetFiledValue(2584, "title"));
	delete pSearcher;
	return 0;
}

void JZSearchIndex(char *szParagma)
{
	if (!JZIndexer_Init(".\\Data\\JZSearch", 0, INDEX_ENCODING_GBK_FANTI,false,1,"9aFI2|P#5hT`94VK(@LjK("))
	{
		printf("初始化失败");
		return ;
	}
	JZIndexer_FieldAdd("title",NULL,FIELD_TYPE_TEXT,true,true,true,true);
	//	//对标题建索引，需要搜索
	JZIndexer_FieldAdd("content",NULL,FIELD_TYPE_TEXT,true,true,true,true);
	//	//对内容建索引，需要搜索
	JZIndexer_FieldAdd("file",NULL,FIELD_TYPE_TEXT,true,true,true,true);
	//	//对内容建索引，需要搜索
	JZIndexer_FieldSave("field.dat");


	vector<string> vsFileName;
	fn_vScanFiles(szParagma, vsFileName,"txt");

	CJZIndexer *pclIndexer = new CJZIndexer("./output/");
	for(int i=0; i<vsFileName.size(); i++) {
		string sTitle = vsFileName[i].c_str();
		string sContent;
		gfn_bReadFile(vsFileName[i].c_str(), sContent);
		pclIndexer->MemIndexing(sTitle.c_str(), "title");
		//WriteLog(theDlg->clBrowseDir.m_vFileList[doc_id].c_str());
		pclIndexer->FileIndexing(sContent.c_str(),"content");
		pclIndexer->MemIndexing(sContent.c_str(),"file");
		printf("Indexing %s completed!\n",sTitle.c_str());
		pclIndexer->AddDoc();
	}
	pclIndexer->Save();
	printf("Indexing create %s!\n", pclIndexer->GetStatus() == 1 ? "succeed":"failed");
	delete pclIndexer;
	printf("Indexing create completed!\n");
	JZIndexer_Exit();
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