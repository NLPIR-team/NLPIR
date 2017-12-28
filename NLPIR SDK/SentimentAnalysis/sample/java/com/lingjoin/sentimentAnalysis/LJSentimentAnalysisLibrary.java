package com.lingjoin.sentimentAnalysis;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;


/**
 * 细粒度情感分析组件
 * @author 张亚鹏
 *
 */
public class LJSentimentAnalysisLibrary {
	/**
	 * 加载Summary的库文件
	 * @author LiYan
	 *
	 */
	public interface CLibrarySentimentAnalysis extends Library {

	CLibrarySentimentAnalysis Instance = (CLibrarySentimentAnalysis) Native.loadLibrary(
				OSinfo.getSysAndBit("LJSentimentAnalysis"), CLibrarySentimentAnalysis.class);
		
	
	 /**
	  * 初始化组件
	 * @param path Data文件夹的路径，为空字符串时默认从工程根目录下开始寻找
	 * @param encode  编码格式，具体如下：
						0：GBK；1：UTF8；2：BIG5；3：GBK（里面包含繁体字）
	 * @param sLicenceCode  授权码,写成空字符串就可以
	 * @return
	 */
	public int LJST_Inits(String path, int encode, String sLicenceCode);
	 
	 /**
	  * 导入用户自定义的情感词典
	 * @param dicPath 情感词典的路径（文本的编码应该和初始化时设定的编码保持一致）
	 * @param overwriter 是否删除先前的自定义情感词典，true：删除；false：不删除
	 * @return
	 */
	public int LJST_ImportUserDict(String dicPath, boolean overwriter);
	 
	 /**
	  * 获得情感分析结果。
	  *     EMOTION_HAPPY：表示文章中属于“乐”的情感词的个数；
    		EMOTION_GOOD：表示文章中属于“好”的情感词的个数；
    		EMOTION_ANGER：表示文章中属于“怒”的情感词的个数；
    		EMOTION_SORROW：表示文章中属于“哀”的情感词的个数；
    		EMOTION_FEAR：表示文章中属于“惧”的情感词的个数；
    		EMOTION_EVIL：表示文章中属于“恶”的情感词的个数；
    		EMOTION_SURPRISE：表示文章中属于“惊”的情感词的个数；
	 * @param lpszFilename 文本文件的路径
	 * @param szRes 分析后的结果
	 * @return
	 */
	public boolean LJST_GetFileSent(String lpszFilename, byte[] szRes);
	
	 /**
	  * 分析文章的情感内容。
	  *     EMOTION_HAPPY：表示文章中属于“乐”的情感词的个数；
    		EMOTION_GOOD：表示文章中属于“好”的情感词的个数；
    		EMOTION_ANGER：表示文章中属于“怒”的情感词的个数；
    		EMOTION_SORROW：表示文章中属于“哀”的情感词的个数；
    		EMOTION_FEAR：表示文章中属于“惧”的情感词的个数；
    		EMOTION_EVIL：表示文章中属于“恶”的情感词的个数；
    		EMOTION_SURPRISE：表示文章中属于“惊”的情感词的个数；
	 * @param lpszParagraph 文本内容
	 * @param szRes 分析后的结果
	 * @return
	 */
	public boolean  LJST_GetParagraphSent(String lpszParagraph,byte[] szRes);
	 
	 /**
	 * 退出组件
	 */
	public void LJST_Exits();
	 

	}
}
