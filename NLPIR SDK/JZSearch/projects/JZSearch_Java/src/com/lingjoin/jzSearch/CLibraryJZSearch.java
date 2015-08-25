package com.lingjoin.jzSearch;

import com.lingjoin.fileutil.OSinfo;
import com.sun.jna.Library;
import com.sun.jna.Native;


/**
 * 精准搜索组件的Java接口，采用JNA技术来实现
 * @author 张亚鹏
 *
 */
public interface CLibraryJZSearch extends Library {
	CLibraryJZSearch Instance = (CLibraryJZSearch) Native.loadLibrary("./JZSearchAPI.dll", CLibraryJZSearch.class);
	
	/*
	 * 索引部分的API - 开始
	 */
	/**
	 * 索引系统初始化，必须初始化后，才能使用CJZIndexer
	 * @param sDictPath 词典文件名；为空时，采用n-gram索引方法
	 * @param sFieldInfoFile 域字段信息，用于支持多域索引，为空则只支持一个字段
	 * @param encoding 编码格式，具体的编码对照如下：
									0：GBK
									1：UTF8
									2：BIG5
									3：GBK，里面包含繁体字；
	 * @param bICTCLAS false
	 * @param lang_type 语言类型， 0 : LANGUAGE_TYPE_UNKNOWN;
	 *                         1 : LANGUAGE_TYPE_CHINESE;
	 *                         2 : LANGUAGE_TYPE_UYGHAN;   
	 * @param sLicenceCode 授权码，为空字符串（即：""）就可以了
	 * @return 1：初始化成功；0：初始化失败
	 */
	public int JZIndexer_Init(String sDictPath, String sFieldInfoFile, int encoding);
	
	/**
	 * 在字段文件中添加字段
	 * @param sFieldName 域名称，在索引建立与搜索过程中，域的唯一标示符
	 * @param sDBFieldName 对应于数据库的字段名称；在数据库搜索的时候，用于获取数据库的数据
	 * @param nFieldType 数据类型   1 :  FIELD_TYPE_TEXT;
	 *                         2 : FIELD_TYPE_INT;
	 *                         3 : FIELD_TYPE_LONG;
	 *                         4 : FIELD_TYPE_DATETIME;
	 *                         5 : FIELD_TYPE_FLOAT;
	 * @param bIndexed 是否需要索引
	 * @param bRetrieved 搜索结果中是否要输出该字段内容
	 * @param bGeneral 是否纳入通配搜索的范畴
	 * @param bAbstracted 是否进行搜索摘要提取并红显
	 * @return
	 */
	public boolean JZIndexer_FieldAdd(String sFieldName, String sDBFieldName, int nFieldType, boolean bIndexed, boolean bRetrieved, boolean bGeneral, boolean bAbstracted);


	/**
	 * 保存的域信息数据文件
	 * @param sFieldInfoDataFile(.dat格式的文件)
	 * @return
	 */
	public boolean JZIndexer_FieldSave(String sFieldInfoDataFile);
	
	/**
	 * 读取已经保存好的域信息数据文件
	 * @param sFieldInfoDataFile(.dat格式的文件)
	 * @return
	 */
	public boolean JZIndexer_FieldLoad(String sFieldInfoDataFile);
	
	/**
	 * 生成实例失败，则返回为-1，否则为实例的Handle
	 * @param pcIndexFile
	 * @param nMaxMemSize 512000000
	 * @return 生成实例失败，则返回为-1，否则为实例的Handle
	 */
	public int JZIndexer_NewInstance(String pcIndexFile, int nMaxMemSize);

	/**
	 * 索引一段内存
	 * @param handle handle为JZIndexer_NewInstance返回的结果
	 * @param pText
	 * @param sFieldName 字段名称，为空则表示无字段信息
	 * @param nMemSize 0
	 * @return
	 */
	public int JZIndexer_MemIndexing(int handle, String pText, String sFieldName, int nMemSize);
	

	/**
	 * 索引一个文本文件
	 * @param handle
	 * @param TextFilename
	 * @param sFieldName 字段名称，为空则表示无字段信息
	 * @return
	 */
	public int JZIndexer_FileIndexing(int handle,String TextFilename, String sFieldName);

	/**
	 * 索引一个Big File中指定的偏移量和长度的文本文件
	 * @param handle
	 * @param sBigFilename Big File的文件名；
	 * @param nOffset 偏移量；
	 * @param nSize 文件长度
	 * @param sFieldName 字段名称，为空则表示无字段信息
	 * @return
	 */
	public int JZIndexer_BigFileIndexing(int handle, String sBigFilename, int nOffset, int nSize, String sFieldName);

	/**
	 * 对数值进行索引
	 * @param handle
	 * @param value
	 * @param sFieldName 字段名称，为空则表示无字段信息
	 * @return
	 */
	public int JZIndexer_IntIndexing(int handle, int value, String sFieldName);
	

	/**
	 * 对数值进行索引
	 * @param handle
	 * @param value
	 * @param sFieldName 字段名称，为空则表示无字段信息
	 * @return
	 */
	public int JZIndexer_FloatIndexing(int handle, float value, String sFieldName);
		
	/**
	 * 索引保存的名称
	 * @param handle
	 * @return
	 */
	public int JZIndexer_Save(int handle);
	
	
	/**
	 * 增加文档
	 * @param handle
	 * @return
	 */
	public int JZIndexer_AddDoc(int handle);
	
	
	/**
	 * 删除实例
	 * @param handle
	 * @return
	 */
	public int JZIndexer_DeleteInstance(int handle);
	
	/**
	 * 程序退出
	 * @return
	 */
	public boolean JZIndexer_Exit();
	/*
	 * 索引部分的API - 结束
	 */
	
	/*
	 * 搜索部分的API - 开始
	 */
	
	/**
	 * @param sIndexFile
	 * @param sDictPath 词典文件名；为空时，采用n-gram索引方法
	 * @param sFieldInfoFile 域字段信息，用于支持多域索引，为空则只支持一个字段
	 * @param MaxMemSize 512000000
	 * @param encoding 编码格式，具体的编码对照如下：
									0：GBK
									1：UTF8
									2：BIG5
									3：GBK，里面包含繁体字；
	 * @param nGroupMaxCount
	 * @param bICTCLAS false
	 * @param lang_type 语言类型， 0 : LANGUAGE_TYPE_UNKNOWN;
	 *                         1 : LANGUAGE_TYPE_CHINESE;
	 *                         2 : LANGUAGE_TYPE_UYGHAN;   
	 * @param sLicenceCode 授权码，为空字符串（即：""）就可以了
	 * @return searcher_handle值，用于调用JZSearcher_NewInstance方法
	 */
	public int JZSearch_Init(String sIndexFile, String sDictPath, String sFieldInfoFile, int MaxMemSize, int encoding, int nGroupMaxCount, boolean bICTCLAS, int lang_type, String sLicenceCode);
	/**
	 * @param sort_type 排序方式   1 : 按照DocID排序(SORT_TYPE_DOCID);
	 *                        2 : 按照相关度排序(SORT_TYPE_RELEVANCE)
	 *			  			  3 : 按照DocID倒序排序(SORT_TYPE_DOCID_REVERSE)
	 * @param searcher_handle 
	 * @return 生成实例失败，则返回为-1，否则为实例的Handle
	 */
	public int JZSearcher_NewInstance(int sort_type, int searcher_handle);
	
	/**
	 * @param handle
	 * @param query_line  查询表达式
	 * @param nStart 记录起始地址
	 * @param nPageCount 当前页返回结果数目
	 * @return 当前页需要返回所有的结果json字符串
	 */
	public String JZSearcher_Search(int handle, String query_line, int nStart, int nPageCount);
		
	public int JZSearcher_DeleteInstance(int handle);
	/*
	 * 索引部分的API - 结束
	 */

	/*
	 * 导出词频
	 */
	public int JZSearch_Export(String sExportFile, int handle);
	
	public int JZSearch_ExportTF(String sExportFile, int handle);
}
