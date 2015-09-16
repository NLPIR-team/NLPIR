/***************************************************
*  Copyright (c) 2009. All rights reserved.
*  Procession or use of this file requires a written 
*  license from the author.
*  
*  Created: 2009-12-23
***************************************************/
#ifndef _H_CLUSTER_DLL
#define _H_CLUSTER_DLL

#ifdef OS_LINUX
#define CLUSTER_API extern "C" 
#else
#ifdef LJCLUSTER_EXPORTS
#define CLUSTER_API extern "C" __declspec(dllexport)
#else
#define CLUSTER_API extern "C"  __declspec(dllimport)
#endif
#endif

#define GBK_CODE 0//默认支持GBK编码
#define UTF8_CODE GBK_CODE+1//UTF8编码
#define BIG5_CODE GBK_CODE+2//BIG5编码
#define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字


/*-----------------------------------------------------------------------
* 功能：初始化
* 参数：sDefaultPath - 数据词典Data文件夹所在的路径
*		sLicenseCode - 授权码
*		encode - 编码
* 返回：true - 成功；false - 失败
* 备注：在进程中此函数必须在其他函数之前调用（只需执行一次）
------------------------------------------------------------------------*/
CLUSTER_API bool CLUS_Init(const char *sDefaultPath,const char *sLicenseCode=0,int encode=GBK_CODE);
//聚类最大数量，每个聚类最大文档数，停用词文件路径

/*-----------------------------------------------------------------------
* 功能：设置参数
* 参数：nMaxClus 最多输出前多少个类     nMaxDoc 每个类最多输出前多少个文档   
* 返回：true - 成功；false - 失败
* 备注：在进程中此函数必须在其他函数之前调用
*       如果不调用，参数默认均为2000； 参数越大，系统占用内存越大，处理速度越慢
*       类和类内的文档均已按照重要性和及时性排过序
------------------------------------------------------------------------*/
CLUSTER_API bool CLUS_SetParameter(int nMaxClus, int nMaxDoc);

/*-----------------------------------------------------------------------
* 功能：追加内存内容
* 参数：sText           - [IN] 正文内容（以'\0'结束的字符串）
*       sSignature      - [IN] 唯一标识符（以'\0'结束的字符串）
* 返回：true - 成功；false - 失败
* 备注：在进程中此函数可以在打印结果之前执行多次
------------------------------------------------------------------------*/
CLUSTER_API bool CLUS_AddContent(const char *sText, const char* sSignature);

/*-----------------------------------------------------------------------
* 功能：追加文件内容
* 参数：sFileName       - [IN] 文件全路径名称（以'\0'结束的字符串）
*       sSignature      - [IN] 唯一标识符（以'\0'结束的字符串）
* 返回：true - 成功；false - 失败
* 备注：在进程中此函数可以在打印结果之前执行多次
------------------------------------------------------------------------*/
CLUSTER_API bool CLUS_AddFile(const char *sFileName, const char* sSignature);

/*-----------------------------------------------------------------------
* 功能：打印结果
* 参数：sXmlFileName    
- [OUT]聚类内容输出到XML文件格式的内存中
* 返回：true - 成功；false - 失败
------------------------------------------------------------------------*/
CLUSTER_API bool CLUS_GetLatestResult(const char* sXmlFileName);


/*-----------------------------------------------------------------------
* 功能：打印结果
* 参数：sXmlFileName    - [OUT]聚类内容输出到XML文件格式的内存中
* 返回：true - 成功；false - 失败
------------------------------------------------------------------------*/
CLUSTER_API const char* CLUS_GetLatestResultE();

//清空历史数据
CLUSTER_API void CLUS_CleanData();

//退出，释放资源；进程结束前须调用它释放所占用的内存资源
CLUSTER_API void CLUS_Exit();

//获得错误消息
CLUSTER_API const char* CLUS_GetLastErrMsg();

#endif //_H_CLUSTER_DLL


/*备注：  XML格式

<?xml version="1.0" encoding="gb2312" standalone="yes" ?>
<LJCluster-Result>
<clusnum>2</clusnum>

<clus id="0">
	<feature>奥巴马 竞选 财务部</feature>
    <docs num="6">
       <doc>2</doc>
       <doc>3</doc>       
       <doc>35</doc>
       <doc>86</doc>
       <doc>345</doc>
       <doc>975</doc>       
    </docs>
</clus>    

<clus id="1">
	<feature>林志玲 影视 电影 广告</feature>
    <docs num="4">
       <doc>45</doc>
       <doc>86</doc>       
       <doc>135</doc>
       <doc>286</doc>      
    </docs>
</clus>  
</LJCluster-Result>
*/
