// DupRemove.cpp : 定义控制台应用程序的入口点。
//

#include "../LJRedupRemover.h"

#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <stdio.h>
#ifdef OS_LINUX
#include <dirent.h>
#include <unistd.h> 
#else
#include <direct.h>
#include <io.h>

#endif
#include <sys/stat.h>
#include <ctype.h>
using namespace std;
typedef  std::string  tstring;
//support subtree
bool gfn_vScanFiles(const char* sFolderName, std::vector<std::string>& vsFileName,const char* sFilter)
{//sFilter: "*.txt"
	tstring sDirFiles = sFolderName;	
	sDirFiles += "/";
	tstring sNoSuffixDir = sDirFiles;
	sDirFiles+="*.*";
	//sDirFiles +=sFilter;
#ifndef OS_LINUX
	intptr_t iNoFile, hFoundFile=-1;
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
			gfn_vScanFiles(newPath.c_str(),vsFileName,sFilter);
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
				gfn_vScanFiles(newPath.c_str(),vsFileName,sFilter);
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
			if(!lpszFilename) {
				fclose(fp);
				return false;
			}

			fread(lpszFileText, sizeof(char), lSize,fp);

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

int main(int argc, char* argv[])
{
	/*
	FILE *fp = fopen("Data.txt", "wb");
	if (fp!=NULL)
	{
		fwrite("", 0, 0, fp);
		fclose(fp);
	}
	*/
	if (!RR_Init("Data.txt", "./",false,0,UTF8_CODE))
	{
		printf("%s\r\n", RR_GetLastErrMsg());
		printf("去重组件初始化失败，请退出并检查！该联系www.nlpir.org/或者新浪微博 @ICTCLAS张华平博士 ！\n");
		return-1;
	}

	vector<string> fileDir;
	string path = argv[1];
	string sContent = "";
	if(!gfn_vScanFiles(path.c_str(),fileDir,".txt"))
	{
		printf("获取文件夹中文件失败......\n");
		system("pause");
		return -1;
	}
	string sFilename;
	char *pcFindAll = new char[65565];
	pcFindAll[0]=0;
	char sID[100];
	for (int i = 0; i < fileDir.size();i++)
	//for (int i = 0; i < 10;i++)
	{
		sFilename = fileDir.at(i);
		gfn_bReadFile(sFilename.c_str(), sContent);
		/*
		if (i<5)
		{
			sContent="局申请绿皮车预算公开11人被困电梯求救无效后在墙上挖洞自救(图)新闻视频：桥下彻与右翼分子会谈 拍案对骂险动手专栏 | 农民的房子为何不计入GDP 揭开外逃贪官保护层国际 | 日本女大臣:去不去参拜不该由他国说三道四法国道达尔公司总裁深夜在莫斯科遇空难身亡财经 | 多地社保现运动式征缴扩面:任务不完成不收队院士反思塔里木油田会战：急于求成 造成极大资源浪费";
		}
		else
		{
			sContent="大众新速腾车主不接受召回方案 在美受损车辆国考最热职位竞争比达1300:1 有700余职位零报冯仑隐退江湖还是投身理想城 实惠走进校园免费送福利科技 |[第一线]苍井空做内衣电商：半数买家为男性苹果发布iOS 8.1 升级指南 iPad销量连续三个季度下滑丛林偶遇世界最大蜘蛛似幼犬 英一家人养145只动物同住时尚 | 抢镜必备“一抹蚊子血” 高圆圆周迅新婚娇美热点 | 听军事家解析时局热点 体育赛事一网打尽关注 | 协力找马航失联客机 昌平苹果甜蜜的选择";
		}*/
		sprintf(sID,"%d",i);
		sContent += "\r\n";
		if (RR_FileProcess(sContent.c_str(), sFilename.c_str()) == 1)
		//if (RR_FileProcess(sContent.c_str(), sFilename.c_str()) == 1)
		//if (RR_FileProcessE(sFilename.c_str()) == 1)
		{
			//memset(pcFindAll, 0, 65565);
			RR_FindRepeat(pcFindAll, true);//可不输出中间过程
			printf("sID=%s FindAllRepeat are : %s \n",sFilename.c_str(),pcFindAll);
		}
	}

	if (pcFindAll != NULL)
	{
		delete[] pcFindAll;
		pcFindAll = NULL;
	}
	
	RR_Output("RepeatFile.txt");
	RR_SaveHistoryData("Data.txt");
	RR_Exit();
	return 0;
}

