
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
 *          NewWordFinder.h: definition of the NewWordFinder new word finder system API
 * Author:   Kevin Zhang 
 *          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
 *			Weibo: http://weibo.com/drkevinzhang
 * Date:     2013-3-1
 *
 * Notes:
 *                
 ****************************************************************************/
#if !defined(__NEW_WORD_FINDER_2016_LIB_INCLUDED__)
#define __NEW_WORD_FINDER_2016_LIB_INCLUDED__
#ifdef OS_LINUX
#define NEWWORDFINDER_API extern "C" 
#else
#ifdef NEWWORDFINDER_EXPORTS
#define NEWWORDFINDER_API extern "C" __declspec(dllexport)
#else
#define NEWWORDFINDER_API extern "C" __declspec(dllimport)
#endif
#endif

#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字

/*********************************************************************
 *
 *  Func Name  : NWF_Init
 *
 *  Description: Init NewWordFinder
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
NEWWORDFINDER_API int NWF_Init(const char * sDataPath=0,int encode=GBK_CODE,const char*sLicenceCode=0);

/*********************************************************************
 *
 *  Func Name  : NWF_Exit
 *
 *  Description: Exist NewWordFinder and free related buffer
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
NEWWORDFINDER_API bool NWF_Exit();

/*********************************************************************
*
*  Func Name  : NWF_GetNewWords
*
*  Description: Extract New words from sLine
*
*  Parameters : sLine, the input paragraph; 
*						the input size cannot be very big(less than 60MB). Process large memory, recommendate use NWF_NWI series functions
*				bArguOut,whether  the keyword weight output
*				nMaxKeyLimit:maximum of key words, up to 50
*  Returns    : new words list like:
*               "科学发展观 屌丝 "or
				"科学发展观 23.80 屌丝 12.20" with weight
*
*  Author     :   
*  History    : 
*              1.create  2012/11/12
*********************************************************************/
NEWWORDFINDER_API const char * NWF_GetNewWords(const char *sLine,int nMaxKeyLimit=50,bool bWeightOut=false);

/*********************************************************************
*
*  Func Name  : NWF_GetFileNewWords
*
*  Description: Extract new words from a text file
*
*  Parameters : sFilename, the input text file name 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimit:maximum of key words, up to 50
*  Returns    : keywords list like:
*               "科学发展观 宏观经济 " or
				"科学发展观 23.80 宏观经济 12.20" with weight

*
*  Author     :   
*  History    : 
*              1.create 2012/11/12
*********************************************************************/
NEWWORDFINDER_API const char * NWF_GetFileNewWords(const char *sFilename,int nMaxKeyLimit=50,bool bWeightOut=false);


/*********************************************************************
*
*  以下函数为2013版本专门针对新词发现的过程，一般建议脱机实现，不宜在线处理
*  新词识别完成后，再自动导入到分词系统中，即可完成
*  函数以NWF_NWI(New Word Identification)开头
*********************************************************************/
/*********************************************************************
*
*  Func Name  : NWF_Batch_Start
*
*  Description: 启动新词识别

*
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NEWWORDFINDER_API int NWF_Batch_Start();//New Word Indentification Start
/*********************************************************************
*
*  Func Name  : NWF_Batch_AddFile
*
*  Description: 往新词识别系统中添加待识别新词的文本文件
*				需要在运行NWF_Batch_Start()之后，才有效
*
*  Parameters : const char *sFilename：文件名
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 20132/11/23
*********************************************************************/
NEWWORDFINDER_API unsigned long  NWF_Batch_AddFile(const char *sFilename);
/*********************************************************************
*
*  Func Name  : NWF_Batch_AddMem
*
*  Description: 往新词识别系统中添加一段待识别新词的内存
*				需要在运行NWF_Batch_Start()之后，才有效
*
*  Parameters : const char *sFilename：文件名
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NEWWORDFINDER_API unsigned long NWF_Batch_AddMem(const char *sText);
/*********************************************************************
*
*  Func Name  : NWF_Batch_Complete
*
*  Description: 新词识别添加内容结束
*				需要在运行NWF_Batch_Start()之后，才有效
*
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NEWWORDFINDER_API int NWF_Batch_Complete();//文件或者内存导入结束

/*********************************************************************
*
*  Func Name  : NWF_Batch_GetResult
*
*  Description: 获取新词识别的结果
*				需要在运行NWF_Batch_Complete()之后，才有效
*
*  Parameters : bWeightOut：是否需要输出每个新词的权重参数
*
*  Returns    : 输出格式为
*				【新词1】 【权重1】 【新词2】 【权重2】 ... 
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NEWWORDFINDER_API const char * NWF_Batch_GetResult(bool bWeightOut=false);//输出新词识别结果

/*********************************************************************
*
*  Func Name  : NWF_Result2UserDict
*
*  Description: 将新词识别结果导入到用户词典中
*				需要在运行NLPIR_NWI_Complete()之后，才有效
*				如果需要将新词结果永久保存，建议在执行NLPIR_SaveTheUsrDic
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NEWWORDFINDER_API unsigned int  NWF_Result2UserDict();//新词识别结果转为用户词典,返回新词结果数目
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
NEWWORDFINDER_API const char *  NWF_GetLastErrorMsg();
#endif
