package com.lingjoin.docExtract;

import org.junit.Test;

import com.lingjoin.fileutil.FileOperateUtils;
import com.sun.jna.NativeLong;

public class DocExtractTest {
	

	/**
	 * 测试导入用户自定义词
	 */
	@Test
	public void testImportUserDict() {
		if ( DocExtractLibray.Instance.DE_Init("", 1, "") == 0 ) {
			System.out.println("DocExtractor初始化失败：" + DocExtractLibray.Instance.DE_GetLastErrMsg());
			System.exit(1);
		} 
		System.out.println("DocExtractor初始化成功");
		System.out.println("成功导入的自定义词个数：" + DocExtractLibray.Instance.DE_ImportUserDict("dict/userdic.txt"));
		
		System.out.println("是否安全退出-->"+DocExtractLibray.Instance.DE_Exit());
	}
	
	/**
	 * 测试导入自定义的情感词
	 */
	@Test
	public void testImportSentimentDict() {
		//1、初始化
		if ( DocExtractLibray.Instance.DE_Init("", 1, "") == 0 ) {
			System.out.println("DocExtractor初始化失败：" + DocExtractLibray.Instance.DE_GetLastErrMsg());
			System.exit(1);
		} 
		System.out.println("DocExtractor初始化成功");
		
		//2、导入自定义词典
		System.out.println("成功导入的自定义词个数：" + DocExtractLibray.Instance.DE_ImportUserDict("dict/userdic.txt"));
		//3、导入自定义情感词典
		System.out.println("成功导入的情感词个数：" + DocExtractLibray.Instance.DE_ImportSentimentDict("dict/mySentimentDict.txt"));
		
		//4、退出
		System.out.println("是否安全退出-->"+DocExtractLibray.Instance.DE_Exit());
	}
	
	/**
	 * 测试导入黑名单，注意：黑名单中的词不会出现在关键词中。
	 */
	@Test
	public void testImportKeyBlackList() {
		if ( DocExtractLibray.Instance.DE_Init("", 1, "") == 0 ) {
			System.out.println("DocExtractor初始化失败：" + DocExtractLibray.Instance.DE_GetLastErrMsg());
			System.exit(1);
		} 
		System.out.println("DocExtractor初始化成功");
		System.out.println("成功导入的黑名单词个数：" + DocExtractLibray.Instance.DE_ImportKeyBlackList("dict/myKeyBlackList.txt"));
		
		System.out.println("是否安全退出-->"+DocExtractLibray.Instance.DE_Exit());
	}
	
	
	
	/**
	 *测试文章实体抽取 
	 */
	@Test
	public void testExtratContent() {
		if (DocExtractLibray.Instance.DE_Init("", 1, "") == 0) {
			System.out.println("初始化失败："
					+ DocExtractLibray.Instance.DE_GetLastErrMsg());
			System.exit(1);
		}
		System.out.println("初始化成功");
		
	  String content = FileOperateUtils.getFileContent("test.txt", "utf-8");
//		String content = "王石是呼市中共代表团万科的";
	  int score=DocExtractLibray.Instance.DE_ComputeSentimentDoc(content);
	  System.out.println("--->score--->"+score);
	  NativeLong handle = DocExtractLibray.Instance.DE_ParseDocE(content, "mgc#ngd",
				true, DocExtractLibray.ALL_REQUIRED);
		System.out.println("抽取的人名为-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_PERSON));
		System.out.println("抽取的地名为-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_LOCATION));
		System.out.println("抽取的机构名为-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_ORGANIZATION));
		System.out.println("抽取的关键词为-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_KEYWORD));
		System.out.println("抽取的文章作者为-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_AUTHOR));
		System.out.println("抽取的媒体为-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_MEDIA));
		System.out.println("抽取的文章对应的所在国别为-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_COUNTRY));
		System.out.println("抽取的文章对应的所在省份为-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_PROVINCE));
		System.out.println("抽取的文章摘要为-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_ABSTRACT));
		System.out.println("输出文章的正面情感词为-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_POSITIVE));
		System.out.println("输出文章的副面情感词-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_NEGATIVE));
		System.out.println("输出文章原文-->" + content);
		System.out.println("输出文章去除网页等标签后的正文-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_DEL_HTML));
		System.out.println("去除空格:" + DocExtractLibray.Instance.DE_GetResult(handle, 11).replaceAll("[　*| *| *|//s*]*", ""));
		
		System.out.println("自定义词(mgc)-->"
				+ DocExtractLibray.Instance.DE_GetResult(handle, DocExtractLibray.DOC_EXTRACT_TYPE_USER_DEFINED + 1));
		System.out.println("情感值---->" + DocExtractLibray.Instance.DE_GetSentimentScore(handle));
		DocExtractLibray.Instance.DE_ReleaseHandle(handle);
		
		System.out.println("是否安全退出-->"+DocExtractLibray.Instance.DE_Exit());
	}

}
