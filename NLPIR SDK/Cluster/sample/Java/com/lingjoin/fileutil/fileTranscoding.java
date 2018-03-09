package com.lingjoin.fileutil;

import java.io.File;
import java.util.ArrayList;

public class fileTranscoding {
        public static void main(String [] args){
        	ArrayList alOfFile=FileOperateUtils.getAllFilesPath(new File("tratin140826"));
        	for(int i=0;i<alOfFile.size();i++){
        		String filePath=alOfFile.get(i).toString();
        		
        		System.out.println(filePath);
        		String fileContent=FileOperateUtils.getFileContent(filePath, "utf-8");
        		System.out.println(fileContent);
        		String filePathGai=filePath.replace("train1400826", "train140826UTF");
        	    FileOperateUtils.writeFile(fileContent, filePathGai, "gbk");
        	}
        }
}
