package com.lingjoin.nlpir;

import java.io.File;
import java.io.IOException;

import org.apache.commons.io.FileUtils;
import org.junit.Test;

public class NlpirTest {


	@Test
	/**
	 * 分词测试
	 */
	public void testParticiple() throws IOException {
		/*
		 * 1、初始化
		 */
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		/*
		 * 2、分词
		 */
//		String sSrc = "对于有的粉丝，我真的无语了！大家都为姚贝娜感到惋惜，都觉得太可惜了。但有歌迷的观点真的让人无语，说什么:吴奇隆在姚贝娜追悼会的时候结婚，这样好吗？首先吴刘跟姚的不幸有半毛钱关系啊;其次难道说姚的不幸，全中国有人结婚都得为这事让行？";
//		String sSrc = FileUtils.readFileToString(new File("eng.txt"), "utf-8");
//		String sSrc = "When preparing a Quality Plan, the processes applicable to the contract shall be defined and documented. These should originate from each discipline or department within the Contractor's organization and combined to form the Quality Management System with a scope to match the scope of the project. ";
		String sSrc = "电动机起动电容器";
		String data = CLibraryNlpir.Instance.NLPIR_ParagraphProcess(sSrc, 1);
		System.out.println("~~~分词结果: " + data);
		/*
		 * 3、退出（在实际的web开发中不用退出）
		 */
		CLibraryNlpir.Instance.NLPIR_Exit();
	}

	@Test
	/**
	 * 细粒度分词测试
	 */
	public void testFinerSegment() {
		/*
		 * 1、初始化
		 */
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		/*
		 * 2、细粒度分词
		 */
		String lenWords = "中华人民共和国";
		System.out.println("得到的返回值为-->"
				+ CLibraryNlpir.Instance.NLPIR_FinerSegment(lenWords));

		/*
		 * 3、退出（在实际的web开发中不用退出）
		 */
		CLibraryNlpir.Instance.NLPIR_Exit();
	}

	@Test
	/**
	 * 文件方式的分词测试
	 */
	public void testFileProcess() {
		/*
		 * 1、初始化
		 */
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		
		/*
		 * 2、文件方式的分词
		 */
		double lines = CLibraryNlpir.Instance.NLPIR_FileProcess("text.txt",
				"result.txt", 1);
		System.out.println("分词已结束：请到相应的目录查看");
		
		/*
		 * 3、退出（在实际的web开发中不用退出）
		 */
		CLibraryNlpir.Instance.NLPIR_Exit();
	}

	@Test
	/**
	 * 关键词提取测试
	 */
	public void testKeyWord() throws IOException {
		/*
		 * 1、初始化（在实际的web开发中初始化一次即可）
		 */
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		
		/*
		 * 2、关键词提取
		 */
//		String sSrc = "对于有的粉丝，我真的无语了！大家都为姚贝娜感到惋惜，都觉得太可惜了。但有装设歌迷的观点真的让人无语，说什么:吴奇隆在姚贝娜追悼会的时候结婚，这样好吗？首先吴刘跟姚的不幸有半毛钱关系啊;其次难道说姚的不幸，全中国有人结婚都得为这事让行？";
//		String sSrc = FileUtils.readFileToString(new File("eng.txt"), "utf-8");
//		String sSrc = "When preparing a Quality Plan, the processes applicable to the contract shall be defined and documented. These should originate from each discipline or department within the Contractor's organization and combined to form the Quality Management System with a scope to match the scope of the project. ";
		String sSrc = "5.8.4.2 Collect Quality Management System Data a) Monitor and measure the suitability of the Quality System. b) Monitor and measure the effectiveness of the Quality System. 5.8.4.3 Provide Quality Management Information ";
//		String sSrc = " Generic documentation needed may be contained in the Contractor's quality manual and documented procedures. This documentation may need to be selected, adapted and/or supplemented from existing in-house documentation. The Quality Plan shows how the Contractor's generic documented procedures are related to and applied to any necessary additional procedures peculiar to the contract in order to attain specified quality objectives. For ease of review and use, it is recommended that the structure and sequence of the ISO 9001 standard as applied in this procedure be followed. ";
		System.out.println("文章内容为---->" + sSrc);
		String data = CLibraryNlpir.Instance.NLPIR_GetKeyWords(sSrc, 100, true);
		System.out.println("提取到的关键词：" + data);
		
		/*
		 * 3、退出（在实际的web开发中不用退出）
		 */
		CLibraryNlpir.Instance.NLPIR_Exit();
	}

	@Test
	/**
	 * 新词提取测试
	 */
	public void testNewWord() throws IOException {
		/*
		 * 1、初始化（在实际的web开发中初始化一次即可）
		 */
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		
		
		/*
		 * 2、新词提取
		 */
		String filePath = "text.txt";
		String sSrc = FileUtils.readFileToString(new File(filePath), "utf-8");
		System.out.println("文章内容为---->" + sSrc);
		String data = CLibraryNlpir.Instance
				.NLPIR_GetNewWords(sSrc, 1024, true);
		System.out.println("新词提取结果：" + data);
		
		/*
		 * 3、退出（在实际的web开发中不用退出）
		 */
		CLibraryNlpir.Instance.NLPIR_Exit();
	}

	
	/**
	 * 添加用户自定义词测试 
	 */
	@Test
	public void testAddUserWord() {
		
		/*
		 * 1、初始化（在实际的web开发中初始化一次即可）
		 */
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		
		/*
		 * 2、添加用户自定义词
		 */
		String dict = "[An inspection]";
		CLibraryNlpir.Instance.NLPIR_AddUserWord(dict);
		int i = CLibraryNlpir.Instance.NLPIR_SaveTheUsrDic();
		System.out.println("==========: " + i);
		if (1 == i) {
			System.out.println(dict + "用户词添加成功");
		} else {
			System.out.println(dict + "用户词添加失败");
		}
		
		/*
		 * 3、退出（在实际的web开发中不用退出）
		 */
		CLibraryNlpir.Instance.NLPIR_Exit();
	}
	
	/**
	 * 删除用户自定义词测试 
	 */
	@Test
	public void testDelUserWord() {
		
		/*
		 * 1、初始化（在实际的web开发中初始化一次即可）
		 */
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		
		/*
		 * 2、添加用户自定义词
		 */
		String dict = "半毛钱";
		int handle = CLibraryNlpir.Instance.NLPIR_DelUsrWord(dict);
		
		if ( -1 == handle ) {
			System.out.println("\"" + dict + "\" 不存在，不需要删除");
		} else {
			int i = CLibraryNlpir.Instance.NLPIR_SaveTheUsrDic();
			if (1 == i) {
				System.out.println("\"" + dict + "\" 用户词删除成功");
			} else {
				System.out.println("\"" + dict + "\" 用户词删除失败");
			}
		}
		
		
		
		
		
		/*
		 * 3、退出（在实际的web开发中不用退出）
		 */
		CLibraryNlpir.Instance.NLPIR_Exit();
	}
	

	@Test
	/**
	 * 添加用户词典测试
	 */
	public void testImportUserDict() {
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		int addDictNum = CLibraryNlpir.Instance.NLPIR_ImportUserDict(
				"dict/newWord.txt", true);
		System.out.println("已经添加的用户自定义词个数（累加数）为：" + addDictNum);
		CLibraryNlpir.Instance.NLPIR_Exit();
	}

	@Test
	/**
	 * 添加用户黑名单词典测试
	 */
	public void testImportKeyblacklist() {
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		int addDictNum = CLibraryNlpir.Instance
				.NLPIR_ImportKeyBlackList("dict/keyblacklist.txt");
		System.out.println("已经添加的黑名单单词个数（累加数）为：" + addDictNum);
	}

	@Test
	/**
	 * 指纹提取测试
	 */
	public void testFingerPrint() {
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		String content = "我爱北京天安门";
		long fingerPrint = CLibraryNlpir.Instance.NLPIR_FingerPrint(content);
		System.out.println(fingerPrint);
	}

	@Test
	/**
	 * 是否在核心词典中测试
	 */
	public void testIsWord() {
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		String word = "半毛钱";
		System.out.println(CLibraryNlpir.Instance.NLPIR_IsWord(word));
	}

	@Test
	/**
	 * 词性测试,只对核心词库有效
	 */
	public void testGetWordPOS() {
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		String sWords = "半毛钱";
		System.out.println("传入的词为-->" + sWords);
		String s = CLibraryNlpir.Instance.NLPIR_GetWordPOS(sWords);
		System.out.println("返回词性为-->" + s);
	}

	@Test
	public void testWordFreqStat() {
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		String sSrc = "对于有的粉丝，我真的无语了！大家都为姚贝娜感到惋惜，都觉得太可惜了。但有歌迷的观点真的让人无语，说什么:吴奇隆在姚贝娜追悼会的时候结婚，这样好吗？首先吴刘跟姚的不幸有半毛钱关系啊;其次难道说姚的不幸，全中国有人结婚都得为这事让行？";
		String result = CLibraryNlpir.Instance.NLPIR_WordFreqStat(sSrc);
		System.out.println(String.format("======词频结果如下：====\n%s", result));
	}

	@Test
	public void testFileWordFreqStat() {
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		String filePath = "result.txt";
		String result = CLibraryNlpir.Instance.NLPIR_FileWordFreqStat(filePath);
		System.out.println(String.format("======词频结果如下：====\n%s", result));
	}

	@Test
	public void testNLPIR_GetEngWordOrign() {
		boolean flag = CLibraryNlpir.Instance.NLPIR_Init("", 1, "0");
		if (flag) {
			System.out.println("nlpir初始化成功");
		} else {
			System.out.println("nlpir初始化失败："
					+ CLibraryNlpir.Instance.NLPIR_GetLastErrorMsg());
		}
		String word = "Industry ";
		String result = CLibraryNlpir.Instance.NLPIR_GetEngWordOrign(word);
		System.out.println(String.format("输入的单词：%s\n单词的原型：%s", word, result));
	}
}
