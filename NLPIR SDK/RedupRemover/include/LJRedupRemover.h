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

#define GBK_CODE 0//Ĭ��֧��GBK����
#define UTF8_CODE GBK_CODE+1//UTF8����
#define BIG5_CODE GBK_CODE+2//BIG5����
#define GBK_FANTI_CODE GBK_CODE+3//GBK���룬�������������

//��ʼ��,��װ�����еĲ�������

/*********************************************************************
 *
 *  Func Name  : RR_Init
 *
 *  Description: RR_Init
 *               The function must be invoked before any operation listed as following
 *
 *  Parameters : const char *sHistoryDataFile: ������ʷ�����ļ�
 *				 const char *sInitDirPath: ��Ȩ��ϵͳ�ļ����·����Ĭ��Ϊ�ա�the default value is NULL, it indicates the initial directory is current working directory path
 *				 bHistoryLoad:  �Ƿ������ʷ���ݣ�Ĭ��Ϊ��
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
 *  Parameters : const char *sContent: �ı����ݣ����룻
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
 *  Parameters : const char *sFilename: �ı��ļ����ƣ���ΪID��
 *
 *  Returns    : int
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
LJRR_API int RR_FileProcessE(const char *sFilename);

//�������ļ�
/*********************************************************************
 *
 *  Func Name  : RR_FindRepeat
 *
 *  Description: RR_FindRepeat
 *               find repeat file
 *
 *  Parameters : char *sReturnString: return result string��
 *				 bAllOutput��,true return all repeat file��false:only return one file
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
 *  Parameters : const char *sOutputFile: output file name��
 *				
 *  Returns    : bool: 1=repeat; 0=no repeat;-1=failed
 *  Author     :  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
//�����ظ��ļ���Ϣ
LJRR_API bool RR_Output(const char *sHistoryDataFile = "RepeatFile.txt");

/*********************************************************************
 *
 *  Func Name  : RR_SaveHistoryData
 *
 *  Description: RR_SaveHistoryData
 *               ���������ʷ���ݣ��������´μ��أ���������
 *
 *  Parameters : const char *sHistoryDataFile: ������ʷ�����ļ���
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
 *              ��ô�����ʾ��Ϣ
 *
 *  Parameters : None��
 *				
 *  Returns    : const char*�� return message
 *  Author     :  
 *  History    : 
 *              1.create 2014-7-16
 *********************************************************************/
LJRR_API const char* RR_GetLastErrMsg();

#endif //__LJREDUP_REMOVER_INCLUDED_H__
