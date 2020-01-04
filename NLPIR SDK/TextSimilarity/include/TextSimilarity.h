/****************************************************************************
*
* NLPIR/ICTCLAS Lexical Analysis System Copyright (c) 2000-2018
*     Dr. Kevin Zhang (Hua-Ping Zhang)
*     All rights reserved.
*
* This file is the confidential and proprietary property of
* Kevin Zhang and the possession or use of this file requires
* a written license from the author.
* Filename:
* Abstract:
*          TextSimilarity.h: definition of the Text Similarity system API
* Author:   Kevin Zhang
*          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
*			Weibo: http://weibo.com/drkevinzhang
*			Homepage: http://www.nlpir.org
* Date:     2018-2-28
*
* Notes:
*
****************************************************************************/
#if !defined(__TS_TEXT_SIMILARITY_H_INCLUDED__)
#define __TS_TEXT_SIMILARITY_H_INCLUDED__

#ifdef OS_LINUX
#define TEXTSIMILARITY_API extern "C" 
#else
#ifdef TEXTSIMILARITY_EXPORTS
#define TEXTSIMILARITY_API extern "C" __declspec(dllexport)
#else
#define TEXTSIMILARITY_API extern "C"  __declspec(dllimport)
#endif
#endif

//计算相似度的模型选择
#define SIM_MODEL_CHAR 1//字模型，速度最快，适用于相对规范的短文本
#define SIM_MODEL_WORD 2//词模型，速度适中，常规适用于正常规范的长文档
#define SIM_MODEL_KEY 3//主题词模型，速度最慢，考虑语义最多，适合于复杂文本

#define UNKNOWN_CODE -1//如果是各种编码混合，设置为-1，系统自动检测，并内部转换。会多耗费时间，不推荐使用
#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
#define UTF8_FANTI_CODE GBK_CODE+4//UTF8编码

/*********************************************************************
*
*  Func Name  : Init
*
*  Description: Init Text Similarity
*               The function must be invoked before any operation listed as following
*
*  Parameters : const char * sInitDirPath=NULL
*				 sDataPath:  Path where Data directory stored.
*				 the default value is NULL, it indicates the initial directory is current working directory path
*				 encode: encoding code;
*				 sLicenseCode: license code for unlimited usage. common user ignore it
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
TEXTSIMILARITY_API int TS_Init(const char * sDataPath = 0, int encode = GBK_CODE, const char*sLicenceCode = 0);
/*********************************************************************
*
*  Func Name  : TS_Exit
*
*  Description: Exist Text Similarity and free related buffer
*               Exit the program and free memory
*				 The function must be invoked while you needn't any lexical anlysis
*
*  Parameters : None
*
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2002-8-6
*********************************************************************/
TEXTSIMILARITY_API bool TS_Exit();
/*********************************************************************
*
*  Func Name  : TS_GetLastErrorMsg
*
*  Description: GetLastErrorMessage
*
*
*  Parameters : void
*
*
*  Returns    : the result buffer pointer
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-2-27
*********************************************************************/
TEXTSIMILARITY_API const char * TS_GetLastErrorMsg();


/*********************************************************************
*
*  Func Name  : TS_ComputeSim
*
*  Description: 计算内存文本的相似度
*
*
*  Parameters : sText1: 文本内容1； sText2:文本内容2
*				nModel:选择相似度比较模型
*  Returns    : the result buffer pointer
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2003-12-22
*********************************************************************/
TEXTSIMILARITY_API double TS_ComputeSim(const char *sText1, const char *sText2,int nModel= SIM_MODEL_WORD);

/*********************************************************************
*
*  Func Name  : TS_ComputeSimF
*
*  Description: 计算文本文件的相似度
*
*
*  Parameters : sTextFilename1: 文本文件名1； sTextFilename2:文本文件名2
*				nModel:选择相似度比较模型
*  Returns    : the result buffer pointer
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2003-12-22
*********************************************************************/
TEXTSIMILARITY_API double TS_ComputeSimFile(const char *sTextFilename1, const char *sTextFilename2, int nModel = SIM_MODEL_WORD);

#endif