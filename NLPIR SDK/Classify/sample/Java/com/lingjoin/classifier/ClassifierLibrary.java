package com.lingjoin.classifier;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;

public interface ClassifierLibrary extends Library {

	ClassifierLibrary Instance = (ClassifierLibrary) Native
			.loadLibrary(OSinfo.getSysAndBit("LJClassifier"),
					ClassifierLibrary.class);
	
	/**
	 * 文件方式初始化
	 * @param conf 规则文件的路径
	 * @param sInitDirPath Data文件夹的父路径
	 * @return true:成功；false：失败  
	 * 出错信息记录在硬盘的./ljclassifier.log和./DataFile/ljclassifier.log
	 */
	public boolean classifier_init(String conf, String sInitDirPath);
	
	/**
	 * 对输入的文章结构进行分类
	 * @param sTitle 文章的标题
	 * @param sContent 文章的内容
	 * @param iType 输出类名和置信度：
	 *      	 	iType=0:  输出类名，各类之间用\t隔开  内容格式举例：“要闻	敏感	诉讼”       
	 *       		iType=1:  输出类名和置信度，各类之间用\t隔开，类名和权重用“ ”隔开   内容格式举例：“要闻 1.00	敏感 0.95	诉讼 0.82”
	 * @return 主题类别串  各类之间用\t隔开，类名按照置信度从高到低排序
	 */
	public String classifier_exec(String sTitle, String sContent, int iType);
	

	/**
	 * 对于当前文档，输入类名，取得结果明细
	 * @param classname classname:结果类名
	 * @return 结果明细 例如:
			   RULE3:
			   SUBRULE1: 内幕 1	
			   SUBRULE2: 股市 1	基金 3	股票 8	
			   SUBRULE3: 书摘 2	
	 */
	public String classifier_detail(String classname);
	
	
	/**
	 * 退出，释放资源
	 */
	public void classifier_exit();
}











