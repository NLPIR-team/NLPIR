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
//	以下部分为字段定义的API
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
//字段名称	索引名称	数据类型	是否需要索引	是否需要过滤用	是否需要存储	是否为通配符检索域	解释
//sFieldName:域名称，在索引建立与搜索过程中，域的唯一标示符
//sDBFieldName：对应于数据库的字段名称；在数据库搜索的时候，用于获取数据库的数据
//nFieldType:数据类型
	//FIELD_TYPE_TEXT
	//FIELD_TYPE_INT
	//FIELD_TYPE_LONG
	//FIELD_TYPE_DATETIME
//bIndexed:是否需要索引
//bRetrieved:搜索结果中是否要输出该字段内容
//bGeneral:是否纳入通配搜索的范畴
//bAbstract:是否进行搜索摘要提取并红显


JZSearchAPI_API bool JZIndexer_FieldSave(const char *sFieldInfoDataFile);
//保存的域信息数据文件
JZSearchAPI_API bool JZIndexer_FieldLoad(const char *sFieldInfoDataFile);
//读取已经保存好的域信息数据文件




//////////////////////////////////////////////////////////////////////////
//
//	以下部分为索引建立的API
//
//////////////////////////////////////////////////////////////////////////
#define INDEX_ENCODING_GBK 0
#define INDEX_ENCODING_UTF8 INDEX_ENCODING_GBK+1
#define INDEX_ENCODING_BIG5 INDEX_ENCODING_GBK+2
#define INDEX_ENCODING_GBK_FANTI INDEX_ENCODING_GBK+3//GBK中包含繁体字，统一兼容，推荐使用INDEX_ENCODING_GBK_FANTI
#define INDEX_ENCODING_COUNT 4

#define LANGUAGE_TYPE_UNKNOWN 0
#define LANGUAGE_TYPE_CHINESE 1
#define LANGUAGE_TYPE_UYGHAN 2


JZSearchAPI_API bool JZIndexer_Init(const char *sDictPath=0,const char *sFieldInfoFile=0,int encoding=INDEX_ENCODING_GBK_FANTI,bool bICTCLAS=false,int lang_type=LANGUAGE_TYPE_CHINESE,const char*sLicenceCode=NULL);
//索引系统初始化，必须初始化后，才能使用CJZIndexer
//sDictPath：词典文件名；为空时，采用n-gram索引方法
//sFieldInfoFile:域字段信息，用于支持多域索引，为空则只支持一个字段

JZSearchAPI_API bool JZIndexer_Exit();
//系统退出

//建立索引的类
class JZSearchAPI_API CJZIndexer {
public:
	//内存大小控制
	CJZIndexer(const char *pcIndexFile,int nMaxMemSize=512000000 );

	~CJZIndexer(void);
	// TODO: add your methods here.
	int MemIndexing(const char *pText,const char *sFieldName=0,int nMemSize=0);
	//索引一段内存，，
	//sFieldName：字段名称，为空则表示无字段信息

	int FileIndexing(const char *sTextFilename,const char *sFieldName=0);
	//索引一个文本文件，
	//sFieldName：字段名称，为空则表示无字段信息

	int BigFileIndexing(const char *sBigFilename,unsigned int nOffset,unsigned int nSize,const char *sFieldName=0);
	//索引一个Big File中指定的偏移量和长度的文本文件，
	//sBigFilename: Big File的文件名；
	//nOffset:偏移量；
	//nSize: 文件长度
	//sFieldName：字段名称，为空则表示无字段信息

	int IdIndexing(int term_id,const char *sFieldName=0);
	//词ID索引,
	//sFieldName：字段名称，为空则表示无字段信息

	int IntIndexing(int value,const char *sFieldName=0);
	//对数值进行索引,
	//sFieldName：字段名称，为空则表示无字段信息
#ifndef _WIN32
	int LongIndexing(long long value,const char *sFieldName=0);
	//对64位数值进行索引,
	//sFieldName：字段名称，为空则表示无字段信息
#else
	int LongIndexing(__int64 value,const char *sFieldName=0);
	//对64位数值进行索引,
	//sFieldName：字段名称，为空则表示无字段信息
#endif
	int FloatIndexing(float value,const char *sFieldName=0);
	//对数值进行索引,

	//sFieldName：字段名称，为空则表示无字段信息
	bool Save();
	//索引保存的名称
	
	//索引保存的名称
	int Merge();
	//索引合并
	
	int AddDoc();//增加文档
	int GetStatus();//获取系统状态，1：表示CIndexer构建成功
private://以下部分为系统使用，应用开发者不要改写，只能读取数据
	int m_nHandle;//索引器的Handle，无需调用申请
	int m_nStatus;
	char m_sBigfilename[1000];//big filename,added in 2011/12/4
	FILE *m_fpBigFile;//Big File pointer,added in 2011/12/4
};


//////////////////////////////////////////////////////////////////////////
//
//	以下部分为搜索API
//
//////////////////////////////////////////////////////////////////////////

#define SORT_TYPE_DOCID 1//按照Doc ID排序，默认方式
#define SORT_TYPE_RELEVANCE 2//按照相关度排序
#define SORT_TYPE_DOCID_REVERSE 3//按照Doc ID倒序排序，默认方式
#define  SEARCHER_HANDLE int

JZSearchAPI_API SEARCHER_HANDLE JZSearch_Init(const char *sIndexFile,const char *sDictPath=0,const char *sFieldInfoFile=0,int MaxMemSize=512000000,int encoding=INDEX_ENCODING_GBK_FANTI,int nGroupMaxCount=0,bool bICTCLAS=false,int lang_type=LANGUAGE_TYPE_CHINESE,const char*sLicenceCode=NULL);
//检索系统初始化，必须初始化后，才能使用CJZSearcher
//sDictPath：词典文件名；为空时，采用n-gram索引方法
//sIndexFile：索引文件

JZSearchAPI_API bool JZSearch_Exit(SEARCHER_HANDLE handle=0);
//第handle个搜索器系统退出，如果(handle==0)，则要求退出并销毁所有内存开销

JZSearchAPI_API bool JZSearch_Reload(SEARCHER_HANDLE handle=0);
//系统索引增量更新后，重新加载

JZSearchAPI_API const char * JZSearch_ReloadBlackList(void);
//搜索禁用词黑名单更新后，重新加载

JZSearchAPI_API const char * JZSearch_ReloadQueryExpand(void);
//搜索扩展词更新后，重新加载

JZSearchAPI_API int JZSearch_ListFieldAllValue(const char *sFieldLine,const char *sExportFile,bool bDuplicateErase=false,SEARCHER_HANDLE handle=1);
//列出指定字段索引的内容

JZSearchAPI_API bool JZSearch_Export(const char *sExportFile,const char *sWordList,char arg,SEARCHER_HANDLE handle=0);
//导出内部的数据，以便核查

JZSearchAPI_API bool JZSearch_Export(int nTermID,const char *sExportFile,const char *sWordList,SEARCHER_HANDLE handle=0);
//导出内部的数据，以便核查

JZSearchAPI_API bool JZSearch_Merge(SEARCHER_HANDLE handle=0);
//系统自动优化，对索引信息进行归并处理

JZSearchAPI_API bool JZSearch_Backup(const char *sFilename=0,SEARCHER_HANDLE handle=0);
//系统索引数据自动备份，一般不建议用户自行使用，系统会自动备份

JZSearchAPI_API bool JZSearch_Restore(SEARCHER_HANDLE handle=0);
//系统索引数据自动回复，一般不建议用户自行使用，系统会在无法加载当前数据时自动恢复

typedef struct tRESULT_RECORD {//搜索结果结构，用于检索计算使用
	int doc_id;
	int offset;//在域字段内的偏移量
	double score;//排序用的打分机制
}RESULT_RECORD;
typedef RESULT_RECORD * RESULT_RECORD_VECTOR;
class JZSearchAPI_API  CJZSearcher{
public:
	CJZSearcher(int sort_type=SORT_TYPE_DOCID,SEARCHER_HANDLE handle=1);
	~CJZSearcher(void);
	// TODO: add your methods here.
	
	void Search(const char *query_line,int nStart,int nPageCount,const char *sResultName=0);
	//query_line: 查询表达式
	//nStart:记录起始地址
	//nPageCount：当前页返回结果数目
	//nPageCount=-1:当前页需要返回所有的结果数目
	//sResultName：结果存储的XML地址

	const RESULT_RECORD_VECTOR Search(const char *query_line,int *p_nResultCountRet,bool bNoSort=false);
	//query_line: 查询表达式
	//p_nResultCountRet:搜索结果总数
	//bool bNoSort:不进行排序操作
	
	int Search(const char *query_line,std::vector<int> &vecDocID);
	//query_line: 查询表达式
	//vecDocID：结果DocID数组
	//Return the result count
	//added in 2013/8/15

	//Get field value according to docID and fieldName
	const char * GetFiledValue(int nDocID, const char * sFiledName);
	////nDocID:要获取的检索结果的序号，从0开始
	////sFiledName:要获取的域的名称	
	//added in 2013/8/15

	const char *GetResultBuf(const char *pcQuery, int nQuerySize, int &nBufSize);
	//与Search(const char *query_line,int nStart,int nPageCount,const char *sResultName=0)配合使用，获取检索结果内容
	//提供给DBTSearch服务端使用，由DBTSearch客户端编程接口解析;应用开发者无需调用

	const RESULT_RECORD_VECTOR  GetForeignKeyValues(const char *sFieldName, int *nResultCountRet);
	//与Search(const char *query_line,int nStart,int nPageCount,const char *sResultName=0)配合使用，获取检索结果内容
	//指定内容的值列表

	int FilterWithForeignKeyValues(const char *sFieldName, RESULT_RECORD_VECTOR pVecValues,int nResultCount,const char *sQueryLine);
	//

	bool DocDelete(int doc_id);

private://以下部分为系统使用，应用开发者不要改写，只能读取数据
	int m_nSearcherHandle;//Searcher handle;added in 2012/9/10
	int m_nHandle;
	int m_nSortType;//排序方法编号

	char *m_pResultBuf;
	int m_nResultMaxSize;//最大长度
};
#endif
