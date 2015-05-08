using System;
using System.Text;

namespace Lingjoin.SentimentAnalysisTest
{
    class Program
    {
        static void Main(string[] args)
        {
            SentimentAnalysis sentimentAnalysis = new SentimentAnalysis();

            if (sentimentAnalysis.LJST_Inits(sentimentAnalysis.RootDir, 0, "") == 0)
            {
                Console.WriteLine("初始化失败");
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }


            /**
             * 根据内容获得情感分析
             */
            // sentimentAnalysis.LJST_ImportUserDict(sentimentAnalysis.RootDir + "test.txt", true);//导入词典
            byte[] result = new byte[100];//分析结果
            String content = "被查封7周之后，全球最大BT网站“海盗湾”又重新活过来了 | Pirate Bay（海盗湾）是全球最大的 BT 种子分享下载网站，去年 12 月因为遭到瑞典当局查封关闭服务长达 7 周时间。近日海盗湾以熟悉的thepiratebay.se域名继续上线运行，并在网站上用凤凰取代了海盗旗。";
            //根据内容获得情感分析
            sentimentAnalysis.LJST_GetParagraphSent(content, result);
            Console.WriteLine("根据文本内容分析结果：\n" + Encoding.UTF8.GetString(result));//输出分析结果

            /**
             * 根据文本文件获得情感分析
             */
            //result = new StringBuilder();
            //sentimentAnalysis.LJST_GetFileSent(sentimentAnalysis.RootDir + "content.txt", result);
            // Console.WriteLine("根据文本文件分析结果：\n" + result);//输出分析结果

            sentimentAnalysis.LJST_Exits();

            Console.WriteLine("结束");
            Console.WriteLine("按任意键继续...");
            Console.ReadKey(true);
        }
    }
}
