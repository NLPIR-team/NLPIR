/****************************************************************************
*
* NLPIR SplitSentence�־�ϵͳ Copyright (c) 2000-2017
*     Dr. Kevin Zhang (Hua-Ping Zhang)
*     All rights reserved.
*
* This file is the confidential and proprietary property of
* Kevin Zhang and the possession or use of this file requires
* a written license from the author.
* Filename: 
* Abstract:
*          SplitSentence.h: definition of NLPIR SplitSentence�־�ϵͳ system API
* Author:   Kevin Zhang
*          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
*			Weibo: http://weibo.com/drkevinzhang
*			Homepage: http://www.nlpir.org
* Date:     2013-12-19
*
* Notes:
*
****************************************************************************/
#if !defined(__NLPIR_SPLIT_SENTENCE_H_INCLUDED__)
#define __NLPIR_SPLIT_SENTENCE_H_INCLUDED__

#ifdef OS_LINUX
#define SPLITSENTENCE_API extern "C" 
#else
#ifdef SPLITSENTENCE_EXPORTS
#define SPLITSENTENCE_API extern "C" __declspec(dllexport)
#else
#define SPLITSENTENCE_API extern "C" __declspec(dllimport)
#endif
#endif

#define GBK_CODE 0//Ĭ��֧��GBK����
#define UTF8_CODE GBK_CODE+1//UTF8����
#define BIG5_CODE GBK_CODE+2//BIG5����
#define GBK_FANTI_CODE GBK_CODE+3//GBK���룬�������������
#define UTF8_FANTI_CODE GBK_CODE+4//UTF8����
/*********************************************************************
*
*  Func Name  : SS_Init
*
*  Description: Init SplitSentence
*               The function must be invoked before any operation listed as following
*
*  Parameters : const char * sInitDirPath=NULL
*				 sDataPath:  Path where Data directory stored. ָ����Data���ڵ�Ŀ¼���� D:/NLPIR/Data����ֻ��Ҫ���� D:/NLPIR
*				 the default value is NULL, it indicates the initial directory is current working directory path
*				 sLicenseCode: license code for unlimited usage. common user ignore it
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2017-8-26
*********************************************************************/
SPLITSENTENCE_API int SS_Init(const char * sDataPath = 0, const char*sLicenceCode = 0);
/*********************************************************************
*
*  Func Name  : SS_Exit
*
*  Description: Exit SplitSentence
*              
*
*  Parameters : void
*  Returns    : void
*  Author     : Kevin Zhang
*  History    :
*              1.create	2017-8-26
*********************************************************************/
SPLITSENTENCE_API void SS_Exit();
/*********************************************************************
*
*  Func Name  : SS_GetSentence
*
*  Description: SS_GetSentence
*               
*  Parameters : const char * sText
*				1.��һ�ε��õ�ʱ�򣬸ò���Ϊ�����ı���������ĵĵ�һ���������ݣ�
*				2.�������õ�ʱ�򣬸ò���ΪNULL��������ϴ������ı��Ľ������ľ������ݣ�ֱ��û�н�������Ϊ��Ϊֹ
*				encode: ����ı��룬��һ�����ɾ��ӵ�ʱ����Ч����������Ҫ���룬Ĭ��Ϊ��һ�ε�ֵ;
*				
*  Returns    : const char*
				����о��ӣ��򷵻ؾ��ӵ����ݣ�
				���򷵻ؿ��ַ�����""
*  Author     : Kevin Zhang
*  History    :
*              1.create 2017-8-26
*********************************************************************/
SPLITSENTENCE_API const char* SS_GetSentence(const char * sText = 0, int encode = GBK_CODE);
/*********************************************************************
*
*  Func Name  : SS_GetLastErrorMsg
*
*  Description: SS_GetLastErrorMsg 
*
*  Parameters : void
*
*  Returns    : const char*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2017-8-26
*********************************************************************/
SPLITSENTENCE_API const char * SS_GetLastErrorMsg();
#endif
