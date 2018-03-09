
/****************************************************************************
 *
 * NLPIR Chinese Keyword Extraxt System Copyright (c) 2000-2013
 *     Dr. Kevin Zhang (Hua-Ping Zhang)
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          NewWordFinder.h: definition of the NewWordFinder new word finder system API
 * Author:   Kevin Zhang 
 *          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
 *			Weibo: http://weibo.com/drkevinzhang
 * Date:     2013-3-1
 *
 * Notes:
 *                
 ****************************************************************************/
#if !defined(__NEW_WORD_FINDER_2016_LIB_INCLUDED__)
#define __NEW_WORD_FINDER_2016_LIB_INCLUDED__
#ifdef OS_LINUX
#define NEWWORDFINDER_API extern "C" 
#else
#ifdef NEWWORDFINDER_EXPORTS
#define NEWWORDFINDER_API extern "C" __declspec(dllexport)
#else
#define NEWWORDFINDER_API extern "C" __declspec(dllimport)
#endif
#endif

#define GBK_CODE 0//Ĭ��֧��GBK����
#define UTF8_CODE GBK_CODE+1//UTF8����
#define BIG5_CODE GBK_CODE+2//BIG5����
#define GBK_FANTI_CODE GBK_CODE+3//GBK���룬�������������

/*********************************************************************
 *
 *  Func Name  : NWF_Init
 *
 *  Description: Init NewWordFinder
 *               The function must be invoked before any operation listed as following
 *
 *  Parameters : const char * sInitDirPath=NULL
 *				 sDataPath:  Path where Data directory stored.
 *				 the default value is NULL, it indicates the initial directory is current working directory path
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-2-6
 *********************************************************************/
NEWWORDFINDER_API int NWF_Init(const char * sDataPath=0,int encode=GBK_CODE,const char*sLicenceCode=0);

/*********************************************************************
 *
 *  Func Name  : NWF_Exit
 *
 *  Description: Exist NewWordFinder and free related buffer
 *               Exit the program and free memory
 *				 The function must be invoked while you needn't any lexical anlysis
 *
 *  Parameters : None
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2002-8-6
 *********************************************************************/
NEWWORDFINDER_API bool NWF_Exit();

/*********************************************************************
*
*  Func Name  : NWF_GetNewWords
*
*  Description: Extract New words from sLine
*
*  Parameters : sLine, the input paragraph; 
*						the input size cannot be very big(less than 60MB). Process large memory, recommendate use NWF_NWI series functions
*				bArguOut,whether  the keyword weight output
*				nMaxKeyLimit:maximum of key words, up to 50
*  Returns    : new words list like:
*               "��ѧ��չ�� ��˿ "or
				"��ѧ��չ�� 23.80 ��˿ 12.20" with weight
*
*  Author     :   
*  History    : 
*              1.create  2012/11/12
*********************************************************************/
NEWWORDFINDER_API const char * NWF_GetNewWords(const char *sLine,int nMaxKeyLimit=50,bool bWeightOut=false);

/*********************************************************************
*
*  Func Name  : NWF_GetFileNewWords
*
*  Description: Extract new words from a text file
*
*  Parameters : sFilename, the input text file name 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimit:maximum of key words, up to 50
*  Returns    : keywords list like:
*               "��ѧ��չ�� ��۾��� " or
				"��ѧ��չ�� 23.80 ��۾��� 12.20" with weight

*
*  Author     :   
*  History    : 
*              1.create 2012/11/12
*********************************************************************/
NEWWORDFINDER_API const char * NWF_GetFileNewWords(const char *sFilename,int nMaxKeyLimit=50,bool bWeightOut=false);


/*********************************************************************
*
*  ���º���Ϊ2013�汾ר������´ʷ��ֵĹ��̣�һ�㽨���ѻ�ʵ�֣��������ߴ���
*  �´�ʶ����ɺ����Զ����뵽�ִ�ϵͳ�У��������
*  ������NWF_NWI(New Word Identification)��ͷ
*********************************************************************/
/*********************************************************************
*
*  Func Name  : NWF_Batch_Start
*
*  Description: �����´�ʶ��

*
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NEWWORDFINDER_API int NWF_Batch_Start();//New Word Indentification Start
/*********************************************************************
*
*  Func Name  : NWF_Batch_AddFile
*
*  Description: ���´�ʶ��ϵͳ����Ӵ�ʶ���´ʵ��ı��ļ�
*				��Ҫ������NWF_Batch_Start()֮�󣬲���Ч
*
*  Parameters : const char *sFilename���ļ���
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 20132/11/23
*********************************************************************/
NEWWORDFINDER_API unsigned long  NWF_Batch_AddFile(const char *sFilename);
/*********************************************************************
*
*  Func Name  : NWF_Batch_AddMem
*
*  Description: ���´�ʶ��ϵͳ�����һ�δ�ʶ���´ʵ��ڴ�
*				��Ҫ������NWF_Batch_Start()֮�󣬲���Ч
*
*  Parameters : const char *sFilename���ļ���
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NEWWORDFINDER_API unsigned long NWF_Batch_AddMem(const char *sText);
/*********************************************************************
*
*  Func Name  : NWF_Batch_Complete
*
*  Description: �´�ʶ��������ݽ���
*				��Ҫ������NWF_Batch_Start()֮�󣬲���Ч
*
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NEWWORDFINDER_API int NWF_Batch_Complete();//�ļ������ڴ浼�����

/*********************************************************************
*
*  Func Name  : NWF_Batch_GetResult
*
*  Description: ��ȡ�´�ʶ��Ľ��
*				��Ҫ������NWF_Batch_Complete()֮�󣬲���Ч
*
*  Parameters : bWeightOut���Ƿ���Ҫ���ÿ���´ʵ�Ȩ�ز���
*
*  Returns    : �����ʽΪ
*				���´�1�� ��Ȩ��1�� ���´�2�� ��Ȩ��2�� ... 
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NEWWORDFINDER_API const char * NWF_Batch_GetResult(bool bWeightOut=false);//����´�ʶ����

/*********************************************************************
*
*  Func Name  : NWF_Result2UserDict
*
*  Description: ���´�ʶ�������뵽�û��ʵ���
*				��Ҫ������NLPIR_NWI_Complete()֮�󣬲���Ч
*				�����Ҫ���´ʽ�����ñ��棬������ִ��NLPIR_SaveTheUsrDic
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NEWWORDFINDER_API unsigned int  NWF_Result2UserDict();//�´�ʶ����תΪ�û��ʵ�,�����´ʽ����Ŀ
/*********************************************************************
 *
 *  Func Name  : KeyExtract_GetLastErrorMsg
 *
 *  Description: GetLastErrorMessage
 *    
 *
 *  Parameters : void
 *               
 *				  
 *  Returns    : the result buffer pointer 
 *
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2014-2-27
 *********************************************************************/
NEWWORDFINDER_API const char *  NWF_GetLastErrorMsg();
#endif
