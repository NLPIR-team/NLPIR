/***************************************************
*  Copyright (c) 2011. All rights reserved.
*  Procession or use of this file requires a written 
*  license from the author.
*  
*  Created: 2011-05-20
***************************************************/
#ifndef _H_SENTIMENT_DLL
#define _H_SENTIMENT_DLL


#ifdef OS_LINUX
#define SENTIMENT_API extern "C" 
#else
#ifdef LJSENTIMENT_EXPORTS
#define SENTIMENT_API extern "C" __declspec(dllexport)
#else
#define SENTIMENT_API extern "C"  __declspec(dllimport)
#endif
#endif

#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
/*-----------------------------------------------------------------------
* 功能：初始化
* 参数：sLicenseCode           - [IN]  函数调用码
* 返回：true - 成功；false - 失败
* 备注：在进程中此函数必须在其他函数之前调用（只需执行一次）
------------------------------------------------------------------------*/
SENTIMENT_API bool ST_Init(const char *sInitDirPath=0,int encode=GBK_CODE,const char* sLicenseCode="");

/*-----------------------------------------------------------------------
* 功能：单条对象观点信息的分析和抽取
* 参数：sTitle           - [IN]  输入文章标题
*		sContent         - [IN]  输入文章内容
*       sObject			 - [IN]  输入分析对象名称
* 返回：输出结果字符串（xml格式）
* 备注：在进程中此函数可以执行多次，支持多线程执行
------------------------------------------------------------------------*/

SENTIMENT_API const char* ST_GetOneObjectResult(const char* sTitle, const char* sContent, const char* sObject);

/*-----------------------------------------------------------------------
* 功能：批量对象观点信息的分析和抽取
* 参数：sTitle           - [IN]  输入文章标题
*		sContent         - [IN]  输入文章内容
*       sObjectRuleFile	 - [OUT] 输入分析对象配置文件
* 返回：输出结果字符串（xml格式）
* 备注：在进程中此函数可以执行多次，支持多线程执行
------------------------------------------------------------------------*/
SENTIMENT_API const char* ST_GetMultiObjectResult(const char* sTitle, const char* sContent, const char* sObjectRuleFile);

/*-----------------------------------------------------------------------
* 功能：批量导入导出情感词典
* 参数：sPositiveFile           - [IN]  积极词典文件名；
*		sNegativeFile         - [IN]   积极词典文件名
*       bInputOutput	 - [IN] true: 导入词典到系统中； false:导出系统词典到文本文件
* 返回：int: 1:成果；0:失败
* 备注：
------------------------------------------------------------------------*/
SENTIMENT_API int ST_SentiDictIO(const char* sPositiveFile,const char* sNegativeFile,bool bInputOutput=false);


//退出，释放资源；进程结束前须调用它释放所占用的内存资源
SENTIMENT_API void ST_Exit();

//获得最近一次的错误消息
SENTIMENT_API const char* ST_GetLastErrMsg();

#endif //_H_SENTIMENT_DLL
