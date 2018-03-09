package com.lingjoin.cluster;

import java.io.File;

import org.junit.Test;


public class ClusterTest {
	
	/**
	 * 根据文本文件聚类
	 */
	@Test
	public void testCluster0(){
		System.out.println("初始化开始....");
		boolean flag = ClibraryCluster.Instance.CLUS_Init("", "", 1);
		if (flag) {
			System.out.println("初始化成功....");
		} else {
			System.out.println("初始化失败....");
			System.out.println(ClibraryCluster.Instance.CLUS_GetLastErrMsg());
			System.exit(1);
		}
		
		ClibraryCluster.Instance.CLUS_SetParameter(500, 200);
		
		/*
		 * 读取项目根目录下名为test的文件夹内的所有文档
		 */
		File fileDir = new File("test");
		if ( fileDir.isDirectory() ) {
			File[] filesArray = fileDir.listFiles();
			for ( File file : filesArray ) {
				String fileName = file.getName();
				String filePath = file.getAbsolutePath();
				System.out.println("fileName: " + fileName);
				System.out.println("filePath: " + filePath);
				System.out.println("==================================");
				ClibraryCluster.Instance.CLUS_AddFile(filePath, fileName);
			}
		}
		
		ClibraryCluster.Instance.CLUS_GetLatestResult("d:/ClusterResultByFile.xml");
		ClibraryCluster.Instance.CLUS_Exit();
	}
	
	
	/**
	 * 根据文本内容聚类
	 */
	@Test
	public void testCluster1(){
		System.out.println("初始化开始....");
		boolean flag = ClibraryCluster.Instance.CLUS_Init("", "", 1);
		if (flag) {
			System.out.println("初始化成功....");
		} else {
			System.out.println("初始化失败....");
			System.out.println(ClibraryCluster.Instance.CLUS_GetLastErrMsg());
			System.exit(1);
		}
		
		ClibraryCluster.Instance.CLUS_SetParameter(10, 20);
		
		for ( int i = 0; i < 7; i++ ) {
			String content = "周公恐惧流言日，王莽谦恭下士时。假使当年身便死，一生真伪有谁知。";
			ClibraryCluster.Instance.CLUS_AddContent(content, "文章" + i);
		}
		
		ClibraryCluster.Instance.CLUS_GetLatestResult("ClusterResultByContent.xml");
		ClibraryCluster.Instance.CLUS_Exit();
		
	}
}
