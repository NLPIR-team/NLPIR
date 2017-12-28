/****************************************************************************
 *
 * NLPIR Rule-Based Classifier System Copyright (c) 2000-2014
 *     Dr. Kevin Zhang (Hua-Ping Zhang)
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          LJCLassifier.h: definition of the NLPIR lexical analysis system API
 * Author:   Kevin Zhang 
 *          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
 *			Weibo: http://weibo.com/drkevinzhang
 *			Homepage: http://ictclas.nlpir.org
 * Date:     2013-12-19
 *
 * Notes:
 *                
 ****************************************************************************/
#ifndef _H_CLASSIFIER_DLL
#define _H_CLASSIFIER_DLL

#include <string>
using namespace std;
#ifndef OS_LINUX
#pragma warning(disable:4786)
#endif

#ifdef OS_LINUX
#define CLASSIFIER_API  extern "C"
#else
#ifdef LJCLASSIFIER_EXPORTS
#define CLASSIFIER_API extern "C" __declspec(dllexport)
#else
#define CLASSIFIER_API extern "C"  __declspec(dllimport)
#endif
#endif


typedef struct _stDoc {
	string sTitle;
	string sContent;
	string sAuthor;
	string sBoard;
	string sDatatype;
}stDoc;

// 功能：  文件方式初始化
// 返回值：成功/失败  
//         出错信息记录在硬盘的./ljclassifier.log和./DataFile/ljclassifier.log上
CLASSIFIER_API bool classifier_init(const char *conf="rulelist.xml",const char *sInitDirPath="",const char *sLicenseCode=NULL);

// 功能：对输入的文章结构进行分类
// 参数：d:文章结构指针
//       iType=0:  输出类名，各类之间用\t隔开  内容格式举例：“要闻	敏感	诉讼”
//       iType=1:  输出类名和置信度，各类之间用\t隔开，类名和权重用“ ”隔开   内容格式举例：“要闻 1.00	敏感 0.95	诉讼 0.82”
//       iType 默认值为0
// 返回值：主题类别串  各类之间用\t隔开，类名按照置信度从高到低排序      
CLASSIFIER_API const char* classifier_exec1(stDoc& d, int iType=0);
CLASSIFIER_API const char* classifier_exec(const char* sTitle,const char*sContent, int iType);
// 功能：对于当前文档，输入类名，取得结果明细
// 参数：classname:结果类名
// 返回值：结果明细 例如:
/*		   RULE3:
		   SUBRULE1: 内幕 1	
		   SUBRULE2: 股市 1	基金 3	股票 8	
		   SUBRULE3: 书摘 2	*/
CLASSIFIER_API const char* classifier_detail(const char *classname);

// 功能：退出，释放资源
CLASSIFIER_API void classifier_exit();

CLASSIFIER_API void classifier_setsimthresh(float fSim);

CLASSIFIER_API const char* classifier_GetLastErrorMsg();

#endif //_H_CLASSIFIER_DLL

