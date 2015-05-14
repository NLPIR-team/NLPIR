/***************************************************
 * Copyright (c) 2006. All rights reserved.
 * Posession or use of this file requires a written 
 * license from the author.
 *  
 * Author:  Lingjoin
 * Email:	lingjoin@lingjoin.com
 * Created: 2009-12-26
 ***************************************************/
#ifndef _H_HTMLPARSER_API_INCLUDED
#define _H_HTMLPARSER_API_INCLUDED

#ifdef OS_LINUX
#define HPARSER_API extern "C" 
#else
#ifdef LJHTMLPARSER_EXPORTS
#define HPARSER_API extern "C" __declspec(dllexport)
#else
#define HPARSER_API extern "C"  __declspec(dllimport)
#endif
#endif


//初始化
HPARSER_API int HPR_Init(const char * sDataPath=0,const char *sLicenseCode=0);

//退出，释放资源
HPARSER_API void HPR_Exit();

//对HTML进行解析（只有执行此函数后才能HPR_GetContent）
HPARSER_API bool HPR_ParseFile(const char *sHtmlFilename);
HPARSER_API bool HPR_ParseBuffer(const char *sHtmlBuffer, int nLen);

//提取正文，返回NULL时表示失败（调用TE_GetLastErrMsg可获得错误提示）
HPARSER_API const char* HPR_GetContent();

//提取标题，返回NULL时表示失败（调用TE_GetLastErrMsg可获得错误提示）
HPARSER_API const char* HPR_GetTitle();

//获得错误提示消息
HPARSER_API const char* HPR_GetLastErrMsg();

#endif //_H_HTMLPARSER_API_INCLUDED