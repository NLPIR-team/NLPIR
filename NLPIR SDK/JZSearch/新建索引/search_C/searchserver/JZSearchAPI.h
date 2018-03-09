/****************************************************************************
 *
 * Copyright (c) 2011
 *     Kevin Zhang
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          JZSearchAPI.h: definition of the JZSearch API
 * Author:   Kevin Zhang 
 *          (pipy_zhang@msn.com) www.nlpir.org
 * Date:     2011-8-20
 *
 * Notes:
 *                
 ****************************************************************************/
#if !defined(__JZSEARCH_2010_LIB_INCLUDED__)
#define __JZSEARCH_2010_LIB_INCLUDED__

#ifdef _WIN32
#ifdef JZSEARCHAPI_EXPORTS
#define JZSearchAPI_API __declspec(dllexport)
#else
#define JZSearchAPI_API __declspec(dllimport)
#endif
#else
#define JZSearchAPI_API
#endif
#include <stdio.h>
#include <vector>
//////////////////////////////////////////////////////////////////////////
//
//	���²���Ϊ�ֶζ����API
//
//////////////////////////////////////////////////////////////////////////

#define FIELD_TYPE_TEXT 1
#define FIELD_TYPE_INT 2
#define FIELD_TYPE_LONG 3
#define FIELD_TYPE_DATETIME 4
#define FIELD_TYPE_FLOAT 5
#define DATA_TYPE_BIGTEXT 6
#define FIELD_TYPE_NAME 8
JZSearchAPI_API bool JZIndexer_FieldAdd(const char *sFieldName,const char *sDBFieldName,int nFieldType,bool bIndexed,bool bRetrieved,bool bGeneral=false,bool bAbstracted=false);
//�ֶ�����	��������	��������	�Ƿ���Ҫ����	�Ƿ���Ҫ������	�Ƿ���Ҫ�洢	�Ƿ�Ϊͨ���������	����
//sFieldName:�����ƣ����������������������У����Ψһ��ʾ��
//sDBFieldName����Ӧ�����ݿ���ֶ����ƣ������ݿ�������ʱ�����ڻ�ȡ���ݿ������
//nFieldType:��������
	//FIELD_TYPE_TEXT
	//FIELD_TYPE_INT
	//FIELD_TYPE_LONG
	//FIELD_TYPE_DATETIME
//bIndexed:�Ƿ���Ҫ����
//bRetrieved:����������Ƿ�Ҫ������ֶ�����
//bGeneral:�Ƿ�����ͨ�������ķ���
//bAbstract:�Ƿ��������ժҪ��ȡ������


JZSearchAPI_API bool JZIndexer_FieldSave(const char *sFieldInfoDataFile);
//���������Ϣ�����ļ�
JZSearchAPI_API bool JZIndexer_FieldLoad(const char *sFieldInfoDataFile);
//��ȡ�Ѿ�����õ�����Ϣ�����ļ�




//////////////////////////////////////////////////////////////////////////
//
//	���²���Ϊ����������API
//
//////////////////////////////////////////////////////////////////////////
#define INDEX_ENCODING_GBK 0
#define INDEX_ENCODING_UTF8 INDEX_ENCODING_GBK+1
#define INDEX_ENCODING_BIG5 INDEX_ENCODING_GBK+2
#define INDEX_ENCODING_GBK_FANTI INDEX_ENCODING_GBK+3//GBK�а��������֣�ͳһ���ݣ��Ƽ�ʹ��INDEX_ENCODING_GBK_FANTI
#define INDEX_ENCODING_COUNT 4

#define LANGUAGE_TYPE_UNKNOWN 0
#define LANGUAGE_TYPE_CHINESE 1
#define LANGUAGE_TYPE_UYGHAN 2


JZSearchAPI_API bool JZIndexer_Init(const char *sDictPath=0,const char *sFieldInfoFile=0,int encoding=INDEX_ENCODING_GBK_FANTI,bool bICTCLAS=false,int lang_type=LANGUAGE_TYPE_CHINESE,const char*sLicenceCode=NULL);
//����ϵͳ��ʼ���������ʼ���󣬲���ʹ��CJZIndexer
//sDictPath���ʵ��ļ�����Ϊ��ʱ������n-gram��������
//sFieldInfoFile:���ֶ���Ϣ������֧�ֶ���������Ϊ����ֻ֧��һ���ֶ�

JZSearchAPI_API bool JZIndexer_Exit();
//ϵͳ�˳�

//������������
class JZSearchAPI_API CJZIndexer {
public:
	//�ڴ��С����
	CJZIndexer(const char *pcIndexFile,int nMaxMemSize=512000000 );

	~CJZIndexer(void);
	// TODO: add your methods here.
	int MemIndexing(const char *pText,const char *sFieldName=0,int nMemSize=0);
	//����һ���ڴ棬��
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ

	int FileIndexing(const char *sTextFilename,const char *sFieldName=0);
	//����һ���ı��ļ���
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ

	int BigFileIndexing(const char *sBigFilename,unsigned int nOffset,unsigned int nSize,const char *sFieldName=0);
	//����һ��Big File��ָ����ƫ�����ͳ��ȵ��ı��ļ���
	//sBigFilename: Big File���ļ�����
	//nOffset:ƫ������
	//nSize: �ļ�����
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ

	int IdIndexing(int term_id,const char *sFieldName=0);
	//��ID����,
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ

	int IntIndexing(int value,const char *sFieldName=0);
	//����ֵ��������,
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ
#ifndef _WIN32
	int LongIndexing(long long value,const char *sFieldName=0);
	//��64λ��ֵ��������,
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ
#else
	int LongIndexing(__int64 value,const char *sFieldName=0);
	//��64λ��ֵ��������,
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ
#endif
	int FloatIndexing(float value,const char *sFieldName=0);
	//����ֵ��������,

	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ
	bool Save();
	//�������������
	
	//�������������
	int Merge();
	//�����ϲ�
	
	int AddDoc();//�����ĵ�
	int GetStatus();//��ȡϵͳ״̬��1����ʾCIndexer�����ɹ�
private://���²���Ϊϵͳʹ�ã�Ӧ�ÿ����߲�Ҫ��д��ֻ�ܶ�ȡ����
	int m_nHandle;//��������Handle�������������
	int m_nStatus;
	char m_sBigfilename[1000];//big filename,added in 2011/12/4
	FILE *m_fpBigFile;//Big File pointer,added in 2011/12/4
};


//////////////////////////////////////////////////////////////////////////
//
//	���²���Ϊ����API
//
//////////////////////////////////////////////////////////////////////////

#define SORT_TYPE_DOCID 1//����Doc ID����Ĭ�Ϸ�ʽ
#define SORT_TYPE_RELEVANCE 2//������ض�����
#define SORT_TYPE_DOCID_REVERSE 3//����Doc ID��������Ĭ�Ϸ�ʽ
#define  SEARCHER_HANDLE int

JZSearchAPI_API SEARCHER_HANDLE JZSearch_Init(const char *sIndexFile,const char *sDictPath=0,const char *sFieldInfoFile=0,int MaxMemSize=512000000,int encoding=INDEX_ENCODING_GBK_FANTI,int nGroupMaxCount=0,bool bICTCLAS=false,int lang_type=LANGUAGE_TYPE_CHINESE,const char*sLicenceCode=NULL);
//����ϵͳ��ʼ���������ʼ���󣬲���ʹ��CJZSearcher
//sDictPath���ʵ��ļ�����Ϊ��ʱ������n-gram��������
//sIndexFile�������ļ�

JZSearchAPI_API bool JZSearch_Exit(SEARCHER_HANDLE handle=0);
//��handle��������ϵͳ�˳������(handle==0)����Ҫ���˳������������ڴ濪��

JZSearchAPI_API bool JZSearch_Reload(SEARCHER_HANDLE handle=0);
//ϵͳ�����������º����¼���

JZSearchAPI_API const char * JZSearch_ReloadBlackList(void);
//�������ôʺ��������º����¼���

JZSearchAPI_API const char * JZSearch_ReloadQueryExpand(void);
//������չ�ʸ��º����¼���

JZSearchAPI_API int JZSearch_ListFieldAllValue(const char *sFieldLine,const char *sExportFile,bool bDuplicateErase=false,SEARCHER_HANDLE handle=1);
//�г�ָ���ֶ�����������

JZSearchAPI_API bool JZSearch_Export(const char *sExportFile,const char *sWordList,char arg,SEARCHER_HANDLE handle=0);
//�����ڲ������ݣ��Ա�˲�

JZSearchAPI_API bool JZSearch_Export(int nTermID,const char *sExportFile,const char *sWordList,SEARCHER_HANDLE handle=0);
//�����ڲ������ݣ��Ա�˲�

JZSearchAPI_API bool JZSearch_Merge(SEARCHER_HANDLE handle=0);
//ϵͳ�Զ��Ż�����������Ϣ���й鲢����

JZSearchAPI_API bool JZSearch_Backup(const char *sFilename=0,SEARCHER_HANDLE handle=0);
//ϵͳ���������Զ����ݣ�һ�㲻�����û�����ʹ�ã�ϵͳ���Զ�����

JZSearchAPI_API bool JZSearch_Restore(SEARCHER_HANDLE handle=0);
//ϵͳ���������Զ��ظ���һ�㲻�����û�����ʹ�ã�ϵͳ�����޷����ص�ǰ����ʱ�Զ��ָ�

typedef struct tRESULT_RECORD {//��������ṹ�����ڼ�������ʹ��
	int doc_id;
	int offset;//�����ֶ��ڵ�ƫ����
	double score;//�����õĴ�ֻ���
}RESULT_RECORD;
typedef RESULT_RECORD * RESULT_RECORD_VECTOR;
class JZSearchAPI_API  CJZSearcher{
public:
	CJZSearcher(int sort_type=SORT_TYPE_DOCID,SEARCHER_HANDLE handle=1);
	~CJZSearcher(void);
	// TODO: add your methods here.
	
	void Search(const char *query_line,int nStart,int nPageCount,const char *sResultName=0);
	//query_line: ��ѯ���ʽ
	//nStart:��¼��ʼ��ַ
	//nPageCount����ǰҳ���ؽ����Ŀ
	//nPageCount=-1:��ǰҳ��Ҫ�������еĽ����Ŀ
	//sResultName������洢��XML��ַ

	const RESULT_RECORD_VECTOR Search(const char *query_line,int *p_nResultCountRet,bool bNoSort=false);
	//query_line: ��ѯ���ʽ
	//p_nResultCountRet:�����������
	//bool bNoSort:�������������
	
	int Search(const char *query_line,std::vector<int> &vecDocID);
	//query_line: ��ѯ���ʽ
	//vecDocID�����DocID����
	//Return the result count
	//added in 2013/8/15

	//Get field value according to docID and fieldName
	const char * GetFiledValue(int nDocID, const char * sFiledName);
	////nDocID:Ҫ��ȡ�ļ����������ţ���0��ʼ
	////sFiledName:Ҫ��ȡ���������	
	//added in 2013/8/15

	const char *GetResultBuf(const char *pcQuery, int nQuerySize, int &nBufSize);
	//��Search(const char *query_line,int nStart,int nPageCount,const char *sResultName=0)���ʹ�ã���ȡ�����������
	//�ṩ��DBTSearch�����ʹ�ã���DBTSearch�ͻ��˱�̽ӿڽ���;Ӧ�ÿ������������

	const RESULT_RECORD_VECTOR  GetForeignKeyValues(const char *sFieldName, int *nResultCountRet);
	//��Search(const char *query_line,int nStart,int nPageCount,const char *sResultName=0)���ʹ�ã���ȡ�����������
	//ָ�����ݵ�ֵ�б�

	int FilterWithForeignKeyValues(const char *sFieldName, RESULT_RECORD_VECTOR pVecValues,int nResultCount,const char *sQueryLine);
	//

	bool DocDelete(int doc_id);

private://���²���Ϊϵͳʹ�ã�Ӧ�ÿ����߲�Ҫ��д��ֻ�ܶ�ȡ����
	int m_nSearcherHandle;//Searcher handle;added in 2012/9/10
	int m_nHandle;
	int m_nSortType;//���򷽷����

	char *m_pResultBuf;
	int m_nResultMaxSize;//��󳤶�
};
#endif
