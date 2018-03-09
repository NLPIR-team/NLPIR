/***************************************************
 * Copyright (c) 2006. All rights reserved.
 * Posession or use of this file requires a written 
 * license from the author.
 *  
 * Author:  Lingjoin
 * Email:	lingjoin@lingjoin.com
 * Created: 2009-12-26
 ***************************************************/
#ifndef __LJREDUP_REMOVER_INCLUDED_H__
#define __LJREDUP_REMOVER_INCLUDED_H__

#ifdef OS_LINUX
#define LJRR_API extern "C" 
#else
#ifdef LJREDUPREMOVER_EXPORTS
#define LJRR_API extern "C" __declspec(dllexport)
#else
#define LJRR_API extern "C"  __declspec(dllimport)
#endif
#endif

#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字

//初始化,并装载已有的查重数据

/*********************************************************************
 *
 *  Func Name  : RR_Init
 *
 *  Description: RR_Init
 *               The function must be invoked before any operation listed as following
 *
 *  Parameters : const char *sHistoryDataFile: 查重历史数据文件
 *				 const char *sInitDirPath: 授权等系统文件存放路径，默认为空。the default value is NULL, it indicates the initial directory is current working directory path
 *				 bHistoryLoad:  是否加载历史数据，默认为否
 *				 sLicenseCode: license code for unlimited usage. common user ignore it
 *				 encode: encoding code;
 *  Returns    : success or fail; if fail,please see the current date log file.
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
LJRR_API bool RR_Init(const char *sHistoryDataFile = "Data.txt", const char *sInitDirPath=0,bool bHistoryLoad=false, const char *sLicenseCode=0,int encode=GBK_CODE);

/*********************************************************************
 *
 *  Func Name  : RR_Exit
 *
 *  Description: RR_Exit
 *               The function must be invoked before quit the sysytem
 *
 *  Parameters : None
 *  Returns    : Non
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
LJRR_API void RR_Exit();

/*********************************************************************
 *
 *  Func Name  : RR_FileProcess
 *
 *  Description: RR_FileProcess
 *               process each file
 *
 *  Parameters : const char *sContent: 文本内容，编码；
 *				 const char *sID: the unique ID
 *  Returns    : int
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
LJRR_API int RR_FileProcess(const char *sContent, const char *sID);
/*********************************************************************
 *
 *  Func Name  : RR_FileProcessE
 *
 *  Description: RR_FileProcessE
 *               process each file
 *
 *  Parameters : const char *sFilename: 文本文件名称；作为ID；
 *
 *  Returns    : int
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
LJRR_API int RR_FileProcessE(const char *sFilename);

//处理单个文件
/*********************************************************************
 *
 *  Func Name  : RR_FindRepeat
 *
 *  Description: RR_FindRepeat
 *               find repeat file
 *
 *  Parameters : char *sReturnString: return result string；
 *				 bAllOutput，,true return all repeat file，false:only return one file
 *  Returns    : bool: true=repeat; failed=no repeat;or failed
 *  Author     :  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
LJRR_API bool RR_FindRepeat(char *sReturnString, bool bAllOutput = false);

/*********************************************************************
 *
 *  Func Name  : RR_Output
 *
 *  Description: RR_Output
 *               output all repeat results
 *
 *  Parameters : const char *sOutputFile: output file name；
 *				
 *  Returns    : bool: 1=repeat; 0=no repeat;-1=failed
 *  Author     :  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
//保存重复文件信息
LJRR_API bool RR_Output(const char *sHistoryDataFile = "RepeatFile.txt");

/*********************************************************************
 *
 *  Func Name  : RR_SaveHistoryData
 *
 *  Description: RR_SaveHistoryData
 *               保存查重历史数据，可用于下次加载，增量处理
 *
 *  Parameters : const char *sHistoryDataFile: 查重历史数据文件；
 *				
 *  Returns    : bool: 1=repeat; 0=no repeat;-1=failed
 *  Author     :  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
LJRR_API bool RR_SaveHistoryData(const char *DataFilePath = "Data.txt");

//
/*********************************************************************
 *
 *  Func Name  : RR_GetLastErrMsg
 *
 *  Description: RR_GetLastErrMsg
 *              获得错误提示消息
 *
 *  Parameters : None；
 *				
 *  Returns    : const char*： return message
 *  Author     :  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
LJRR_API const char* RR_GetLastErrMsg();

#endif //__LJREDUP_REMOVER_INCLUDED_H__
