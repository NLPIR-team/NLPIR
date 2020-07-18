/****************************************************************************
*
* NLPIR Document Compare System Copyright (c) 2000-2019

*     All rights reserved.
*
* This file is the confidential and proprietary property of
* Kevin Zhang and the possession or use of this file requires
* a written license from the author.
* Filename:
* Abstract:
*          NLPIR.h: definition of the NLPIR lexical analysis system API
* Date:     2019-8-9
*
* Notes:
*
****************************************************************************/
#ifdef OS_LINUX
#define DOCCOMPARE_API extern "C" 
#else
#ifdef DOCCOMPARE_EXPORTS
#define DOCCOMPARE_API extern "C" __declspec(dllexport)
#else
#define DOCCOMPARE_API extern "C"  __declspec(dllimport)
#endif
#endif
DOCCOMPARE_API int DocComp_Init(void);


DOCCOMPARE_API void* DocComp_NewInstance(const char* outputDir, const char* exePath, bool useJson);


DOCCOMPARE_API void DocComp_Exit(void * pCompare);

DOCCOMPARE_API int DocComp_ImportTemplate(void *pCompare, const char* filePath);

DOCCOMPARE_API const char * DocComp_compareDocFile(void *pCompare, const char* sTextFile);

DOCCOMPARE_API const char * DocComp_compareDoc2Files(void *pCompare, const char* sCmpFile,const char *sBeCmpedFile);
//两个指定的文件之间进行比对;忽略范文查找过程 sCmpFile:比较文件；sBeCmpedFile:带比较的文件
//added in 2019/8/12


DOCCOMPARE_API void DocComp_setConvertexeDir(void *pCompare, const char* filePath);

DOCCOMPARE_API void DocComp_setOutputDir(void *pCompare, const char* filePath);

DOCCOMPARE_API int DocComp_convert2TXT(void *pCompare, const char* filePath);

DOCCOMPARE_API int DocComp_LoadFile(void *pCompare, const char* filePath, int isTest);
DOCCOMPARE_API void DocComp_GenerateResult(void *pCompare);


