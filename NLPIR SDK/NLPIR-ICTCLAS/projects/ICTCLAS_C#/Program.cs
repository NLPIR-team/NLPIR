using System;

namespace Lingjoin.ICTCLASTest
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            ICTCLAS nlpir = new ICTCLAS();


            if (nlpir.NLPIR_Init(nlpir.RootDir, 0, ""))
            {
                Console.WriteLine("初始化成功");
            }
            else
            {
                Console.WriteLine("初始化失败");
                Console.WriteLine("结束");
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }


            //  添加用户词语
            int addWordNum = nlpir.NLPIR_AddUserWord("全球通 user");
            // nlpir.NLPIR_SaveTheUsrDic(); 调用该方法可以使导入的单词保存到用户词典中
            Console.WriteLine("用户添加单词个数：" + addWordNum);
            Console.WriteLine();

            // 分词测试	
            String sSrc = "全球通，新华网北京4月28日电（记者陈二厚、董峻）“五一”国际劳动节即将来临之际，2015年庆祝“五一”国际劳动节暨表彰全国劳动模范和先进工作者大会28日在北京人民大会堂隆重举行。中共中央总书记、国家主席、中央军委主席习近平在会上发表重要讲话，代表党中央、国务院，向全国各族工人、农民、知识分子和其他各阶层劳动群众，向人民解放军指战员、武警部队官兵和公安民警，向香港同胞、澳门同胞、台湾同胞和海外侨胞，致以节日的祝贺；向为改革开放和社会主义现代化建设作出突出贡献的劳动模范和先进工作者，致以崇高的敬意。习近平还代表中国工人阶级和广大劳动群众，向全世界工人阶级和广大劳动群众，致以诚挚的问候。习近平在讲话中强调，我们所处的时代是催人奋进的伟大时代，我们进行的事业是前无古人的伟大事业。全面建成小康社会，进而建成富强民主文明和谐的社会主义现代化国家，根本上靠劳动、靠劳动者创造。无论时代条件如何变化，我们始终都要崇尚劳动、尊重劳动者，始终重视发挥工人阶级和广大劳动群众的主力军作用。这就是我们今天纪念“五一”国际劳动节的重大意义。李克强主持大会，张德江、俞正声、王岐山、张高丽出席，刘云山宣读表彰决定。上午10时，大会开始，全体起立，唱国歌。刘云山宣读《中共中央、国务院关于表彰全国劳动模范和先进工作者的决定》。决定指出，2010年以来特别是党的十八大以来，各行各业涌现出一大批爱岗敬业、勇于创新、品格高尚、业绩突出的先进模范人物，党中央、国务院决定授予2064人全国劳动模范荣誉称号、授予904人全国先进工作者荣誉称号。";


            Console.WriteLine("原文：" + sSrc);
            Console.WriteLine("\n分词结果：" + nlpir.NLPIR_ParagraphProcess(sSrc, 1));
            Console.WriteLine("\n新词发现：" + nlpir.NLPIR_GetNewWords(sSrc, 50, false));
            Console.WriteLine("\n关键词：" + nlpir.NLPIR_GetKeyWords(sSrc, 5, false));

            Console.WriteLine();

            // 细粒度分词测试
            String lenWords = "知识结构，奔三的人了";
            Console.WriteLine("原文：" + lenWords);
            Console.WriteLine("\n细粒度分词测试结果：" + nlpir.NLPIR_FinerSegment(lenWords));
            Console.WriteLine();

            // 添加用户词典测试
            int addDictNum = 0;
            addDictNum += nlpir.NLPIR_ImportUserDict(nlpir.RootDir + @"test/userdict.txt", true);
            // addDictNum += nlpir.NLPIR_ImportUserDict(nlpir.RootDir + @"dict/test/2.txt", true);
            Console.WriteLine("用户词典单词个数：" + addDictNum);
            Console.WriteLine();

            // 添加用户黑名单词典测试
            int addDictNum1 = nlpir.NLPIR_ImportKeyBlackList(nlpir.RootDir + @"test/keyblacklist.txt");
            Console.WriteLine("用户黑名单单词个数：" + addDictNum1);
            Console.WriteLine();

            // 关键词提取测试
            String sSrc1 = "数字签名，全球旅行必备话中蒙友好合作，谈中国周边外交，论亚洲国家相处之道，强调互尊互信、聚同化异、守望相助、合作共赢，共创中蒙关系发展新时代，共促亚洲稳定繁荣";
            String data1 = nlpir.NLPIR_GetKeyWords(sSrc1, 10, true);
            Console.WriteLine("原文：" + sSrc1);
            Console.WriteLine("\n关键词：" + data1);
            Console.WriteLine("\n分词结果：" + nlpir.NLPIR_ParagraphProcess(sSrc1, 1));
            Console.WriteLine();

            string sDelWord = "全球通";
            var resultDel = nlpir.NLPIR_DelUsrWord(sDelWord);
            Console.WriteLine("删除结果" + resultDel);
            Console.WriteLine();

            Console.WriteLine("原文：" + sSrc1);
            Console.WriteLine("\n分词结果：" + nlpir.NLPIR_ParagraphProcess(sSrc, 1));
            Console.WriteLine();

            // 指纹提取测试
            String content = "我爱北京天安门";
            long fingerPrint = nlpir.NLPIR_FingerPrint(content);
            Console.WriteLine("原文：" + content);
            Console.WriteLine("指纹提取：" + fingerPrint);
            Console.WriteLine();

            // 是否在核心词典中测试
            String word = "阿拉";
            Console.WriteLine("是否在核心词典中：" + nlpir.NLPIR_IsWord(word));
            Console.WriteLine();

            // 词性测试
            String sWords = "中华人民共和国";
            Console.WriteLine("传入的词为-->" + sWords);
            String s = nlpir.NLPIR_GetWordPOS(sWords);
            Console.WriteLine("返回词性为-->" + s);
            Console.WriteLine();

            String sSrc2 = "，全球旅行必备话中蒙友好合作，谈中国周边外交，论亚洲国家相处之道，强调互尊互信、聚同化异、守望相助、合作共赢，共创中蒙关系发展新时代，共促亚洲稳定繁荣";
            String result = nlpir.NLPIR_WordFreqStat(sSrc2);
            Console.WriteLine(String.Format("======词频结果如下：====\n{0}", result));
            Console.WriteLine();

            String word1 = "DRIVEN";
            String result2 = nlpir.NLPIR_GetEngWordOrign(word1);
            Console.WriteLine(String.Format("输入的单词：{0}\n单词的原型：{1}", word, result2));
            Console.WriteLine();

            nlpir.NLPIR_Exit();

            Console.WriteLine("测试结束");
            Console.WriteLine("按任意键继续...");
            Console.ReadKey(true);
        }
    }
}
