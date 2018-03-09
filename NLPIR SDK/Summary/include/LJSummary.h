/***************************************************
*  Copyright (c) 2009. All rights reserved.
*  Procession or use of this file requires a written 
*  license from the author.
*  
*  Created: 2009-12-30
***************************************************/
#ifndef _H_DOCSUMMARY_DLL
#define _H_DOCSUMMARY_DLL

#if defined(OS_LINUX)
	#define DOCSUMMARY_API  extern "C"
#else
#if defined(LJSUMMARY_EXPORTS)
#define DOCSUMMARY_API extern "C"  __declspec(dllexport)
#else
#define DOCSUMMARY_API extern "C"  __declspec(dllimport)
#endif
#endif

#if defined(ICTCLAS_JNI_EXPORTS)||defined(LJSUMMARY_JNI_EXPORTS) 
#define DOCSUMMARY_API 
#endif

#define GBK_CODE 0//Ĭ��֧��GBK����
#define UTF8_CODE GBK_CODE+1//UTF8����
#define BIG5_CODE GBK_CODE+2//BIG5����
#define GBK_FANTI_CODE GBK_CODE+3//GBK���룬�������������
/*-----------------------------------------------------------------------
* ���ܣ���ʼ��
* ������sLicenseCode - ��Ȩ��
*		sPath-default path
* ���أ�true - �ɹ���false - ʧ��
* ��ע���ڽ����д˺�����������������֮ǰ���ã�ֻ��ִ��һ�Σ�
------------------------------------------------------------------------*/
DOCSUMMARY_API int DS_Init(const char *sPath=0,int nEncoding=GBK_CODE,const char *sLicenseCode=0);

/*-----------------------------------------------------------------------
* ���ܣ����ɵ��ĵ�ժҪ
* ������sText	    -[IN] �ĵ�����
*		fSumRate	-[IN] �ĵ�ժҪռԭ�İٷֱȣ�Ϊ0.00�����ƣ�
*		iSumLen		-[IN] �û��޶���ժҪ����  ��Ϊ0�����ƣ�
*		bHtmlTagRemove-[IN] �Ƿ���Ҫ��ԭ�Ľ���Html��ǩ��ȥ��
* ���أ�ժҪ�ַ����������ؿմ�
* ��ע���ڽ����д˺�������ִ�ж��
------------------------------------------------------------------------*/

DOCSUMMARY_API const char* DS_SingleDoc(const char *sText, float fSumRate=0.00, int iSumLen=250,int bHtmlTagRemove=0);

// DOCSUMMARY_API const char* DS_SingleDoc(const char *sText, float fSumRate=0.00, int iSumLen=250,bool bHtmlTagRemove=false);

/*-----------------------------------------------------------------------
* ���ܣ����ɵ��ĵ�ժҪ�ú���֧�ֶ��̣߳��Ƕ��̰߳�ȫ��
* ������sResult    -[IN] ժҪ����
*		sText	    -[IN] �ĵ�����
*		fSumRate	-[IN] �ĵ�ժҪռԭ�İٷֱȣ�Ϊ0.00�����ƣ�
*		iSumLen		-[IN] �û��޶���ժҪ����  ��Ϊ0�����ƣ�
*		bHtmlTagRemove-[IN] �Ƿ���Ҫ��ԭ�Ľ���Html��ǩ��ȥ��
* ���أ�ժҪ�ַ����������ؿմ�
* ��ע���ڽ����д˺�������ִ�ж��
------------------------------------------------------------------------*/

DOCSUMMARY_API const char* DS_SingleDocE(char *sResult,const char *sText, float fSumRate=0.00, int iSumLen=250,int bHtmlTagRemove=0);

// DOCSUMMARY_API const char* DS_SingleDocE(char *sResult,const char *sText, float fSumRate=0.00, int iSumLen=250,bool bHtmlTagRemove=false);

//
/*-----------------------------------------------------------------------
* ���ܣ����ɵ��ĵ�ժҪ�ú���֧�ֶ��̣߳��Ƕ��̰߳�ȫ��
* ������sTextFilename	    -[IN] �ĵ��ļ���
*		fSumRate	-[IN] �ĵ�ժҪռԭ�İٷֱȣ�Ϊ0.00�����ƣ�
*		iSumLen		-[IN] �û��޶���ժҪ����  ��Ϊ0�����ƣ�
*		bHtmlTagRemove-[IN] �Ƿ���Ҫ��ԭ�Ľ���Html��ǩ��ȥ��
* ���أ�ժҪ�ַ����������ؿմ�
* ��ע���ڽ����д˺�������ִ�ж��
------------------------------------------------------------------------*/
DOCSUMMARY_API const char* DS_FileProcess(const char *sTextFilename, float fSumRate=0.00, int iSumLen=250,int bHtmlTagRemove=0);


//

//�˳����ͷ���Դ�����̽���ǰ��������ͷ���ռ�õ��ڴ���Դ
DOCSUMMARY_API void DS_Exit();

//��ô�����Ϣ
DOCSUMMARY_API const char* DS_GetLastErrMsg();

#endif //_H_DOCSUMMARY_DLL
