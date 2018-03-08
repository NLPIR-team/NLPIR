package com.lingjoin.cluster;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;

	public interface ClibraryCluster extends Library {

		/**
		 * 聚类组件接口的静态变量
		 */
		ClibraryCluster Instance = (ClibraryCluster) Native.loadLibrary(
				OSinfo.getSysAndBit("LJCluster"), ClibraryCluster.class);

		/**
		 * 初始化
		 * @param sDefaultPath Data文件夹的路径，置为空字符串时从项目根目录下寻找Data文件夹
		 * @param sLicenseCode 授权码，置为空字符串就可以了
		 * @param encode 文档编码格式，具体对照为：0：GBK；1：UTF8；2：BIG5；3：GBK（里面包含繁体字）
		 * @return true - 成功；false - 失败
		 */
		public boolean CLUS_Init(String sDefaultPath, String sLicenseCode, int encode);
		
		/**
		 * 功能：设置参数
		 * @param nMaxClus 最多输出前多少个类
		 * @param nMaxDoc 每个类最多输出前多少个文档
		 * @return true - 成功；false - 失败
		 *	备注：在进程中此函数必须在其他函数(除了初始化函数)之前调用
		 *       如果不调用，参数默认均为2000； 参数越大，系统占用内存越大，处理速度越慢
		 *       类和类内的文档均已按照重要性和及时性排过序
		 */
		public boolean CLUS_SetParameter(int nMaxClus, int nMaxDoc);

		/**
		 * 功能：追加内存内容
		 * @param sText  正文内容
		 * @param sSignature 唯一标识符
		 * @return true - 成功；false - 失败
		 * 备注：在进程中此函数可以在打印结果之前执行多次
		 */
		public boolean CLUS_AddContent(String sText, String sSignature);

		/**
		 * 功能：追加文件内容
		 * @param sFileName 文件全路径名称
		 * @param sSignature 唯一标识符
		 * @return true - 成功；false - 失败
		 * 备注：在进程中此函数可以在打印结果之前执行多次
		 */
		public boolean CLUS_AddFile(String sFileName, String sSignature);

		/**
		 * 打印结果
		 * @param sXmlFileName 聚类内容输出到XML文件中
		 * @return true - 成功；false - 失败
		 */
		public boolean CLUS_GetLatestResult(String sXmlFileName);

		/**
		 * 清空历史数据
		 */
		public void CLUS_CleanData();

		/**
		 * 退出，释放资源；进程结束前须调用它释放所占用的内存资源
		 */
		public void CLUS_Exit();

		/**
		 * 获得最后一次的错误消息
		 * @return 最后一次的错误消息
		 */
		public String CLUS_GetLastErrMsg();

	}
