					九眼智能过滤系统介绍
   九眼智能过滤系统面向复杂文本大数据的内容智能过滤系统，可实时智能识别不良关键词音变、形变与拆字等常见变体，并实现了语义的精准排歧，系统内置了国内最新最全的不良词库，适用于诈骗、传销、暴恐、色情、邪教胁迫、网络赌博、反伦理、假发票、语言暴力、垃圾广告等不良内容的智能过滤发现。适用于国家安全、互联网内容发布、传媒出版等领域。

1.关键词列表的格式，采用文本文件，每行的格式如下：
	　词条　　词类  权重  是否变形处理
   例如： AV电影 色情 2 0
				 六合彩 涉赌 8 1
	 通过KS_ImportUserDict导入追加不良内容词表
2.目前系统内置了一部不良内容词典，主要类型定义如下：
诈骗、传销、暴恐、色情、邪教胁迫、网络赌博、反伦理、假发票、语言暴力、垃圾广告

3. 文件介绍如下：
+---bin                     可执行文件目录
|   |   09Eyes.exe          九眼单机版演示程序
|   |   importDict.bat      导入用户定义的关键词词典
|   |   JZSearchAPI.dll     
|   |   KeyScan.bat
|   |   KeyScanAPI.dll 
|   |   KeyScanAPI.lib
|   |   KeyScanner.exe
|   |   
|   \---output             目录扫描结果存储目录
|       \---scan
+---Data                   数据目录
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
|   |   GBK.pdat
|   |   GBK.wordlist
|   |   GBK2BIG.map
|   |   GBK2GBKA.map
|   |   GBK2UTF.map
|   |   GBK2UTF8.map
|   |   GBKA.pdat
|   |   GBKA.wordlist
|   |   GBKA2GBK.map
|   |   GBKA2UTF.map
|   |   GBKC2GBK.map
|   |   GranDict.pdat
|   |   GranDict.pos
|   |   hanzi.pdat
|   |   hanzi.wordlist
|   |   hanzi2pinyin.map
|   |   ICTPOS.map
|   |   KeyBlackList.pdat
|   |   LJHtmlParser.user
|   |   location.map
|   |   location.pdat
|   |   location.wordlist
|   |   NewWord.lst
|   |   NLPIR.ctx
|   |   NLPIR_First.map
|   |   nr.ctx
|   |   nr.fsa
|   |   nr.role
|   |   pinyin.pdat
|   |   pinyin.wordlist
|   |   PKU.map
|   |   PKU_First.map
|   |   sentiment.pdat
|   |   sentiment.ung
|   |   sentiment.wordlist
|   |   summary.user
|   |   UserDefinedDict.lst
|   |   UserDict.pdat
|   |   userdict2.txt
|   |   UTF2GBK.map
|   |   UTF2GBKA.map
|   |   UTF8.pdat
|   |   UTF8.wordlist
|   |   UTF82GBK.map
|   |   Xing.pdat
|   |   Xing.wordlist
|   |   Xing2Zi.map
|   |   Zi.pdat
|   |   Zi.wordlist
|   |   清除log.bat
|   |   
|   +---English
|   |       English.pdat
|   |       English.pos
|   |       English.ung
|   |       English.wordlist
|   |       Irrel2regular.map
|   |       ne.pdat
|   |       ne.pos
|   |       ne.wordlist
|   |       
|   \---KeyScanner
|           Filter0_class.pdat
|           Filter0_class.wordlist
|           Filter0_key.pdat
|           Filter0_key.pos
|           Filter0_key.wordlist
|           Filter0_py.pdat
|           Filter0_py.wordlist
|           Filter0_py2word.map
|           Filter0_word.pdat
|           Filter0_word.wordlist
|           keyScan.user
|           
+---doc                                文档目录
|       九眼智能过滤系统开发手册2017版.pdf
|       
+---include                            头文件
|       KeyScanAPI.h
|       
+---lib                                开发包
|   +---linux32
|   |       libKeyScanAPI.so
|   |       
|   +---linux64
|   |       libKeyScanAPI.so
|   |       
|   +---win32
|   |       KeyScanAPI.dll
|   |       KeyScanAPI.lib
|   |       KeyScanner.exe
|   |       
|   \---win64
|           KeyScanAPI.dll
|           KeyScanAPI.lib
|           KeyScanner.exe
|           
+---sample                       示例程序
|   \---c
|           Sample.cpp
|           
\---不良内容测试文件               测试文件目录
        keylist.txt              测试关键词表
        sample.TXT	             测试的样本文件

