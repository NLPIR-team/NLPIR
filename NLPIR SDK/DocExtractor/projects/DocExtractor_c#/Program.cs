using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using Lingjoin.Global;

namespace Lingjoin.DocExtractorTest
{
    class Program
    {
        static void Main(string[] args)
        {
            DocExtractor docExtractor = new DocExtractor();

            if (docExtractor.DE_Init(docExtractor.RootDir, 0, "") == 0)
            {
                Console.WriteLine("初始化失败");
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }

            String content = "<td width=\"92%\"><font color=\"red\">新华网</font>天安门广场10月1日电（记者李大伟、李宣良）陆军铁骑可蹈海，在《战车进行曲》的昂扬旋律中，两栖突击车方队滚滚而来。装备05式...</td>";

            Console.WriteLine("内容为：\n" + content + '\n');

            int score = docExtractor.DE_ComputeSentimentDoc(content);
            Console.WriteLine("--->score--->" + score);
            long handle = docExtractor.DE_ParseDocE(content, "mgc#ngd", true, DocExtractor.ALL_REQUIRED);

            Console.WriteLine("抽取的人名为-->"+ docExtractor.DE_GetResult(handle, 0));
            Console.WriteLine("抽取的地名为-->"+ docExtractor.DE_GetResult(handle, 1));
            Console.WriteLine("抽取的机构名为-->"+ docExtractor.DE_GetResult(handle, 2));
            Console.WriteLine("抽取的关键词为-->"+ docExtractor.DE_GetResult(handle, 3));
            Console.WriteLine("抽取的文章作者为-->"+ docExtractor.DE_GetResult(handle, 4));
            Console.WriteLine("抽取的媒体为-->"+ docExtractor.DE_GetResult(handle, 5));
            Console.WriteLine("抽取的文章对应的所在国别为-->"+ docExtractor.DE_GetResult(handle, 6));
            Console.WriteLine("抽取的文章对应的所在省份为-->"+ docExtractor.DE_GetResult(handle, 7));
            Console.WriteLine("抽取的文章摘要为-->"+ docExtractor.DE_GetResult(handle, 8));
            Console.WriteLine("输出文章的正面情感词为-->"+ docExtractor.DE_GetResult(handle, 9));
            Console.WriteLine("输出文章的副面情感词-->"+ docExtractor.DE_GetResult(handle, 10));
            Console.WriteLine("输出文章去除网页等标签后的正文-->"+ docExtractor.DE_GetResult(handle, 11));

            // Console.WriteLine("去除空格:" + Regex.Replace(docExtractor.DE_GetResult(handle, 11), "[　*| *| *|//s*]*", ""));

            Console.WriteLine("自定义词(mgc)-->"+ docExtractor.DE_GetResult(handle, 12));
            Console.WriteLine("情感值---->" + docExtractor.DE_GetSentimentScore(handle));
            docExtractor.DE_ReleaseHandle(handle);


            docExtractor.DE_Exit();

            Console.WriteLine("结束");
            Console.WriteLine("按任意键继续...");
            Console.ReadKey(true);
        }
    }
}
