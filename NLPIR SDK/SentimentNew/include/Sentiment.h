/****************************************************************************
 *
 * NLPIR Sentimental Analysis System Copyright (c) 2000-2015
 *     Dr. Kevin Zhang (Hua-Ping Zhang)
 *     All rights reserved.
 *
 * This file is the confidential and proprietary property of 
 * Kevin Zhang and the possession or use of this file requires 
 * a written license from the author.
 * Filename: 
 * Abstract:
 *          Sentiment.h: definition of the NLPIR Sentiment Analysis system API
 * Author:   Kevin Zhang 
 *          Email: pipy_zhang@msn.com kevinzhang@bit.edu.cn
 *			Weibo: http://weibo.com/drkevinzhang
 *			Homepage: http://www.nlpir.org
 * Date:     2013-12-19
 *
 * Notes:
 *                
 ****************************************************************************/
#ifndef SENTIMENTANALYSIS_H
#define SENTIMENTANALYSIS_H

#define ENCODING_GBK 0
#define ENCODING_UTF8 ENCODING_GBK+1
#define ENCODING_BIG5 ENCODING_GBK+2
#define ENCODING_GBK_FANTI ENCODING_GBK+3//GBK中包含繁体
#define ENCODING_FANTI_UTF8 ENCODING_GBK+4
#define ENCODING_COUNT 4


#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC 
#endif

#ifdef OS_LINUX
	#define ST_API EXTERNC 
#else
#ifdef ST_EXPORTS
#define ST_API EXTERNC __declspec(dllexport)
#else
#define ST_API EXTERNC __declspec(dllimport)
#endif
#endif

/*********************************************************************
 *
 *  Func Name  : ST_Init
 *
 *  Description: Init ST_Init
 *               The function must be invoked before any operation listed as following
 *
 *  Parameters : const char * sInitDirPath=NULL
 *				 sDataPath:  Path where Data directory stored.
 *				 the default value is NULL, it indicates the initial directory is current working directory path
 *				 encode: encoding code;
 *				 sLicenseCode: license code for unlimited usage. common user ignore it
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2013-6-8
 *********************************************************************/
ST_API int ST_Init(const char * sDataPath=0, int encode=ENCODING_GBK, const char*sLicenceCode=0);
/*********************************************************************
 *
 *  Func Name  : ST_Exit
 *
 *  Description: Exist ST and free related buffer
 *               Exit the program and free memory
 *				 The function must be invoked while you needn't any lexical anlysis
 *
 *  Parameters : None
 *
 *  Returns    : success or fail
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2015-8-6
 *********************************************************************/
ST_API int ST_Exit();

/*********************************************************************
 *
 *  Func Name  : ST_GetOneObjectResult
 *
 *  Description: Get one object sentimental result
 *
 *  Parameters : sTitle: document title
 *               sContent: document content
 *               sObject: given an object, such as a product, a person or a brand
 *
 *  Returns    : const char * result buffer
 *               sample see  Appendix I:Sentimental analysis result sample
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2016-3-20
 *********************************************************************/
ST_API const char * ST_GetOneObjectResult(const char *sTitle, const char *sContent, const char *sObject);

/*********************************************************************
 *
 *  Func Name  : ST_GetMultiObjectResult
 *
 *  Description: Get multiple object sentimental result
 *
 *  Parameters : sTitle: document title
 *               sContent: document content
 *               sObjectRuleFile: see Appendix II: Multiple Object configure sample
 *
 *  Returns    : const char * result buffer
 *               sample see  Appendix I:Sentimental analysis result sample
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2016-3-20
 *********************************************************************/
ST_API const char * ST_GetMultiObjectResult(const char *sTitle, const char *sContent, const char *sObjectRuleFile);

/*********************************************************************
 *
 *  Func Name  : ST_GetSentimentPoint
 *
 *  Description: Get multiple object sentimental result
 *
 *  Parameters : sSentence: sentence memory
 *
 *  Returns    : const char * result buffer
 *               sample see  Appendix I:Sentimental analysis result sample
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2016-3-20
 *********************************************************************/
ST_API const char *  ST_GetSentencePoint(const char *sSentence);
/*********************************************************************
 *
 *  Func Name  : ST_GetSentimentPoint
 *
 *  Description: Get multiple object sentimental result
 *
 *  Parameters : sSentence: sentence memory
 *
 *  Returns    : double,Sentimental point
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2016-3-20
 *********************************************************************/
ST_API double ST_GetSentimentPoint(const char *sSentence);

/*********************************************************************
 *
 *  Func Name  : ST_ImportUserDict
 *
 *  Description: Import User-defined dictionary
 *  Parameters : 
 *				sFilename:Text filename for user dictionary 
 *				bOverwrite: true,  overwrite the existing dictionary 
 *						   false, add to  the existing dictionary 		
 *  Returns    : The  number of  lexical entry imported successfully
 *  Author     : Kevin Zhang
 *  History    : 
 *              1.create 2014-8-3
 *********************************************************************/
ST_API int ST_ImportUserDict(const char *sFilePath, int bOverwrite=false);
/*********************************************************************
 *
 *  Func Name  : ST_GetLastErrMsg
 *
 *  Description: Get Last ErrorMessage
 *    
 *
 *  Parameters : void
 *               
 *				  
 *  Returns    : the result buffer pointer 
 *
 *  Author     : Kevin Zhang  
 *  History    : 
 *              1.create 2014-2-27
 *********************************************************************/
ST_API const char * ST_GetLastErrMsg();


/*Appendix I:Sentimental analysis result sample
<?xml version="1.0" encoding="gbk" standalone="yes"?>
<LJSentiment-Result>
        <result>
                <object>郭德纲</object>
                <polarity>-0.50</polarity>
                <positivepoint>1.00</positivepoint>
                <negativepoint>-1.50</negativepoint>
                <sentenceclue>
                        <titlesentenceclue><![CDATA[
郭德纲需<neg value="-2">反思</neg>：观众如水，能载舟亦能覆舟。
]]></titlesentenceclue>
                        <contentsentenceclue><![CDATA[
郭德纲真<neg_word>不是</neg_word><neg value="-1">好人</neg>啊
目前德云社已申请<neg value="-1">行政复议</neg>，而郭德纲与<neg value="-1">打人</neg>字眼再次引起人们的热议
在舞台上，郭德纲把自己的身段放的那么低，与观众是那样的亲，为什么一到舞台下面就似乎<pos value="1">完全</pos>是换了一个人呢
　　郭德纲<neg_word>不</neg_word>在体制内，按他的话说自己就是一个<neg_word>非</neg_word><neg value="-1">著名</neg>相声演员，而那些在体质内的则<pos value="1">统 一</pos>被他戏称为主流的，而且在一切场合尽自己的最<pos value="1">大</pos>的可能 来<neg value="-1">讽刺</neg>和<neg value="-1">挖苦</neg>这些所谓的主流相声演员
郭德纲<pos value="1">成名</pos>，靠的<neg_word>不是</neg_word>哪个政府部门，靠的是自己<neg value="-1">坚持不懈</neg>的<pos value="1">努力</pos>，靠的是观众们的 力捧，靠的是电视台网络的<pos value="1">大力</pos>宣传
]]></contentsentenceclue>
                </sentenceclue>
        </result>
</LJSentiment-Result>
*/
/*Appendix II: Multiple Object configure sample
<?xml version="1.0" encoding="gb2312" standalone="yes" ?>
<LJSentiment-Config>
  <eventcategory>
    <categorynum>3</categorynum>

    <category id="1">
      <description>明星</description>
      <brandword>|鱼|李光耀|德云社|赵薇|范冰冰|</brandword>
      <featureword></featureword>
      <sentimentword>
        <advantage>|[positive.dat]|</advantage>
        <disadvantage>|[negative.dat]|</disadvantage>
        <negative>|[否]|</negative>
      </sentimentword>
    </category>

    <category id="2">
      <description>品牌</description>
      <brandword>|比亚迪|五粮液|龙大花生油|方正笔记本|比亚迪|</brandword>
      <featureword></featureword>
      <sentimentword>
        <advantage>|[positive.dat]|</advantage>
        <disadvantage>|[negative.dat]|</disadvantage>
        <negative>|[否]|</negative>
      </sentimentword>
    </category>

    <category id="3">
      <description>地区</description>
      <brandword>|亚洲|人民币|</brandword>
      <featureword></featureword>
      <sentimentword>
        <advantage>|[positive.dat]|</advantage>
        <disadvantage>|[negative.dat]|</disadvantage>
        <negative>|[否]|</negative>
      </sentimentword>
    </category>

  </eventcategory>
</LJSentiment-Config>

*/
#endif
