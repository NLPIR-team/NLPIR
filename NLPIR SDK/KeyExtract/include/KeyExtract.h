/****************************************************************************
 *
 * NLPIR Chinese Keyword Extraxt System Copyright (c) 2000-2013
 *     Dr. Kevin Zhang (Hua-Ping Zhang)
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          KeyExtract.h: definition of the NLPIR lexical analysis system API
 * Author:   Kevin Zhang 
 *          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
 *			Weibo: http://weibo.com/drkevinzhang
 * Date:     2013-3-1
 *
 * Notes:
 *                
 ****************************************************************************/
#if !defined(__KEYEXTRACT_2013_LIB_INCLUDED__)
#define __KEYEXTRACT_2013_LIB_INCLUDED__
#ifdef OS_LINUX
#define KEYEXTRACT_API extern "C" 
#else
#ifdef KEYEXTRACT_EXPORTS
#define KEYEXTRACT_API extern "C" __declspec(dllexport)
#else
#define KEYEXTRACT_API extern "C" __declspec(dllimport)
#endif
#endif

#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字

/*********************************************************************
 *
 *  Func Name  : Init
 *
 *  Description: Init KeyExtract
 *               The function must be invoked before any operation listed as following
 *
 *  Parameters : const char * sInitDirPath=NULL
 *				 sDataPath:  Path where Data directory stored.
 *				 the default value is NULL, it indicates the initial directory is current working directory path
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-2-6
 *********************************************************************/
KEYEXTRACT_API int KeyExtract_Init(const char * sDataPath=0,int encode=GBK_CODE,const char*sLicenceCode=0);

/*********************************************************************
 *
 *  Func Name  : KeyExtract_Exit
 *
 *  Description: Exist KeyExtract and free related buffer
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
KEYEXTRACT_API bool KeyExtract_Exit();

/*********************************************************************
*
*  Func Name  : KeyExtract_GetKeyWords
*
*  Description: Extract keyword from sLine
*
*  Parameters : sLine, the input paragraph 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimt:maximum of key words, up to 50
*  Returns    : keywords list like:
*               "科学发展观 宏观经济 " or
				"科学发展观/n/23.80 宏观经济/n/12.20" with weight
				分别表示 关键词/关键词词性/权重

*
*  Author     :   
*  History    : 
*              1.create 2012/11/12
*********************************************************************/
KEYEXTRACT_API const char * KeyExtract_GetKeyWords(const char *sLine,int nMaxKeyLimit=50,bool bWeightOut=false);

/*********************************************************************
*
*  Func Name  : KeyExtract_GetFileKeyWords
*
*  Description: Extract keyword from a text file
*
*  Parameters : sFilename, the input text file name 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimt:maximum of key words, up to 50
*  Returns    : keywords list like:
*               "科学发展观 宏观经济 " or
*				"科学发展观/n/23.80 宏观经济/n/12.20" with weight
*				分别表示 关键词/关键词词性/权重

*
*  Author     :   
*  History    : 
*              1.create 2012/11/12
*********************************************************************/
KEYEXTRACT_API const char * KeyExtract_GetFileKeyWords(const char *sFilename,int nMaxKeyLimit=50,bool bWeightOut=false);

/*********************************************************************
 *
 *  Func Name  : KeyExtract_ImportUserDict
 *
 *  Description: Import keyword user defined dictionary
 *  Parameters : Text filename for user dictionary, each line for a imported keyword
 *				 
 *  Returns    : The  number of  lexical entry imported successfully
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2014-6-26
 *********************************************************************/
KEYEXTRACT_API unsigned int KeyExtract_ImportUserDict(const char *sFilename,bool bOverwrite=false);
/*********************************************************************
*
*  Func Name  : KeyExtract_AddUserWord
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
KEYEXTRACT_API int KeyExtract_AddUserWord(const char *sWord);
/*********************************************************************
*
*  Func Name  : KeyExtract_CleanUserWord
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
KEYEXTRACT_API int KeyExtract_CleanUserWord();
/*********************************************************************
*
*  Func Name  : KeyExtract_SaveTheUsrDic
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
KEYEXTRACT_API int KeyExtract_SaveTheUsrDic();

/*********************************************************************
*
*  Func Name  : KeyExtract_DelUsrWord
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
KEYEXTRACT_API int KeyExtract_DelUsrWord(const char *sWord);

/*********************************************************************
 *
 *  Func Name  : KeyExtract_ImportKeyBlackList
 *
 *  Description: Import keyword black list 
 *  Parameters : sFilename: Text filename for user defined blacklist dictionary, each line for a stop keyword
 *				 sPOSBlacklist: 停用的词性列表，即列为该词性列表访问的词不纳入关键词范围，
 *								如设置为#nr#ns#表示nr,ns不作为关键词
 *  Returns    : The  number of  lexical entry imported successfully
 *  Author     : Kevin Zhang
 *  History    :
 *              1.create 2003-11-28
 *********************************************************************/
KEYEXTRACT_API unsigned int KeyExtract_ImportKeyBlackList(const char *sFilename, const char *sPOSBlacklist = 0);
/*********************************************************************
 *
 *  Func Name  : KeyExtract_GetLastErrorMsg
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
KEYEXTRACT_API const char * KeyExtract_GetLastErrorMsg();


/*********************************************************************
*
*  以下函数为2013版本专门针对关键词批量发现的过程，一般建议脱机实现，不宜在线处理
*********************************************************************/
/*********************************************************************
*
*  Func Name  : KeyExtract_Batch_Start
*
*  Description: 启动关键词识别

*
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013/11/23
*********************************************************************/
KEYEXTRACT_API int KeyExtract_Batch_Start();//New Word Indentification Start
/*********************************************************************
*
*  Func Name  : KeyExtract_Batch_AddFile
*
*  Description: 往关键词识别系统中添加待识别关键词的文本文件
*				需要在运行KeyExtract_Batch_Start()之后，才有效
*
*  Parameters : const char *sFilename：文件名
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 20132/11/23
*********************************************************************/
KEYEXTRACT_API unsigned long  KeyExtract_Batch_AddFile(const char *sFilename);
/*********************************************************************
*
*  Func Name  : KeyExtract_Batch_AddMem
*
*  Description: 往关键词识别系统中添加一段待识别关键词的内存
*				需要在运行KeyExtract_Batch_Start()之后，才有效
*
*  Parameters : const char *sFilename：文件名
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013/11/23
*********************************************************************/
KEYEXTRACT_API unsigned long KeyExtract_Batch_AddMem(const char *sText);
/*********************************************************************
*
*  Func Name  : KeyExtract_Batch_Complete
*
*  Description: 关键词识别添加内容结束
*				需要在运行KeyExtract_Batch_Start()之后，才有效
*
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013/11/23
*********************************************************************/
KEYEXTRACT_API int KeyExtract_Batch_Complete();//文件或者内存导入结束

/*********************************************************************
*
*  Func Name  : KeyExtract_Batch_GetResult
*
*  Description: 获取关键词识别的结果
*				需要在运行KeyExtract_Batch_Complete()之后，才有效
*
*  Parameters : bWeightOut：是否需要输出每个关键词的权重参数
*
*  Returns    : 输出格式为
*				【关键词1】 【权重1】 【关键词2】 【权重2】 ...
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013/11/23
*********************************************************************/
KEYEXTRACT_API const char * KeyExtract_Batch_GetResult(bool bWeightOut = false);//输出关键词识别结果

#endif//__KEYEXTRACT_2013_LIB_INCLUDED__
