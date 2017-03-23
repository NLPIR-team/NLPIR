#include "LJCluster.h"
#include <string>

using namespace std;

#pragma comment(lib,"LJCluster.lib")


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
			if(!lpszFilename) {
				fclose(fp);
				return false;
			}

			fread(lpszFileText, sizeof(char), lSize,fp);
			lpszFileText[lSize]=0;
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

void gfn_vReplaceSubstr(string& sString, string sSubOld, string sSubNew) {

	if(sString.empty())
		return;

	if(sSubOld.empty())
		return;

	int iPos = 0;

	while(iPos != string::npos) {

		// 抽取出各个记录条	
		iPos = sString.find(sSubOld, iPos);

		if(iPos == string::npos)
			continue;

		sString.replace(iPos, sSubOld.size(), sSubNew);

		iPos += sSubNew.size();

	}

	return;
}

int main()
{
	if(!CLUS_Init("./Data/Cluster"))
	{
		const char* sMsg = CLUS_GetLastErrMsg();
		printf("分类模块初始化失败: %s\n",sMsg);
		return -1;
	}
	
	CLUS_CleanData();
	CLUS_SetParameter(3, 2);
	char  sText[100] = "中华人民共和国正式成立的时间是1949.10.1，代表人名正式当家作主的日子到了";
	CLUS_AddFile("旅游业已成为西部地区的重要产业.txt", "旅游业");
	
	string sResult;
	CLUS_GetLatestResult("Result.xml");

	gfn_bReadFile("Result.xml", sResult);
	gfn_vReplaceSubstr(sResult, "\n", "\r\n");


	printf("sResult : %s \n",sResult.c_str());
	CLUS_Exit();
	return 0;
}
