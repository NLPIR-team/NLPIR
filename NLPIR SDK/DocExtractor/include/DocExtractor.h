/****************************************************************************
 *
 * NLPIR/ICTCLAS Lexical Analysis System DocExtractor Copyright (c) 2000-2015
 *     Dr. Kevin Zhang (Hua-Ping Zhang)
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          NLPIR.h: definition of the NLPIR lexical analysis system API
 * Author:   Kevin Zhang 
 *          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
 *			Weibo: http://weibo.com/drkevinzhang
 *			Homepage: http://ictclas.nlpir.org
 * Date:     2013-12-19
 *
 * Notes:
 *                
 ****************************************************************************/

#ifdef DOCEXTRACTOR_EXPORTS
#define DOCEXTRACTOR_API extern "C" __declspec(dllexport)
#else
#define DOCEXTRACTOR_API extern "C" __declspec(dllimport)
#endif
#ifdef OS_LINUX
#define DOCEXTRACTOR_API extern "C"  
#endif
#include <stddef.h>

#define DOC_EXTRACT_TYPE_PERSON 0//输出的人名
#define DOC_EXTRACT_TYPE_LOCATION 1//输出的地名
#define DOC_EXTRACT_TYPE_ORGANIZATION 2//输出的机构名
#define DOC_EXTRACT_TYPE_KEYWORD 3//输出的关键词
#define DOC_EXTRACT_TYPE_AUTHOR 4//输出的文章作者
#define DOC_EXTRACT_TYPE_MEDIA 5//输出的媒体
#define DOC_EXTRACT_TYPE_COUNTRY 6//输出的文章对应的所在国别
#define DOC_EXTRACT_TYPE_PROVINCE 7//输出的文章对应的所在省份
#define DOC_EXTRACT_TYPE_ABSTRACT 8//输出文章的摘要
#define DOC_EXTRACT_TYPE_POSITIVE 9//输出文章的正面情感词
#define DOC_EXTRACT_TYPE_NEGATIVE 10//输出文章的负面情感词
#define DOC_EXTRACT_TYPE_TEXT 11//输出文章去除网页等标签后的正文
#define DOC_EXTRACT_TYPE_TIME 12//输出时间词
#define DOC_EXTRACT_TYPE_USER 13//用户自定义的词类，第一个自定义词
//后续的自定义词，依次序号为：DOC_EXTRACT_TYPE_USER+1；DOC_EXTRACT_TYPE_USER+2；...

#define PERSON_REQUIRED			0x0001
#define LOCATION_REQUIRED		0x0002
#define ORGANIZATION_REQUIRED	0x0004
#define KEYWORD_REQUIRED		0x0008
#define AUTHOR_REQUIRED			0x0010
#define MEDIA_REQUIRED			0x0100
#define COUNTRY_REQUIRED		0x0200
#define PROVINCE_REQUIRED		0x0400
#define ABSTRACT_REQUIRED		0x0800
#define SENTIWORD_REQUIRED		0x1000
#define SENTIMENT_REQUIRED		0x2000
#define TIME_REQUIRED			0x4000
#define HTML_REMOVER_REQUIRED	0x8000//是否需要去除网页标签的功能选项
#define ALL_REQUIRED			0xffff

#define DOC_EXTRACT_DELIMITER "#"
#define DOC_EXTRACT_TYPE_MAX_LENGTH 600
#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
typedef  size_t DOC_PARSER_HANDLE;

/*-----------------------------------------------------------------------
* 功能：初始化
* 参数：
*		sPath-default path
*		nEncoding:编码类别
*		sLicenseCode - 授权码
* 返回：true - 成功；false - 失败
* 备注：在进程中此函数必须在其他函数之前调用（只需执行一次）
------------------------------------------------------------------------*/
DOCEXTRACTOR_API int DE_Init(const char *sPath=0,int nEncoding=GBK_CODE,const char *sLicenseCode=0);

/*-----------------------------------------------------------------------
* 功能：生成单文档摘要
* 参数：sText	    -[IN] 文档内容
*	bool bSummaryNeeded=true-[IN]:是否需要计算摘要
*	
*		sUserDefPos:用户自定义的词性标记，最多三种（人名、地名、机构名、媒体等内置，无需设置），不同词类之间采用#分割，如"gms#gjtgj#g"

*		_tDocExtractResult	-[OUT] 文档Extract result
* 备注：在进程中此函数可以执行多次
------------------------------------------------------------------------*/
DOCEXTRACTOR_API DOC_PARSER_HANDLE DE_ParseDocE(const char *sText,const char *sUserDefPos=NULL,bool bSummaryNeeded=true,unsigned int nFuncRequired=ALL_REQUIRED);
//Process a text, and return DOC_PARSER_HANDLE
/*-----------------------------------------------------------------------
* 功能：从运行完的DE_ParseDocE结果中，获取指定抽取的结果内容
* 参数：handle	    -[IN] DE_ParseDocE执行后返回的HANDLE
*	int nDocExtractType[IN]:是否获取的抽取类型，从DOC_EXTRACT_TYPE_PERSON开始的结果
* 备注：必须在DE_ParseDocE之后执行方可，此函数可以执行多次
------------------------------------------------------------------------*/
DOCEXTRACTOR_API const char *DE_GetResult(DOC_PARSER_HANDLE handle,int nDocExtractType);

/*-----------------------------------------------------------------------
* 功能：从运行完的DE_ParseDocE结果中，获取指定文章的情感得分
* 参数：handle	    -[IN] DE_ParseDocE执行后返回的HANDLE
* 返回值：情感正负得分
* 备注：必须在DE_ParseDocE之后执行方可，此函数可以执行多次
------------------------------------------------------------------------*/
DOCEXTRACTOR_API int DE_GetSentimentScore(DOC_PARSER_HANDLE handle);
/*-----------------------------------------------------------------------
* 功能：DE_ReleaseHandle释放DE_ParseDocE结果所占据的空间
* 参数：handle	    -[IN] DE_ParseDocE执行后返回的HANDLE
* 返回值：无
* 备注：必须在DE_ParseDocE之后执行方可，此函数可以执行多次
------------------------------------------------------------------------*/
DOCEXTRACTOR_API void DE_ReleaseHandle(DOC_PARSER_HANDLE handle);


DOCEXTRACTOR_API unsigned int DE_ImportSentimentDict(const char *sFilename);//导入用户情感词典
////导入用户自定义的情感词表，每行一个词，空格后加上正负权重，如：语焉不详 -2;
//如果导入的情感词属于新词，现在用户词典中导入，否则情感识别自动跳跃
DOCEXTRACTOR_API unsigned int DE_ImportUserDict(const char *sFilename,bool bOverwite=false);//导入用户词典
////导入用户自定义的词典
/*********************************************************************
*
*  Func Name  : DE_ImportKeyBlackList
*
*  Description: Import keyword black list
*  Parameters : sFilename: Text filename for user defined blacklist dictionary, each line for a stop keyword
*				 sPOSBlacklist: 停用的词性列表，即列为该词性列表访问的词不纳入关键词范围，
*								如设置为#nr#ns#表示nr,ns不作为关键词
*  Returns    : The  number of  lexical entry imported successfully
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-6-26
*********************************************************************/

DOCEXTRACTOR_API unsigned int DE_ImportKeyBlackList(const char *sFilename, const char *sPOSBlacklist = 0);//导入关键词黑名单
////导入用户自定义的关键词黑名单

/*********************************************************************
*
*  Func Name  : DE_AddUserWord
*
*  Description: add a word to the user dictionary ,example:
*				一带一路  key
*				需要作为关键词的，标引前缀必须为key
*  Parameters : const char *sWord: 加入到临时用户词典重点词与词性，用空格分割
*
*  Returns    : 1,true ; 0,false
*
*  Author     :
*  History    :
*              1.create 2017/6/3
*********************************************************************/
DOCEXTRACTOR_API int DE_AddUserWord(const char *sWord);
/*********************************************************************
*
*  Func Name  : DE_CleanUserWord
*
*  Description: Clean all temporary added user words
*
*  Parameters :
*  Returns    : 1,true ; 0,false
*
*  Author     :
*  History    :
*              1.create 2017/6/3
*********************************************************************/
DOCEXTRACTOR_API int DE_CleanUserWord();
/*********************************************************************
*
*  Func Name  : DE_SaveTheUsrDic
*
*  Description: Save dictionary to file
*
*  Parameters :
*
*  Returns    : 1,true; 2,false
*
*  Author     :
*  History    :
*              1.create 2017/6/3
*********************************************************************/
DOCEXTRACTOR_API int DE_SaveTheUsrDic();

/*********************************************************************
*
*  Func Name  : DE_DelUsrWord
*
*  Description: delete a word from the  user dictionary
*
*  Parameters :
*  Returns    : -1, the word not exist in the user dictionary; else, the handle of the word deleted
*
*  Author     :
*  History    :
*              1.create 2017/6/3
*********************************************************************/
DOCEXTRACTOR_API int DE_DelUsrWord(const char *sWord);

/*----b--------------------------------------------------------------
* 功能：生成单文档摘要
* 参数：sText	    -[IN] 文档内容
*	bool bSummaryNeeded=true-[IN]:是否需要计算摘要
*	
*		_tDocExtractResult	-[OUT] 文档Extract result
* 备注：在进程中此函数可以执行多次
------------------------------------------------------------------------*/
DOCEXTRACTOR_API int  DE_ComputeSentimentDoc(const char *sText);


DOCEXTRACTOR_API void DE_Exit();

//获得错误消息
DOCEXTRACTOR_API const char* DE_GetLastErrMsg();
