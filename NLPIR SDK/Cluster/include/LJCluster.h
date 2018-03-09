/***************************************************
*  Copyright (c) 2009. All rights reserved.
*  Procession or use of this file requires a written 
*  license from the author.
*  
*  Created: 2009-12-23
***************************************************/
#ifndef _H_CLUSTER_DLL
#define _H_CLUSTER_DLL

#ifdef OS_LINUX
#define CLUSTER_API extern "C" 
#else
#ifdef LJCLUSTER_EXPORTS
#define CLUSTER_API extern "C" __declspec(dllexport)
#else
#define CLUSTER_API extern "C"  __declspec(dllimport)
#endif
#endif

#define GBK_CODE 0//Ĭ��֧��GBK����
#define UTF8_CODE GBK_CODE+1//UTF8����
#define BIG5_CODE GBK_CODE+2//BIG5����
#define GBK_FANTI_CODE GBK_CODE+3//GBK���룬�������������


/*-----------------------------------------------------------------------
* ���ܣ���ʼ��
* ������sDefaultPath - ���ݴʵ�Data�ļ������ڵ�·��
*		sLicenseCode - ��Ȩ��
*		encode - ����
* ���أ�true - �ɹ���false - ʧ��
* ��ע���ڽ����д˺�����������������֮ǰ���ã�ֻ��ִ��һ�Σ�
------------------------------------------------------------------------*/
CLUSTER_API bool CLUS_Init(const char *sDefaultPath,const char *sLicenseCode=0,int encode=GBK_CODE);
//�������������ÿ����������ĵ�����ͣ�ô��ļ�·��

/*-----------------------------------------------------------------------
* ���ܣ����ò���
* ������nMaxClus ������ǰ���ٸ���     nMaxDoc ÿ����������ǰ���ٸ��ĵ�   
* ���أ�true - �ɹ���false - ʧ��
* ��ע���ڽ����д˺�����������������֮ǰ����
*       ��������ã�����Ĭ�Ͼ�Ϊ2000�� ����Խ��ϵͳռ���ڴ�Խ�󣬴����ٶ�Խ��
*       ������ڵ��ĵ����Ѱ�����Ҫ�Ժͼ�ʱ���Ź���
------------------------------------------------------------------------*/
CLUSTER_API bool CLUS_SetParameter(int nMaxClus, int nMaxDoc);

/*-----------------------------------------------------------------------
* ���ܣ�׷���ڴ�����
* ������sText           - [IN] �������ݣ���'\0'�������ַ�����
*       sSignature      - [IN] Ψһ��ʶ������'\0'�������ַ�����
* ���أ�true - �ɹ���false - ʧ��
* ��ע���ڽ����д˺��������ڴ�ӡ���֮ǰִ�ж��
------------------------------------------------------------------------*/
CLUSTER_API bool CLUS_AddContent(const char *sText, const char* sSignature);

/*-----------------------------------------------------------------------
* ���ܣ�׷���ļ�����
* ������sFileName       - [IN] �ļ�ȫ·�����ƣ���'\0'�������ַ�����
*       sSignature      - [IN] Ψһ��ʶ������'\0'�������ַ�����
* ���أ�true - �ɹ���false - ʧ��
* ��ע���ڽ����д˺��������ڴ�ӡ���֮ǰִ�ж��
------------------------------------------------------------------------*/
CLUSTER_API bool CLUS_AddFile(const char *sFileName, const char* sSignature);

/*-----------------------------------------------------------------------
* ���ܣ���ӡ���
* ������sXmlFileName    
- [OUT]�������������XML�ļ���ʽ���ڴ���
* ���أ�true - �ɹ���false - ʧ��
------------------------------------------------------------------------*/
CLUSTER_API bool CLUS_GetLatestResult(const char* sXmlFileName);


/*-----------------------------------------------------------------------
* ���ܣ���ӡ���
* ������sXmlFileName    - [OUT]�������������XML�ļ���ʽ���ڴ���
* ���أ�true - �ɹ���false - ʧ��
------------------------------------------------------------------------*/
CLUSTER_API const char* CLUS_GetLatestResultE();

//�����ʷ����
CLUSTER_API void CLUS_CleanData();

//�˳����ͷ���Դ�����̽���ǰ��������ͷ���ռ�õ��ڴ���Դ
CLUSTER_API void CLUS_Exit();

//��ô�����Ϣ
CLUSTER_API const char* CLUS_GetLastErrMsg();

#endif //_H_CLUSTER_DLL


/*��ע��  XML��ʽ

<?xml version="1.0" encoding="gb2312" standalone="yes" ?>
<LJCluster-Result>
<clusnum>2</clusnum>

<clus id="0">
	<feature>�°��� ��ѡ ����</feature>
    <docs num="6">
       <doc>2</doc>
       <doc>3</doc>       
       <doc>35</doc>
       <doc>86</doc>
       <doc>345</doc>
       <doc>975</doc>       
    </docs>
</clus>    

<clus id="1">
	<feature>��־�� Ӱ�� ��Ӱ ���</feature>
    <docs num="4">
       <doc>45</doc>
       <doc>86</doc>       
       <doc>135</doc>
       <doc>286</doc>      
    </docs>
</clus>  
</LJCluster-Result>
*/
