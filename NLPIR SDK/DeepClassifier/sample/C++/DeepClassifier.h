/****************************************************************************
 *
 * DeepClassifier Copyright (c) 2000-2014
 *     Dr. Kevin Zhang (Hua-Ping Zhang)
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          Training: DC_Init; DC_AddTrain,DC_AddTrainFile;DC_Train;DC_Exit;
			Classify: DC_Init;DC_LoadTrainResult;DC_Classify,DC_ClassifyFile;DC_Exit
			Support Multiple Channel of Classification
 * Author:   Kevin Zhang 
 *          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
 *			Weibo: http://weibo.com/drkevinzhang
 *			Homepage: http://ictclas.nlpir.org
 * Date:     2013-12-19
 *
 * Notes: 
 *  2016/10/9:
 *	 增加了特征维度，最多1000类; 2.特征自动选择； 3.支持中文分类、英文分类以及中英文混合分类； 4.内测效果达到了95%
 *                
 ****************************************************************************/

#ifndef __DEEP_CLASSIFIER_H_INCLUDED__
#define __DEEP_CLASSIFIER_H_INCLUDED__
#ifdef OS_LINUX
#define DEEP_CLASSIFIER_API  extern "C"
#else
#ifdef LJDEEPCLASSIFIER_EXPORTS
#define DEEP_CLASSIFIER_API extern "C" __declspec(dllexport)
#else
#define DEEP_CLASSIFIER_API extern "C"  __declspec(dllimport)
#endif
#endif
#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码

#define DC_HANDLE int  //Added in 2015/9/22
#define FEATURE_COUNT 1000
/*********************************************************************
 *
 *  Func Name  : DC_Init
 *
 *  Description: Init DeepClassifier
 *               The function must be invoked before any operation listed as following
 *
 *  Parameters : const char * sInitDirPath=NULL
 *				 sDataPath:  Path where Data directory stored.
 *				 the default value is NULL, it indicates the initial directory is current working directory path
 *				 encode: encoding code;
 *				 nFeathureCount: feature count	
 *				 sLicenseCode: license code for unlimited usage. common user ignore it
 *				
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
DEEP_CLASSIFIER_API int DC_Init(const char * sDataPath = 0, int encode = GBK_CODE, int nFeatureCount = FEATURE_COUNT, const char*sLicenceCode = 0);

/*********************************************************************
 *
 *  Func Name  : DC_Exit
 *
 *  Description: Exit DeepClassifier
 *               The function must be invoked before quit the whole system
 *
 *  Parameters : None
 *  Returns    : None
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
DEEP_CLASSIFIER_API void DC_Exit();

/*********************************************************************
 *
 *  Func Name  : DC_NewInstance
 *
 *  Description: New a  DeepClassifier Instance
 *               The function must be invoked before mulitiple classifiers
 *
 *  Parameters : int nFeatureCount: Feature count
 *  Returns    : DC_HANDLE , DeepClassifier Handle if success; otherwise return -1; 
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2015-9-22
 *********************************************************************/
DEEP_CLASSIFIER_API DC_HANDLE  DC_NewInstance(int nFeatureCount = FEATURE_COUNT);

/*********************************************************************
 *
 *  Func Name  : DC_DeleteInstance
 *
 *  Description: Delete a  DeepClassifier Instance with handle
 *               The function must be invoked before release a specific classifier
 *
 *  Parameters : None
 *  Returns    : DC_HANDLE , DeepClassifier Handle
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2015-9-22
 *********************************************************************/
DEEP_CLASSIFIER_API int DC_DeleteInstance(DC_HANDLE handle);

/*********************************************************************
 *
 *  Func Name  : DC_AddTrain
 *
 *  Description: DeepClassifier Training on given text in Memory    
 *
	Parameter:   const char * sClassName: class name
 *				 sText: text content
 *               handle: classifier handle
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
DEEP_CLASSIFIER_API int DC_AddTrain(const char *sClassName,const char *sText,DC_HANDLE handle=0);

/*********************************************************************
 *
 *  Func Name  : DC_AddTrainFile
 *
 *  Description: DeepClassifier Training on given text in file    
 *
	Parameter:   const char * sClassName: class name
 *				 sFilename: text file name
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
DEEP_CLASSIFIER_API int DC_AddTrainFile(const char *sClassName,const char *sFilename,DC_HANDLE handle=0);

/*********************************************************************
 *
 *  Func Name  : DC_Train
 *
 *  Description: DeepClassifier Training on given text in Memory    
 *				 After training, the training result will stored.
 *				Then the classifier can load it with DC_LoadTrainResult at any time(offline or online).
	Parameter:   const char * sClassName: class name
 *				 sFilename: text file name
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
DEEP_CLASSIFIER_API int DC_Train(DC_HANDLE handle=0);

/*********************************************************************
 *
 *  Func Name  : DC_LoadTrainResult
 *
 *  Description: DeepClassifier Load already training data    
 *
	Parameter:   None
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
DEEP_CLASSIFIER_API int DC_LoadTrainResult(DC_HANDLE handle=0);
/*********************************************************************
*
*  Func Name  : DC_ExportFeatures
*
*  Description: DeepClassifier Exports Features after training
*
Parameter:   None
*
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
DEEP_CLASSIFIER_API int DC_ExportFeatures(const char *sFilename,DC_HANDLE handle = 0);

/*********************************************************************
 *
 *  Func Name  : DC_Classify
 *
 *  Description: DeepClassifier Classify on given text in Memory    
 *
	Parameter:   const char * sClassName: class name
 *				 sFilename: text file name
 *
 *  Returns    : the best class name
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
DEEP_CLASSIFIER_API const char * DC_Classify(const char *sText,DC_HANDLE handle=0);
/*********************************************************************
*
*  Func Name  : DC_ClassifyEx
*
*  Description: DeepClassifier Classify on given text in Memory
*				return multiple class with weights, sorted by weights
Parameter:   const char * sClassName: class name
*				 sFilename: text file name
*
*  Returns    : multiple class name with weights, sorted by weights
*               For instance: 政治/1.20##经济/1.10
*			bookyzjs/7.00##bookxkfl/6.00##booktslx/5.00##bookny-xyfl/4.00##booksy/3.00##bookdwpz/2.00##booknyjj/1.00##
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
DEEP_CLASSIFIER_API const char * DC_ClassifyEx(const char *sText, DC_HANDLE handle = 0);

/*********************************************************************
 *
 *  Func Name  : DC_ClassifyFile
 *
 *  Description: DeepClassifier Classify on given text in file    
 *
	Parameter:   const char * sClassName: class name
 *				 sFilename: text file name
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
DEEP_CLASSIFIER_API const char * DC_ClassifyFile(const char *sFilename,DC_HANDLE handle=0);
/*********************************************************************
*
*  Func Name  : DC_ClassifyExFile
*
*  Description: DeepClassifier Classify on given text in file
*
Parameter:   const char * sClassName: class name
*				 sFilename: text file name
*
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2013-6-8
*********************************************************************/
DEEP_CLASSIFIER_API const char * DC_ClassifyExFile(const char *sFilename, DC_HANDLE handle = 0);
/*********************************************************************
 *
 *  Func Name  : DC_GetLastErrorMsg
 *
 *  Description: GetLastErrorMessage
 *    
 *
 *  Parameters : none
 *               
 *				  
 *  Returns    : the result buffer pointer 
 *
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2014-2-27
 *********************************************************************/
DEEP_CLASSIFIER_API const char * DC_GetLastErrorMsg();
#endif //__DEEP_CLASSIFIER_H_INCLUDED__

