#ifndef __LJSENTIMENTANALYSIS__H__
#define __LJSENTIMENTANALYSIS__H__
#include <string>
#if !defined(LJSentimentAnalysis_2014_INCLUDE)
#define LJSentimentAnalysis_2014_INCLUDE
 
#ifdef OS_LINUX
	#define LJSentimentAnalysis_API extern "C" 
#else 
#ifdef LJSentimentAnalysis_EXPORTS
	#define LJSentimentAnalysis_API extern "C" __declspec(dllexport)
#else
#define LJSentimentAnalysis_API extern "C"  __declspec(dllimport)
#endif
#endif

#define GBK_CODE 0
#define UTF8_CODE GBK_CODE+1
#define BIG5_CODE GBK_CODE+2
#define GBK_FANTI_CODE GBK_CODE+3
#define UTF8_FANTI_CODE GBK_CODE+4

//feeling define
#define EMOTION_HAPPY 0
#define EMOTION_GOOD  EMOTION_HAPPY+1
#define EMOTION_ANGER EMOTION_HAPPY+2
#define EMOTION_SORROW EMOTION_HAPPY+3
#define EMOTION_FEAR EMOTION_HAPPY+4
#define EMOTION_EVIL EMOTION_HAPPY+5
#define EMOTION_SURPRISE EMOTION_HAPPY+6

LJSentimentAnalysis_API int LJST_Inits(const char *path, int encode, const char*sLicenceCode=0);
LJSentimentAnalysis_API bool LJST_GetParagraphSent(const char* lpszParagraph, char* szRes);
LJSentimentAnalysis_API bool LJST_GetFileSent(const char* lpszFilename, char* szRes);
LJSentimentAnalysis_API void LJST_Exits();
LJSentimentAnalysis_API int LJST_ImportUserDict(const char* lpszFilename,bool bOverwrite=true);
#endif

#endif
