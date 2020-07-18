/****************************************************************************
*
* NLPIR iEncoder intelligent encoding (IE) system Copyright (c) 2000-2020
*     Dr. Kevin Zhang (Hua-Ping Zhang)
*     All rights reserved.
*
* This file is the confidential and proprietary property of
* Kevin Zhang and the possession or use of this file requires
* a written license from the author.
* Filename:
* Abstract:
*          iEncodingAPI.h: definition of NLPIR iEncoding intelligent encoding system
* Author:   Kevin Zhang
*          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
*			Weibo: http://weibo.com/drkevinzhang
*			Homepage: http://www.nlpir.org
* Date:     2010-7-13
*			Adding IE_Tokenizer4IR in 2019/12/26
* Notes:
*
****************************************************************************/
#if !defined(__IE_IENCODER_API_H_INCLUDED__)
#define __IE_IENCODER_API_H_INCLUDED__

#ifdef OS_LINUX
#define IENCODINGAPI_API extern "C" 
#else
#ifdef IENCODINGAPI_EXPORTS
#define IENCODINGAPI_API extern "C" __declspec(dllexport)
#else
#define IENCODINGAPI_API extern "C"  __declspec(dllimport)
#endif
#endif

// 编码类型
#define IE_UNKNOWN_CODE		0
#define IE_UTF8_CODE		1
#define IE_GBK_CODE			2
#define IE_BIG5_CODE		3
#define IE_SHIFT_JIS		4
#define IE_EUC_JP			5
#define IE_EUC_KR			6
#define IE_UTF7_CODE		7
#define IE_UNICODE_CODE		8

typedef int IE_CODE_TYPE;

/*********************************************************************
*
*  Func Name  : Init
*
*  Description: Init IE
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
IENCODINGAPI_API int IE_Init(const char * sDataPath = 0,  const char*sLicenceCode = 0);
/*********************************************************************
*
*  Func Name  : IE_Exit
*
*  Description: 编码转换器的销毁
*
*  Parameters : None
*
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2002-8-6
*********************************************************************/
IENCODINGAPI_API void IE_Exit();

/*********************************************************************
*
*  Func Name  : IE_GetLastErrorMsg
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
IENCODINGAPI_API const char * IE_GetLastErrorMsg();

/*********************************************************************
*
*  Func Name  : IE_CodeDetect
*
*  Description: 功能说明：编码智能识别
*
*
*  Parameters : sSrc: [IN], 源文本
*				nSrcLen: [IN], 源文本的长度
*
*
*  Returns    : 源文本的编码类型
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-2-27
*********************************************************************/
IENCODINGAPI_API IE_CODE_TYPE IE_CodeDetect(const char* sSrc, size_t nSrcLen);


/*********************************************************************
*
*  Func Name  : IE_ToUnicode
*
*  Description: 编码转换，转换为Unicode编码，Unicode编码采用Little endian
*               对编码未知的文本，首先进行编码识别
*
*
*  Parameters : enCodeType: [IN], 源文本所使用的编码，若源文本的编码未知，则用UNKNOWN_CODE
*				sSrc: [IN], 源文本
*				nSrcLen: [IN], 源文本的长度
*				sDest: [OUT], 编码转换后的文本
*				nDestLen: [IN/OUT], pcDest的有效长度，输出编码转换后的文本长度
*
*  Returns    : 实际转换的字节数，出错返回(size_t)-1
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-2-27
*********************************************************************/
IENCODINGAPI_API size_t IE_ToUnicode(const char* sSrc, size_t nSrcLen, char* sDest, size_t nDestLen, IE_CODE_TYPE codeType = IE_UNKNOWN_CODE);

/*********************************************************************
*
*  Func Name  : IE_ToUnicodeFile
*
*  Description: 编码转换，转换为Unicode编码，Unicode编码采用Little endian
*               将文本文件转换为特定格式的文本文件
*
*
*  Parameters : sSrcFilename: [IN], 源文本文本文件
*				sDestFilename: [OUT], 编码转换后的文本文件
*
*  Returns    : 实际转换的字节数，出错返回(size_t)-1
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-2-27
*********************************************************************/
IENCODINGAPI_API  size_t IE_ToUnicodeFile(const char* sSrcFilename, const char* sDestFilename);
/*********************************************************************
*
*  Func Name  : IE_ToUtf8
*
*  Description: 编码转换，转换为Utf8编码
*               对编码未知的文本，首先进行编码识别
*
*
*  Parameters : enCodeType: [IN], 源文本所使用的编码，若源文本的编码未知，则用UNKNOWN_CODE
*				sSrc: [IN], 源文本
*				nSrcLen: [IN], 源文本的长度
*				sDest: [OUT], 编码转换后的文本
*				nDestLen: [IN/OUT], pcDest的有效长度，输出编码转换后的文本长度
*
*  Returns    : 实际转换的字节数，出错返回(size_t)-1
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-2-27
*********************************************************************/
IENCODINGAPI_API size_t IE_ToUtf8( const char* sSrc, size_t nSrcLen, char* pcDest, size_t iDestLen, IE_CODE_TYPE codeType = IE_UNKNOWN_CODE);
/*********************************************************************
*
*  Func Name  : IE_ToUtf8File
*
*  Description: 编码转换，转换为Utf8编码
*               将文本文件转换为特定格式的文本文件
*
*
*  Parameters : sSrcFilename: [IN], 源文本文本文件
*				sDestFilename: [OUT], 编码转换后的文本文件
*
*  Returns    : 实际转换的字节数，出错返回(size_t)-1
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-2-27
*********************************************************************/
IENCODINGAPI_API size_t IE_ToUtf8File(const char* sSrcFilename, const char* sDestFilename);
/*********************************************************************
*
*  Func Name  : IE_ToGBK
*
*  Description: 编码转换，转换为GBK编码
*               对编码未知的文本，首先进行编码识别
*
*
*  Parameters : enCodeType: [IN], 源文本所使用的编码，若源文本的编码未知，则用UNKNOWN_CODE
*				sSrc: [IN], 源文本
*				nSrcLen: [IN], 源文本的长度
*				sDest: [OUT], 编码转换后的文本
*				nDestLen: [IN/OUT], pcDest的有效长度，输出编码转换后的文本长度
*
*  Returns    : 实际转换的字节数，出错返回(size_t)-1
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-2-27
*********************************************************************/
IENCODINGAPI_API size_t IE_ToGBK(const char* sSrc, size_t nSrcLen, char* pcDest, size_t iDestLen, IE_CODE_TYPE codeType = IE_UNKNOWN_CODE);
/*********************************************************************
*
*  Func Name  : IE_ToGBKFile
*
*  Description: 编码转换，转换为GBK编码
*               将文本文件转换为特定格式的文本文件
*
*
*  Parameters : sSrcFilename: [IN], 源文本文本文件
*				sDestFilename: [OUT], 编码转换后的文本文件
*
*  Returns    : 实际转换的字节数，出错返回(size_t)-1
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-2-27
*********************************************************************/
IENCODINGAPI_API size_t IE_ToGBKFile(const char* sSrcFilename, const char* sDestFilename);
#endif
