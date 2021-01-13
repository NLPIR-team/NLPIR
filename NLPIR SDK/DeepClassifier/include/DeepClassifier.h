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
 *          Training: DeepClassifier_Init; DeepClassifier_AddTrain,DeepClassifier_AddTrainFile;DeepClassifier_Train;DeepClassifier_Exit;
			Classify: DeepClassifier_Init;DeepClassifier_LoadTrainResult;DeepClassifier_Classify,DeepClassifier_ClassifyFile;DeepClassifier_Exit
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

#define DeepClassifier_Handle int  //Added in 2015/9/22
#define FEATURE_COUNT 1000
/*********************************************************************
 *
 *  Func Name  : DeepClassifier_Init
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
DEEP_CLASSIFIER_API int DeepClassifier_Init(const char * sDataPath = 0, int encode = GBK_CODE, int nFeatureCount = FEATURE_COUNT, const char*sLicenceCode = 0);

/*********************************************************************
 *
 *  Func Name  : DeepClassifier_Exit
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
DEEP_CLASSIFIER_API void DeepClassifier_Exit();

/*********************************************************************
 *
 *  Func Name  : DeepClassifier_NewInstance
 *
 *  Description: New a  DeepClassifier Instance
 *               The function must be invoked before mulitiple classifiers
 *
 *  Parameters : int nFeatureCount: Feature count
 *  Returns    : DeepClassifier_Handle , DeepClassifier Handle if success; otherwise return -1; 
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2015-9-22
 *********************************************************************/
DEEP_CLASSIFIER_API DeepClassifier_Handle  DeepClassifier_NewInstance(int nFeatureCount = FEATURE_COUNT);

/*********************************************************************
 *
 *  Func Name  : DeepClassifier_DeleteInstance
 *
 *  Description: Delete a  DeepClassifier Instance with handle
 *               The function must be invoked before release a specific classifier
 *
 *  Parameters : None
 *  Returns    : DeepClassifier_Handle , DeepClassifier Handle
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2015-9-22
 *********************************************************************/
DEEP_CLASSIFIER_API int DeepClassifier_DeleteInstance(DeepClassifier_Handle handle);

/*********************************************************************
 *
 *  Func Name  : DeepClassifier_AddTrain
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
DEEP_CLASSIFIER_API int DeepClassifier_AddTrain(const char *sClassName,const char *sText,DeepClassifier_Handle handle=0);

/*********************************************************************
 *
 *  Func Name  : DeepClassifier_AddTrainFile
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
DEEP_CLASSIFIER_API int DeepClassifier_AddTrainFile(const char *sClassName,const char *sFilename,DeepClassifier_Handle handle=0);

/*********************************************************************
 *
 *  Func Name  : DeepClassifier_Train
 *
 *  Description: DeepClassifier Training on given text in Memory    
 *				 After training, the training result will stored.
 *				Then the classifier can load it with DeepClassifier_LoadTrainResult at any time(offline or online).
	Parameter:   const char * sClassName: class name
 *				 sFilename: text file name
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
DEEP_CLASSIFIER_API int DeepClassifier_Train(DeepClassifier_Handle handle=0);

/*********************************************************************
 *
 *  Func Name  : DeepClassifier_LoadTrainResult
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
DEEP_CLASSIFIER_API int DeepClassifier_LoadTrainResult(DeepClassifier_Handle handle=0);
/*********************************************************************
*
*  Func Name  : DeepClassifier_ExportFeatures
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
DEEP_CLASSIFIER_API int DeepClassifier_ExportFeatures(const char *sFilename,DeepClassifier_Handle handle = 0);

/*********************************************************************
 *
 *  Func Name  : DeepClassifier_Classify
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
DEEP_CLASSIFIER_API const char * DeepClassifier_Classify(const char *sText,DeepClassifier_Handle handle=0);
/*********************************************************************
*
*  Func Name  : DeepClassifier_ClassifyEx
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
DEEP_CLASSIFIER_API const char * DeepClassifier_ClassifyEx(const char *sText, DeepClassifier_Handle handle = 0);

/*********************************************************************
 *
 *  Func Name  : DeepClassifier_ClassifyFile
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
DEEP_CLASSIFIER_API const char * DeepClassifier_ClassifyFile(const char *sFilename,DeepClassifier_Handle handle=0);
/*********************************************************************
*
*  Func Name  : DeepClassifier_ClassifyExFile
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
DEEP_CLASSIFIER_API const char * DeepClassifier_ClassifyExFile(const char *sFilename, DeepClassifier_Handle handle = 0);
/*********************************************************************
 *
 *  Func Name  : DeepClassifier_GetLastErrorMsg
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
DEEP_CLASSIFIER_API const char * DeepClassifier_GetLastErrorMsg();
#endif //__DEEP_CLASSIFIER_H_INCLUDED__

