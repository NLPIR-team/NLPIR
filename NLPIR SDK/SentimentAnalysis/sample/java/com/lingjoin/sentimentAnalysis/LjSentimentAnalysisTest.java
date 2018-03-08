package com.lingjoin.sentimentAnalysis;

import org.junit.Test;

import com.lingjoin.sentimentAnalysis.LJSentimentAnalysisLibrary.CLibrarySentimentAnalysis;

public class LjSentimentAnalysisTest {

	/**
	 * 测试导入自定义情感词典
	 */
	@Test
	public void testImportUserDict() {
		// 初始化
		int flag = CLibrarySentimentAnalysis.Instance.LJST_Inits(
				"sentimentAnalysisData", 1, "");
		if (flag == 0) {
			System.out.println("SentimentAnalysis初始化失败");
			System.exit(0);
		} else {
			System.out.println("SentimentAnalysis初始化成功");
		}

		// 导入词典
		int count = CLibrarySentimentAnalysis.Instance.LJST_ImportUserDict("dict/sentiment_lib.txt", true);
		System.out.println("count: " + count);
		CLibrarySentimentAnalysis.Instance.LJST_Exits();
	}

	/**
	 * 根据内容获得情感分析
	 */
	@Test
	public void testGetParagraphSent() {
		// 初始化
		int flag = CLibrarySentimentAnalysis.Instance.LJST_Inits(
				"sentimentAnalysisData", 1, "");
		if (flag == 0) {
			System.out.println("SentimentAnalysis初始化失败");
			System.exit(0);
		} else {
			System.out.println("SentimentAnalysis初始化成功");
		}

		// 根据内容获得情感分析
		byte[] resultByte = new byte[10000];
//		String content = "对于有的粉丝，我真的无语了！大家都为姚贝娜感到惋惜，都觉得太可惜了。但有歌迷的观点真的让人无语，说什么:吴奇隆在姚贝娜追悼会的时候结婚，这样好吗？首先吴刘跟姚的不幸有半毛钱关系啊;其次难道说姚的不幸，全中国有人结婚都得为这事让行？";
		String content = "喜欢中山狼";
		CLibrarySentimentAnalysis.Instance.LJST_GetParagraphSent(content,
				resultByte);
		System.out.println("根据文本内容分析结果：\n" + new String(resultByte));// 输出分析结果

		// 退出
		CLibrarySentimentAnalysis.Instance.LJST_Exits();
	}

	/**
	 * 根据文本文件获得情感分析
	 */
	@Test
	public void testGetFileSent() {
		// 初始化
		int flag = CLibrarySentimentAnalysis.Instance.LJST_Inits("sentimentAnalysisData", 1, "");
		if (flag == 0) {
			System.out.println("SentimentAnalysis初始化失败");
			System.exit(0);
		} else {
			System.out.println("SentimentAnalysis初始化成功");
		}

		// 根据文本文件获得情感分析
		byte[] resultByte = new byte[10000];
		CLibrarySentimentAnalysis.Instance.LJST_GetFileSent("content.txt",
				resultByte);
		System.out.println("根据文件分析结果：" + new String(resultByte));// 输出分析结果

		// 退出
		CLibrarySentimentAnalysis.Instance.LJST_Exits();
	}
}
