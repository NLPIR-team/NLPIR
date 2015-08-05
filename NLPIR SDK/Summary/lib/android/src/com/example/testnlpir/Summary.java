package com.example.testnlpir;

public class Summary {
		public native int  NLPIR_Init(byte[] sDataPath,int encoding,byte[] sLicenceCode);
		public native boolean  NLPIR_Exit();
		public native  byte[] NLPIR_GetLastMsg();
		public native   int NLPIR_ImportUserDict(byte[] sPath);
		public native float NLPIR_GetUniProb(byte[] sWord);
		public native boolean NLPIR_IsWord(byte[] sWord);
		public native   byte[] NLPIR_ParagraphProcess(byte[] sSrc,int bPOSTagged);
		public native   boolean NLPIR_FileProcess(byte[] sSrcFilename,byte[] sDestFilename,int bPOSTagged);
		public native   byte[] nativeProcAPara(byte[] src);	
		public native int NLPIR_AddUserWord(byte[] sWord);//add by qp 2008.11.10
		public native int NLPIR_SaveTheUsrDic();
		public native int NLPIR_DelUsrWord(byte[] sWord);
	 
	 	public native int NLPIR_SetPOSmap(int nPOSmap);
		public native int NLPIR_GetElemLength(int nIndex);
		
		public native  byte[] NLPIR_GetKeyWords( byte[] sLine,int nMaxKeyLimit,boolean bWeightOut);
		public native  byte[] NLPIR_GetFileKeyWords( byte[] sFilename,int nMaxKeyLimit,boolean bWeightOut);
		public native  byte[] NLPIR_GetNewWords( byte[]sLine,int nMaxKeyLimit,boolean bWeightOut);
		public native  byte[] NLPIR_GetFileNewWords( byte[] sFilename,int nMaxKeyLimit,boolean bWeightOut);

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
*  Returns    : boolean, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2012/11/23
*********************************************************************/
public native boolean NLPIR_NWI_Start();//New Word Indentification Start
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_AddFile
*
*  Description: 往新词识别系统中添加待识别新词的文本文件
*				需要在运行NLPIR_NWI_Start()之后，才有效
*
*  Parameters : byte[]sFilename：文件名
*  Returns    : boolean, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2012/11/23
*********************************************************************/
public native int  NLPIR_NWI_AddFile(byte[]sFilename);
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_AddMem
*
*  Description: 往新词识别系统中添加一段待识别新词的内存
*				需要在运行NLPIR_NWI_Start()之后，才有效
*
*  Parameters : byte[]sFilename：文件名
*  Returns    : boolean, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2012/11/23
*********************************************************************/
public native boolean NLPIR_NWI_AddMem(byte[]sText);
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_Complete
*
*  Description: 新词识别添加内容结束
*				需要在运行NLPIR_NWI_Start()之后，才有效
*
*  Parameters : None
*  Returns    : boolean, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2012/11/23
*********************************************************************/
public native boolean NLPIR_NWI_Complete();//新词
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
*              1.create 2012/11/23
*********************************************************************/
public native byte[] NLPIR_NWI_GetResult(boolean bWeightOut);//输出新词识别结果
/*********************************************************************
*
*  Func Name  : NLPIR_NWI_Result2UserDict
*
*  Description: 将新词识别结果导入到用户词典中
*				需要在运行NLPIR_NWI_Complete()之后，才有效
*				如果需要将新词结果永久保存，建议在执行NLPIR_SaveTheUsrDic
*  Parameters : None
*  Returns    : boolean, true:success, false:fail
*
*  Author     : Kevin Zhang
*  History    : 
*              1.create 2012/11/23
*********************************************************************/
public native int  NLPIR_NWI_Result2UserDict();//新词识别结果转为用户词典,返回新词结果数目

public native  byte[] NLPIR_GetSummary( byte[] sText,int iSumLenInput,int bHtmlTagRemove);
public native  byte[] NLPIR_GetFileSummary( byte[] sFilename,int iSumLenInput,int bHtmlTagRemove);

    /* Use static intializer */
    static {
			System.loadLibrary("SummaryJNI");
    }
}