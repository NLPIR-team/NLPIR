    	NLPIRParser文本搜索与挖掘开发平台
 
一、简介
	NLPIRParser文本搜索与挖掘开发平台针对互联网内容处理的需要，融合了自然语言理解、网络搜索和文本挖掘的技术，提供了用于技术二次开发的基础工具集。开发平台由多个中间件组成，各个中间件API可以无缝地融合到客户的各类复杂应用系统之中，可兼容Windows，Linux， Android，Maemo5, FreeBSD等不同操作系统平台，可以供Java，C，C#等各类开发语言使用。
	NLPIRParser是一套专门针对原始文本集进行处理和加工的软件，提供了中间件处理效果的可视化展示，也可以作为小规模数据的处理加工工具。用户可以使用该软件对自己的数据进行处理。



二、功能
  	NLPIRParser文本搜索与挖掘开发平台的十二大功能：
	1. 新词发现：
	从文件集合中挖掘出内涵的新词语列表，可以用于用户专业词典的编撰；还可以进一步编辑标注，导入分词词典中，从而提高分词系统的准确度，并适应新的语言变化。
	2. 批量分词标注：
	对原始语料进行分词、自动识别人名地名机构名等未登录词、新词标注以及词性标注。并可在分析过程中，导入用户定义的词典。
	3. 统计分析与术语翻译
	针对切分标注结果，系统可以自动地进行一元词频统计、二元词语转移概率统计（统计两个词左右连接的频次即概率）。针对常用的术语，会自动给出相应的英文解释。
	4. 文本聚类及热点分析
	能够从大规模数据中自动分析出热点事件，并提供事件话题的关键特征描述。同时适用于长文本和短信、微博等短文本的热点分析。
	5. 大数据文本分类过滤
	针对事先指定的规则或示例样本，系统自动从海量文档中筛选出符合需求的样本。
	6. 摘要提取
	能够对单篇或多篇文章，自动提炼出内容的摘要，抽取人名、地名、机构名、时间及主题关键词；方便用户快速浏览文本内容。能够对单篇文章或文章集合，提取出若干个代表文章中心思想的词汇或短语，可用于精化阅读、语义查询和快速匹配等。
	7. 敏感信息扫描分析
	根据配置的敏感关键，快速扫描各种关键词及变种。
	8. 情感分析
	针对事先指定的分析对象和示例样本，系统自动从海量文档中筛选出正负面的得分和句子样例。
	9. 文档去重
	能够快速准确地判断文件集合或数据库中是否存在相同或相似内容的记录，同时找出所有的重复记录。
	10. HTML正文提取
	自动剔除导航性质的网页，剔除网页中的HTML标签和导航、广告等干扰性文字，返回有价值的正文内容。适用于大规模互联网信息的预处理和分析。
	12. 全文精准检索
	支持文本、数字、日期、字符串等各种数据类型，多字段的高效搜索，支持AND/OR/NOT以及NEAR邻近等查询语法，支持维语、藏语、蒙语、阿拉伯、韩语等多种少数民族语言的检索。可以无缝地与现有文本处理系统与数据库系统融合。
	13. 编码自动识别与转换
	自动识别内容的编码，并把编码统一转换为GBK编码。

三、文件说明

├─bin-win32       Windows 32bit环境下的可执行程序和库文件，也可运行于Win64；点击NLPIRParser.exe即可运行。
│  └─output       运行结果存放路径
├─bin-win64       Windows 64bit环境下的可执行程序和库文件；点击NLPIRParser.exe即可运行。
│  └─output				运行结果存放路径
├─Data					  整个系统运行需要的数据文件
│  ├─Cluster	    聚类系统运行需要的数据文件
│  │  └─Data
│  ├─DeepClassifier	    机器学习分类运行需要的数据文件
│  ├─English            英语处理需要的数据文件
│  ├─JZSearch           JZSearch精准语义搜索引擎处理需要的数据文件
│  ├─KeyScanner         JZSearch精准语义搜索引擎处理需要的数据文件
│  ├─RedupRemover			  去重需要的数据文件
│  └─SentimentNew		    情感分析需要的数据文件
│      └─Data
│          └─English
├─doc	  						    NLPIRParser使用手册与各模块接口文档文件
│  └─大数据组件接口文档
│      ├─Classifier
│      ├─Cluster
│      ├─DocExtractor
│      ├─DupRemove
│      ├─JZSearch
│      ├─KeyExtract
│      ├─LJSentimentAnalysis
│      ├─Summary
│      └─WordFreq
├─演示语料				  						    NLPIRParser提供的测试语料，可以自行替换
├─编码转换测试文本	  						  NLPIRParser提供的编码转换测试语料，可以自行替换
└─训练分类用文本  									NLPIRParser提供的分类训练语料，可以自行替换
    ├─交通
    ├─体育
    ├─军事
    ├─政治
    ├─教育
    ├─经济
    └─艺术

1. NLPIRParser.exe	可执行文件，本版本为共享版本（只能处理200个文件，总量不超过500KB纯文本），大规模语料处理需要购买正式版
2. 演示语料，用户可替换，必须为文本文件，如果为GBK以外的编码，必须先进行编码识别与转换后方可进行其他操作。
3. 各种dll为各组件的调用接口，本演示程序全部基于已有的调用接口实现；
4. 文档说明，参见当前目录下的用户手册。

四、联系方式
 
张华平 博士 副教授 研究生导师
大数据搜索挖掘实验室 主任
地址：北京海淀区中关村南大街5号 100081
电话：+86-10-68918642 13681251543(助理)
Email:kevinzhang@bit.edu.cn
MSN:  pipy_zhang@msn.com;
网站: http://www.nlpir.org (自然语言处理与信息检索共享平台)
         http://www.bigdataBBS.com (大数据论坛)
微信公众号：大数据千人会
微博:http://www.weibo.com/drkevinzhang/
Dr. Kevin Zhang  (张华平，Zhang Hua-Ping)
Associate Professor, Graduate Supervisor
Director, Big Data Search and Mining Lab.
Beijing Institute of Technology 
Add: No.5, South St.,Zhongguancun,Haidian District,Beijing,P.R.C  PC:100081
Tel: +86-10-68918642 13681251543(Assistant)
Email:kevinzhang@bit.edu.cn
MSN:  pipy_zhang@msn.com;
Website: http://www.nlpir.org (Natural Language Processing and 
Information Retrieval Sharing Platform)
                http://www.bigdataBBS.com (Big Data Forum)
Subscriptions: Thousands of  Big Data ExpertsTwitter: http://www.weibo.com/drkevinzhang/
