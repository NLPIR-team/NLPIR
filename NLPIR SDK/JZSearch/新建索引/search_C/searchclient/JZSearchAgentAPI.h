
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the LJSEARCHAGENTAPI_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// JZSEARCHAGENTAPI_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.

#ifdef LJSEARCHAGENTAPI_EXPORTS
#define JZSEARCHAGENTAPI_API extern "C" __declspec(dllexport)//
#else
#define JZSEARCHAGENTAPI_API extern "C" __declspec(dllimport)//extern "C"
#endif


JZSEARCHAGENTAPI_API int jzsearch_query_client(const char *XMLfile,const char *query_line,int nStart,int nPageCount,const char *sResultName);
//SearchAgent.XML的存放地址
//query_line:查询的语句  [FIELD] * [AND] 钢铁 ;*表示除标准号之外的通配符；2.AND后面可以放多个值；
//nStart：起始结果的行号，从0开始
//nPageCount:每页结果数目
//sResultName:result.xml存放的文件名
//

JZSEARCHAGENTAPI_API bool jzsearch_query_client_exit();
