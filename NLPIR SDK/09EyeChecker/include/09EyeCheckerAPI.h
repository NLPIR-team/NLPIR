/****************************************************************************
*
* NERICS (09Eye Report Intelligent Checker System) Copyright (c) 2017-2018
*     Dr. Kevin Zhang (Hua-Ping Zhang)
*     All rights reserved.
*
* This file is the confidential and proprietary property of
* Kevin Zhang and the possession or use of this file requires
* a written license from the author.
* Filename:
* Abstract:
*          09EyeCheckerAPI.h: definition of the NLPIR lexical analysis system API
* Author:   Kevin Zhang
*          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
*			Weibo: http://weibo.com/drkevinzhang
*			Homepage: http://www.nlpir.org
* Date:     2018-2-28
*
* Notes:
*
****************************************************************************/
#if !defined(__NLPIR_NINE_EYE_CHECKER_H_INCLUDED__)
#define __NLPIR_NINE_EYE_CHECKER_H_INCLUDED__

#ifdef OS_LINUX
#define MY09EYECHECKERAPI_API extern "C"
#else
#ifdef MY09EYECHECKERAPI_EXPORTS
#define MY09EYECHECKERAPI_API extern "C" __declspec(dllexport)
#else
#define MY09EYECHECKERAPI_API extern "C" __declspec(dllimport)
#endif
#endif
#define NERICS_HANDLE int
#include <string>
//Define Report Type
#define RPT_UNSPECIFIC 0//No Specific type
#define RPT_JIAYOUZHAN 1//加油站报告
#define RPT_ANPING 2//安评报告
#define RPT_CONTRACT 3//合同
#define RPT_LEGAL 4//法律法规
#define RPT_OFFICIAL_DOC 5//公文
#define RPT_PAPER 6//学术论文
#define RPT_DISSERTATION 7//毕业论文
#define RPT_ARGUMENT 8//标准参数
#define RPT_IPO  9//IPO金融上市文档
#define RPT_INSURANCE 10//保险文档

#define FORMAT_XML 0
#define FORMAT_JSON 1

#define RESULT_TYPE_CHECK 0//获取核查结果内容
#define RESULT_TYPE_KG 1//获取知识图谱内容
#define RESULT_TYPE_CONTENT 2//获取目录内容
#define RESULT_TYPE_TEXT 3//获取正文内容
#define RESULT_TYPE_FIGURE 4//获取图片内容
#define RESULT_TYPE_TABLE 5//获取图片内容
#define RESULT_TYPE_SINGLE_KEY 6//获取单个知识
#define RESULT_TYPE_TUPLE 7//获取元组
#define RESULT_TYPE_ENTITY 8//获取命名实体

/*********************************************************************
*
*  Func Name  : NERICS_Init
*
*  Description: Init NERICS
*               The function must be invoked before any operation listed as following
*
*  Parameters : const char * sInitDirPath=NULL
*				  Path where Data directory stored.
*				 the default value is NULL, it indicates the initial directory is current working directory path
*				 sLicenseCode: license code for unlimited usage. common user ignore it
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-4-20
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_Init(const char *sInitPath, const char*sLicenceCode = 0);

/*********************************************************************
*
*  Func Name  : NERICS_Exit
*
*  Description: Exit NERICS
*               and free related buffer
 *               Exit the program and free memory
 *				 The function must be invoked while you needn't any lexical anlysis
*
*  Parameters : void
*  Returns    : void
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-4-20
*********************************************************************/
MY09EYECHECKERAPI_API void NERICS_Exit(void);

/*********************************************************************
*
*  Func Name  : NERICS_ImportFieldDict
*
*  Description: Import field dictionary
*
*
*  Parameters : sFiledDictFile: field dictioary file
*				bOverwrite: Overwrite
*  Returns    : Return status: int
*				1: success
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-12-16
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_ImportFieldDict(const char *sFiledDictFile, bool bPinyinAbbrevNeeded = false, bool bOverwrite=true);

/*********************************************************************
*
*  Func Name  : NERICS_NewInstance
*
*  Description: New a  NERICS Instance
*               The function must be invoked before mulitiple keyword scan filter
*
*  Parameters :
*  Returns    : NERICS_HANDLE: KeyScan Handle if success; otherwise return -1;
*  Author     : Kevin Zhang
*  History    :
*              1.create 2016-11-15
*********************************************************************/
MY09EYECHECKERAPI_API NERICS_HANDLE NERICS_NewInstance();

/*********************************************************************
*
*  Func Name  : NERICS_DeleteInstance
*
*  Description: Delete a  KeyScan Instance with handle
*               The function must be invoked before release a specific classifier
*
*  Parameters : DC_HANDLE , NERICS Handle
*  Returns    :
*  Author     : Kevin Zhang
*  History    :
*              1.create 2015-9-22
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_DeleteInstance(NERICS_HANDLE handle);

/*********************************************************************
*
*  Func Name  : NERICS_ImportDoc
*
*  Description: Read a Report file  and save the result in file with XML format
*
*
*  Parameters : sReportFile: Report File
*				sURLPrefix: URL前缀路径
*				handle: NERICS handle, generated by NERICS_NewInstance
*  Returns    : Return result file name: sXMLFile: XML file stored
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-4
*********************************************************************/
MY09EYECHECKERAPI_API const char * NERICS_ImportDoc(const char *sReportFile, const char *sURLPrefix = "", NERICS_HANDLE handle = 0);

/*********************************************************************
*
*  Func Name  : NERICS_LoadDocResult
*
*  Description: Read a result XML file  and save the result in file with XML format
*
*
*  Parameters : sReportFile: Report File
*				sURLPrefix: URL前缀路径
*				handle: NERICS handle, generated by NERICS_NewInstance
*  Returns    : Return result file name: sXMLFile: XML file stored
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-4
*********************************************************************/
MY09EYECHECKERAPI_API size_t NERICS_LoadDocResult(const char *sResultXMLFile, NERICS_HANDLE handle = 0);

/*********************************************************************
*
*  Func Name  : NERICS_CheckReportF
*
*  Description: Check a Report file  and save the result in file with XML format 
*
*
*
*  Parameters : sReportFile: Report File: 支持doc,docx,xml文件
*				sURLPrefix: URL前缀路径
*				nType: Report Type, Default is RPT_UNSPECIFIC
*				handle: NERICS handle, generated by NERICS_NewInstance
*				int  nResultFormat：0: XML; 1:Jason
*  Returns    : Return result file name: sXMLFile: XML file stored

*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-4
*********************************************************************/
MY09EYECHECKERAPI_API const char * NERICS_CheckReportF(const char *sReportFile, 
	const char *sURLPrefix = "", 
	const char *sOrgnization="",//使用单位参数
	int nType = RPT_UNSPECIFIC, 
	int  nResultFormat = FORMAT_JSON,
	bool bDebug = false,
	NERICS_HANDLE handle = 0);
/*********************************************************************
*
*  Func Name  : NERICS_GetResult
*
*  Description: 获取分析结果，默认为JSON格式
*
*
*
*  Parameters : result_type:
*				handle: NERICS handle, generated by NERICS_NewInstance
*				
*  Returns    : Return result file name: sXMLFile: XML file stored

*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-4
*********************************************************************/
MY09EYECHECKERAPI_API const char * NERICS_GetResult(int result_type,
	NERICS_HANDLE handle = 0);

/*********************************************************************
*
*  Func Name  : NERICS_AddAuditRule
*
*  Description: Add Audit Rule
*
*
*
*  Parameters : sAuditRule: Audit rule,需要遵循KGB Audit语法规则
*				nType: Report Type, Default is RPT_UNSPECIFIC
*				
*  Returns    : int: 1: success, other: failed. Get error message via NERICS_GetLastErrorMsg()

*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-9-19
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_AddAuditRule(const char *sAuditRule, int nType = RPT_UNSPECIFIC);

/*********************************************************************
*
*  Func Name  : NERICS_CheckReportDir
*
*  Description: Scan a dir and  Check all doc files
*
*
*  Parameters : sReportDir: Report File Directory
*
*				nType: Report Type, Default is RPT_UNSPECIFIC
*				handle: NERICS handle, generated by NERICS_NewInstance
*  Returns    : Return result file name: sXMLFile: XML file stored
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-6-5
*********************************************************************/
MY09EYECHECKERAPI_API size_t NERICS_CheckReportDir(const char *sReportDir, 
	const char *sOrgnization,int nType = RPT_UNSPECIFIC, int format= FORMAT_JSON, int nThreadCount = 10);

/*********************************************************************
*
*  Func Name  : NERICS_ReviseReportF
*
*  Description: Revised a Report file
*				and revised information stored in file
*
*
*  Parameters : sReviseXMLFile: Revised information file with XML format
*				nType: Report Type, Default is RPT_UNSPECIFIC
*				handle: NERICS handle, generated by NERICS_NewInstance
*  Returns    : Return : new docx file name with path； return "" if failed!
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-4
*********************************************************************/
MY09EYECHECKERAPI_API const char * NERICS_ReviseReportF(const char *sReviseXMLFile, NERICS_HANDLE handle = 0);

MY09EYECHECKERAPI_API const char * NERICS_ShowHtmlError(const char *sReviseXMLFile, NERICS_HANDLE handle = 0);
/*********************************************************************
*
*  Func Name  : NERICS_ImportTemplate
*
*  Description: Import a document Template 
*			
*
*  Parameters : sTemplateFile: Template file using doc or docx format
*				nType: document type
*				sOrg: organization 
*				sArgumemt: arguments
*  Returns    : Return status: int
*				1: success
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-8
*			   2.modified in 2018-11-20
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_ImportTemplate(const char *sTemplateFile,int nType = RPT_UNSPECIFIC,const char *sOrg=0, const char *sArea = 0,const char* sArgumemt=0);
/*********************************************************************
*
*  Func Name  : NERICS_EditTemplate
*
*  Description: Edit a document Template 
*			
*
*  Parameters : sTemplateFile: Template file using doc or docx format
*				nType: document type
*				sOrg: organization 
*				sArgumemt: arguments
*  Returns    : Return status: int
*				1: success
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-8
*			   2.modified in 2018-11-20
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_EditTemplate(int nTemplateID,const char *sTemplateFile,int nType = RPT_UNSPECIFIC,const char *sOrg=0, const char *sArea = 0,const char* sArgumemt=0);
/*********************************************************************
*
*  Func Name  : NERICS_FindTemplate
*
*  Description: Find a document Template
*
*
*  Parameters : 
*				nType: document type
*				sOrg: organization
*				sArgumemt: arguments
*  Returns    : Return status: int
*				1: success
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-8
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_FindTemplate(int nType = RPT_UNSPECIFIC, const char *sOrg = 0, const char *sArea = 0, const char* sArgumemt = 0);
/*********************************************************************
*
*  Func Name  : NERICS_DeleteTemplate
*
*  Description: delete a document Template
*
*
*  Parameters : nTempID: template ID
*  Returns    : Return : int
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-11-20
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_DeleteTemplate(int nTemplateID);
/*********************************************************************
*
*  Func Name  : NERICS_GetTemplate
*
*  Description: Get a document Template
*
*
*  Parameters : nTempID: template ID
*  Returns    : Return status: const char* :template data
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-11-20
*********************************************************************/
MY09EYECHECKERAPI_API const char* NERICS_GetTemplate(int nTemplateID);

/*********************************************************************
*
*  Func Name  : NERICS_GetTemplateCount
*
*  Description: Get  document Template count
*
*
*  Parameters : nTempID: template ID
*  Returns    : Return status: const char* :template data
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-11-20
*********************************************************************/
MY09EYECHECKERAPI_API size_t NERICS_GetTemplateCount();


/*********************************************************************
*
*  Func Name  : NERICS_GetCurTemplateInfo
*
*  Description: Get current document Template information
*
*
*  Parameters :
*  Returns    : Return status: const char* :template information using Jason format
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-12-5
*********************************************************************/
MY09EYECHECKERAPI_API const char* NERICS_GetCurTemplateInfo(NERICS_HANDLE handle = 0);

/*********************************************************************
*
*  Func Name  : NERICS_GetTemplateList
*
*  Description: Get  Template information
*
*
*  Parameters :	docType: docType;
*				sOrgnization: organization name
*  Returns    : Return status: const char* :template information using Jason format
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-12-5
*********************************************************************/
MY09EYECHECKERAPI_API const char *NERICS_GetTemplateList(int docType, const char *sOrgnization);
/*********************************************************************
*
*  Func Name  : NERICS_ReCheckFormat
*
*  Description: ReCheck a format
*
*  Parameters : sReportFile: Report File: 支持doc,docx,xml文件
*				sURLPrefix: URL前缀路径
*				nType: Report Type, Default is RPT_UNSPECIFIC
*				handle: NERICS handle, generated by NERICS_NewInstance
*				int  nResultFormat：0: XML; 1:Jason
*  Returns    : Return result file name: sXMLFile: XML file stored

*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-11-27
*********************************************************************/
MY09EYECHECKERAPI_API const char * NERICS_ReCheckFormat(const char *sCheckXML, int nTemplateID, int  nResultFormat = 0, NERICS_HANDLE handle = 0);

/*********************************************************************
*
*  Func Name  : NERICS_ImportKGBRules
*
*  Description: 针对报告类型nType导入相应的KGB规则集合
*			
*
*  Parameters : sTemplateFile: Template file using doc or docx format
*  Returns    : Return status: int
*				1: success
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-8
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_ImportKGBRules(const char *sRuleFile,bool bOverwrite=false,int nType = RPT_UNSPECIFIC);

/*********************************************************************
*
*  Func Name  : NERICS_ImportErrorMsg
*
*  Description: Import a error message table
*			
*
*  Parameters : sErrorListFile: Template file using doc or docx format
*  Returns    : Return status: int
*				1: success
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-8
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_ImportErrorMsg(const char *sErrorListFile);

/*********************************************************************
*
*  Func Name  : NERICS_ImportSimDict
*
*  Description: Import simary dictionary
*			
*
*  Parameters : sErrorListFile: Template file using doc or docx format
*  Returns    : Return status: int
*				1: success
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-8
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_ImportSimDict(const char *sSimDictFile);

/*********************************************************************
*
*  Func Name  : NERICS_ImportSpellErrorDict
*
*  Description: Import Spelling Error dictionary
*
*
*  Parameters : sSpellErrorDict: Spelling Error dictionary
*  Returns    : Return status: int
*				1: success
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-5-8
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_ImportSpellErrorDict(const char *sSpellErrorDict);

/*********************************************************************
*
*  Func Name  : NERICS_ImportUserDict
*
*  Description: Import Spelling Error dictionary
*
*
*  Parameters : sUserDict: User defined dictionary
*  Returns    : Return status: int
*				1: success
*
*  Author     : Kevin Zhang
*  History    :
*              1.create 2019-12-3
*********************************************************************/
MY09EYECHECKERAPI_API int NERICS_ImportUserDict(const char *sUserDict);

/*********************************************************************
*
*  Func Name  : NERICS_GetLastErrorMsg
*
*  Description: Return Last Error Message
*
*
*  Parameters : void
*  Returns    : Return error message
*  Author     : Kevin Zhang
*  History    :
*              1.create 2018-4-20
*********************************************************************/
MY09EYECHECKERAPI_API const char * NERICS_GetLastErrorMsg(void);


MY09EYECHECKERAPI_API const char * KGB_GetSysInfo(void);//读取第一个页面
MY09EYECHECKERAPI_API const char*KGB_GetRuleListId(int type);
MY09EYECHECKERAPI_API const char*KGB_GetRuleInfo(int rule_id, int type);
MY09EYECHECKERAPI_API int KGB_DelRule(int rule_id, int type);
MY09EYECHECKERAPI_API int KGB_AddRule(const char *sJsonStr, int type);
MY09EYECHECKERAPI_API int KGB_EditRule(int rule_id, const char *sJsonStr, int type);
MY09EYECHECKERAPI_API const char* KGB_ScanTextMem(const char *sLine, int rule_id, int type, NERICS_HANDLE handle = 0);

MY09EYECHECKERAPI_API const char * Audit_GetSysInfo(int type);
MY09EYECHECKERAPI_API const char*Audit_GetRuleListId(int type);
MY09EYECHECKERAPI_API const char*Audit_GetRuleInfo(int rule_id, int type);
MY09EYECHECKERAPI_API int Audit_DelRule(int rule_id, int type);
MY09EYECHECKERAPI_API int Audit_AddRule(const char *sJsonStr, int type);
MY09EYECHECKERAPI_API int Audit_EditRule(int rule_id, const char *sJsonStr, int type);
MY09EYECHECKERAPI_API const char * Audit_GetErrorInfo(void);

#endif//__NLPIR_EYE_CHECKER_H_INCLUDED__
