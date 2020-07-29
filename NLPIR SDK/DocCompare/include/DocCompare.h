/****************************************************************************
*
* NLPIR Document Compare System Copyright (c) 2000-2020
*	  提供各类复杂的文档比较功能，生成比较结果的json格式串
*     All rights reserved.
*
* This file is the confidential and proprietary property of
* Kevin Zhang and the possession or use of this file requires
* a written license from the author.
* Filename:
* Abstract:
*          DocCompare.h: definition of the NLPIR Document Compare System
*
* Date:     2019-8-9
*
* Notes:  第一版本：实验室研究生王刚（wanggang@nlpir.org）
*
****************************************************************************/
#ifndef __NLPIR_DOC_COMPARE_INCLUDED_H___
#ifdef OS_LINUX
#define DOCCOMPARE_API extern "C" 
#else
#ifdef DOCCOMPARE_EXPORTS
#define DOCCOMPARE_API extern "C" __declspec(dllexport)
#else
#define DOCCOMPARE_API extern "C"  __declspec(dllimport)
#endif
#endif

typedef size_t DC_HANDLE;//文本比较的运算HANDLE

/*********************************************************************
*
*  Func Name  : DC_Init
*
*  Description: Init DC
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
DOCCOMPARE_API int DC_Init(const char * sDataPath = 0, const char*sLicenceCode = 0);
/*********************************************************************
*
*  Func Name  : DC_Exit
*
*  Description: Exit DC
*               The function must be invoked before any operation listed as following
*
*  Parameters : void
*  Returns    : void
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
DOCCOMPARE_API void DC_Exit(void);

/*********************************************************************
*
*  Func Name  : DC_NewInstance
*
*  Description: Init IE
*               The function must be invoked before any operation listed as following
*
*  Parameters : const char* outputDir:  Path where Data directory stored.
*				useJson: 是否使用Json格式;
*  Returns    : DC_HANDLE, failed return size_t -1;
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
DOCCOMPARE_API DC_HANDLE DC_NewInstance(const char* outputDir,  bool useJson=false);

/*********************************************************************
*
*  Func Name  : DC_DeleteInstance
*
*  Description: Delete Instance
*
*  Parameters : DC_HANDLE：由DC_NewInstance生成的Handle
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
DOCCOMPARE_API void DC_DeleteInstance(DC_HANDLE pDCHandle);

/*********************************************************************
*
*  Func Name  : DC_GetLastErrorMsg
*
*  Description: GetLastErrorMessage
*
*
*  Parameters : const char* 返回的错误信息
*
*
*  Returns    : the result buffer pointer
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-2-27
*********************************************************************/
DOCCOMPARE_API const char * DC_GetLastErrorMsg();

/*********************************************************************
*
*  Func Name  : DC_Cmp2Files
*
*  Description: 比较两个文档，结果采用json格式存储并返回
*
*  Parameters : DC_HANDLE：由DC_NewInstance生成的Handle
*				const char* sFile1：比较的文件1
*				const char *sFile1：比较的文件2
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
DOCCOMPARE_API const char * DC_Cmp2Files(DC_HANDLE pDCHandle, const char* sFile1, const char *sFile2);
//两个指定的文件之间进行比对;忽略范文查找过程 sCmpFile:比较文件；sBeCmpedFile:带比较的文件
//added in 2019/8/12

/*********************************************************************
*
*  Func Name  : DC_Cmp2Str
*
*  Description: 比较两个文档，结果采用json格式存储并返回
*
*  Parameters : DC_HANDLE：由DC_NewInstance生成的Handle
*				const char* sStr1：比较的字符串1
*				const char *sStr2：比较的字符串2
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
DOCCOMPARE_API const char * DC_Cmp2Str(DC_HANDLE pDCHandle, const char* sStr1, const char *sStr2);
//两个指定的文件之间进行比对;忽略范文查找过程 sCmpFile:比较文件；sBeCmpedFile:带比较的文件
//added in 2019/8/12


/*********************************************************************
*
*  Func Name  : DC_AddFile2Lib
*
*  Description: 添加待比较的文档进入模板文档库
*
*  Parameters : DC_HANDLE：由DC_NewInstance生成的Handle
*				const char* sFilename：模板文件名
*
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
DOCCOMPARE_API int DC_AddFile2Lib(DC_HANDLE pDCHandle, const char* sFilename);

/*********************************************************************
*
*  Func Name  : DC_CmpFile2Lib
*
*  Description: 添加待比较的文档进入模板文档库
*
*  Parameters : DC_HANDLE：由DC_NewInstance生成的Handle
*				const char* sFilename：待比较的文本文件
*
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
DOCCOMPARE_API const char * DC_CmpFile2Lib(DC_HANDLE pDCHandle, const char* sFilename);

#endif // !__NLPIR_DOC_COMPARE_INCLUDED_H___
