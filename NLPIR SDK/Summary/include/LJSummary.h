/***************************************************
*  Copyright (c) 2009. All rights reserved.
*  Procession or use of this file requires a written 
*  license from the author.
*  
*  Created: 2009-12-30
***************************************************/
#ifndef _H_DOCSUMMARY_DLL
#define _H_DOCSUMMARY_DLL

#if defined(OS_LINUX)
	#define DOCSUMMARY_API  extern "C"
#else
#if defined(LJSUMMARY_EXPORTS)
#define DOCSUMMARY_API extern "C"  __declspec(dllexport)
#else
#define DOCSUMMARY_API extern "C"  __declspec(dllimport)
#endif
#endif

#if defined(ICTCLAS_JNI_EXPORTS)||defined(LJSUMMARY_JNI_EXPORTS) 
#define DOCSUMMARY_API 
#endif

#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
/*-----------------------------------------------------------------------
* 功能：初始化
* 参数：sLicenseCode - 授权码
*		sPath-default path
* 返回：true - 成功；false - 失败
* 备注：在进程中此函数必须在其他函数之前调用（只需执行一次）
------------------------------------------------------------------------*/
DOCSUMMARY_API int DS_Init(const char *sPath=0,int nEncoding=GBK_CODE,const char *sLicenseCode=0);

/*-----------------------------------------------------------------------
* 功能：生成单文档摘要
* 参数：sText	    -[IN] 文档内容
*		fSumRate	-[IN] 文档摘要占原文百分比（为0.00则不限制）
*		iSumLen		-[IN] 用户限定的摘要长度  （为0则不限制）
*		bHtmlTagRemove-[IN] 是否需要对原文进行Html标签的去除
* 返回：摘要字符串；出错返回空串
* 备注：在进程中此函数可以执行多次
------------------------------------------------------------------------*/

DOCSUMMARY_API const char* DS_SingleDoc(const char *sText, float fSumRate=0.00, int iSumLen=250,int bHtmlTagRemove=0);

// DOCSUMMARY_API const char* DS_SingleDoc(const char *sText, float fSumRate=0.00, int iSumLen=250,bool bHtmlTagRemove=false);

/*-----------------------------------------------------------------------
* 功能：生成单文档摘要该函数支持多线程，是多线程安全的
* 参数：sResult    -[IN] 摘要内容
*		sText	    -[IN] 文档内容
*		fSumRate	-[IN] 文档摘要占原文百分比（为0.00则不限制）
*		iSumLen		-[IN] 用户限定的摘要长度  （为0则不限制）
*		bHtmlTagRemove-[IN] 是否需要对原文进行Html标签的去除
* 返回：摘要字符串；出错返回空串
* 备注：在进程中此函数可以执行多次
------------------------------------------------------------------------*/

DOCSUMMARY_API const char* DS_SingleDocE(char *sResult,const char *sText, float fSumRate=0.00, int iSumLen=250,int bHtmlTagRemove=0);

// DOCSUMMARY_API const char* DS_SingleDocE(char *sResult,const char *sText, float fSumRate=0.00, int iSumLen=250,bool bHtmlTagRemove=false);

//
/*-----------------------------------------------------------------------
* 功能：生成单文档摘要该函数支持多线程，是多线程安全的
* 参数：sTextFilename	    -[IN] 文档文件名
*		fSumRate	-[IN] 文档摘要占原文百分比（为0.00则不限制）
*		iSumLen		-[IN] 用户限定的摘要长度  （为0则不限制）
*		bHtmlTagRemove-[IN] 是否需要对原文进行Html标签的去除
* 返回：摘要字符串；出错返回空串
* 备注：在进程中此函数可以执行多次
------------------------------------------------------------------------*/
DOCSUMMARY_API const char* DS_FileProcess(const char *sTextFilename, float fSumRate=0.00, int iSumLen=250,int bHtmlTagRemove=0);


//

//退出，释放资源；进程结束前须调用它释放所占用的内存资源
DOCSUMMARY_API void DS_Exit();

//获得错误消息
DOCSUMMARY_API const char* DS_GetLastErrMsg();

#endif //_H_DOCSUMMARY_DLL
