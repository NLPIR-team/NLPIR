/***************************************************
 * Copyright (c) 2006. All rights reserved.
 * Posession or use of this file requires a written 
 * license from the author.
 *  
 * Author:  Lingjoin
 * Email:	lingjoin@lingjoin.com
 * Created: 2009-12-26
 ***************************************************/
#ifndef _H_HTMLPARSER_API_INCLUDED
#define _H_HTMLPARSER_API_INCLUDED

#ifdef OS_LINUX
#define HPARSER_API extern "C" 
#else
#ifdef LJHTMLPARSER_EXPORTS
#define HPARSER_API extern "C" __declspec(dllexport)
#else
#define HPARSER_API extern "C"  __declspec(dllimport)
#endif
#endif


//��ʼ��
HPARSER_API int HPR_Init(const char * sDataPath=0,const char *sLicenseCode=0);

//�˳����ͷ���Դ
HPARSER_API void HPR_Exit();

//��HTML���н�����ֻ��ִ�д˺��������HPR_GetContent��
HPARSER_API bool HPR_ParseFile(const char *sHtmlFilename);
HPARSER_API bool HPR_ParseBuffer(const char *sHtmlBuffer, int nLen);

//��ȡ���ģ�����NULLʱ��ʾʧ�ܣ�����TE_GetLastErrMsg�ɻ�ô�����ʾ��
HPARSER_API const char* HPR_GetContent();

//��ȡ���⣬����NULLʱ��ʾʧ�ܣ�����TE_GetLastErrMsg�ɻ�ô�����ʾ��
HPARSER_API const char* HPR_GetTitle();

//��ô�����ʾ��Ϣ
HPARSER_API const char* HPR_GetLastErrMsg();

#endif //_H_HTMLPARSER_API_INCLUDED