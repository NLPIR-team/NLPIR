package com.lingjoin.sentimentAnalysis;

import org.apache.log4j.Logger;

import com.lingjoin.sentimentAnalysis.LJSentimentAnalysisLibrary.CLibrarySentimentAnalysis;



public class LJSentimentAnalysisMethod {
	private static Logger logger = Logger.getLogger(LJSentimentAnalysisMethod.class.getName());
	private static final int GBK_CODE = 0;// 默认支持GBK编码
	private static final int UTF8_CODE = 1;// UTF8编码
	private static final int BIG5_CODE = 2;// BIG5编码
	private static final int GBK_FANTI_CODE = 3;// GBK编码，里面包含繁体字
	
	
	public static boolean sentiment_init() {
		logger.debug("初始化开始。。。。");
		String dataPath = "";// data目录的地址，为空默认到项目根目录下找Data目录
		String licenseCode = "0";// licenseCode默认为0
		int init_flag = CLibrarySentimentAnalysis.Instance.LJST_Inits(dataPath, UTF8_CODE,
				licenseCode);

		if (0 == init_flag) {
			logger.debug("初始化失败！");
			return false;
		}
		logger.debug("初始化成功。。。");
		return true;
	}
	
	
	/**
	 * 获取情感分析结果，需要传进去文件的路径                   
	 * @param Filename
	 * @return
	 */
	public static String LJST_GetFileSent(String Filename){
		byte[]  resultByte = new byte[10000];
		String  resultStr = null;
		try{
			boolean runResult = CLibrarySentimentAnalysis.Instance.LJST_GetFileSent(Filename, resultByte);
			resultStr = new String(resultByte);
			logger.debug("is run success----"+runResult);
			logger.debug("result----"+resultStr);
		}catch(Exception e){
			e.printStackTrace();
		} 
		return resultStr;
	}
	/**
	 * 获取情感分析结果，需要传进字符串                   
	 * @param Filename
	 * @return
	 */
	public static String LJST_GetParagraphSent(String Paragraph){
		byte[]  resultByte = new byte[10000];
		String  resultStr = null;
		try{
			boolean runResult = CLibrarySentimentAnalysis.Instance.LJST_GetParagraphSent(Paragraph, resultByte);
			resultStr = new String(resultByte);
			logger.debug("is run success----"+runResult);
			logger.debug("情感值为：----"+resultStr);
		}catch(Exception e){
			e.printStackTrace();
		} 
		return resultStr;
	}
	public static int LJST_ImportUserDict(String dicPath, boolean overwriter){
		   return CLibrarySentimentAnalysis.Instance.LJST_ImportUserDict(dicPath,overwriter);
	}

}
