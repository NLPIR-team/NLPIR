# NLPIR-TC 繁体中文分词系统功能模块使用手册

## 1. 功能模块概述

**NLPIR-TC提供一套完整的API接口，可供用户灵活使用。功能模块分为：**

> * **分词系统初始化与退出；**
> * **用户词典；**
> * **其他接口等。**

**核心模块以用户词和分词为主，通过用户词配置完成词典扩充，相关系统设置项，请参看第3部分分词系统配置。使用顺序和方法如下图，详细方法请参看第2部分。**![](/NLPIR%20SDK/NLPIR-ICTCLAS/doc/nlpir.png)

## 2.功能模块使用方法

### 2.1 初始化与退出

#### 2.1.1 分词系统初始化

**分词系统初始化是使用分词系统的第一步，该过程为：加载词典和授权信息，需设定三个参数，接口如下：**
默认只支持 UTF-8编码的繁体中文
```
/*********************************************************************
*
*  Func Name  : Init
*
*  Description: Init NLPIRTC
*               The function must be invoked before any operation listed as following
*
*  Parameters : const char * sInitDirPath=NULL
*				 sDataPath:  Path where Data directory stored.
*				 the default value is NULL, it indicates the initial directory is current working directory path
*				 sLicenseCode: license code for unlimited usage. common user ignore it
*  Returns    : success or fail
*  Author     : Kevin Zhang
*  History    :
*              1.create 2020-6-8
*********************************************************************/
NLPIRTC_API int NLPIRTC_Init(const char * sDataPath = 0, const char*sLicenceCode = 0);
```

> 参数：
>
> * sDataPath:为分词系统的词典路径（目录Data所在的相对路径或绝对路径的），请保证Data目录下的nlpir.user授权文件日期有效；
> * 
> ```
>
<<<<<<< HEAD
<<<<<<< HEAD
> * sLicenseCode：分词系统授权码，以授权码的形式授权分词。可以设置为空，自动引用nlpir.user授权文件
=======
> * sLicenceCode：分词系统授权码，以授权码的形式授权分词。可以设置为空，自动引用nlpir.user授权文件
>>>>>>> 0f7977c44f2a601dffa078c14aeadbfc4ddc2990
=======
> * sLicenceCode：分词系统授权码，以授权码的形式授权分词。可以设置为空，自动引用nlpir.user授权文件
>>>>>>> 0f7977c44f2a601dffa078c14aeadbfc4ddc2990

**初始化方法的返回值为int型，1为初始化成功，0为失败（原因：词典路径错误或授权过期等）。**

#### 2.1.2 分词系统退出

**分词系统的退出函数是分词系统处理完，资源销毁接口，该函数在处理完数据后，最后调用。**

```
NLPIRTC_API bool NLPIRTC_Exit();
```

**成功退出时返回为true，否则为false。**

#### 2.1.3 关于分词系统的初始化和退出函数的使用问题

**初始化为系统使用的第一步，退出为系统的最后一步，请不要频繁调用初始化和退出，意外引起系统异常，初始化只需一次即可。**

### 2.2 用户词典

**用户词典是分词系统开发给用户的词典扩展接口，接口分为两种形式:**

> * **一种是以文件形式；**

** 批量用户词导入**  
**用户词典以文件形式存储，批量导入函数。**

```
NLPIRTC_API unsigned int NLPIRTC_ImportUserDict(const char *sFilename, bool bOverwrite = false);
```

> 参数：
>
> * sFilename:用户词典文件名，注用户词典文件编码与初始化方法一致，用户词性形式如下：
> * bOverwrite：是否覆盖现有用户词典，true为覆盖，false为不覆盖。

## 2.3 分词

**分词接口为分词系统的核心功能接口，有字符串分词接口，文件分词接口和字符串细粒度分词接口等。**

### 2.3.1 字符串分词接口

字符串分词接口能够接受字符串类型数据和返回字符串结果数据。C的接口数据类型是字符指针，对应Java中的String类，接口形式如下：

```
NLPIRTC_API const char * NLPIRTC_ParagraphProcess(const char *sParagraph, int bPOStagged = 1);
```

参数：

> * sParagraph:待分词字符串，保证以正常的数据样子传入即可。
> * bPOStagged:分词系统的标注集设定，参数值如下：
>
> ```
 ```

（对不上）  
**分词结果将返回结果：词与词之间以单个空格空开，bPOStagged设置为0时，分词系统将不对系统进行词性标注，空格空开的词为切分的词语不带词性信息，bPOStagged设置为非0值时，结果将附带词性信息，以“/”分开，结果如下：**

> * 接口调用：
>
> ```
> NLPIR_ParagraphProcess("我是中国人",1)
> ```
>
> * 返回值
>
> ```
> 我/rr 是/vshi 中国/ns 人/n
> ```

> 参数：
>
> * nCount：词数
> * result：定义的结构体

### 2.3.2 文件类型的分词接口

**针对文件的分词接口，参数传入为待分词的文本文件。**

```
NLPIRTC_API double NLPIRTC_FileProcess(const char *sSourceFilename, const char *sResultFilename, int bPOStagged = 1);
```

> 参数：
>
> * sSourceFilename:待分词的文本文件路径
> * sResultFilename:分词结果文件内容存储路径
> * bPOStagged：词性标注设置，同字符串分词接口2.3.1。


### 2.6 系统初始化失败等获取错误信息接口

**分词系统初始化失败后，调用错误信息获取接口，获取失败原因，接口如下：**

```
NLPIRTC_API const char * NLPIRTC_GetLastErrorMsg();```

> 返回值：字符串类型错误信息

```



