package com.lingjoin.sentimentAnalysis;

import org.junit.Test;

import com.lingjoin.sentimentAnalysis.LJSentimentAnalysisLibrary.CLibrarySentimentAnalysis;


public class LjSentimentAnalysisTest {


	/**
	 * 根据内容获得情感分析
	 */
	@Test
	public void testGetParagraphSent(){
		//初始化
		int flag = CLibrarySentimentAnalysis.Instance.LJST_Inits("", 1, "");
		if ( flag == 0 ) {
			System.out.println("SentimentAnalysis初始化失败");
			System.exit(0);
		} else {
			System.out.println("SentimentAnalysis初始化成功");
		}
		
		//导入词典
		CLibrarySentimentAnalysis.Instance.LJST_ImportUserDict("dict/test.txt", true);
		
		
		byte[]  resultByte = new byte[10000];//分析结果
		String content = "真伪";
		//根据内容获得情感分析
		CLibrarySentimentAnalysis.Instance.LJST_GetParagraphSent(content, resultByte);
		System.out.println("根据文本内容分析结果：" + new String(resultByte));//输出分析结果
		
		//退出
		CLibrarySentimentAnalysis.Instance.LJST_Exits();
	}
	
	/**
	 * 根据文本文件获得情感分析
	 */
	@Test
	public void testGetFileSent(){
		//初始化
		int flag = CLibrarySentimentAnalysis.Instance.LJST_Inits("", 1, "");
		if ( flag == 0 ) {
			System.out.println("SentimentAnalysis初始化失败");
			System.exit(0);
		} else {
			System.out.println("SentimentAnalysis初始化成功");
		}
		
		//导入词典
		CLibrarySentimentAnalysis.Instance.LJST_ImportUserDict("dict/test.txt", true);
		
		
		byte[]  resultByte = new byte[10000];//分析结果
		//根据内容获得情感分析
		CLibrarySentimentAnalysis.Instance.LJST_GetFileSent("content.txt", resultByte);
		System.out.println("根据文件分析结果：" + new String(resultByte));//输出分析结果
		
		//退出
		CLibrarySentimentAnalysis.Instance.LJST_Exits();
	}
}
