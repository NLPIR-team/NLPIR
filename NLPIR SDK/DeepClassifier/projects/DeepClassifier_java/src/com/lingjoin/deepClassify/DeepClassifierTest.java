package com.lingjoin.deepClassify;


import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

import org.apache.commons.io.FileUtils;
import org.junit.Test;

import com.lingjoin.fileutil.FileOperateUtils;

public class DeepClassifierTest {
	
	
	/**
	 * 训练过程
	 * @throws IOException 
	 */
	@Test
	public void didTrain() throws IOException {
		//1、训练过程--初始化
		boolean flag = DeepClassifierLibrary.Instance.DC_Init("", 1, 800, "");
		if (flag) {
			System.out.println("deepClassifier初始化成功");
		} else {
			System.out.println("deepClassifier初始化失败：" + DeepClassifierLibrary.Instance.DC_GetLastErrorMsg());
			System.exit(1);
		}
		//2、训练过程--遍历训练分类文本的文件夹，添加所有的训练分类文本
		ArrayList list = FileOperateUtils.getAllFilesPath(new File("训练分类用文本"));
		for (int i = 0; i < list.size(); i++) {
			File f = new File(list.get(i).toString());
			String className = f.getParent();
			className = className
					.substring(className.lastIndexOf("\\") + 1);
			//将训练分类文本加载到内存中
			String contentText = FileUtils.readFileToString(f, "utf-8");
			DeepClassifierLibrary.Instance.DC_AddTrain(
					className, contentText);
		}
		//3、训练过程--开始训练
		DeepClassifierLibrary.Instance.DC_Train();
		//4、训练过程--训练结束，退出
		DeepClassifierLibrary.Instance.DC_Exit();
	}
	
	/**
	 * 分类过程
	 * @throws IOException
	 */
	@Test
	public void didClassify() throws IOException { 
		//1、分类过程--初始化
		if (DeepClassifierLibrary.Instance.DC_Init("", 1, 800, "")) {
			System.out.println("deepClassifier初始化成功");
		} else {
			System.out.println("deepClassifier初始化失败：" + DeepClassifierLibrary.Instance.DC_GetLastErrorMsg());
			System.exit(1);
		}
		//2、分类过程--加载训练结果
		DeepClassifierLibrary.Instance.DC_LoadTrainResult();
		
		//3、分类过程--读取待分类的文本
		String content = FileOperateUtils.getFileContent("test.txt", "utf-8");
		
		//4、分类过程--输出分类结果
		System.out.println("分类结果：" + DeepClassifierLibrary.Instance.DC_Classify(content));
		
		//5、分类过程--退出
		DeepClassifierLibrary.Instance.DC_Exit();
	}

}
