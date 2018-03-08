// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 DOCEXTRACTOR_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// DOCEXTRACTOR_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef DOCEXTRACTOR_EXPORTS
#define DOCEXTRACTOR_API extern "C" __declspec(dllexport)
#else
#define DOCEXTRACTOR_API extern "C" __declspec(dllimport)
#endif
#ifdef OS_LINUX
#define DOCEXTRACTOR_API extern "C"  
#endif
#include <stddef.h>

#define DOC_EXTRACT_TYPE_PERSON 0//输出的人名
#define DOC_EXTRACT_TYPE_LOCATION 1//输出的地名
#define DOC_EXTRACT_TYPE_ORGANIZATION 2//输出的机构名
#define DOC_EXTRACT_TYPE_KEYWORD 3//输出的关键词
#define DOC_EXTRACT_TYPE_AUTHOR 4//输出的文章作者
#define DOC_EXTRACT_TYPE_MEDIA 5//输出的媒体
#define DOC_EXTRACT_TYPE_COUNTRY 6//输出的文章对应的所在国别
#define DOC_EXTRACT_TYPE_PROVINCE 7//输出的文章对应的所在省份
#define DOC_EXTRACT_TYPE_ABSTRACT 8//输出文章的摘要
#define DOC_EXTRACT_TYPE_POSITIVE 9//输出文章的正面情感词
#define DOC_EXTRACT_TYPE_NEGATIVE 10//输出文章的副面情感词
#define DOC_EXTRACT_TYPE_TEXT 11//输出文章去除网页等标签后的正文
#define DOC_EXTRACT_TYPE_USER 12//用户自定义的词类，第一个自定义词
//后续的自定义词，依次序号为：DOC_EXTRACT_TYPE_USER+1；DOC_EXTRACT_TYPE_USER+2；...

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
#define USER_REQUIRED			0x4000
#define HTML_REMOVER_REQUIRED	0x8000//是否需要去除网页标签的功能选项
#define ALL_REQUIRED			0xffff

#define DOC_EXTRACT_DELIMITER "#"
#define DOC_EXTRACT_TYPE_MAX_LENGTH 600
#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
typedef  size_t DOC_PARSER_HANDLE;

/*-----------------------------------------------------------------------
* 功能：初始化
* 参数：
*		sPath-default path
*		nEncoding:编码类别
*		sLicenseCode - 授权码
* 返回：true - 成功；false - 失败
* 备注：在进程中此函数必须在其他函数之前调用（只需执行一次）
------------------------------------------------------------------------*/
DOCEXTRACTOR_API int DE_Init(const char *sPath=0,int nEncoding=GBK_CODE,const char *sLicenseCode=0);

/*-----------------------------------------------------------------------
* 功能：生成单文档摘要
* 参数：sText	    -[IN] 文档内容
*	bool bSummaryNeeded=true-[IN]:是否需要计算摘要
*	
*		sUserDefPos:用户自定义的词性标记，最多三种（人名、地名、机构名、媒体等内置，无需设置），不同词类之间采用#分割，如"gms#gjtgj#g"

*		_tDocExtractResult	-[OUT] 文档Extract result
* 备注：在进程中此函数可以执行多次
------------------------------------------------------------------------*/
DOCEXTRACTOR_API DOC_PARSER_HANDLE DE_ParseDocE(const char *sText,const char *sUserDefPos=NULL,bool bSummaryNeeded=true,unsigned int nFuncRequired=ALL_REQUIRED);
//Process a text, and return DOC_PARSER_HANDLE
DOCEXTRACTOR_API const char *DE_GetResult(DOC_PARSER_HANDLE handle,int nDocExtractType);
DOCEXTRACTOR_API int DE_GetSentimentScore(DOC_PARSER_HANDLE handle);
DOCEXTRACTOR_API void DE_ReleaseHandle(DOC_PARSER_HANDLE handle);
////导入用户自定义的情感词表，每行一个词，空格后加上正负权重，如：语焉不详 -2;
//如果导入的情感词属于新词，现在用户词典中导入，否则情感识别自动跳跃

DOCEXTRACTOR_API unsigned int DE_ImportSentimentDict(const char *sFilename);//导入用户情感词典
DOCEXTRACTOR_API unsigned int DE_ImportUserDict(const char *sFilename,bool bOverwite=true);//导入用户词典
DOCEXTRACTOR_API unsigned int DE_ImportKeyBlackList(const char *sFilename);//导入关键词黑名单


/*----b--------------------------------------------------------------
* 功能：生成单文档摘要
* 参数：sText	    -[IN] 文档内容
*	bool bSummaryNeeded=true-[IN]:是否需要计算摘要
*	
*		_tDocExtractResult	-[OUT] 文档Extract result
* 备注：在进程中此函数可以执行多次
------------------------------------------------------------------------*/
DOCEXTRACTOR_API int  DE_ComputeSentimentDoc(const char *sText);


DOCEXTRACTOR_API void DE_Exit();

//获得错误消息
DOCEXTRACTOR_API const char* DE_GetLastErrMsg();
