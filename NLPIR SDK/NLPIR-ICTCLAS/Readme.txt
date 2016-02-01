				          Readme
一、欢迎使用NLPIR/ICTCLAS2016分词系统
    NLPIR分词系统前身为2000年发布的ICTCLAS词法分析系统，从2009年开始，为了和以前工作进行大的区隔，并推广NLPIR自然语言处理与信息检索共享平台，调整命名为NLPIR分词系统。张华平博士先后倾力打造十余年，内核升级十余次，先后获得了2010年钱伟长中文信息处理科学技术奖一等奖，2003年国际SIGHAN分词大赛综合第一名，2002年国内973评测综合第一名。全球用户突破30万，包括中国移动、华为、中搜、3721、NEC、中华商务网、硅谷动力、云南日报等企业，清华大学、新疆大学、华南理工、麻省大学等机构：同时，ICTCLAS广泛地被《科学时报》、《人民日报》海外版、《科技日报》等多家媒体报道。您可以访问Google进一步了解ICTCLAS的应用情况。
   我们提供各类二次开发接口，特别欢迎相关的科研人员、工程技术人员使用，并承诺非商用应用永久免费的共享策略。访问http://ictclas.nlpir.org/(自然语言处理与信息检索共享平台)，您可以获取NLPIR系统的最新版本，并欢迎您关注张华平博士的新浪微博 @ICTCLAS张华平博士 交流。

 		
            
二、文件包介绍
|   Readme.txt-------------------------->介绍
|   
+---bin
|   +---DocExtractor----------->文档篇章语义抽取系统
|   |       DocExtractor.bat-->批处理，可以针对指定的文件夹进行语义抽取
|   |       DocExtractor.dll-->支撑的动态链接库，基于分词基础上
|   |       DocExtractorSample.exe-->应用程序
|   |       
|   \---ICTCLAS2014----------->分词系统
|           ICTCLAS-tools.exe-->分词的支撑工具，可用于测试，本处主要用来做用户词典导入
|           importuserdict.bat-->可将用户词典自动导入到系统内
|           NLPIR.dll-->Win32下的支撑动态链接库，其他环境的库，可以访问lib对应环境的库文件
|           NLPIR.lib
|           NLPIR_WinDemo.exe-->Win32下的演示程序，在Win8 32位下编译而成，部分环境可能不支持，或者显示异常
|           userdic.txt-->用户词典，用户可以自行编辑
|           
+---Data-->系统核心词库
|   |   BIG2GBK.map
|   |   BIG5.pdat
|   |   BIG5.wordlist
|   |   BiWord.big
|   |   charset.type
|   |   Configure.xml
|   |   CoreDict.pdat
|   |   CoreDict.pos
|   |   CoreDict.unig
|   |   DocExtractor.user
|   |   FieldDict.pdat
|   |   FieldDict.pos
|   |   GBK.pdat
|   |   GBK.wordlist
|   |   GBK2BIG.map
|   |   GBK2GBKC.map
|   |   GBK2UTF.map
|   |   GBKA.pdat
|   |   GBKA.wordlist
|   |   GBKA2UTF.map
|   |   GBKC.pdat
|   |   GBKC.wordlist
|   |   GBKC2GBK.map
|   |   GranDict.pdat
|   |   GranDict.pos
|   |   ICTPOS.map
|   |   location.map
|   |   location.pdat
|   |   location.wordlist
|   |   NewWord.lst
|   |   NLPIR.ctx
|   |   NLPIR.user
|   |   NLPIR_First.map
|   |   nr.ctx
|   |   nr.fsa
|   |   nr.role
|   |   PKU.map
|   |   PKU_First.map
|   |   sentiment.pdat
|   |   sentiment.ung
|   |   UserDict.pdat
|   |   UTF2GBK.map
|   |   UTF2GBKA.map
|   |   UTF8.pdat
|   |   UTF8.wordlist
|   |   
|   \---English-->英文处理的支持知识库，如果不需要英文处理的功能，可以不加载本库。
|           English.pdat
|           English.pos
|           English.ung
|           English.wordlist
|           Irrel2regular.map
|           ne.pdat
|           ne.pos
|           ne.wordlist
|           
+---doc-->相关文档支持
|       ICTPOS3.0.doc-->我们的词性标注集说明
|       NLPIR-ICTCLAS2014分词系统开发手册.pdf-->开发使用手册
|       
+---include-->系统头文件
|       NLPIR.h
|       
+---lib-->不同环境下的支撑库，每一种库，同时支持C/C++/C#/Java库。其他小众化的环境支持，请联系我们
|   +---linux32-->Linux 32bit操作系统下的支持库
|   |       libNLPIR.so
|   |       
|   +---linux64-->Linux 64bit操作系统下的支持库
|   |       libNLPIR.so
|   |       Readme.txt
|   |       
|   +---win32-->Win 32bit操作系统下的支持库
|   |       NLPIR.dll
|   |       NLPIR.lib
|   |       
|   \---win64-->Win 64bit操作系统下的支持库
|           NLPIR.dll
|           NLPIR.lib
|           
+---ppt-->NLPIR2014开幕演讲的内容
|       NLPIR2014开幕演讲.pptx
|       
+---sample-->NLPIR2014示例程序，均调试通过
|   +---C-->NLPIR2014 C语言示例程序
|   |       Example-C.cpp
|   |       Makefile: Linux下的编译makefile
|   +---C#-->NLPIR2014 C#语言示例程序
|   |       Example.cs
|   |       
|   +---hadoop-->NLPIR2014 hadoop示例程序
|   |   |   .classpath
|   |   |   .project
|   |   |   asm-3.2.jar
|   |   |   aspectjrt-1.6.11.jar
|   |   |   aspectjtools-1.6.11.jar
|   |   |   commons-beanutils-1.7.0.jar
|   |   |   commons-beanutils-core-1.8.0.jar
|   |   |   commons-cli-1.2.jar
|   |   |   commons-codec-1.4.jar
|   |   |   commons-collections-3.2.1.jar
|   |   |   commons-configuration-1.6.jar
|   |   |   commons-daemon-1.0.1.jar
|   |   |   commons-digester-1.8.jar
|   |   |   commons-el-1.0.jar
|   |   |   commons-httpclient-3.0.1.jar
|   |   |   commons-io-2.1.jar
|   |   |   commons-lang-2.4.jar
|   |   |   commons-logging-1.1.1.jar
|   |   |   commons-logging-api-1.0.4.jar
|   |   |   commons-math-2.1.jar
|   |   |   commons-net-3.1.jar
|   |   |   core-3.1.1.jar
|   |   |   hadoop-ant-1.2.0.jar
|   |   |   hadoop-capacity-scheduler-1.2.0.jar
|   |   |   hadoop-client-1.2.0.jar
|   |   |   hadoop-core-1.2.0.jar
|   |   |   hadoop-examples-1.2.0.jar
|   |   |   hadoop-fairscheduler-1.2.0.jar
|   |   |   hadoop-minicluster-1.2.0.jar
|   |   |   hadoop-test-1.2.0.jar
|   |   |   hadoop-thriftfs-1.2.0.jar
|   |   |   hadoop-tools-1.2.0.jar
|   |   |   HadoopTestZel.jar
|   |   |   hsqldb-1.8.0.10.jar
|   |   |   hsqldb-1.8.0.10.LICENSE.txt
|   |   |   jackson-core-asl-1.8.8.jar
|   |   |   jackson-mapper-asl-1.8.8.jar
|   |   |   jasper-compiler-5.5.12.jar
|   |   |   jasper-runtime-5.5.12.jar
|   |   |   jdeb-0.8.jar
|   |   |   jersey-core-1.8.jar
|   |   |   jersey-json-1.8.jar
|   |   |   jersey-server-1.8.jar
|   |   |   jets3t-0.6.1.jar
|   |   |   jetty-6.1.26.jar
|   |   |   jetty-util-6.1.26.jar
|   |   |   jna-4.0.0.jar
|   |   |   jsch-0.1.42.jar
|   |   |   junit-4.5.jar
|   |   |   kfs-0.2.2.jar
|   |   |   kfs-0.2.LICENSE.txt
|   |   |   log4j-1.2.15.jar
|   |   |   mockito-all-1.8.5.jar
|   |   |   oro-2.0.8.jar
|   |   |   pom.xml
|   |   |   servlet-api-2.5-20081211.jar
|   |   |   slf4j-api-1.4.3.jar
|   |   |   slf4j-log4j12-1.4.3.jar
|   |   |   word-segmentation-job.iml
|   |   |   xmlenc-0.52.jar
|   |   |   
|   |   +---.settings
|   |   |       org.eclipse.core.resources.prefs
|   |   |       org.eclipse.jdt.core.prefs
|   |   |       
|   |   +---bin
|   |   |   +---com
|   |   |   |   \---joinsoft
|   |   |   |       \---hwhadoop
|   |   |   |           \---wordseg
|   |   |   |                   CLibrary.class
|   |   |   |                   MainTest.class
|   |   |   |                   NLPIR$CLibrary.class
|   |   |   |                   NLPIR.class
|   |   |   |                   Utils.class
|   |   |   |                   WordSegmentationJob.class
|   |   |   |                   WordSegmentationMapper.class
|   |   |   |                   WordSegmentationReduce.class
|   |   |   |                   
|   |   |   \---main
|   |   |       \---resources
|   |   |               nlpir.properties
|   |   |               
|   |   \---src
|   |       +---com
|   |       |   \---joinsoft
|   |       |       \---hwhadoop
|   |       |           \---wordseg
|   |       |                   CLibrary.java
|   |       |                   MainTest.java
|   |       |                   NLPIR.java
|   |       |                   Utils.java
|   |       |                   WordSegmentationJob.java
|   |       |                   WordSegmentationMapper.java
|   |       |                   WordSegmentationReduce.java
|   |       |                   
|   |       \---main
|   |           \---resources
|   |                   nlpir.properties
|   +---pythonsample-->NLPIR2014 Python示例程序
|   |                   
|   \---JnaTest_NLPIR-->NLPIR2014 Java采用JNA调用的示例程序
|       |   .classpath
|       |   .project
|       |   nlpir.properties
|       |   Readme.txt
|       |   
|       +---.settings
|       |       org.eclipse.core.resources.prefs
|       |       org.eclipse.jdt.core.prefs
|       |       
|       +---bin
|       |   +---code
|       |   |       NlpirTest$CLibrary.class
|       |   |       NlpirTest.class
|       |   |       
|       |   \---utils
|       |           ReadConfigUtil.class
|       |           SystemParas.class
|       |           
|       +---lib
|       |       jna-4.0.0.jar
|       |       
|       \---src
|           +---code
|           |       NlpirTest.java
|           |       
|           \---utils
|                   ReadConfigUtil.java
|                   SystemParas.java
|                   
\---test-->NLPIR2014测试文档集合
    |   18届三中全会.TXT
    |   English.txt
    |   中英文混杂示例.txt
    |   屌丝，一个字头的诞生.TXT
    |   用户词典.txt
    |   
    \---docs-->NLPIR2014测试文档集合
            0-两栖战车亮相.txt
            1-辽宁阜新官员涉嫌淫乱事件举报者被刑拘.txt
            2-辽宁一男子女厕用手机拍照被拘(图).txt
            3-两人打甲流疫苗后死亡 另有15例较严重异常反应.txt
            4-English.txt
        
四、文件包介绍
	1.
五、联系方式
	张华平 博士 副教授
北京理工大学大数据搜索与挖掘实验室 主任
地址：北京海淀区中关村南大街5号 100081
电话：+86-10-68918642
Email:kevinzhang@bit.edu.cn
MSN:  pipy_zhang@msn.com;
官网: http://ictclas.nlpir.org (NLPIR/ICTCLAS官网)
微博:http://www.weibo.com/drkevinzhang/
 
Dr. Kevin Zhang  (张华平，Zhang Hua-Ping)
Associate Professor, Graduate Supervisor
Director, Big Data Search and Mining Lab.
Beijing Institute of Technology 
Add: No.5, South St.,Zhongguancun,Haidian District,Beijing,P.R.C  PC:100081
Tel: +86-10-68918642
Email:kevinzhang@bit.edu.cn
MSN:  pipy_zhang@msn.com;
Website: http://ictclas.nlpir.org (NLPIR/ICTCLAS Official Website)
Microblog: http://www.weibo.com/drkevinzhang/