#NLPIR
开发者：张华平/Dr. Kevin Zhang</br>
NLPIR官方网站：<http://www.nlpir.org/>
在线演示网址： http://ictclas.nlpir.org/nlpir/
张华平 博士 副教授 研究生导师
大数据搜索挖掘实验室（北京市海量语言信息处理与云计算应用工程技术研究中心） 主任
地址：北京海淀区中关村南大街5号 100081
电话：+86-10-68918642
手机（助手）：+86-13681251543
Email:kevinzhang@bit.edu.cn
MSN:  pipy_zhang@msn.com;
网站: http://www.nlpir.org (自然语言处理与信息检索共享平台)
http://www.bigdataBBS.com (大数据论坛)
微博:http://www.weibo.com/drkevinzhang/
微信：drkevinzhang
微信公众号：大数据千人会
Dr. Kevin Zhang  (张华平，Zhang Hua-Ping)
Associate Professor, Graduate Supervisor
Director, Big Data Search and Mining Lab. 
Beijing Engineering Research Center of Massive Language Information Processing and Cloud Computing Application
Beijing Institute of Technology
Add: No.5, South St.,Zhongguancun,Haidian District,Beijing,P.R.C  PC:100081
Tel: +86-10-68918642
Mobile(Assistant)：+86-13681251543
Email:kevinzhang@bit.edu.cn
MSN:  pipy_zhang@msn.com;
Website: http://www.nlpir.org (Natural Language Processing and
Information Retrieval Sharing Platform)
http://www.bigdataBBS.com (Big Data Forum)
Twitter: http://www.weibo.com/drkevinzhang/
Webchat: drkevinzhang
Subscriptions: Thousands of  Big Data Experts
 
##简介
NLPIR是一套专门针对原始文本集进行处理和加工的软件，提供了中间件处理效果的可视化展示，也可以作为小规模数据的处理加工工具。用户可以使用该软件对自己的数据进行处理。
>NLPIR分词系统前身为2000年发布的ICTCLAS词法分析系统，从2009年开始，为了和以前工作进行大的区隔，并推广NLPIR自然语言处理与信息检索共享平台，调整命名为NLPIR分词系统。</br>
>NLPIR 系统支持多种编码（GBK 编码、UTF8 编码、BIG5 编码）、多种操作系统（Windows, Linux， FreeBSD 等所有主流操作系统）、多种开发语言与平台（包括：C/C++/C#,Java,Python,Hadoop 等）。

##NLPIR工程包简介
License--一个月的授权文件；如果发生授权过期的情况，可以在此目录下下载更新。</br>
NLPIR_Demo--组件功能演示demo（NLPIR大数据搜索与挖掘共享开发平台）</br>
NLPIR_SDK--14个组件包，提供了用于技术二次开发的基础工具集，各个组件API可以无缝地融合到客户的各类复杂应用系统之中，可兼容Windows，Linux， Android，Maemo5, FreeBSD等不同操作系统平台，可以供Java，C，C#等各类开发语言使用。


##功能介绍

#####NLPIR大数据搜索与挖掘共享开发平台的14种功能：
                
1. 全文精准检索-JZSearch
> 支持文本、数字、日期、字符串等各种数据类型，多字段的高效搜索，支持AND/OR/NOT以及NEAR邻近等查询语法，支持维语、藏语、蒙语、阿拉伯、韩语等多种少数民族语言的检索。可以无缝地与现有文本处理系统与数据库系统融合。

2. 新词发现
>从文件集合中挖掘出内涵的新词语列表，可以用于用户专业词典的编撰；还可以进一步编辑标注，导入分词词典中，从而提高分词系统的准确度，并适应新的语言变化。

3. 分词标注
>对原始语料进行分词、自动识别人名地名机构名等未登录词、新词标注以及词性标注。并可在分析过程中，导入用户定义的词典。

4. 统计分析与术语翻译
>针对切分标注结果，系统可以自动地进行一元词频统计、二元词语转移概率统计（统计两个词左右连接的频次即概率）。针对常用的术语，会自动给出相应的英文解释。

5. 大数据聚类及热点分析-Cluster
>能够从大规模数据中自动分析出热点事件，并提供事件话题的关键特征描述。同时适用于长文本和短信、微博等短文本的热点分析。

6. 大数据分类过滤
>针对事先指定的规则和示例样本，系统自动从海量文档中筛选出符合需求的样本。

7. 自动摘要-Summary
>能够对单篇或多篇文章，自动提炼出内容的精华，方便用户快速浏览文本内容。

8. 关键词提取-KeyExtract
>能够对单篇文章或文章集合，提取出若干个代表文章中心思想的词汇或短语，可用于精化阅读、语义查询和快速匹配等。

9. 文档去重-RedupRemover
>能够快速准确地判断文件集合或数据库中是否存在相同或相似内容的记录，同时找出所有的重复记录。

10. HTML正文提取-HTMLPaser
>自动剔除导航性质的网页，剔除网页中的HTML标签和导航、广告等干扰性文字，返回有价值的正文内容。适用于大规模互联网信息的预处理和分析。

11. 编码自动识别与转换
>自动识别文档内容的编码，并进行自动转换，目前支持Unicode/BIG5/UTF-8等编码自动转换为简体的GBK，同时将繁体BIG5和繁体GBK进行繁简转化。 

12. 敏感关键词扫描系统KeyScanner
>关键词扫描系统，可以设置一组关键词，可实现实时高效的关键词扫描出来。设置一个关键词，可以自动识别扫描各类敏感词的变体，如繁体形式、中间加各类干扰噪音。例如：法轮大法 可以自动匹配 	法_轮*大-法 及繁体形式。

##下载说明（Download Instructions）

>如何在github上下载单个文件夹</br>
需要工具：TortoiseSVN</br>
操作举例：例如，你只需要“NLPIR SDK”中“classify”文件夹下的代码，先打开 classify, 其 URL 为: "https://github.com/NLPIR-team/NLPIR/tree/master/NLPIR%20SDK/Classify"  然后将   /tree/master/ 换成 /trunk/ 。</br>
"https://github.com/NLPIR-team/NLPIR/trunk/NLPIR%20SDK/Classify"</br>
然后, 输入:</br>
svn checkout https://github.com/NLPIR-team/NLPIR/trunk/NLPIR%20SDK/Classify</br>
ps: 第一次使用的话, 可能会出现下面这个提示:R)eject, accept (t)emporarily or accept (p)ermanently?</br>
输入 P 就行了.
