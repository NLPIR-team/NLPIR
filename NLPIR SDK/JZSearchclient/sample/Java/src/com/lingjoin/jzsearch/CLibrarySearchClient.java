package com.lingjoin.jzsearch;

import com.sun.jna.Library;
import com.sun.jna.Native;

// 定义接口CLibrary，继承自com.sun.jna.Library
public interface CLibrarySearchClient extends Library {
	

	CLibrarySearchClient Instance = (CLibrarySearchClient) Native.loadLibrary(OSinfo
			.getSysAndBit("JZSearchAgentAPI"), CLibrarySearchClient.class);

	/**
	 * @param query_line 查询的语句  [FIELD] * [AND] 钢铁 ;*表示除标准号之外的通配符；2.AND后面可以放多个值；
	 * @param nStart 起始结果的行号，从0开始
	 * @param nPageCount 每页结果数目
	 * @param sHostIP 服务器主机IP
	 * @param nPortID 服务器主机端口号
	 * @return  搜索结果存放的XM格式的内存块，内容与XML一致
	 */
	public String jzsearch_query_client(String query_line, int nStart, int nPageCount, String sHostIP, int nPortID);
	

	/**
	 * 释放内存空间
	 * @return
	 */
	public boolean jzsearch_query_client_exit();

}
