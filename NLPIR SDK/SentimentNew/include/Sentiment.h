/****************************************************************************
 *
 * NLPIR/ICTCLAS Lexical Analysis System Copyright (c) 2000-2014
 *     Dr. Kevin Zhang (Hua-Ping Zhang)
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          Sentiment.h: definition of the NLPIR Sentiment Analysis system API
 * Author:   Kevin Zhang 
 *          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
 *			Weibo: http://weibo.com/drkevinzhang
 *			Homepage: http://ictclas.nlpir.org
 * Date:     2013-12-19
 *
 * Notes:
 *                
 ****************************************************************************/
#ifndef SENTIMENTANALYSIS_H
#define SENTIMENTANALYSIS_H

#define ENCODING_GBK 0
#define ENCODING_UTF8 ENCODING_GBK+1
#define ENCODING_BIG5 ENCODING_GBK+2
#define ENCODING_GBK_FANTI ENCODING_GBK+3//GBKÖÐ°üº¬·±Ìå
#define ENCODING_FANTI_UTF8 ENCODING_GBK+4
#define ENCODING_COUNT 4


#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC 
#endif

#ifdef OS_LINUX
	#define ST_API EXTERNC 
#else
#ifdef ST_EXPORTS
#define ST_API EXTERNC __declspec(dllexport)
#else
#define ST_API EXTERNC __declspec(dllimport)
#endif
#endif

ST_API int ST_Init(const char * sDataPath, int encode, const char*sLicenceCode);

ST_API int ST_Exit();

ST_API const char * ST_GetOneObjectResult(const char *sTitle, const char *sContent, const char *sObject);

ST_API const char * ST_GetMultiObjectResult(const char *sTitle, const char *sContent, const char *sObjectRuleFile);

ST_API const char * ST_GetLastErrMsg();

ST_API int ST_ImportUserDict(const char *sFilePath, int bSaveDict);

ST_API int ST_DelUsrWord(const char *sWord, int bSaveDict);

ST_API double ST_GetSentimentPoint(const char *sSentence);

ST_API const char *  ST_GetSentencePoint(const char *sSentence);

#endif
