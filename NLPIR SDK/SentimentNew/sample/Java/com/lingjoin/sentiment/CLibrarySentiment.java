package com.lingjoin.sentiment;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;

public interface CLibrarySentiment extends Library {
	
//	CLibrarySentiment Instance = (CLibrarySentiment) Native.loadLibrary(
//			OSinfo.getSysAndBit("Sentiment"), CLibrarySentiment.class);

	CLibrarySentiment Instance = (CLibrarySentiment) Native.loadLibrary(
			"./SentimentNew.dll", CLibrarySentiment.class);
	
	public boolean ST_Init(String sInitDirPath, int encode, String sLicenseCode);

	public String ST_GetOneObjectResult(String sTitle, String sContent, String sObject);
//
	public String ST_GetMultiObjectResult(String sTitle, String sContent,			String sObjectRuleFile);
//
	public void ST_Exit();

	public String ST_GetLastErrorMsg();

	public double ST_GetSentimentPoint(String sSentence);

//	/**
//	 * 功能：批量导入导出情感词典
//	 * @param sPositiveFile 积极词典文件名；
//	 * @param sNegativeFile 消极词典文件名
//	 * @param bInputOutput true: 导入词典到系统中； false:导出系统词典到文本文件
//	 * @return int: 1:成功；0:失败
//	 */
//	public int ST_SentiDictIO(String sPositiveFile,String sNegativeFile,boolean bInputOutput);


//	/**
//	 * 导入情感词典
//	 * @param sFilePath 词典的路径
//	 * @param bSaveDict 1:保存到词库，0：不保存到词库
//	 * @return 导入单词的个数
//	 */
//	public int ST_ImportUserDict(String sFilePath, int bSaveDict);
//
//	/**
//	 * 删除单词
//	 * @param sWord 单词
//	 * @return
//	 */
//	public int ST_DelUsrWord(String sWord);
}
