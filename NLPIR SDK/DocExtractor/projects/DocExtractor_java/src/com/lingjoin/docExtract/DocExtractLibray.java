package com.lingjoin.docExtract;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.NativeLong;


/**
 * 实体抽取java调用接口
 * @author 张亚鹏
 *
 */
public interface DocExtractLibray extends Library {

	// 定义并初始化接口的静态变量
	DocExtractLibray Instance = (DocExtractLibray) Native.loadLibrary(OSinfo.getSysAndBit("DocExtractor"), DocExtractLibray.class);

	/**
	 * 组件初始化
	 * @param sPath  Data文件夹的父目录，如果为空字符串（即：""），那么，程序自动从项目的根目录中寻找
	 * @param nEncoding 编码格式，具体的编码对照如下：
									0：GBK
									1：UTF8
									2：BIG5
									3：GBK，里面包含繁体字；
	 * @param sLicenseCode 授权码，为空字符串（即：""）就可以了
	 * @return 0:初始化失败；1：初始化成功
	 */
	/**
	 * @param sLicenceCode 
	 * @return true：初始化成功；false：初始化失败
	 */
	public int DE_Init(String sPath, int nEncoding, String sLicenseCode);

	/**
	 * 进行文本提取
	 * 
	 * @param content
	 *            :进行文本提取的内容
	 * @param sUserDefPos
	 *            :用户自定义或已有的三个标注，用#分割，如：a#v#adj
	 * @param bSummaryNeeded
	 *            ：是否需要摘要，默认为true
	 * @param nFuncRequired
	 *            ：需要提取的内容
	 * @return: 句柄
	 */
	public NativeLong DE_ParseDocE(String sText, String sUserDefPos,
			boolean bSummaryNeeded, int nFuncRequired);

	/**
	 * 获得结果
	 * 
	 * @param handle
	 *            :DE_ParseDocE返回的handle标志
	 * @param nDocExtractType
	 *            ：实体抽取类型
	 * @return：抽取结果
	 */
	public String DE_GetResult(NativeLong handle, int nDocExtractType);

	/**
	 * 
	 * @param handle
	 *            :DE_ParseDocE返回的handle标志
	 * @return:情感分值
	 */
	public int DE_GetSentimentScore(NativeLong handle);

	/**
	 * 
	 * @param handle
	 *            :DE_ParseDocE返回的handle标志
	 * @description:释放handle
	 */
	public void DE_ReleaseHandle(NativeLong handle);

	/**
	 * 计算文章的情感值
	 * @param sText 文章内容
	 * @return 情感值
	 */
	public int DE_ComputeSentimentDoc(String sText);

	/**
	 *  退出
	 * @return
	 */
	public boolean DE_Exit();

	/**
	 *  获得错误消息
	 * @return
	 */
	public String DE_GetLastErrMsg();

	/**
	 * 导入用户情感词典，注意：定义的情感词需在自定义词库或者核心词库中存在，如果不存在，应该先使用DE_ImportUserDict()把这个词加入到自定义词库中。
	 * @param sFilename 情感词典的路径
	 * @return
	 */
	public int DE_ImportSentimentDict(String sFilename);

	/**
	 * 导入用户词典
	 * @param sFilename 用户词典的路径
	 * @return
	 */
	public int DE_ImportUserDict(String sFilename);

	/**
	 * 导入关键词黑名单，凡是出现在黑名单中的词都不会作为关键词出现。
	 * @param sFilename
	 * @return
	 */
	public int DE_ImportKeyBlackList(String sFilename);
	
	
	/**
	 * 输出的人名
	 */
	public static final int DOC_EXTRACT_TYPE_PERSON = 0;
	/**
	 * 输出的地名
	 */
	public static final int DOC_EXTRACT_TYPE_LOCATION = 1; 
	/**
	 *  输出的机构名
	 */
	public static final int DOC_EXTRACT_TYPE_ORGANIZATION = 2;
	/**
	 *  输出的关键词
	 */
	public static final int DOC_EXTRACT_TYPE_KEYWORD = 3;
	/**
	 * 输出的文章作者
	 */
	public static final int DOC_EXTRACT_TYPE_AUTHOR = 4;
	/**
	 *  输出的媒体
	 */
	public static final int DOC_EXTRACT_TYPE_MEDIA = 5;
	/**
	 *  输出的文章对应的所在国别
	 */
	public static final int DOC_EXTRACT_TYPE_COUNTRY = 6;
	/**
	 * 输出的文章对应的所在省份
	 */
	public static final int DOC_EXTRACT_TYPE_PROVINCE = 7;
	/**
	 * 输出文章的摘要
	 */
	public static final int DOC_EXTRACT_TYPE_ABSTRACT = 8; 
	/**
	 * 输出文章的正面情感词为
	 */
	public static final int DOC_EXTRACT_TYPE_POSITIVE = 9;
	/**
	 * 输出文章的副面情感词
	 */
	public static final int DOC_EXTRACT_TYPE_NEGATIVE = 10;
	/**
	 * 输出文章去除网页等标签后的正文
	 */
	public static final int DOC_EXTRACT_TYPE_DEL_HTML = 11;
	/**
	 * 用户自定义词，其中：
	 * DOC_EXTRACT_TYPE_USER_DEFINED + 1:表示自定义的第一类词;
	 * DOC_EXTRACT_TYPE_USER_DEFINED + 2:表示自定义的第二类词;
	 * DOC_EXTRACT_TYPE_USER_DEFINED + 3:表示自定义的第三类词;
	 * DOC_EXTRACT_TYPE_USER_DEFINED + 4:表示自定义的第四类词;
	 * ...以此类推。
	 */
	public static final int DOC_EXTRACT_TYPE_USER_DEFINED = 11;

	public static final int PERSON_REQUIRED = 0x0001;
	public static final int LOCATION_REQUIRED = 0x0002;
	public static final int ORGANIZATION_REQUIRED = 0x0004;
	public static final int KEYWORD_REQUIRED = 0x0008;
	public static final int AUTHOR_REQUIRED = 0x0010;
	public static final int MEDIA_REQUIRED = 0x0100;
	public static final int COUNTRY_REQUIRED = 0x0200;
	public static final int PROVINCE_REQUIRED = 0x0400;
	public static final int ABSTRACT_REQUIRED = 0x0800;
	public static final int TRANS_REQUIRED = 0x1000;
	public static final int FOOD_REQUIRED = 0x2000;
	public static final int APPS_REQUIRED = 0x4000;
	public static final int SENTIMENT_REQUIRED = 0x8000;
	public static final int ALL_REQUIRED = 0xffff;
}
