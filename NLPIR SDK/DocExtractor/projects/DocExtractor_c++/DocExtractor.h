// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DOCEXTRACTOR_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DOCEXTRACTOR_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DOCEXTRACTOR_EXPORTS
#define DOCEXTRACTOR_API extern "C" __declspec(dllexport)
#else
#define DOCEXTRACTOR_API extern "C" __declspec(dllimport)
#endif
#ifdef OS_LINUX
#define DOCEXTRACTOR_API extern "C"  
#endif
#include <stddef.h>

#define DOC_EXTRACT_TYPE_PERSON 0//���������
#define DOC_EXTRACT_TYPE_LOCATION 1//����ĵ���
#define DOC_EXTRACT_TYPE_ORGANIZATION 2//����Ļ�����
#define DOC_EXTRACT_TYPE_KEYWORD 3//����Ĺؼ���
#define DOC_EXTRACT_TYPE_AUTHOR 4//�������������
#define DOC_EXTRACT_TYPE_MEDIA 5//�����ý��
#define DOC_EXTRACT_TYPE_COUNTRY 6//��������¶�Ӧ�����ڹ���
#define DOC_EXTRACT_TYPE_PROVINCE 7//��������¶�Ӧ������ʡ��
#define DOC_EXTRACT_TYPE_ABSTRACT 8//������µ�ժҪ
#define DOC_EXTRACT_TYPE_POSITIVE 9//������µ�������д�
#define DOC_EXTRACT_TYPE_NEGATIVE 10//������µĸ�����д�
#define DOC_EXTRACT_TYPE_TEXT 11//�������ȥ����ҳ�ȱ�ǩ�������
#define DOC_EXTRACT_TYPE_USER 12//�û��Զ���Ĵ��࣬��һ���Զ����
//�������Զ���ʣ��������Ϊ��DOC_EXTRACT_TYPE_USER+1��DOC_EXTRACT_TYPE_USER+2��...

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
#define HTML_REMOVER_REQUIRED	0x8000//�Ƿ���Ҫȥ����ҳ��ǩ�Ĺ���ѡ��
#define ALL_REQUIRED			0xffff

#define DOC_EXTRACT_DELIMITER "#"
#define DOC_EXTRACT_TYPE_MAX_LENGTH 600
#define GBK_CODE 0//Ĭ��֧��GBK����
#define UTF8_CODE GBK_CODE+1//UTF8����
#define BIG5_CODE GBK_CODE+2//BIG5����
#define GBK_FANTI_CODE GBK_CODE+3//GBK���룬�������������
typedef  size_t DOC_PARSER_HANDLE;

/*-----------------------------------------------------------------------
* ���ܣ���ʼ��
* ������
*		sPath-default path
*		nEncoding:�������
*		sLicenseCode - ��Ȩ��
* ���أ�true - �ɹ���false - ʧ��
* ��ע���ڽ����д˺�����������������֮ǰ���ã�ֻ��ִ��һ�Σ�
------------------------------------------------------------------------*/
DOCEXTRACTOR_API int DE_Init(const char *sPath=0,int nEncoding=GBK_CODE,const char *sLicenseCode=0);

/*-----------------------------------------------------------------------
* ���ܣ����ɵ��ĵ�ժҪ
* ������sText	    -[IN] �ĵ�����
*	bool bSummaryNeeded=true-[IN]:�Ƿ���Ҫ����ժҪ
*	
*		sUserDefPos:�û��Զ���Ĵ��Ա�ǣ�������֣���������������������ý������ã��������ã�����ͬ����֮�����#�ָ��"gms#gjtgj#g"

*		_tDocExtractResult	-[OUT] �ĵ�Extract result
* ��ע���ڽ����д˺�������ִ�ж��
------------------------------------------------------------------------*/
DOCEXTRACTOR_API DOC_PARSER_HANDLE DE_ParseDocE(const char *sText,const char *sUserDefPos=NULL,bool bSummaryNeeded=true,unsigned int nFuncRequired=ALL_REQUIRED);
//Process a text, and return DOC_PARSER_HANDLE
DOCEXTRACTOR_API const char *DE_GetResult(DOC_PARSER_HANDLE handle,int nDocExtractType);
DOCEXTRACTOR_API int DE_GetSentimentScore(DOC_PARSER_HANDLE handle);
DOCEXTRACTOR_API void DE_ReleaseHandle(DOC_PARSER_HANDLE handle);
////�����û��Զ������дʱ�ÿ��һ���ʣ��ո���������Ȩ�أ��磺���ɲ��� -2;
//����������д������´ʣ������û��ʵ��е��룬�������ʶ���Զ���Ծ

DOCEXTRACTOR_API unsigned int DE_ImportSentimentDict(const char *sFilename);//�����û���дʵ�
DOCEXTRACTOR_API unsigned int DE_ImportUserDict(const char *sFilename,bool bOverwite=true);//�����û��ʵ�
DOCEXTRACTOR_API unsigned int DE_ImportKeyBlackList(const char *sFilename);//����ؼ��ʺ�����


/*----b--------------------------------------------------------------
* ���ܣ����ɵ��ĵ�ժҪ
* ������sText	    -[IN] �ĵ�����
*	bool bSummaryNeeded=true-[IN]:�Ƿ���Ҫ����ժҪ
*	
*		_tDocExtractResult	-[OUT] �ĵ�Extract result
* ��ע���ڽ����д˺�������ִ�ж��
------------------------------------------------------------------------*/
DOCEXTRACTOR_API int  DE_ComputeSentimentDoc(const char *sText);


DOCEXTRACTOR_API void DE_Exit();

//��ô�����Ϣ
DOCEXTRACTOR_API const char* DE_GetLastErrMsg();
