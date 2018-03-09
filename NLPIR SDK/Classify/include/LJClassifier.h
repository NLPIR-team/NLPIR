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

// ���ܣ�  �ļ���ʽ��ʼ��
// ����ֵ���ɹ�/ʧ��  
//         ������Ϣ��¼��Ӳ�̵�./ljclassifier.log��./DataFile/ljclassifier.log��
CLASSIFIER_API bool classifier_init(const char *conf="rulelist.xml",const char *sInitDirPath="",const char *sLicenseCode=NULL);

// ���ܣ�����������½ṹ���з���
// ������d:���½ṹָ��
//       iType=0:  �������������֮����\t����  ���ݸ�ʽ��������Ҫ��	����	���ϡ�
//       iType=1:  ������������Ŷȣ�����֮����\t������������Ȩ���á� ������   ���ݸ�ʽ��������Ҫ�� 1.00	���� 0.95	���� 0.82��
//       iType Ĭ��ֵΪ0
// ����ֵ���������  ����֮����\t�����������������ŶȴӸߵ�������      
CLASSIFIER_API const char* classifier_exec1(stDoc& d, int iType=0);
CLASSIFIER_API const char* classifier_exec(const char* sTitle,const char*sContent, int iType);
// ���ܣ����ڵ�ǰ�ĵ�������������ȡ�ý����ϸ
// ������classname:�������
// ����ֵ�������ϸ ����:
/*		   RULE3:
		   SUBRULE1: ��Ļ 1	
		   SUBRULE2: ���� 1	���� 3	��Ʊ 8	
		   SUBRULE3: ��ժ 2	*/
CLASSIFIER_API const char* classifier_detail(const char *classname);

// ���ܣ��˳����ͷ���Դ
CLASSIFIER_API void classifier_exit();

CLASSIFIER_API void classifier_setsimthresh(float fSim);

CLASSIFIER_API const char* classifier_GetLastErrorMsg();

#endif //_H_CLASSIFIER_DLL

