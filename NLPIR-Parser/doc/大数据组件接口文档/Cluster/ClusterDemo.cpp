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

		// ��ȡ��������¼��	
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
		printf("����ģ���ʼ��ʧ��: %s\n",sMsg);
		return -1;
	}
	
	CLUS_CleanData();
	CLUS_SetParameter(3, 2);
	char  sText[100] = "�л����񹲺͹���ʽ������ʱ����1949.10.1������������ʽ�������������ӵ���";
	CLUS_AddFile("����ҵ�ѳ�Ϊ������������Ҫ��ҵ.txt", "����ҵ");
	
	string sResult;
	CLUS_GetLatestResult("Result.xml");

	gfn_bReadFile("Result.xml", sResult);
	gfn_vReplaceSubstr(sResult, "\n", "\r\n");


	printf("sResult : %s \n",sResult.c_str());
	CLUS_Exit();
	return 0;
}
