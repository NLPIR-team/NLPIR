
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
#ifdef OS_LINUX
#define JZSEARCHAGENTAPI_API
#endif

JZSEARCHAGENTAPI_API const char* jzsearch_query_client(const char *query_line,int nStart,int nPageCount,const char *sHostIP,int nPortID);
//query_line:��ѯ�����  [FIELD] * [AND] ���� ;*��ʾ����׼��֮���ͨ�����2.AND������ԷŶ��ֵ��
//nStart����ʼ������кţ���0��ʼ
//nPageCount:ÿҳ�����Ŀ
//sHostIP: ����������IP
//nPortID: Port ID
//return: ���������ŵ�XM��ʽ���ڴ�飬������XMLһ��

JZSEARCHAGENTAPI_API bool jzsearch_query_client_exit();
//�ͷ��ڴ�ռ�