/****************************************************************************
*
* NLPIR-TC/ICTCLAS Tranditional Chinese Lexical Analysis System Copyright (c) 2000-2018
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
*			Homepage: http://www.nlpir.org
* Date:     2018-2-28
*			Adding NLPIRTC_Tokenizer4IR in 2019/12/26
* Notes:
*
****************************************************************************/
#if !defined(__NLPIRTC_ICTCLAS_TRADICTIONAL_CHINESE_H_INCLUDED__)
#define __NLPIRTC_ICTCLAS_TRADICTIONAL_CHINESE_H_INCLUDED__

#ifdef OS_LINUX
#define NLPIRTC_API extern "C" 
#else
#ifdef NLPIRTC_EXPORTS
#define NLPIRTC_API extern "C" __declspec(dllexport)
#else
#define NLPIRTC_API extern "C"  __declspec(dllimport)
#endif
#endif

#define  POS_SIZE 40

/*********************************************************************
*
*  Func Name  : Init
*
*  Description: Init NLPIRTC
*               The function must be invoked before any operation listed as following
*
*  Parameters : const char * sInitDirPath=NULL
*				 sDataPath:  Path where Data directory stored.
*				 the default value is NULL, it indicates the initial directory is current working directory path
*				 sLicenseCode: license code for unlimited usage. common user ignore it
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2020-6-8
*********************************************************************/
NLPIRTC_API int NLPIRTC_Init(const char * sDataPath = 0, const char*sLicenceCode = 0);
/*********************************************************************
*
*  Func Name  : NLPIRTC_Exit
*
*  Description: Exist NLPIR and free related buffer
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
NLPIRTC_API bool NLPIRTC_Exit();
/*********************************************************************
*
*  Func Name  : ParagraphProcessing
*
*  Description: Process a paragraph
*
*
*  Parameters : sParagraph: The source paragraph
*
*				 bPOStagged:Judge whether need POS tagging, 0 for no tag;default:1
*				i.e.  张华平于1978年3月9日出生于江西省波阳县。
*					Result: 张华平/nr  于/p  1978年/t  3月/t  9日/t  出生于/v  江西省/ns  波阳县/ns  。/w
*  Returns    : the result buffer pointer
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2003-12-22
*********************************************************************/
NLPIRTC_API const char * NLPIRTC_ParagraphProcess(const char *sParagraph, int bPOStagged = 1);
/*********************************************************************
*
*  Func Name  : NLPIRTC_GetLastErrorMsg
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
NLPIRTC_API const char * NLPIRTC_GetLastErrorMsg();
/*********************************************************************
*
*  Func Name  : NLPIRTC_FileProcess
*
*  Description: Process a text file
*
*
*  Parameters : sSourceFilename: The source file name
*               sResultFilename: The result file name
*				 bPOStagged:Judge whether need POS tagging, 0 for no tag;default:1
*  i.e. FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");
*  Returns    : success:
*               fail:
*  Author     : Kevin Zhang
*  History    :
*              1.create 2005-11-22
*********************************************************************/
NLPIRTC_API double NLPIRTC_FileProcess(const char *sSourceFilename, const char *sResultFilename, int bPOStagged = 1);

/*********************************************************************
*
*  Func Name  : ImportUserDict
*
*  Description: Import User-defined dictionary
*  Parameters :
*				sFilename:Text filename for user dictionary
*				bOverwrite: true,  overwrite the existing dictionary
*						   false, add to  the existing dictionary
*  Returns    : The  number of  lexical entry imported successfully
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-8-3
*********************************************************************/
NLPIRTC_API unsigned int NLPIRTC_ImportUserDict(const char *sFilename, bool bOverwrite = false);
#endif