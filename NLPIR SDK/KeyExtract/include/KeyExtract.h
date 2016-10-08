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
 *  Func Name  : KeyExtract_ImportKeyBlackList
 *
 *  Description: Import keyword black list 
 *  Parameters : Text filename for user dictionary, each line for a stop keyword
 *  Returns    : The  number of  lexical entry imported successfully
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2014-6-26
 *********************************************************************/
KEYEXTRACT_API unsigned int KeyExtract_ImportKeyBlackList(const char *sFilename);
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
#endif//__KEYEXTRACT_2013_LIB_INCLUDED__
