package com.lingjoin.summary;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;

/**
 * 生成摘要的组件，该组件可以自定义摘要的长度
 * @author lingjoin_zyp
 *
 */
public interface CLibraryDS extends Library {
	// 定义并初始化接口的静态变量
	CLibraryDS Instance = (CLibraryDS) Native.loadLibrary(OSinfo.getSysAndBit("LJSummary"), CLibraryDS.class);

	
	/**
	 * 功能：初始化
	 * @param sPath Data目录的父目录，可以直接传入""来表示寻找项目下的Data目录
	 * @param nEncoding 设置分词编码，只能处理相应初始编码的文件.默认为GBK。
	 *            0：GBK；1：UTF-8;2:BIG5;3:GBK_FANTI
	 * @param sLicenseCode  授权码，这里直接用"0"，就可以了
	 * @return true - 成功；false - 失败
	 * 备注：在进程中此函数必须在其他函数之前调用（只需执行一次）
	 */
	public boolean DS_Init(String sPath, int nEncoding, String sLicenseCode);
	
	
	/**
	 * 功能：生成单文档摘要
	 * @param sText 文档内容
	 * @param fSumRate 文档摘要占原文百分比,该值最大不能超过1.00
	 * @param iSumLen 用户限定的摘要长度  
	 * @param bHtmlTagRemove-[IN] 是否需要对原文进行Html标签的去除
	 * @return
	 * 备注：fSumRate和iSumLen这个两个参数设置一个就可以了，例如：
	 * 		DS_SingleDoc(sText, 0.00f, 80);
	 * 		DS_SingleDoc(sText, 0.50f, 0);
	 */
	public String DS_SingleDoc(String sText, float fSumRate, int iSumLen, boolean bHtmlTagRemove);
	
	/**
	 * 退出，释放资源；进程结束前须调用它释放所占用的内存资源
	 * 备注：如果需要频繁的生成摘要，那么不要调用这个方法
	 */
	public void DS_Exit();

	/**
	 * 获得错误消息
	 * @return 错误消息
	 * 备注：如果初始化失败，可以用该方法输出初始化失败原因
	 */
	public String DS_GetLastErrMsg();
}
