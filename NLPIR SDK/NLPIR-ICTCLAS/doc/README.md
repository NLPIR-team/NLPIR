# NLPIR-ICTCLAS 中英文分词系统功能模块使用手册

## 1. 功能模块概述

**NLPIR/ICTCLAS中英文分词提供一套完整的API接口，可供用户灵活使用。功能模块分为：**

> * **分词系统初始化与退出；**
> * **用户词典；**
> * **中英文分词；**
> * **其他接口等。**

**核心模块以用户词和分词为主，通过用户词配置完成词典扩充，相关系统设置项，请参看第3部分分词系统配置。使用顺序和方法如下图，详细方法请参看第2部分。**![](/NLPIR%20SDK/NLPIR-ICTCLAS/doc/nlpir.png)

## 2.功能模块使用方法

### 2.1 初始化与退出

#### 2.1.1 分词系统初始化

**分词系统初始化是使用分词系统的第一步，该过程为：加载词典和授权信息，需设定三个参数，接口如下：**

```
NLPIR_API int NLPIR_Init(const char * sDataPath=0,int encode=GBK_CODE,const char*sLicenceCode=0);
```

> 参数：
>
> * sDataPath:为分词系统的词典路径（目录Data所在的相对路径或绝对路径的），请保证Data目录下的nlpir.user授权文件日期有效；
> * encode：为分词系统的编码设置项，该值的设定，标志着整个系统的输入输出编码均与之对应，包括文件类接口。如有不符，可能导致结果异常等现象。具体编码对应值，如下：
>
> ```
> #define GBK_CODE 0//默认支持GBK编码
> #define UTF8_CODE GBK_CODE+1//UTF8编码
> #define BIG5_CODE GBK_CODE+2//BIG5编码
> #define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
> #define UTF8_FANTI_CODE GBK_CODE+4//UTF8编码
> ```
>
> * sLicenseCode：分词系统授权码，以授权码的形式授权分词。可以设置为空，自动引用nlpir.user授权文件

**初始化方法的返回值为int型，1为初始化成功，0为失败（原因：词典路径错误或授权过期等）。**

#### 2.1.2 分词系统退出

**分词系统的退出函数是分词系统处理完，资源销毁接口，该函数在处理完数据后，最后调用。**

```
NLPIR_API bool NLPIR_Exit();
```

**成功退出时返回为true，否则为false。**

#### 2.1.3 关于分词系统的初始化和退出函数的使用问题

**初始化为系统使用的第一步，退出为系统的最后一步，请不要频繁调用初始化和退出，意外引起系统异常，初始化只需一次即可。**

### 2.2 用户词典

**用户词典是分词系统开发给用户的词典扩展接口，接口分为两种形式:**

> * **一种是以文件形式；**
> * **一种是单词导入。**

**用户词导入应该在分词操作的前一步，初始化的后一步完成。**

#### 2.2.1单词导入接口

**单词导入接口为单个词语导入的方法，由多个函数配合使用。相关接口如下：**

* ##### **单词添加接口**

```
NLPIR_API int NLPIR_AddUserWord(const char *sWord);
```

> 参数：
>
> * sWord:用户词，格式“词 词性”，词和词性以空格分开的字符串。

**调用该接口，将会向分词系统导入一个用户词，如果是临时使用，那么指定用该接口，系统只是加载到分词系统的内存中，如系统推出，重加初始化使用，那么添加的词将不再起作用。**

* ##### **保存接口**

**为了保证单词添加接口添加的词长期有效，那么需要调用用户词保存接口。**

```
NLPIR_API int NLPIR_SaveTheUsrDic();
```

**该接口的缓存文件将会在分词系统的Data目录中出现，保存后下次分词系统初始化后无需重复导入用户词即可使用。**

* ##### ** 删除单个用户词接口**

**用户词删除接口将删除指定的用户词。**

```
NLPIR_API int NLPIR_DelUsrWord(const char *sWord);
```

> 参数：
>
> * sWord：要删除的用户词。词语字符串

* ##### **清除用户词点接口**

**批量清除添加的用户词用户词**

```
NLPIR_API int NLPIR_CleanUserWord();
```

**2.2.2 批量用户词导入**  
**用户词典以文件形式存储，批量导入函数。**

```
NLPIR_API unsigned int NLPIR_ImportUserDict(const char *sFilename,bool bOverwrite=false);
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
NLPIR_API const char * NLPIR_ParagraphProcess(const char *sParagraph,int bPOStagged=1);
```

参数：

> * sParagraph:待分词字符串，保证以正常的数据样子传入即可。
> * bPOStagged:分词系统的标注集设定，参数值如下：
>
> ```
> #define ICT_POS_MAP_FIRST 1  //计算所一级标注集
> #define ICT_POS_MAP_SECOND 0 //计算所二级标注集
> #define PKU_POS_MAP_SECOND 2 //北大二级标注集
> #define PKU_POS_MAP_FIRST 3  //北大一级标注集
> ```

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

### 2.3.2 字符串分词词数统计接口

**该接口完成输入字符串的词数统计功能，统计该字符串中出现的总词数，接口形式如下：**

```
NLPIR_API int NLPIR_GetParagraphProcessAWordCount(const char *sParagraph);
```

> 参数：
>
> * sParagraph:待进行词数统计的字符串。
>
> 返回值为int型，词数统计结果。结果如下：
>
> 接口调用：
>
> ```
> NLPIR_GetParagraphProcessAWordCount("我是中国人")
> ```
>
> 结果：4

### 2.3.3 词频统计接口

**对输入的字符串进行词频统计，接口形式如下：**

```
NLPIR_API const char*  NLPIR_WordFreqStat(const char *sText);
```

> 参数：
>
> * sText:待分词统计字符串
>
> 返回结果：张华平/nr/10\#博士/n/9\#分词/n/8，带词性和词频的统计结果。

```
NLPIR_API const char*  NLPIR_FileWordFreqStat(const char *sFilename);
```

> 参数：
>
> * sFilename:待分词统计文件路径
>
> 返回结果：张华平/nr/10\#博士/n/9\#分词/n/8，带词性和词频的统计结果。

### 2.3.4 C/C++/C\#等支持

* #### 结构体定义

```
struct result_t{
  int start; //start position,词语在输入句子中的开始位置
  int length; //length,词语的长度
  char  sPOS[POS_SIZE];//word type，词性ID值，可以快速的获取词性表
  int    iPOS;//词性标注的编号
  int word_ID; //该词的内部ID号，如果是未登录词，设成0或者-1
  int word_type; //区分用户词典;1，是用户词典中的词；0，非用户词典中的词
  int weight;//word weight,read weight
 };
```

* #### 分词接口

```
NLPIR_API const result_t * NLPIR_ParagraphProcessA(const char *sParagraph,int *pResultCount,bool bUserDict=true);
```

> 参数：
>
> * sParagraph:待分词字符串
> * pResultCount:分词结果词数
> * bUserDict:是否启用用户词典 
>
> 返回结果为：
>
> ```
>     定义的结构体
> ```

* #### C\#词频统计接口

```
NLPIR_API void NLPIR_ParagraphProcessAW(int nCount,result_t * result);
```

> 参数：
>
> * nCount：词数
> * result：定义的结构体

### 2.3.5 文件类型的分词接口

**针对文件的分词接口，参数传入为待分词的文本文件。**

```
NLPIR_API double NLPIR_FileProcess(const char *sSourceFilename,const char *sResultFilename,int bPOStagged=1);
```

> 参数：
>
> * sSourceFilename:待分词的文本文件路径
> * sResultFilename:分词结果文件内容存储路径
> * bPOStagged：词性标注设置，同字符串分词接口2.3.1。

### 2.3.6 细粒度分词

**当前的切分结果过大时，如“中华人民共和国”，需要执行该函数，将切分结果细分为“中华 人民 共和国”，细分粒度最大为三个汉字。**

```
NLPIR_API const char*  NLPIR_FinerSegment(const char *sLine);
```

> 参数：
>
> * sLine:词语
>
> 返回结果为细粒度分词结果，不带词性。

## 2.4 英文分词

### 2.4.1 获取各类英文单词的原型

```
NLPIR_API const char*  NLPIR_GetEngWordOrign(const char *sWord);
```

> 参数：
>
> * sWord:词语
>   返回的词原型形式。

### 2.4.2 其他分词接口同中文分词接口

## 2.5 其他接口

### 2.5.1 获取词的一元概率

```
NLPIR_API double NLPIR_GetUniProb(const char *sWord);
```

> 参数：
>
> * sWord:词语
>   返回结果为double型的概率值。

### 2.5.2 判断是否为分词系统已有的词

* #### 判断是否为核心词典的词

```
NLPIR_API int NLPIR_IsWord(const char *sWord);
```

> 参数：
>
> * sWord：词语
>
> 返回值：0是不存在，1是存在

* #### 判断是否为用户词

```
NLPIR_API int NLPIR_IsUserWord(const char *sWord);
```

> 参数：
>
> * sWord:词语
>
> 返回值：0是不存在，1是存在

### 2.5.3 获取指定词的词性

```
NLPIR_API const char * NLPIR_GetWordPOS(const char *sWord);
```

> 参数：
>
> * sWord:词语
>
> 返回值：词的所有词性

### 2.5.3 设置词性标注集

```
NLPIR_API int NLPIR_SetPOSmap(int nPOSmap);
```

> 参数：
>
> * nPOSmap:词语 （对不上）
>
> ```
> #define GBK_CODE 0//默认支持GBK编码
> #define UTF8_CODE GBK_CODE+1//UTF8编码
> #define BIG5_CODE GBK_CODE+2//BIG5编码
> #define GBK_FANTI_CODE GBK_CODE+3//GBK编码，里面包含繁体字
> #define UTF8_FANTI_CODE GBK_CODE+4//UTF8编码
> ```
>
> 返回值：0是失败，1是成功

### 2.6 系统初始化失败等获取错误信息接口

**分词系统初始化失败后，调用错误信息获取接口，获取失败原因，接口如下：**

```
NLPIR_API const char * NLPIR_GetLastErrorMsg();
```

> 返回值：字符串类型错误信息

## 3. 分词系统配置

**分词系统的配置项，可控制用户词的优先级以及用户词典的启用等设置，详细设置请看配置文件。位于Data目录下Configure.xml中**

```
<?xmlversion="1.0"encoding="GB2312"?>
<NLPIR>
    <TagSet>ICTPOS.map</TagSet>//词性标注集映射文件
    <UserDict>on</UserDict>//On：UserDictionaryapplied;Off:notapplied；
    <UserDictPrior>Off</UserDictPrior>//用户词典优先,Addedin2006-03-16,requiredbyNECOn：用户词典和核心词典中同时有的词汇，用户词典优先，本功能不要滥用，如果将核心词典中的词都设置为用户词典，其效果适得其反
    <FieldDict>on</FieldDict>//On：FieldDictionaryapplied;Off:notapplied；  
    <GranularityContorl>off</GranularityContorl>
    <Log>on</Log>//On,Off；例如：Off:关闭日志功能；On:打开日志功能
    <version>2013</version>//系统版本号
    <Modify>2012-11-14</Modify>//系统最近修订时间
    <Lexicon>2012-11-14</Lexicon>//词典最近修订时间
    <Sentiment>On</Sentiment>//On,Off；例如：Off:关闭情感分析功能；On:打开情感分析功能
    <adaptive>true</adaptive>//自适应分词，默认为false，自适应分词的效率会较低
    <FinerSegCombined>false</FinerSegCombined>//true:粗细切分结合模式（中华人民共和国 切分结果为： 中华人民共和国 中华 人民 共和国），默认为false;
    <author>张华平博士</author>//作者
    <Contact>pipy_zhang@msn.com</Contact>//作者联系方式
</NLPIR>
```



