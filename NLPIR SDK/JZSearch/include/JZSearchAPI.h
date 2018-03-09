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

#if	defined(_WIN32) || defined(WIN64)
#ifdef JZSEARCHAPI_EXPORTS
#define JZSearchAPI_API extern "C"  __declspec(dllexport)
#else
#define JZSearchAPI_API extern "C" __declspec(dllimport)
#endif
#else
#define JZSearchAPI_API extern "C" 
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
JZSearchAPI_API int JZIndexer_FieldAdd(const char *sFieldName,const char *sDBFieldName,int nFieldType,bool bIndexed,bool bRetrieved);
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


JZSearchAPI_API int JZIndexer_FieldSave(const char *sFieldInfoDataFile);
//���������Ϣ�����ļ�
JZSearchAPI_API int JZIndexer_FieldLoad(const char *sFieldInfoDataFile);
//��ȡ�Ѿ�����õ�����Ϣ�����ļ�

JZSearchAPI_API int JZIndexer_FieldImport(const char *sTxtFile);
//��������Ϣ�����ļ�
JZSearchAPI_API int JZIndexer_FieldExport(const char *sTxtFile,int bStatInfo=false);
//��������Ϣ�����ļ�



//////////////////////////////////////////////////////////////////////////
//
//	���²���Ϊ����������API
//
//////////////////////////////////////////////////////////////////////////
#define INDEX_ENCODING_GBK 0
#define INDEX_ENCODING_UTF8 INDEX_ENCODING_GBK+1
#define INDEX_ENCODING_BIG5 INDEX_ENCODING_GBK+2
#define INDEX_ENCODING_GBK_FANTI INDEX_ENCODING_GBK+3//GBK�а��������֣�ͳһ���ݣ��Ƽ�ʹ��INDEX_ENCODING_GBK
#define INDEX_ENCODING_COUNT 4

#define LANGUAGE_TYPE_UNKNOWN 0
#define LANGUAGE_TYPE_CHINESE 1
#define LANGUAGE_TYPE_UYGHAN 2


JZSearchAPI_API int JZIndexer_Init(const char *sDictPath=0,const char *sFieldInfoFile=0,int encoding=INDEX_ENCODING_GBK,int bICTCLAS=false,int lang_type=LANGUAGE_TYPE_CHINESE,const char*sLicenceCode=NULL);
//����ϵͳ��ʼ���������ʼ���󣬲���ʹ��CJZIndexer
//sDictPath���ʵ��ļ�����Ϊ��ʱ������n-gram��������
//sFieldInfoFile:���ֶ���Ϣ������֧�ֶ���������Ϊ����ֻ֧��һ���ֶ�

#define JZINDEX_STATUS_NORMAL 0//����״̬
#define JZINDEX_STATUS_PROCESSING 1//�������������У�����������
#define JZINDEX_STATUS_MERGE 2//���ڹ鲢�����У�����������
#define JZINDEX_STATUS_RELOAD 3//�������¼��ع����У�����������
#define JZINDEX_STATUS_UPDATED 4//���µ��������ݣ���������û�и��¹���
#define JZINDEX_STATUS_BACKUP 5//backup status,added in 2013/8/15
JZSearchAPI_API int JZIndexer_SetStatus(int nStatus);
//����ϵͳ������״̬�������ں����Ĳٿ�

JZSearchAPI_API int JZIndexer_Exit();
//ϵͳ�˳�



//������������
#ifdef OS_LINUX
class  CJZIndexer {
#else
class  __declspec(dllexport) CJZIndexer {
#endif
//class JZSearchAPI_API CJZIndexer {
public:
	//�ڴ��С����
	CJZIndexer(const char *pcIndexFile,int nMaxMemSize=512000000,int bIncrementalIndex=0 );

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

	int IdIndexing(int term_id,const char *sFieldName=0,int nOffset=0xff,const char *sStoreData=NULL);
	//��ID����,
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ
	//sStoreData: need to store

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

JZSearchAPI_API SEARCHER_HANDLE JZSearch_Init(const char *sIndexFile,const char *sDictPath=0,const char *sFieldInfoFile=0,size_t MaxMemSize=512000000,int encoding=INDEX_ENCODING_GBK,int nGroupMaxCount=0,int bICTCLAS=false,int lang_type=LANGUAGE_TYPE_CHINESE,const char*sLicenceCode=NULL);
//����ϵͳ��ʼ���������ʼ���󣬲���ʹ��CJZSearcher
//sDictPath���ʵ��ļ�����Ϊ��ʱ������n-gram��������
//sIndexFile�������ļ�

JZSearchAPI_API int JZSearch_Exit(SEARCHER_HANDLE handle=0);
//��handle��������ϵͳ�˳������(handle==0)����Ҫ���˳������������ڴ濪��

JZSearchAPI_API int JZSearch_Reload(SEARCHER_HANDLE handle=0);
//ϵͳ�����������º����¼���

JZSearchAPI_API unsigned int JZSearch_SetResultLimit(unsigned int nMaxResultLimit=1000);
//�趨���ؽ��������

JZSearchAPI_API const char * JZSearch_ReloadBlackList(void);
//�������ôʺ��������º����¼���

JZSearchAPI_API const char * JZSearch_ReloadQueryExpand(void);
//������չ�ʸ��º����¼���

JZSearchAPI_API size_t JZSearch_AddSimDict(const char *sLine);
//���ڴ��У�����ͬ���
//��ʽ  w1 w1a w1b##w2 w2a w2b##w3 w3a w3b
//�磺 ���� ������##������ ����
/*********************************************************************
*
*  Func Name  : JZSearch_CleanQueryExpand
*
*  Description: Clean QueryExpand dictionary
*
*  Parameters : none
*
*  Returns    : prompt message
*
*  Author    :    NLPIR.org
*  History    :
*              1.create 9:9:2016
*********************************************************************/
JZSearchAPI_API bool JZSearch_CleanQueryExpand(void);

JZSearchAPI_API size_t JZSearch_AddSimDictFile(const char *sSimDictFile, const char *sAssociateDictFile);
//��ͬ��ʱ��ļ�����չ�ʱ�������ͬ��ʣ����¼���
//��ʽ  w1 w1a w1b##w2 w2a w2b##w3 w3a w3b
//�磺 ���� ������##������ ����

JZSearchAPI_API int JZSearch_ListFieldAllValue(const char *sFieldLine,const char *sExportFile,bool bDuplicateErase=false,SEARCHER_HANDLE handle=1);
//�г�ָ���ֶ�����������

JZSearchAPI_API int JZSearch_Export(const char *sExportFile,char arg,SEARCHER_HANDLE handle=1);
//�����ڲ������ݣ��Ա�˲�

JZSearchAPI_API int JZSearch_ExportTF(const char *sExportFile,SEARCHER_HANDLE handle=1);
//�����ڲ��Ĵ�Ƶ���ݣ��Ա�˲飻added in 2015/7/5

JZSearchAPI_API int JZSearch_ExportTerm(int nTermID,const char *sExportFile,SEARCHER_HANDLE handle=0);
//�����ڲ������ݣ��Ա�˲�

JZSearchAPI_API int JZSearch_Merge(SEARCHER_HANDLE handle=0);
//ϵͳ�Զ��Ż���

JZSearchAPI_API int JZSearch_Backup(const char *sFilename=0,SEARCHER_HANDLE handle=0);
//ϵͳ���������Զ����ݣ�һ�㲻�����û�����ʹ�ã�ϵͳ���Զ�����

JZSearchAPI_API int JZSearch_Restore(SEARCHER_HANDLE handle=0);
//ϵͳ���������Զ��ظ���һ�㲻�����û�����ʹ�ã�ϵͳ�����޷����ص�ǰ����ʱ�Զ��ָ�

typedef struct tRESULT_RECORD {//��������ṹ�����ڼ�������ʹ��
	int doc_id;
	int offset;//�����ֶ��ڵ�ƫ����
	double score;//�����õĴ�ֻ���
}RESULT_RECORD;
typedef RESULT_RECORD * RESULT_RECORD_VECTOR;
#ifdef OS_LINUX
class  CJZSearcher {
#else
class  __declspec(dllexport) CJZSearcher {
#endif
public:
	CJZSearcher(int sort_type=SORT_TYPE_RELEVANCE,SEARCHER_HANDLE handle=1);
	~CJZSearcher(void);
	// TODO: add your methods here.
	
	const char * Search(const char *query_line,int nStart,int nPageCount,const char *sResultName=0,bool bMemUsed=false,int *n_pResultCountRet=0);
	//query_line: ��ѯ���ʽ
	//nStart:��¼��ʼ��ַ
	//nPageCount����ǰҳ���ؽ����Ŀ
	//nPageCount=-1:��ǰҳ��Ҫ�������еĽ����Ŀ
	//sResultName������洢��XML��ַ
	//bMemUsed:false,������ֵ��ļ��У��ļ�����sResultNameָ��������sResultNameΪ�ڴ���ʼ��ַ

	const RESULT_RECORD_VECTOR Search(const char *query_line,int *p_nResultCountRet,bool bNoSort=false,RESULT_RECORD_VECTOR pVecFKs=0,int nFKCount=0,const char *sFKFieldName=0);
	//query_line: ��ѯ���ʽ
	//p_nResultCountRet:�����������
	//bool bNoSort:�������������
	
	int Search(const char *query_line,std::vector<int> &vecDocID);
	//query_line: ��ѯ���ʽ
	//vecDocID�����DocID����
	//Return the result count
	//added in 2013/8/15

	//int GetDF(int nTermID, const char * sFiledName);
	//Get Document DF
	//const RESULT_RECORD_VECTOR GetInvertPostList(int nTermID, const char * sFiledName,int *p_nResultCountRet);

	//Get field value according to docID and fieldName
	const char * GetFiledValue(int nDocID, const char * sFiledName);
	////nDocID:Ҫ��ȡ�ļ����������ţ���0��ʼ
	////sFiledName:Ҫ��ȡ���������	
	//added in 2013/8/15

	const char *GetResultBuf(const char *pcQuery, int nQuerySize, int &nBufSize,int nProtocol=2);//
	//��Search(const char *query_line,int nStart,int nPageCount,const char *sResultName=0)���ʹ�ã���ȡ�����������
	//�ṩ��DBTSearch�����ʹ�ã���DBTSearch�ͻ��˱�̽ӿڽ���;Ӧ�ÿ������������

	const RESULT_RECORD_VECTOR  GetForeignKeyValues(const char *sFieldName, int *nResultCountRet);
	//��Search(const char *query_line,int nStart,int nPageCount,const char *sResultName=0)���ʹ�ã���ȡ�����������
	//ָ�����ݵ�ֵ�б�

	bool DocDelete(int doc_id);

private://���²���Ϊϵͳʹ�ã�Ӧ�ÿ����߲�Ҫ��д��ֻ�ܶ�ȡ����
	int m_nSearcherHandle;//Searcher handle;added in 2012/9/10
	int m_nHandle;
	int m_nSortType;//���򷽷����

	char *m_pResultBuf;
	int m_nResultMaxSize;//��󳤶�
};



//Added in 2015/3/6
#define JZSEARCH_HANDLE int 

JZSearchAPI_API JZSEARCH_HANDLE  JZIndexer_NewInstance(const char *pcIndexFile,int nMaxMemSize=512000000,int bIncrementalIndex=0);
//����ʵ��ʧ�ܣ��򷵻�Ϊ-1������Ϊʵ����Handle
//bIncrementalIndex=1: ����������

JZSearchAPI_API int JZIndexer_MemIndexing(JZSEARCH_HANDLE handle,const char *pText,const char *sFieldName=0,int nMemSize=0);
//handleΪJZIndexer_NewInstance���صĽ��
//����һ���ڴ棬��
//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ

JZSearchAPI_API int JZIndexer_FileIndexing(JZSEARCH_HANDLE handle,const char *sTextFilename,const char *sFieldName=0);
//����һ���ı��ļ���
//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ

JZSearchAPI_API int JZIndexer_BigFileIndexing(JZSEARCH_HANDLE handle,const char *sBigFilename,unsigned int nOffset,unsigned int nSize,const char *sFieldName=0);
	//����һ��Big File��ָ����ƫ�����ͳ��ȵ��ı��ļ���
	//sBigFilename: Big File���ļ�����
	//nOffset:ƫ������
	//nSize: �ļ�����
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ

JZSearchAPI_API int JZIndexer_IntIndexing(JZSEARCH_HANDLE handle,int value,const char *sFieldName=0);
//����ֵ��������,
//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ
#ifndef _WIN32
	int JZIndexer_LongIndexing(JZSEARCH_HANDLE handle,long long value,const char *sFieldName=0);
	//��64λ��ֵ��������,
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ
#else
JZSearchAPI_API int JZIndexer_LongIndexing(JZSEARCH_HANDLE handle,__int64 value,const char *sFieldName=0);
	//��64λ��ֵ��������,
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ
#endif
JZSearchAPI_API int JZIndexer_FloatIndexing(JZSEARCH_HANDLE handle,float value,const char *sFieldName=0);
	//����ֵ��������,
	//sFieldName���ֶ����ƣ�Ϊ�����ʾ���ֶ���Ϣ
JZSearchAPI_API int JZIndexer_Save(JZSEARCH_HANDLE handle);
	//�������������
JZSearchAPI_API int JZIndexer_AddDoc(JZSEARCH_HANDLE handle);//�����ĵ�
JZSearchAPI_API int JZIndexer_DeleteInstance(JZSEARCH_HANDLE handle);



JZSearchAPI_API JZSEARCH_HANDLE  JZSearcher_NewInstance(int sort_type=SORT_TYPE_RELEVANCE,SEARCHER_HANDLE handle=1);
//����ʵ��ʧ�ܣ��򷵻�Ϊ-1������Ϊʵ����Handle

JZSearchAPI_API  const char* JZSearcher_Search(JZSEARCH_HANDLE handle,const char *query_line,int nStart,int nPageCount);
	//query_line: ��ѯ���ʽ
	//nStart:��¼��ʼ��ַ
	//nPageCount����ǰҳ���ؽ����Ŀ
	//��ǰҳ��Ҫ�������еĽ��jason�ַ���
	
JZSearchAPI_API int JZSearcher_DeleteInstance(JZSEARCH_HANDLE handle);
JZSearchAPI_API int JZSearch_SetAbstractArgu(unsigned int nAbstractLength,const char *sTagStart,const char*sTagEnd,int nPrefixLeng=6);
//Set Abstract Argument
//nAbstractLength:ժҪ���ȣ�
//sTagStart��sTagEnd�� ���йؼ��ʵĸ�����ʾǰ���HTML���
//nPrefixLeng: ժҪǰ׺�ĳ���
JZSearchAPI_API int JZSearch_SetIndexSizeLimit(int nLimitSize=20480);
//�����������ݵĳ������ƣ�Ĭ��Ϊ20KB����Ϊ-1��ʾ������

JZSearchAPI_API int JZSearch_SetUniqeCountLimit(int nLimitSize=100);//added in 2015/6/10
//����Unique���������ȥ�����������һ������Ϊ100�����ർ��Ч�ʵ���
//nLimitSize<0�������ƣ�ȫ��ȥ��

JZSearchAPI_API int JZSearch_SetHighlightFull(int nTrue=1);//added in 2016/10/22
//���ø�����ʾ�Ƿ����ֻ��ʾ�����ַ������������������롱�����ܺ��� "����"
//True����1�� ֻ��ʾ�����ַ���
//False: ������ʾ�Ӵ�

JZSearchAPI_API int JZSearch_DocDelete(JZSEARCH_HANDLE handle,int doc_id);//ɾ��handle���������е��ڲ����Ϊdoc_id���ĵ�
JZSearchAPI_API const char * JZSearch_GetLastErrorMsg();//ɾ��handle���������е��ڲ����Ϊdoc_id���ĵ�

#endif
