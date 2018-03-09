package com.lingjoin.classifier;

import org.junit.Test;

public class ClassifierTest {

	@Test
	public void Star1() {
		boolean flag = ClassifierLibrary.Instance.classifier_init(
				"ruleFile/rulelist.xml", "DataFile");
		if (!flag) {
			System.out.println("初始化失败！\n");
			return;
		}

		System.out.print("初始化状态：" + (flag == true ? "成功\n\n" : "失败\n\n"));
		String title = "1";
		String content = "习近平总书记在中央军委发表重要讲话，他强调军委四个现代化人民军队";
		String res = ClassifierLibrary.Instance.classifier_exec(title, content,
				1);
		System.out.println("输出结果是:" + res + "\n\n");

		System.out.println(new String(ClassifierLibrary.Instance
				.classifier_detail("政治")));
		
		ClassifierLibrary.Instance.classifier_exit();

	}

}
