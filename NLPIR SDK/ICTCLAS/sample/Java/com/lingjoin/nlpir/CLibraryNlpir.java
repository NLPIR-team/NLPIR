package com.lingjoin.nlpir;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;


/**
 * 分词组件的Java接口，采用JNA技术来实现
 * @author 张亚鹏
 *
 */
public interface CLibraryNlpir extends Library {
	// 定义并初始化接口的静态变量，通过JNA调用NLPIR.dll;

	CLibraryNlpir Instance = (CLibraryNlpir) Native.loadLibrary(OSinfo
			.getSysAndBit("NLPIR"), CLibraryNlpir.class);
	
	/**
	 * 组件初始化
	 * @param sDataPath Data文件夹的父目录，如果为空字符串（即：""），那么，程序自动从项目的根目录中寻找
	 * @param encoding 编码格式，具体的编码对照如下：
									0：GBK
									1：UTF8
									2：BIG5
									3：GBK，里面包含繁体字；
	 * @param sLicenceCode 授权码，为空字符串（即：""）就可以了
	 * @return true：初始化成功；false：初始化失败
	 */
	public boolean NLPIR_Init(String sDataPath, int encoding, String sLicenceCode);

	/**
	 * 返回最后一次的出错信息
	 * @return 最后一次的出错信息
	 */
	public String NLPIR_GetLastErrorMsg();

	/**
	 * 分词
	 * @param sSrc 文本内容
	 * @param bPOSTagged 1：显示词性，0：不显示词性
	 * @return 分词后的结果
	 */
	public String NLPIR_ParagraphProcess(String sSrc, int bPOSTagged);
	
	/**
	 * 分词
	 * 注意：文本的编码集需要和初始化时设置的编码集保持一致
	 * @param sSourceFilename 原文本路径（可以是绝对路径也可以是相对路径，相对路径的话是相对于项目的根目录）
	 * @param sResultFilename 结果文本的路径（可以是绝对路径也可以是相对路径，相对路径的话是相对于项目的根目录）
	 * @param bPOStagged 1：显示词性，0：不显示词性
	 * @return
	 */
	public double NLPIR_FileProcess(String sSourceFilename,String sResultFilename,int bPOStagged);
	/**
	 * 细粒度分词
	 * @param lenWords 文本内容
	 * @return 分词后的结果
	 */
	public String NLPIR_FinerSegment(String lenWords);
	
	/**
	 * 获得关键词
	 * @param sLine 文本内容
	 * @param nMaxKeyLimit 生成的关键词的个数上限
	 * @param bWeightOut true:显示词性信息；false:不显示词性信息
	 * @return 关键词组成的字符串
	 * 备注：黑名单中出现的词，不会作为关键词出现
	 */
	public String NLPIR_GetKeyWords(String sLine, int nMaxKeyLimit,
			boolean bWeightOut);

	/**
	 * 获得关键词
	 * @param sFilename 文本文件的路径
	 * @param nMaxKeyLimit 生成的关键词的个数上限
	 * @param bWeightOut true:显示词性信息；false:不显示词性信息
	 * @return 关键词组成的字符串
	 * 备注：黑名单中出现的词，不会作为关键词出现
	 */
	public String NLPIR_GetFileKeyWords(String sFilename, int nMaxKeyLimit,
			boolean bWeightOut);
	
	/**
	 * 获得新词
	 * 注意：黑名单中出现的词不会作为新词出现
	 * @param sLine 文本内容 
	 * @param nMaxKeyLimit 生成的新词的个数上限
	 * @param bWeightOut true:显示词性信息；false:不显示词性信息
	 * @return 新词组成的字符串
	 */
	public String NLPIR_GetNewWords(String sLine, int nMaxKeyLimit,
			boolean bWeightOut);

	/**
	 * 获得新词
	 * @param string 文本文件的路径
	 * @param nMaxKeyLimit 生成的新词的个数上限
	 * @param bWeightOut true:显示词性信息；false:不显示词性信息
	 * @return 新词组成的字符串
	 */
	public String NLPIR_GetFileNewWords(String sFilename, int nMaxKeyLimit,
			boolean bWeightOut);

	/**
	 * 添加自定义单词
	 * @param userWord
	 * @return
	 */
	public int NLPIR_AddUserWord(String userWord);

	/**
	 * 保存词典, 该方法和NLPIR_AddUserWord搭配使用
	 * @return 1,true; 2,false
	 */
	public int NLPIR_SaveTheUsrDic();
	
	/**
	 * 删除词典中的单词
	 * @return -1, the word not exist in the user dictionary; else, the handle of the word deleted
	 */
	public int NLPIR_DelUsrWord(String sWord);
	
	/**
	 * 导入用户词典
	 * @param dictFileName 用户词典的路径（请使用全路径）
	 * @param bOverwrite 是否删除原有的自定义用户词典，true：覆盖；false：追加
	 * @return
	 * 备注：系统会自动处理重复词的问题
	 */
	public int NLPIR_ImportUserDict(String dictFileName, boolean bOverwrite);

	/**
	 * 退出，释放资源
	 * @return
	 */
	public boolean NLPIR_Exit();

	/**
	 * 导入黑名单，成功导入后，黑名单中出现的词，不会作为"关键词"和"新词"出现
	 * @param sFilename 文件的路径
	 * @return
	 */
	public int NLPIR_ImportKeyBlackList(String sFilename);

	/**
	 * 提取文章的指纹码
	 * @param sLine 文本内容
	 * @return 指纹码
	 */
	public long NLPIR_FingerPrint(String sLine);

	/**
	 * 获得单词的词性
	 * @param sWords 单词，例如：中华人民共和国
	 * @return  单词的词性，例如：中华人民共和国/ns/607#
	 */
	public String NLPIR_GetWordPOS(String sWords);
	
	
	/**
	 * 判断单词是否在核心词库中
	 * @param word 输入的单词
	 * @return  如果单词不存在就返回-1，否则返回单词在词典中的句柄
	 */
	public int NLPIR_IsWord(String word);
	
	/**
	 * 获取输入文本的词，词性，频统计结果，按照词频大小排序
	 * @param sText 文本内容
	 * @return 词频统计结果形式如下：张华平/nr/10#博士/n/9#分词/n/8
	 */
	public String NLPIR_WordFreqStat(String sText);
	
	/**
	 * 获取输入文本文件的词，词性，频统计结果，按照词频大小排序
	 * @param sFilename 文本文件的全路径
	 * @return 词频统计结果形式如下：张华平/nr/10#博士/n/9#分词/n/8
	 */
	public String NLPIR_FileWordFreqStat(String sFilename);
	
	/**
	 * 获取各类英文单词的原型，考虑了过去分词、单复数等情况
	 * @param sWord 输入的单词
	 * @return 词原型形式，例如：driven->drive   drives->drive   drove-->drive  
	 */
	public String NLPIR_GetEngWordOrign(String sWord);

	
}
