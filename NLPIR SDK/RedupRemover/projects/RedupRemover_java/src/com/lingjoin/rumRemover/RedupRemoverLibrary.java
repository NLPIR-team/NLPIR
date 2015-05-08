package com.lingjoin.rumRemover;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;


/**
 * 查重组件--java调用接口（采用JNA实现）
 * @author 张亚鹏
 */
public interface RedupRemoverLibrary extends Library {
	// 定义并初始化接口的静态变量，通过JNA调用NLPIR.dll;
	RedupRemoverLibrary Instance = (RedupRemoverLibrary) Native.loadLibrary(
			OSinfo.getSysAndBit("LJRedupRemover"), RedupRemoverLibrary.class);

	/**
	 * @param sHistoryDataFile 查重历史数据文件的路径，如果没有或者不想使用就置为空字符串
	 * @param sInitDirPath Data文件夹的父路径，为空字符串时默认从工程根目录下开始寻找
	 * @param bHistoryLoad 是否加载历史数据，默认为否
	 * @param sLicenseCode 授权码,写成空字符串就可以
	 * @param encode 文档的编码，具体对照如下：
						0：GBK；1：UTF8；2：BIG5；3：GBK（里面包含繁体字）
	 * @return
	 */
	public boolean RR_Init(String sHistoryDataFile, String sInitDirPath,
			boolean bHistoryLoad, String sLicenseCode, int encode);

	/**
	 * 处理文件
	 * @param fileContent 文章的内容
	 * @param sID 能够唯一标识该文本的字符串（比如：可以是文本的标题,或者数据库表的id字段）
	 * @return 返回1说明该文档是重复的，否则是不重复的
	 */
	public int RR_FileProcess(String fileContent, String sID);

	/**
	 * 返回累计已经发现的和当前文件重复的文件,结果保存在参数returnString中,该方法在RR_FileProcess的返回值是1时可以调用
	 * @param ReturnString 查重结果
	 * @param bAllOutput true：返回所有已经发现的和当前文件重复的文件；false：只返回当前文件，这里一般都设为true就可以了
	 * @return
	 */
	public boolean RR_FindRepeat(byte[] returnString, boolean bAllOutput);

	/**
	 * 保存重复文件信息
	 * 
	 * @param sHistoryDataFile 结果文件的路径（可以是相对路径也可以是绝对路径）
	 * @return
	 */
	public boolean RR_Output(String sHistoryDataFile);

	/**
	 * 保存查重历史数据，可用于下次加载，增量处理
	 * 
	 * @param DataFilePath  查重历史数据文件路径
	 * @return
	 */
	public boolean RR_SaveHistoryData(String DataFilePath);

	/**
	 * 退出
	 */
	public void RR_Exit();

	/**
	 * 获得最后一次错误信息
	 * 
	 * @return 最后一次错误信息
	 */ 
	public String RR_GetLastErrMsg();
	
	/**
	 *  编码：GBK
	 */
	public static final int ENCODE_GBK = 0;
	/**
	 *  编码：UTF8
	 */
	public static final int ENCODE_UTF8 = 1;
	/**
	 * 编码：BIG5
	 */
	public static final int ENCODE_BIG5 = 2;
	/**
	 * 编码：GBK（里面包含繁体字）
	 */
	public static final int ENCODE_GBKF = 3;
}
