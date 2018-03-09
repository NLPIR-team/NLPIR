package com.example.testnlpir;

import com.example.testnlpir.Summary;//�⺯������
import java.util.*;
import java.io.*;

class Result {
	public int start; //start position,��������������еĿ�ʼλ��
	public int length; //length,����ĳ���
	public Character [] sPOS=new Character[40]; //���� char  sPOS[POS_SIZE]
	public int posId;//word type������IDֵ�����Կ��ٵĻ�ȡ���Ա�
	public int wordId; //�����δ��¼�ʣ����0����-1
	public int word_type; //add by qp 2008.10.29 �����û��ʵ�;1�����û��ʵ��еĴʣ�0�����û��ʵ��еĴ�
  public double weight;//add by qp 2008.11.17 word weight
};

public class TestSummary {
	/*
	public static void main(String[] args) throws Exception
	{
		try
		{
			String sInput = "����з������йش�Ƽ�԰���ֻ��Ѿ��ܺ� ý��Ӧ��һ������ �ֻ���绰 ΢��һֱ �� �� �� ����ϵͳ";
			//����Ӧ�ִ�
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

			Summary testNLPIR = new Summary();//������
			String argu = path;
			System.out.println("NLPIR_Init");
			if (testNLPIR.NLPIR_Init(argu.getBytes("UTF8"),1,"".getBytes("UTF8")) == 0)//��ʼ������C���Եĺ�����������
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
			int nAddUserId=testNLPIR.NLPIR_AddUserWord("һ����˾�� cate".getBytes("UTF8"));
	
			//NLPIR_ParagraphProcessΪ�������ַ��������ִʽ��������ַ��������еڶ���������ʾ�Ƿ���д��Ա�ע
			byte nativeBytes[] = testNLPIR.NLPIR_ParagraphProcess(sInput.getBytes("UTF8"), 1);
			String nativeStr = new String(nativeBytes, 0, nativeBytes.length, "UTF8");
			byte nativeBytes2[] =testNLPIR.NLPIR_GetLastMsg();//���������ԣ����Զ�ȡԭ��
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
			
			byte nativeBytes2[] =testNLPIR.NLPIR_GetLastMsg();//���������ԣ����Զ�ȡԭ��
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
			//return "�ڴ�ժҪ���Ϊ�� " + nativeStr+"�ļ�ժҪ���Ϊ�� " + nativeStr3+"��ʾ��ϢΪ��"+"�ڴ�ժҪ���Ϊ�� " + nativeStr2;
			return "�ļ�ժҪ���Ϊ�� 1��" + nativeStr1+"�ļ�ժҪ���Ϊ�� 2��" + nativeStr2+"�ļ�ժҪ���Ϊ�� 3��" + nativeStr3+"�ļ�ժҪ���Ϊ�� 4��" + nativeStr4;
			
		}
		catch (Exception ex)
		{
		} 
		return "";
}
}
 
