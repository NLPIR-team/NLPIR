/****************************************************************************
*
* 关键词扫描过滤系统 Keyword Scan System Copyright (c) 2000-2016
*     Dr. Kevin Zhang (Hua-Ping Zhang)
*
*     All rights reserved.
*
* This file is the confidential and proprietary property of
* Kevin Zhang and the possession or use of this file requires
* a written license from the author.
* Filename:
* Abstract:
*          KeyScan.h: definition of the system API
* Author:   Kevin Zhang
*          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
*			Weibo: http://weibo.com/drkevinzhang
*			Homepage: http://ictclas.nlpir.org
* Date:     2013-12-19
*
* Notes:一次设置关键词，可以扫描各类敏感词的变体，如繁体形式、中间加各类干扰噪音
*
****************************************************************************/
#ifndef _H_KS_DLL
#define _H_KS_DLL

#ifdef OS_LINUX
	#define KEYSCANAPI_API  extern "C"
#else
	#ifdef KEYSCANAPI_EXPORTS
		#define KEYSCANAPI_API extern "C" __declspec(dllexport)
	#else
		#define KEYSCANAPI_API extern "C" __declspec(dllimport)
	#endif
#endif


#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
#define UTF8_FANTI_CODE GBK_CODE+4//UTF8编码

#define KS_HANDLE int
/*********************************************************************
 *
 *  Func Name  : Init
 *
 *  Description: Init KS 系统初始化
 *               The function must be invoked before any operation listed as following
 *
 *  Parameters : const char * sInitDirPath:  Path where Data directory stored. 数据词典存储的路径
 *				 the default value is NULL, it indicates the initial directory is current working directory path
 *				 encode: encoding code;
 *				 sLicenseCode: license code for unlimited usage. common user ignore it
 *  Returns    : success or fail ; 出错原因录通过KS_GetLastErrorMsg
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
KEYSCANAPI_API int KS_Init(const char *sInitDirPath = "", int encode = GBK_CODE, const char*sLicenceCode = 0);


/*********************************************************************
*
*  Func Name  : KS_Exit
*
*  Description: Exist KS and free related buffer 退出，释放资源
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
KEYSCANAPI_API void KS_Exit();

/*********************************************************************
*
*  Func Name  : KS_NewInstance
*
*  Description: New a  KeyScan Instance
*               The function must be invoked before mulitiple keyword scan filter
*
*  Parameters : 
*  Returns    : KS_HANDLE: KeyScan Handle if success; otherwise return -1;
*  Author     : Kevin Zhang
*  History    :
*              1.create 2016-11-15
*********************************************************************/
KEYSCANAPI_API KS_HANDLE KS_NewInstance();

/*********************************************************************
*
*  Func Name  : KS_DeleteInstance
*
*  Description: Delete a  KeyScan Instance with handle
*               The function must be invoked before release a specific classifier
*
*  Parameters : DC_HANDLE , KeyScan Handle
*  Returns    : 
*  Author     : Kevin Zhang
*  History    :
*              1.create 2015-9-22
*********************************************************************/
KEYSCANAPI_API int KS_DeleteInstance(KS_HANDLE handle);

/*********************************************************************
 *
 *  Func Name  : ImportUserDict
 *
 *  Description: Import User-defined dictionary 导入用户词典
 *  Parameters : 
 *				sFilename:Text filename for user dictionary 
 *				bool bOverwrite: 
 *				KS_HANDLE handle： handle of KeyScanner
 *  Returns    : The  number of  lexical entry imported successfully
 *               成功导入的词典条数
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2014-8-3
 *  文本文件的格式为：　词条　　词类  权重 (注意，最多定义255个类别)
 *        例如： AV电影 色情 2
 *				 习近平 涉及领导人 1
*********************************************************************/
KEYSCANAPI_API int KS_ImportUserDict(const char *sFilename, bool bOverwrite = false, KS_HANDLE handle=0);
 
/*********************************************************************
 *
 *  Func Name  : KS_Scan
 *
 *  Description: 扫描输入的文本内容
 *  Parameters : sContent:文本内容
 *				KS_HANDLE handle： handle of KeyScanner
 *  Returns    : const char*: 涉及敏感的所有类别与权重，按照权重排序。
 *				 如： 色情/10#暴力/1#
 *				 ""：表示无扫描命中结果
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2014-8-3
 *  例如输出格式为： 政治反动/2#FLG/1#涉领导人/1#
*********************************************************************/
KEYSCANAPI_API const char* KS_Scan(const char*sContent, KS_HANDLE handle = 0);

/*********************************************************************
 *
 *  Func Name  : KS_ScanDetail
 *
 *  Description: 扫描输入的文本内容
 *  Parameters : sContent:文本内容
 *				KS_HANDLE handle： handle of KeyScanner
 *  Returns    : 返回具体涉及敏感的内容，并标引出来
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2014-8-3
// 返回的格式如下：
// 返回值：返回包含了扫描结果的内容，扫描结果明细:
//
//		*<class name="政治反动" weight=1>习*-包（）子</class>*(散財童子，真心不爽啊。
//		<class name="FLG" weight=1>法*輪大法</class>好！
*********************************************************************/
KEYSCANAPI_API const char* KS_ScanDetail(const char*sContent, KS_HANDLE handle = 0);

/*********************************************************************
*
*  Func Name  : KS_ScanFile
*
*  Description: 扫描输入的文本文件内容
*  Parameters : sFilename:文本文件名
*				KS_HANDLE handle： handle of KeyScanner
*  Returns    : const char*: 涉及敏感的所有类别与权重，按照权重排序。
*				 如： 色情/10##暴力/1##
*				 ""：表示无扫描命中结果
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-8-3
*  文本文件的格式为：　词条　　词类
*        例如： AV电影 色情
*********************************************************************/
KEYSCANAPI_API const char* KS_ScanFile(const char	*sFilename, KS_HANDLE handle = 0);

/*********************************************************************
*
*  Func Name  : KS_ScanFileDetail
*
*  Description: 扫描输入的文本文件内容
*  Parameters : sFilename:文本文件名
*				KS_HANDLE handle： handle of KeyScanner
*  Returns    : 返回具体涉及敏感的内容，并标引出来
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-8-3
// 返回的格式如下：
// 返回值：返回包含了扫描结果的内容，扫描结果明细:
//		   *<class name="政治反动" weight=1>习*-包（）子</class>*(散財童子，真心不爽啊。
//		<class name="FLG" weight=1>法*輪大法</class>好！
*********************************************************************/
KEYSCANAPI_API const char* KS_ScanFileDetail(const char	*sFilename, KS_HANDLE handle = 0);

/*********************************************************************
 *
 *  Func Name  : KS_GetLastErrorMsg
 *
 *  Description: 返回最后出错的消息
 *				 The function must be invoked while you needn't any lexical anlysis
 *
 *  Parameters : 返回最后出错的消息
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2002-8-6
 *********************************************************************/
KEYSCANAPI_API const char* KS_GetLastErrorMsg();

#endif //_H_KS_DLL

