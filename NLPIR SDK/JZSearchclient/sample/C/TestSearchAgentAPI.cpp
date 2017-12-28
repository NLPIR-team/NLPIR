// TestSearchAgentAPI.cpp : Defines the entry point for the console application.
//
#include "JZSearchAgentAPI.h"
//#include "../../Utility/Utility.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
//Linux

#ifdef WIN64
#pragma comment(lib, "../../../bin/JZSearch/x64/JZSearchAgentAPI.lib")
#else
#ifdef	_WIN32
#pragma comment(lib, "../../../bin/JZSearch/JZSearchAgentAPI.lib")
#endif
#endif 

#ifndef _WIN32
	#define _stricmp(X,Y) strcasecmp((X),(Y))
	#define stricmp(X,Y) strcasecmp((X),(Y))
	#define strnicmp(X,Y,Z) strncasecmp((X),(Y),(Z))
	#define _fstat(X,Y)     fstat((X),(Y))
	#define _fileno(X)     fileno((X))
	#define _stat           stat
	#define _getcwd         getcwd
	#define _off_t          off_t
	#define PATH_DELEMETER  "/"
	#include <unistd.h>
#else
	#pragma warning(disable:4786)
	#define PATH_DELEMETER  "\\"
	#include <direct.h>
#endif
int g_iPort;
char g_sServerIP[1024];
/*
bool client_init(const char *XMLfile)
{
	char *pXMLContent;
	int nSize=ReadFile(XMLfile,&pXMLContent);
	char sValue[1024];
	if (nSize==0)
	{//初始化失败
		sprintf(sValue,"Error read %s\n",XMLfile);
		WriteError(sValue);
		return false;
	}

	GetXMLItemValue(pXMLContent,"ServerIP",g_sServerIP);

	GetXMLItemValue(pXMLContent,"Port",sValue);
    g_iPort = atoi(sValue);

	
	GetXMLItemValue(pXMLContent,"Language",sValue);
	g_nLangType=LANGUAGE_TYPE_CHINESE;	
	if( strncmp(sValue,"Minor",5)==0)
	{
		g_nLangType=LANGUAGE_TYPE_UNKNOWN;	
	}	

	delete [] pXMLContent;//added in 2011/10/20
	pXMLContent=0;
	return true;
}*/
int main(int argc, char **argv)
{
	//char *pTmp=new char[100];
	//return 1;
	const char *pResult=0;
	char sLine[2000];

	char sDefaultDir[1000]="";//defaulted dir
	_getcwd(sDefaultDir,1000);//get default dir
	
	char sAgentXMLFile[1024],sResultFile[1024];
	strcpy(sAgentXMLFile,sDefaultDir);
	strcat(sAgentXMLFile,PATH_DELEMETER);
	strcpy(sResultFile,sAgentXMLFile);
	strcat(sAgentXMLFile,"SearchAgent.xml");
	strcat(sResultFile,"Result.html");
	/*
	client_init(sAgentXMLFile);

	char *pXMLFile=0;
	ReadFile(sAgentXMLFile,&pXMLFile);
	char sVal[10]="";
	GetXMLItemValue(pXMLFile,"IndexNo",sVal);
	if (sVal[0]==0)
	{
		strcpy(sVal,"1");
	}
	*/
	char sCmd[1000]="[CMD] ";
	/*<index><no>1</no><cmd>[field] groupname [and] USER_B4E51AB56CF0AF54141E0C94D6E9BF96_GROUP</cmd></index>
		*/	//
	//delete [] pXMLFile;
	char sVal[10]="1";
	//注意设置 IP地址和端口号
	//g_sServerIP,g_iPort

	char sNewCmd[1024];
	const char * pResultBuf;
	if (argc==1)
	{
		printf("Please query\n");
		gets(sLine);

		while (sLine[0]!='q'&&sLine[0]!='Q')
		{
			if (strstr(sLine,"<index>"))
			{//自己拼写新版串
				strcpy(sNewCmd,sLine);
			}
			else
			{
				sprintf(sNewCmd,"<index><no>%s</no><cmd>%s</cmd></index>",sVal,sLine);
			}
			/*
			jzsearch_query_client(sAgentXMLFile,sNewCmd,
				0,30,sResultFile,false);
			nCount=ReadFile(sResultFile,&pResult);
			delete [] pResult;
			*/
			pResultBuf=jzsearch_query_client(sNewCmd,0,30,g_sServerIP,g_iPort);

			/*
			FILE *fp=fopen("Result2.xml","wt");
			fwrite(pResultBuf,strlen(pResultBuf),1,fp);
			fclose(fp);*/
			printf("%s",pResultBuf);
			jzsearch_query_client_exit();//记住，一定要释放内存
			printf("Please query\n");
			gets(sLine);
		}

		jzsearch_query_client_exit();
		return 0;
	}
	
	//Quit/Reload/Merge
	if( strnicmp(argv[1],"QUIT",4)!=0&&
		strnicmp(argv[1],"RESET",5)!=0&&
		strnicmp(argv[1],"RELOAD",6)!=0&&
		strnicmp(argv[1],"VER",3)!=0&&
		strnicmp(argv[1],"MERGE",5)!=0&&
		strnicmp(argv[1],"Backup",6)!=0&&
		strnicmp(argv[1],"Index",5)!=0&&
		strnicmp(argv[1],"Restore",7)!=0&&
		strnicmp(argv[1],"del",3)!=0&&
		strnicmp(argv[1],"where-del",7)!=0&&
		strnicmp(argv[1],"where-update",7)!=0&&
		strnicmp(argv[1],"blacklist",7)!=0&&
		strnicmp(argv[1],"expand",5)!=0
		)
	{
		sCmd[0]=0;
	}

	for (int i=1;i<argc;i++)
	{
		strcat(sCmd,argv[i]);
		strcat(sCmd," ");
	}

	if (strstr(sCmd,"<index>"))
	{//自己拼写新版串
		strcpy(sNewCmd,sLine);
	}
	else
	{
		sprintf(sNewCmd,"<index><no>%s</no><cmd>%s</cmd></index>",sVal,sCmd);
	}

	pResult=jzsearch_query_client(sNewCmd,0,300,g_sServerIP,g_iPort);
	printf("%s",pResult);
	jzsearch_query_client_exit();
	return 0;
}

