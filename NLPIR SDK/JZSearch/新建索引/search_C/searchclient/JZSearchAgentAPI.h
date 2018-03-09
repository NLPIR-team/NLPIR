
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
//SearchAgent.XML�Ĵ�ŵ�ַ
//query_line:��ѯ�����  [FIELD] * [AND] ���� ;*��ʾ����׼��֮���ͨ�����2.AND������ԷŶ��ֵ��
//nStart����ʼ������кţ���0��ʼ
//nPageCount:ÿҳ�����Ŀ
//sResultName:result.xml��ŵ��ļ���
//

JZSEARCHAGENTAPI_API bool jzsearch_query_client_exit();
