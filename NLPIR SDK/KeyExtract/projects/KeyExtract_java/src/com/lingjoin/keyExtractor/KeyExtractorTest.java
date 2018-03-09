package com.lingjoin.keyExtractor;

public class KeyExtractorTest {

	static {
		if ( CLibraryKeyExtractor.instance.KeyExtract_Init("", 1, "") ) {
			System.out.println("KeyExtractor初始化成功");
		} else {
			System.out.println("KeyExtractor初始化失败");
			System.exit(-1);
		}
	}
	
	public static void main(String[] args) {
		String content = "，全球旅行必备话中蒙友好合作，谈中国周边外交，论亚洲国家相处之道，强调互尊互信、聚同化异、守望相助、合作共赢，共创中蒙关系发展新时代，共促亚洲稳定繁荣";
		String keyWordsStr = CLibraryKeyExtractor.instance.KeyExtract_GetKeyWords(content, 10, true);
		System.out.println(keyWordsStr);
		CLibraryKeyExtractor.instance.KeyExtract_Exit();
	}
}
