package com.lingjoin.sentiment;

import com.sun.jna.Library;
import com.sun.jna.Native;

public interface CLibrarySentiment extends Library {

    CLibrarySentiment Instance = (CLibrarySentiment) Native.loadLibrary(
            "./SentimentNew.dll", CLibrarySentiment.class);

    /**
     * 初始化
     * @param sInitDirPath data文件夹所在的目录的路径
     * @param encode 编码
     * @param sLicenseCode 授权码
     * @return
     */
    int ST_Init(String sInitDirPath, int encode, String sLicenseCode);

    /**
     * 对一篇文章的某一个对象进行情感分析
     * @param sTitle 文章标题，若不分析标题则传入空字符串
     * @param sContent 文章内容
     * @param sObject 分析对象
     * @return 分析结果
     */
    String ST_GetOneObjectResult(String sTitle, String sContent, String sObject);

    /**
     * 对一篇文章的多个对象进行情感分析
     * @param sTitle 文章标题，若不分析标题则传入空字符串
     * @param sContent 文章内容
     * @param sObjectRuleFile 存放分析对象等信息的配置文件的路径，具体格式参考data文件夹下的stConduct.xml
     * @return 分析结果
     */
    String ST_GetMultiObjectResult(String sTitle, String sContent, String sObjectRuleFile);

    /**
     * 获取文章的情感值
     * @param sContent 文章内容
     * @return 分析结果
     */
    String ST_GetSentencePoint(String sContent);

    /**
     * 退出
     */
    void ST_Exit();

    /**
     * 获取最后一条出错记录
     * @return
     */
    String ST_GetLastErrMsg();

    double ST_GetSentimentPoint(String sSentence);

    /**
     * 导入情感词典
     * @param sFilePath 词典的路径
     * @param bSaveDict 1:保存到词库，0：不保存到词库
     * @return 导入单词的个数
     */
    public int ST_ImportUserDict(String sFilePath, int bSaveDict);
//

    /**
     * 删除单词
     * @param sWord 单词
     * @return 删除单词的个数
     */
    public int ST_DelUsrWord(String sWord);
}
