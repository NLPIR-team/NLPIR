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

typedef struct _stDoc 
{
	string sTitle;
	string sContent;
	string sAuthor;
	string sBoard;
	string sDatatype;
}stDoc;


#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
#define UTF8_FANTI_CODE GBK_CODE+4//UTF8编码

/*********************************************************************
*
*  Func Name  : classifier_init
*
*  Description: Init classifier
*               The function must be invoked before any operation listed as following
*
*  Parameters : const char *conf: 规则分类对应的分类XML配置文件
*			const char * sInitDirPath=NULL
*				  Path where Data directory stored.
*				 the default value is NULL, it indicates the initial directory is current working directory path
*				 int encode: encoding code;
*				 sLicenseCode: license code for unlimited usage. common user ignore it
*  Returns    : success or fail
*         出错信息记录在硬盘的./ljclassifier.log和./DataFile/ljclassifier.log上
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
CLASSIFIER_API bool classifier_init(const char *conf="rulelist.xml",const char *sInitDirPath="", int encode = GBK_CODE,const char *sLicenseCode=NULL);

/*********************************************************************
*
*  Func Name  : classifier_exec1
*
*  Description: 
*			功能：对输入的文章结构进行分类
*  Parameters   ：d:文章结构指针
*       iType=0:  输出类名，各类之间用\t隔开  内容格式举例：“要闻	敏感	诉讼”
*       iType=1:  输出类名和置信度，各类之间用\t隔开，类名和权重用“ ”隔开   内容格式举例：“要闻 1.00	敏感 0.95	诉讼 0.82”
*       iType 默认值为0
*
*  Returns    : 主题类别串  各类之间用\t隔开，类名按照置信度从高到低排序
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
CLASSIFIER_API const char* classifier_exec1(stDoc& d, int iType=0);

/*********************************************************************
*
*  Func Name  : classifier_exec
*
*  Description:
*			功能：对输入的文章标题与正文进行分类
*  Parameters   ：
*		 sTitle:文章标题
*	   sContent: 文字内容
*       iType=0:  输出类名，各类之间用\t隔开  内容格式举例：“要闻	敏感	诉讼”
*       iType=1:  输出类名和置信度，各类之间用\t隔开，类名和权重用“ ”隔开   内容格式举例：“要闻 1.00	敏感 0.95	诉讼 0.82”
*       iType 默认值为0
*
*  Returns    : 主题类别串  各类之间用\t隔开，类名按照置信度从高到低排序
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
CLASSIFIER_API const char* classifier_exec(const char* sTitle,const char*sContent, int iType);
/*********************************************************************
*
*  Func Name  : classifier_execFile
*
*  Description:
*			功能：对输入的文本文件进行分类
*  Parameters   ：
*		 sTitle:文章标题
*	   sContent: 文字内容
*       iType=0:  输出类名，各类之间用\t隔开  内容格式举例：“要闻	敏感	诉讼”
*       iType=1:  输出类名和置信度，各类之间用\t隔开，类名和权重用“ ”隔开   内容格式举例：“要闻 1.00	敏感 0.95	诉讼 0.82”
*       iType 默认值为0
*
*  Returns    : 主题类别串  各类之间用\t隔开，类名按照置信度从高到低排序
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
CLASSIFIER_API const char* classifier_execFile(const char* sFilename, int iType);

/*********************************************************************
*
*  Func Name  : classifier_detail
*
*  Description:
*			对于当前文档，输入类名，取得结果明细
*  Parameters   ：classname:结果类名
*
*  Returns    : 结果明细 例如:
*		   RULE3:
*		   SUBRULE1: 内幕 1	
*		   SUBRULE2: 股市 1	基金 3	股票 8	
*		   SUBRULE3: 书摘 2
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
CLASSIFIER_API const char* classifier_detail(const char *classname);

/*********************************************************************
*
*  Func Name  : classifier_exit
*
*  Description:
*			退出，释放资源
*  Parameters   ：无
*
*  Returns    : 无
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
CLASSIFIER_API void classifier_exit();

/*********************************************************************
*
*  Func Name  : classifier_setsimthresh
*
*  Description: 设置相似度阈值
*			
*  Parameters   ：float fSim
*
*  Returns    : 无
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
CLASSIFIER_API void classifier_setsimthresh(float fSim);

/*********************************************************************
*
*  Func Name  : classifier_GetLastErrorMsg
*
*  Description: 获取失败的信息
*
*  Parameters   ：无
*
*  Returns    : 返回的错误信息
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
CLASSIFIER_API const char* classifier_GetLastErrorMsg();

#endif //_H_CLASSIFIER_DLL

