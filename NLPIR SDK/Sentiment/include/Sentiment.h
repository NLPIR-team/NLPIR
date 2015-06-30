#ifndef SENTIMENTANALYSIS_H
#define SENTIMENTANALYSIS_H

#define ENCODING_GBK 0
#define ENCODING_UTF8 ENCODING_GBK+1
#define ENCODING_BIG5 ENCODING_GBK+2
#define ENCODING_GBK_FANTI ENCODING_GBK+3//GBKÖÐ°üº¬·±Ìå
#define ENCODING_FANTI_UTF8 ENCODING_GBK+4
#define ENCODING_COUNT 4

#define ST_EXPORTS


#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC 
#endif

#define DLLIMPORT EXTERNC __declspec(dllimport)
#define DLLEXPORT EXTERNC __declspec(dllexport)

#ifdef ST_EXPORTS
#define ST_API DLLEXPORT
#else
#define ST_API DLLIMPORT
#endif

ST_API int ST_Init(const char * sDataPath, int encode, const char*sLicenceCode);

ST_API int ST_Exit();

ST_API const char * ST_GetOneObjectResult(const char *sTitle, const char *sContent, const char *sObject);

ST_API const char * ST_GetMultiObjectResult(const char *sTitle, const char *sContent, const char *sObjectRuleFile);

ST_API const char * ST_GetLastErrMsg();

ST_API int ST_ImportUserDict(const char *sFilePath, int bSaveDict);

ST_API int ST_DelUsrWord(const char *sWord);

ST_API double ST_GetSentimentPoint(const char *sSentence);

ST_API const char *  ST_GetSentencePoint(const char *sSentence);

#endif