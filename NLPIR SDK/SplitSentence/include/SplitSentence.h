/****************************************************************************
*
* NLPIR SplitSentence分句系统 Copyright (c) 2000-2017
*     Dr. Kevin Zhang (Hua-Ping Zhang)
*     All rights reserved.
*
* This file is the confidential and proprietary property of
* Kevin Zhang and the possession or use of this file requires
* a written license from the author.
* Filename: 
* Abstract:
*          SplitSentence.h: definition of NLPIR SplitSentence分句系统 system API
* Author:   Kevin Zhang
*          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
*			Weibo: http://weibo.com/drkevinzhang
*			Homepage: http://www.nlpir.org
* Date:     2013-12-19
*
* Notes:
*
****************************************************************************/
#if !defined(__NLPIR_SPLIT_SENTENCE_H_INCLUDED__)
#define __NLPIR_SPLIT_SENTENCE_H_INCLUDED__

#ifdef OS_LINUX
#define SPLITSENTENCE_API extern "C" 
#else
#ifdef SPLITSENTENCE_EXPORTS
#define SPLITSENTENCE_API extern "C" __declspec(dllexport)
#else
#define SPLITSENTENCE_API extern "C" __declspec(dllimport)
#endif
#endif

#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
#define UTF8_FANTI_CODE GBK_CODE+4//UTF8编码
/*********************************************************************
*
*  Func Name  : SS_Init
*
*  Description: Init SplitSentence
*               The function must be invoked before any operation listed as following
*
*  Parameters : const char * sInitDirPath=NULL
*				 sDataPath:  Path where Data directory stored. 指的是Data所在的目录，如 D:/NLPIR/Data，则只需要输入 D:/NLPIR
*				 the default value is NULL, it indicates the initial directory is current working directory path
*				 sLicenseCode: license code for unlimited usage. common user ignore it
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2017-8-26
*********************************************************************/
SPLITSENTENCE_API int SS_Init(const char * sDataPath = 0, const char*sLicenceCode = 0);
/*********************************************************************
*
*  Func Name  : SS_Exit
*
*  Description: Exit SplitSentence
*              
*
*  Parameters : void
*  Returns    : void
*  Author     : Kevin Zhang
*  History    :
*              1.create	2017-8-26
*********************************************************************/
SPLITSENTENCE_API void SS_Exit();
/*********************************************************************
*
*  Func Name  : SS_GetSentence
*
*  Description: SS_GetSentence
*               
*  Parameters : const char * sText
*				1.第一次调用的时候，该参数为整个文本；输出该文的第一个句子内容；
*				2.后续调用的时候，该参数为NULL，将输出上次输入文本的接下来的句子内容；直到没有结果，输出为空为止
*				encode: 输入的编码，第一次生成句子的时候有效，后续不需要输入，默认为第一次的值;
*				
*  Returns    : const char*
				如果有句子，则返回句子的内容；
				否则返回空字符串。""
*  Author     : Kevin Zhang
*  History    :
*              1.create 2017-8-26
*********************************************************************/
SPLITSENTENCE_API const char* SS_GetSentence(const char * sText = 0, int encode = GBK_CODE);
/*********************************************************************
*
*  Func Name  : SS_GetLastErrorMsg
*
*  Description: SS_GetLastErrorMsg 
*
*  Parameters : void
*
*  Returns    : const char*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2017-8-26
*********************************************************************/
SPLITSENTENCE_API const char * SS_GetLastErrorMsg();
#endif
