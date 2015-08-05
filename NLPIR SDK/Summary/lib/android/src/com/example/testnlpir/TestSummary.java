package com.example.testnlpir;

import com.example.testnlpir.Summary;//库函数申明
import java.util.*;
import java.io.*;

class Result {
	public int start; //start position,词语在输入句子中的开始位置
	public int length; //length,词语的长度
	public Character [] sPOS=new Character[40]; //词性 char  sPOS[POS_SIZE]
	public int posId;//word type，词性ID值，可以快速的获取词性表
	public int wordId; //如果是未登录词，设成0或者-1
	public int word_type; //add by qp 2008.10.29 区分用户词典;1，是用户词典中的词；0，非用户词典中的词
  public double weight;//add by qp 2008.11.17 word weight
};

public class TestSummary {
	/*
	public static void main(String[] args) throws Exception
	{
		try
		{
			String sInput = "多个研发中心中关村科技园区手机已经很好 媒体应该一个连接 手机打电话 微软一直 对 新 的 操作系统";
			//自适应分词
			test(sInput);		
		}
		catch (Exception ex)
		{
		} 
	}*/

	public static String test(String path, String sInput)
	{
		try
		{

			Summary testNLPIR = new Summary();//申请类
			String argu = path;
			System.out.println("NLPIR_Init");
			if (testNLPIR.NLPIR_Init(argu.getBytes("UTF8"),1,"".getBytes("UTF8")) == 0)//初始化，与C语言的函数功能类似
			{
				System.out.println("Init Fail!");
				byte nativeBytes[] =testNLPIR.NLPIR_GetLastMsg();
				String nativeStr = new String(nativeBytes, 0, nativeBytes.length, "UTF8");
				return "Init Fail! reason:"+nativeStr;
			}
			/*
			String dict_file = path+"/Data/";
			dict_file+="userdic.txt";
			int nRecordCount=testNLPIR.NLPIR_ImportUserDict(dict_file.getBytes("UTF8"));
			int nAddUserId=testNLPIR.NLPIR_AddUserWord("一藏寿司吧 cate".getBytes("UTF8"));
	
			//NLPIR_ParagraphProcess为：输入字符串，将分词结果输出到字符串，其中第二个参数表示是否进行词性标注
			byte nativeBytes[] = testNLPIR.NLPIR_ParagraphProcess(sInput.getBytes("UTF8"), 1);
			String nativeStr = new String(nativeBytes, 0, nativeBytes.length, "UTF8");
			byte nativeBytes2[] =testNLPIR.NLPIR_GetLastMsg();//如果结果不对，可以读取原因
			String nativeStr2 = new String(nativeBytes2, 0, nativeBytes2.length, "UTF8");
			System.out.println(nativeStr2);
			*/
			/*
			byte nativeBytes[] = testNLPIR.NLPIR_GetSummary(sInput.getBytes("UTF8"), 300,0);
			String nativeStr = new String(nativeBytes, 0, nativeBytes.length, "UTF8");
			
			String dict_file = path+"/Data/";
			dict_file+="input.txt";
			byte nativeBytes3[]=testNLPIR.NLPIR_GetFileSummary(dict_file.getBytes("UTF8"), 250,0);
			String nativeStr3 = new String(nativeBytes3, 0, nativeBytes3.length, "UTF8");
			
			byte nativeBytes2[] =testNLPIR.NLPIR_GetLastMsg();//如果结果不对，可以读取原因
			String nativeStr2 = new String(nativeBytes2, 0, nativeBytes2.length, "UTF8");
			System.out.println(nativeStr2);

			*/
			String dict_file = path+"/Data/";
			dict_file+="input.txt";
			byte nativeBytes1[]=testNLPIR.NLPIR_GetFileSummary(dict_file.getBytes("UTF8"), 250,0);
			String nativeStr1 = new String(nativeBytes1, 0, nativeBytes1.length, "UTF8");

			dict_file = path+"/Data/";
			dict_file+="input2.txt";
			byte nativeBytes2[]=testNLPIR.NLPIR_GetFileSummary(dict_file.getBytes("UTF8"), 250,0);
			String nativeStr2 = new String(nativeBytes2, 0, nativeBytes2.length, "UTF8");
			
			dict_file = path+"/Data/";
			dict_file+="input3.txt";
			byte nativeBytes3[]=testNLPIR.NLPIR_GetFileSummary(dict_file.getBytes("UTF8"), 250,0);
			String nativeStr3 = new String(nativeBytes3, 0, nativeBytes3.length, "UTF8");
			
			dict_file = path+"/Data/";
			dict_file+="input4.txt";
			byte nativeBytes4[]=testNLPIR.NLPIR_GetFileSummary(dict_file.getBytes("UTF8"), 250,0);
			String nativeStr4 = new String(nativeBytes4, 0, nativeBytes4.length, "UTF8");
			testNLPIR.NLPIR_Exit();
			//return "内存摘要结果为： " + nativeStr+"文件摘要结果为： " + nativeStr3+"提示信息为："+"内存摘要结果为： " + nativeStr2;
			return "文件摘要结果为： 1：" + nativeStr1+"文件摘要结果为： 2：" + nativeStr2+"文件摘要结果为： 3：" + nativeStr3+"文件摘要结果为： 4：" + nativeStr4;
			
		}
		catch (Exception ex)
		{
		} 
		return "";
}
}
 
