/****************************************************************************
 *
 * NLPIR/ICTCLAS Lexical Analysis System DocExtractor Copyright (c) 2000-2015
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
 *			Homepage: http://ictclas.nlpir.org
 * Date:     2013-12-19
 *
 * Notes:
 *                
 ****************************************************************************/

#ifdef DOCEXTRACTOR_EXPORTS
#define DOCEXTRACTOR_API extern "C" __declspec(dllexport)
#else
#define DOCEXTRACTOR_API extern "C" __declspec(dllimport)
#endif
#ifdef OS_LINUX
#define DOCEXTRACTOR_API extern "C"  
#endif
#include <stddef.h>

#define DOC_EXTRACT_TYPE_PERSON 0//���������
#define DOC_EXTRACT_TYPE_LOCATION 1//����ĵ���
#define DOC_EXTRACT_TYPE_ORGANIZATION 2//����Ļ�����
#define DOC_EXTRACT_TYPE_KEYWORD 3//����Ĺؼ���
#define DOC_EXTRACT_TYPE_AUTHOR 4//�������������
#define DOC_EXTRACT_TYPE_MEDIA 5//�����ý��
#define DOC_EXTRACT_TYPE_COUNTRY 6//��������¶�Ӧ�����ڹ���
#define DOC_EXTRACT_TYPE_PROVINCE 7//��������¶�Ӧ������ʡ��
#define DOC_EXTRACT_TYPE_ABSTRACT 8//������µ�ժҪ
#define DOC_EXTRACT_TYPE_POSITIVE 9//������µ�������д�
#define DOC_EXTRACT_TYPE_NEGATIVE 10//������µĸ�����д�
#define DOC_EXTRACT_TYPE_TEXT 11//�������ȥ����ҳ�ȱ�ǩ�������
#define DOC_EXTRACT_TYPE_TIME 12//���ʱ���
#define DOC_EXTRACT_TYPE_USER 13//�û��Զ���Ĵ��࣬��һ���Զ����
//�������Զ���ʣ��������Ϊ��DOC_EXTRACT_TYPE_USER+1��DOC_EXTRACT_TYPE_USER+2��...

#define PERSON_REQUIRED			0x0001
#define LOCATION_REQUIRED		0x0002
#define ORGANIZATION_REQUIRED	0x0004
#define KEYWORD_REQUIRED		0x0008
#define AUTHOR_REQUIRED			0x0010
#define MEDIA_REQUIRED			0x0100
#define COUNTRY_REQUIRED		0x0200
#define PROVINCE_REQUIRED		0x0400
#define ABSTRACT_REQUIRED		0x0800
#define SENTIWORD_REQUIRED		0x1000
#define SENTIMENT_REQUIRED		0x2000
#define TIME_REQUIRED			0x4000
#define HTML_REMOVER_REQUIRED	0x8000//�Ƿ���Ҫȥ����ҳ��ǩ�Ĺ���ѡ��
#define ALL_REQUIRED			0xffff

#define DOC_EXTRACT_DELIMITER "#"
#define DOC_EXTRACT_TYPE_MAX_LENGTH 600
#define GBK_CODE 0//Ĭ��֧��GBK����
#define UTF8_CODE GBK_CODE+1//UTF8����
#define BIG5_CODE GBK_CODE+2//BIG5����
#define GBK_FANTI_CODE GBK_CODE+3//GBK���룬�������������
typedef  size_t DOC_PARSER_HANDLE;

/*-----------------------------------------------------------------------
* ���ܣ���ʼ��
* ������
*		sPath-default path
*		nEncoding:�������
*		sLicenseCode - ��Ȩ��
* ���أ�true - �ɹ���false - ʧ��
* ��ע���ڽ����д˺�����������������֮ǰ���ã�ֻ��ִ��һ�Σ�
------------------------------------------------------------------------*/
DOCEXTRACTOR_API int DE_Init(const char *sPath=0,int nEncoding=GBK_CODE,const char *sLicenseCode=0);

/*-----------------------------------------------------------------------
* ���ܣ����ɵ��ĵ�ժҪ
* ������sText	    -[IN] �ĵ�����
*	bool bSummaryNeeded=true-[IN]:�Ƿ���Ҫ����ժҪ
*	
*		sUserDefPos:�û��Զ���Ĵ��Ա�ǣ�������֣���������������������ý������ã��������ã�����ͬ����֮�����#�ָ��"gms#gjtgj#g"

*		_tDocExtractResult	-[OUT] �ĵ�Extract result
* ��ע���ڽ����д˺�������ִ�ж��
------------------------------------------------------------------------*/
DOCEXTRACTOR_API DOC_PARSER_HANDLE DE_ParseDocE(const char *sText,const char *sUserDefPos=NULL,bool bSummaryNeeded=true,unsigned int nFuncRequired=ALL_REQUIRED);
//Process a text, and return DOC_PARSER_HANDLE
/*-----------------------------------------------------------------------
* ���ܣ����������DE_ParseDocE����У���ȡָ����ȡ�Ľ������
* ������handle	    -[IN] DE_ParseDocEִ�к󷵻ص�HANDLE
*	int nDocExtractType[IN]:�Ƿ��ȡ�ĳ�ȡ���ͣ���DOC_EXTRACT_TYPE_PERSON��ʼ�Ľ��
* ��ע��������DE_ParseDocE֮��ִ�з��ɣ��˺�������ִ�ж��
------------------------------------------------------------------------*/
DOCEXTRACTOR_API const char *DE_GetResult(DOC_PARSER_HANDLE handle,int nDocExtractType);

/*-----------------------------------------------------------------------
* ���ܣ����������DE_ParseDocE����У���ȡָ�����µ���е÷�
* ������handle	    -[IN] DE_ParseDocEִ�к󷵻ص�HANDLE
* ����ֵ����������÷�
* ��ע��������DE_ParseDocE֮��ִ�з��ɣ��˺�������ִ�ж��
------------------------------------------------------------------------*/
DOCEXTRACTOR_API int DE_GetSentimentScore(DOC_PARSER_HANDLE handle);
/*-----------------------------------------------------------------------
* ���ܣ�DE_ReleaseHandle�ͷ�DE_ParseDocE�����ռ�ݵĿռ�
* ������handle	    -[IN] DE_ParseDocEִ�к󷵻ص�HANDLE
* ����ֵ����
* ��ע��������DE_ParseDocE֮��ִ�з��ɣ��˺�������ִ�ж��
------------------------------------------------------------------------*/
DOCEXTRACTOR_API void DE_ReleaseHandle(DOC_PARSER_HANDLE handle);


DOCEXTRACTOR_API unsigned int DE_ImportSentimentDict(const char *sFilename);//�����û���дʵ�
////�����û��Զ������дʱ�ÿ��һ���ʣ��ո���������Ȩ�أ��磺���ɲ��� -2;
//����������д������´ʣ������û��ʵ��е��룬�������ʶ���Զ���Ծ
DOCEXTRACTOR_API unsigned int DE_ImportUserDict(const char *sFilename,bool bOverwite=false);//�����û��ʵ�
////�����û��Զ���Ĵʵ�
/*********************************************************************
*
*  Func Name  : DE_ImportKeyBlackList
*
*  Description: Import keyword black list
*  Parameters : sFilename: Text filename for user defined blacklist dictionary, each line for a stop keyword
*				 sPOSBlacklist: ͣ�õĴ����б�����Ϊ�ô����б���ʵĴʲ�����ؼ��ʷ�Χ��
*								������Ϊ#nr#ns#��ʾnr,ns����Ϊ�ؼ���
*  Returns    : The  number of  lexical entry imported successfully
*  Author     : Kevin Zhang
*  History    :
*              1.create 2014-6-26
*********************************************************************/

DOCEXTRACTOR_API unsigned int DE_ImportKeyBlackList(const char *sFilename, const char *sPOSBlacklist = 0);//����ؼ��ʺ�����
////�����û��Զ���Ĺؼ��ʺ�����

/*********************************************************************
*
*  Func Name  : DE_AddUserWord
*
*  Description: add a word to the user dictionary ,example:
*				һ��һ·  key
*				��Ҫ��Ϊ�ؼ��ʵģ�����ǰ׺����Ϊkey
*  Parameters : const char *sWord: ���뵽��ʱ�û��ʵ��ص������ԣ��ÿո�ָ�
*
*  Returns    : 1,true ; 0,false
*
*  Author     :
*  History    :
*              1.create 2017/6/3
*********************************************************************/
DOCEXTRACTOR_API int DE_AddUserWord(const char *sWord);
/*********************************************************************
*
*  Func Name  : DE_CleanUserWord
*
*  Description: Clean all temporary added user words
*
*  Parameters :
*  Returns    : 1,true ; 0,false
*
*  Author     :
*  History    :
*              1.create 2017/6/3
*********************************************************************/
DOCEXTRACTOR_API int DE_CleanUserWord();
/*********************************************************************
*
*  Func Name  : DE_SaveTheUsrDic
*
*  Description: Save dictionary to file
*
*  Parameters :
*
*  Returns    : 1,true; 2,false
*
*  Author     :
*  History    :
*              1.create 2017/6/3
*********************************************************************/
DOCEXTRACTOR_API int DE_SaveTheUsrDic();

/*********************************************************************
*
*  Func Name  : DE_DelUsrWord
*
*  Description: delete a word from the  user dictionary
*
*  Parameters :
*  Returns    : -1, the word not exist in the user dictionary; else, the handle of the word deleted
*
*  Author     :
*  History    :
*              1.create 2017/6/3
*********************************************************************/
DOCEXTRACTOR_API int DE_DelUsrWord(const char *sWord);

/*----b--------------------------------------------------------------
* ���ܣ����ɵ��ĵ�ժҪ
* ������sText	    -[IN] �ĵ�����
*	bool bSummaryNeeded=true-[IN]:�Ƿ���Ҫ����ժҪ
*	
*		_tDocExtractResult	-[OUT] �ĵ�Extract result
* ��ע���ڽ����д˺�������ִ�ж��
------------------------------------------------------------------------*/
DOCEXTRACTOR_API int  DE_ComputeSentimentDoc(const char *sText);


DOCEXTRACTOR_API void DE_Exit();

//��ô�����Ϣ
DOCEXTRACTOR_API const char* DE_GetLastErrMsg();
