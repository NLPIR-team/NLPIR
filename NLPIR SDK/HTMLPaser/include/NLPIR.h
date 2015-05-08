/****************************************************************************
 *
 * NLPIR/ICTCLAS Lexical Analysis System Copyright (c) 2000-2014
 *     Dr. Kevin Zhang (Hua-Ping Zhang)
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          NLPIR.h: definition of the NLPIR lexical analysis system API
 * Author:   Kevin Zhang 
 *          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
 *			Weibo: http://weibo.com/drkevinzhang
 *			Homepage: http://ictclas.nlpir.org
 * Date:     2013-12-19
 *
 * Notes:
 *                
 ****************************************************************************/
#if !defined(__NLPIR_ICTCLAS_2014_H_INCLUDED__)
#define __NLPIR_ICTCLAS_2014_H_INCLUDED__

#ifdef OS_LINUX
	#define NLPIR_API extern "C" 
#else
#ifdef NLPIR_EXPORTS
#define NLPIR_API extern "C" __declspec(dllexport)
#else
#define NLPIR_API extern "C"  __declspec(dllimport)
#endif
#endif

//内部兼容使用

#ifdef NLPIR_INTERNAL_CALL
#define NLPIR_API 
#endif


//////////////////////////////////////////////////////////////////////////
//
//以下定义为兼容ICTCLAS以前的版本
//
//////////////////////////////////////////////////////////////////////////
#define ICTCLAS_Init NLPIR_Init
#define ICTCLAS_Exit NLPIR_Exit
#define ICTCLAS_ImportUserDict  NLPIR_ImportUserDict
#define ICTCLAS_FileProcess NLPIR_FileProcess
#define ICTCLAS_ParagraphProcess  NLPIR_ParagraphProcess 
#define ICTCLAS_ParagraphProcessA  NLPIR_ParagraphProcessA 
#define ICTCLAS_GetParagraphProcessAWordCount   NLPIR_GetParagraphProcessAWordCount 
#define ICTCLAS_ParagraphProcessAW   NLPIR_ParagraphProcessAW 
#define ICTCLAS_AddUserWord  NLPIR_AddUserWord
#define ICTCLAS_SaveTheUsrDic  NLPIR_SaveTheUsrDic
#define ICTCLAS_DelUsrWord  NLPIR_DelUsrWord
#define ICTCLAS_GetUniProb  NLPIR_GetUniProb
#define ICTCLAS_IsWord  NLPIR_IsWord
#define ICTCLAS_SetPOSmap  NLPIR_SetPOSmap
#define CICTCLAS  CNLPIR
#define GetActiveICTCLAS GetActiveInstance 


#define POS_MAP_NUMBER 4 //add by qp 2008.11.25
#define ICT_POS_MAP_FIRST 1  //计算所一级标注集
#define ICT_POS_MAP_SECOND 0 //计算所二级标注集
#define PKU_POS_MAP_SECOND 2 //北大二级标注集
#define PKU_POS_MAP_FIRST 3	//北大一级标注集
#define  POS_SIZE 40

struct result_t{
  int start; //start position,词语在输入句子中的开始位置
  int length; //length,词语的长度
  char  sPOS[POS_SIZE];//word type，词性ID值，可以快速的获取词性表
  int	iPOS;//词性标注的编号
  int word_ID; //该词的内部ID号，如果是未登录词，设成0或者-1
  int word_type; //区分用户词典;1，是用户词典中的词；0，非用户词典中的词
  int weight;//word weight,read weight
 };

#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
#define UTF8_FANTI_CODE GBK_CODE+4//UTF8编码

/*********************************************************************
 *
 *  Func Name  : Init
 *
 *  Description: Init NLPIR
 *               The function must be invoked before any operation listed as following
 *
 *  Parameters : const char * sInitDirPath=NULL
 *				 sDataPath:  Path where Data directory stored.
 *				 the default value is NULL, it indicates the initial directory is current working directory path
 *				 encode: encoding code;
 *				 sLicenseCode: license code for unlimited usage. common user ignore it
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
NLPIR_API int NLPIR_Init(const char * sDataPath=0,int encode=GBK_CODE,const char*sLicenceCode=0);
/*********************************************************************
 *
 *  Func Name  : NLPIR_Exit
 *
 *  Description: Exist NLPIR and free related buffer
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
NLPIR_API bool NLPIR_Exit();
/*********************************************************************
 *
 *  Func Name  : ParagraphProcessing
 *
 *  Description: Process a paragraph
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               
 *				 bPOStagged:Judge whether need POS tagging, 0 for no tag;default:1
 *				i.e.  张华平于1978年3月9日出生于江西省波阳县。
 *					Result: 张华平/nr  于/p  1978年/t  3月/t  9日/t  出生于/v  江西省/ns  波阳县/ns  。/w   
 *  Returns    : the result buffer pointer 
 *
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2003-12-22
 *********************************************************************/
NLPIR_API const char * NLPIR_ParagraphProcess(const char *sParagraph,int bPOStagged=1);
/*********************************************************************
 *
 *  Func Name  : NLPIR_GetLastErrorMsg
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
NLPIR_API const char * NLPIR_GetLastErrorMsg();
/*********************************************************************
 *
 *  Func Name  : ParagraphProcessingA
 *
 *  Description: Process a paragraph
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               pResultCount: pointer to result vector size
 *  Returns    : the pointer of result vector, it is managed by system,user cannot alloc and free it 
 *  Author     :  Kevin Zhang  
 *  History    : 
 *              1.create 2006-10-26
 *********************************************************************/
NLPIR_API const result_t * NLPIR_ParagraphProcessA(const char *sParagraph,int *pResultCount,bool bUserDict=true);

/*********************************************************************
 *
 *  Func Name  : NLPIR_GetParagraphProcessAWordCount
 *
 *  Description: Get ProcessAWordCount, API for C#
 *				 Get word count and it helps us prepare the proper size buffer for result_t vector
 *
 *  Parameters : sParagraph: The source paragraph 
 *               
 *  Returns    : result vector size 
 *  Author     :  Kevin Zhang  
 *  History    : 
 *              1.create 2007-3-15
 *********************************************************************/
NLPIR_API int NLPIR_GetParagraphProcessAWordCount(const char *sParagraph);
/*********************************************************************
 *
 *  Func Name  : NLPIR_ParagraphProcessAW
 *
 *  Description: Process a paragraph, API for C#
 *    
 *
 *  Parameters : sParagraph: The source paragraph 
 *               result_t * result: pointer to result vector size, it is allocated by the invoker
 *  Returns    : None 
 *  Author     :  
 *  History    : 
 *              1.create 2007-3-15
 *********************************************************************/
NLPIR_API void NLPIR_ParagraphProcessAW(int nCount,result_t * result);

/*********************************************************************
 *
 *  Func Name  : NLPIR_FileProcess
 *
 *  Description: Process a text file
 *    
 *
 *  Parameters : sSourceFilename: The source file name  
 *               sResultFilename: The result file name 
 *				 bPOStagged:Judge whether need POS tagging, 0 for no tag;default:1
 *  i.e. FileProcess("E:\\Sample\\Corpus_NewPOS\\199802_Org.txt","E:\\Sample\\Corpus_NewPOS\\199802_Org_cla.txt");
 *  Returns    : success: 
 *               fail: 
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2005-11-22
 *********************************************************************/
NLPIR_API double NLPIR_FileProcess(const char *sSourceFilename,const char *sResultFilename,int bPOStagged=1);

/*********************************************************************
 *
 *  Func Name  : ImportUserDict
 *
 *  Description: Import User-defined dictionary
 *  Parameters : 
 *				sFilename:Text filename for user dictionary 
 *				bOverwrite: true,  overwrite the existing dictionary 
 *						   false, add to  the existing dictionary 		
 *  Returns    : The  number of  lexical entry imported successfully
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2014-8-3
 *********************************************************************/
NLPIR_API unsigned int NLPIR_ImportUserDict(const char *sFilename,bool bOverwrite=true);

/*********************************************************************
 *
 *  Func Name  : NLPIR_ImportKeyBlackList
 *
 *  Description: Import keyword black list 
 *  Parameters : Text filename for user dictionary, each line for a stop keyword
 *  Returns    : The  number of  lexical entry imported successfully
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2014-6-26
 *********************************************************************/
NLPIR_API unsigned int NLPIR_ImportKeyBlackList(const char *sFilename);
/*********************************************************************
*
*  Func Name  : NLPIR_AddUserWord
*
*  Description: add a word to the user dictionary ,example:你好	
*													 i3s	n
*
*  Parameters : sFilename: file name
*               
*  Returns    : 1,true ; 0,false
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
NLPIR_API int NLPIR_AddUserWord(const char *sWord);//add by qp 2008.11.10

/*********************************************************************
*
*  Func Name  : Save
*
*  Description: Save dictionary to file
*
*  Parameters :
*               
*  Returns    : 1,true; 2,false
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
NLPIR_API int NLPIR_SaveTheUsrDic();

/*********************************************************************
*
*  Func Name  : NLPIR_DelUsrWord
*
*  Description: delete a word from the  user dictionary
*
*  Parameters : 
*  Returns    : -1, the word not exist in the user dictionary; else, the handle of the word deleted
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
NLPIR_API int NLPIR_DelUsrWord(const char *sWord);

/*********************************************************************
*
*  Func Name  : NLPIR_GetUniProb
*
*  Description: Get Unigram Probability
*    
*
*  Parameters : sWord: input word 
*  Returns    : success: 
*               fail: 
*  Author     : Kevin Zhang  
*  History    : 
*              1.create 2005-11-22
*********************************************************************/
NLPIR_API double NLPIR_GetUniProb(const char *sWord);
/*********************************************************************
*
*  Func Name  : NLPIR_IsWord
*
*  Description: Judge whether the word is included in the core dictionary
*    
*
*  Parameters : sWord: input word 
*  Returns    : success: 
*               fail: 
*  Author     : Kevin Zhang  
*  History    : 
*              1.create 2005-11-22
*********************************************************************/
NLPIR_API int NLPIR_IsWord(const char *sWord);

/*********************************************************************
*
*  Func Name  : NLPIR_GetWordPOS
*
*  Description: Get the word Part-Of-Speech　information
*    
*
*  Parameters : sWord: input word 
*
*  Returns    : success: 
*               fail: 
*  Author     : Kevin Zhang  
*  History    : 
*              1.create 2014-10-10
*********************************************************************/
NLPIR_API const char * NLPIR_GetWordPOS(const char *sWord);

/*********************************************************************
*
*  Func Name  : NLPIR_GetKeyWords
*
*  Description: Extract keyword from sLine
*
*  Parameters : sLine, the input paragraph 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimt:maximum of key words, up to 50
*  Returns    : keywords list like:
*               "科学发展观 宏观经济 " or
				"科学发展观/23.80/12#宏观经济/12.20/1" with weight(信息熵加上词频信息)
*
*  Author     :   
*  History    : 
*              1.create 2012/11/12
*********************************************************************/
NLPIR_API const char * NLPIR_GetKeyWords(const char *sLine,int nMaxKeyLimit=50,bool bWeightOut=false);

/*********************************************************************
*
*  Func Name  : NLPIR_GetFileKeyWords
*
*  Description: Extract keyword from a text file
*
*  Parameters : sFilename, the input text file name 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimt:maximum of key words, up to 50
*  Returns    : keywords list like:
*               "科学发展观 宏观经济 " or
				"科学发展观 23.80 宏观经济 12.20" with weight

*
*  Author     :   
*  History    : 
*              1.create 2012/11/12
*********************************************************************/
NLPIR_API const char * NLPIR_GetFileKeyWords(const char *sFilename,int nMaxKeyLimit=50,bool bWeightOut=false);
/*********************************************************************
*
*  Func Name  : NLPIR_GetNewWords
*
*  Description: Extract New words from sLine
*
*  Parameters : sLine, the input paragraph 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimt:maximum of key words, up to 50
*  Returns    : new words list like:
*               "科学发展观 屌丝 "or
				"科学发展观 23.80 屌丝 12.20" with weight
*
*  Author     :   
*  History    : 
*              1.create  2012/11/12
*********************************************************************/
NLPIR_API const char * NLPIR_GetNewWords(const char *sLine,int nMaxKeyLimit=50,bool bWeightOut=false);

/*********************************************************************
*
*  Func Name  : NLPIR_GetFileNewWords
*
*  Description: Extract new words from a text file
*
*  Parameters : sFilename, the input text file name 
				bArguOut,whether  the keyword weight output
				nMaxKeyLimt:maximum of key words, up to 50
*  Returns    : keywords list like:
*               "科学发展观 宏观经济 " or
				"科学发展观 23.80 宏观经济 12.20" with weight

*
*  Author     :   
*  History    : 
*              1.create 2012/11/12
*********************************************************************/
NLPIR_API const char * NLPIR_GetFileNewWords(const char *sFilename,int nMaxKeyLimit=50,bool bWeightOut=false);
/*********************************************************************
*
*  Func Name  : NLPIR_FingerPrint
*
*  Description: Extract a finger print from the paragraph
*
*  Parameters :
*  Returns    : 0, failed; else, the finger print of the content
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
NLPIR_API unsigned long NLPIR_FingerPrint(const char *sLine);

/*********************************************************************
*
*  Func Name  : NLPIR_SetPOSmap
*
*  Description: select which pos map will use
*
*  Parameters :nPOSmap, ICT_POS_MAP_FIRST  计算所一级标注集
						ICT_POS_MAP_SECOND  计算所二级标注集
						PKU_POS_MAP_SECOND   北大二级标注集
						PKU_POS_MAP_FIRST 	  北大一级标注集
*  Returns    : 0, failed; else, success
*
*  Author     :   
*  History    : 
*              1.create 11:10:2008
*********************************************************************/
NLPIR_API int NLPIR_SetPOSmap(int nPOSmap);


/*********************************************************************
*
*  class CNLPIR
*   描述：
*		   NLPIR 类，使用之前必须调用NLPIR_Init(),退出必须调用NLPIR_Exit
*		   在使用过程中可以使用多份CNLPIR，支持多线程分词处理
*			每个线程先调用GetActiveInstance，获取处理类，然后，设置SetAvailable(false)宣示线程主权，
*			处理完成后，SetAvailable(true)释放线程主权
*  History    : 
*              1.create 2005-11-10
*********************************************************************/
#ifdef OS_LINUX
class  CNLPIR {
#else
class  __declspec(dllexport) CNLPIR {
#endif
	public:
		CNLPIR();
		~CNLPIR();
		double FileProcess(const char *sSourceFilename,const char *sResultFilename,int bPOStagged=1);
		//Process a file，类似于C下的NLPIR_FileProcess
		const char * ParagraphProcess(const char *sLine,int bPOStagged=1); 
		//Process a file，类似于C下的NLPIR_ParagraphProcess
		const result_t * ParagraphProcessA(const char *sParagraph,int *pResultCount,bool bUserDict=true);
		//Process a file，类似于C下的NLPIR_ParagraphProcessA

		void ParagraphProcessAW(int nCount,result_t * result);
		int GetParagraphProcessAWordCount(const char *sParagraph);

		const char * GetKeyWords(const char *sLine,int nMaxKeyLimit,bool bWeightOut);
		//获取关键词
		const char * GetFileKeyWords(const char *sFilename,int nMaxKeyLimit,bool bWeightOut);
		//从文本文件中获取关键词
		const char * GetNewWords(const char *sFilename,int nMaxKeyLimit,bool bWeightOut);
		//获取新词
		const char * GetFileNewWords(const char *sFilename,int nMaxKeyLimit,bool bWeightOut);
		//从文本文件中获取新词

		bool SetAvailable(bool bAvailable=true);//当前线程释放该类，可为下一个线程使用
		bool IsAvailable();//判断当前分词器是否被线程占用
		unsigned int GetHandle()
		{
			return m_nHandle;
		}
private:
		unsigned int m_nHandle;//该成员作为该类的Handle值，由系统自动分配，用户不可修改
		bool m_bAvailable;//该成员作为多线程共享控制的参数，由系统自动分配，用户不可修改
		int m_nThreadCount;//Thread Count
		bool m_bWriting;//writing  protection
};

/*********************************************************************
*
*  Func Name  : GetActiveInstance
*
*  Description: 获取可用的CNLPIR类，适用于多线程开发，先获取可用的CNLP，再调用其中的功能

*
*  Parameters : None
*  Returns    : CNLPIR*
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 1:10:2012
*********************************************************************/
NLPIR_API CNLPIR* GetActiveInstance();

/*********************************************************************
*
*  以下函数为2013版本专门针对新词发现的过程，一般建议脱机实现，不宜在线处理
*  新词识别完成后，再自动导入到分词系统中，即可完成
*  函数以NLPIR_NWI(New Word Identification)开头
*********************************************************************/
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_Start
*
*  Description: 启动新词识别

*
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NLPIR_API int NLPIR_NWI_Start();//New Word Indentification Start
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_AddFile
*
*  Description: 往新词识别系统中添加待识别新词的文本文件
*				需要在运行NLPIR_NWI_Start()之后，才有效
*
*  Parameters : const char *sFilename：文件名
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 20132/11/23
*********************************************************************/
NLPIR_API int  NLPIR_NWI_AddFile(const char *sFilename);
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_AddMem
*
*  Description: 往新词识别系统中添加一段待识别新词的内存
*				需要在运行NLPIR_NWI_Start()之后，才有效
*
*  Parameters : const char *sFilename：文件名
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NLPIR_API int NLPIR_NWI_AddMem(const char *sText);
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_Complete
*
*  Description: 新词识别添加内容结束
*				需要在运行NLPIR_NWI_Start()之后，才有效
*
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NLPIR_API int NLPIR_NWI_Complete();//新词
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_GetResult
*
*  Description: 获取新词识别的结果
*				需要在运行NLPIR_NWI_Complete()之后，才有效
*
*  Parameters : bWeightOut：是否需要输出每个新词的权重参数
*
*  Returns    : 输出格式为
*				【新词1】 【权重1】 【新词2】 【权重2】 ... 
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NLPIR_API const char * NLPIR_NWI_GetResult(bool bWeightOut=false);//输出新词识别结果
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_Result2UserDict
*
*  Description: 将新词识别结果导入到用户词典中
*				需要在运行NLPIR_NWI_Complete()之后，才有效
*				如果需要将新词结果永久保存，建议在执行NLPIR_SaveTheUsrDic
*  Parameters : None
*  Returns    : bool, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2013/11/23
*********************************************************************/
NLPIR_API unsigned int  NLPIR_NWI_Result2UserDict();//新词识别结果转为用户词典,返回新词结果数目
/*********************************************************************
*
*  Func Name  : NLPIR_FinerSegment(const char *sLine)
*
*  Description: 当前的切分结果过大时，如“中华人民共和国”
*				需要执行该函数，将切分结果细分为“中华 人民 共和国”
*				细分粒度最大为三个汉字
*  Parameters : sLine:输入的字符串
*  Returns    : 返回的细分串，如果不能细分，则返回为空字符串""
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2014/10/10
*********************************************************************/
NLPIR_API const char*  NLPIR_FinerSegment(const char *sLine);
/*********************************************************************
*
*  Func Name  : NLPIR_GetEngWordOrign(const char *sWord)
*
*  Description: 获取各类英文单词的原型，考虑了过去分词、单复数等情况
*  Parameters : sWord:输入的单词
*  Returns    : 返回的词原型形式
*               driven->drive   drives->drive   drove-->drive
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2014/12/11
*********************************************************************/
NLPIR_API const char*  NLPIR_GetEngWordOrign(const char *sWord);

/*********************************************************************
*
*  Func Name  : NLPIR_WordFreqStat(const char *sText)
*
*  Description: 获取输入文本的词，词性，频统计结果，按照词频大小排序
*  Parameters : sWord:输入的文本内容
*  Returns    : 返回的是词频统计结果形式如下：
*				张华平/nr/10#博士/n/9#分词/n/8
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2014/12/11
*********************************************************************/
NLPIR_API const char*  NLPIR_WordFreqStat(const char *sText);
/*********************************************************************
*
*  Func Name  : NLPIR_FileWordFreqStat(const char *sFilename)
*
*  Description: 获取输入文本的词，词性，频统计结果，按照词频大小排序
*  Parameters : sWord:输入的文本内容
*  Returns    : 返回的是词频统计结果形式如下：
*				张华平/nr/10#博士/n/9#分词/n/8
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2014/12/11
*********************************************************************/
NLPIR_API const char*  NLPIR_FileWordFreqStat(const char *sFilename);

#endif//#define __NLPIR_ICTCLAS_2014_H_INCLUDED__
