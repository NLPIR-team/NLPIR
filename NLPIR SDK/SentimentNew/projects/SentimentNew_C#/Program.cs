using System;

namespace Lingjoin.SentimentNewTest
{
    class Program
    {
        static void Main(string[] args)
        {
            SentimentNew sentiment = new SentimentNew("nlpir.dll", "DocExtractor.dll");

            if (!sentiment.ST_Init(sentiment.DataDir, 1, ""))
            {
                Console.WriteLine("初始化失败");
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }

            int num = sentiment.ST_ImportUserDict(sentiment.RootDir + @"test\dict\sentilexicon.txt");
            Console.WriteLine("添加用户单词{0}个", num);

            Console.WriteLine("==============================================================");
            String sTitle = "";
            String sContent = "据《法制晚报》报道，警方已经证实1月9号在首都国际机场打人的均是德云社员工，且德云社三名员工因打人被警方处以行政拘留并罚款。目前德云社已申请行政复议，而郭德纲与“打人”字眼再次引起人们的热议。\n " +
                    "德云社为什么会频频出现打人事件，这是一个让我们很难理解的事情。在舞台上，郭德纲把自己的身段放的那么低，与观众是那样的亲，为什么一到舞台下面就似乎完全是换了一个人呢?\n" +
                    "郭德纲不在体制内，按他的话说自己就是一个“非著名相声演员”，而那些在体质内的则统一被他戏称为“主流的”，而且在一切场合尽自己的最大的可能来讽刺和挖苦这些所谓的“主流”相声演员。郭德纲成名，靠的不是哪个政府部门，靠的是自己坚持不懈的努力，靠的是观众们的力捧，靠的是电视台网络的大力宣传。所以，他在唱经典段子《大实话》的时候会一直唱“要说亲，观众们亲，观众演员心连着心!”";


            Console.WriteLine("标题为：\n" + sTitle);
            Console.WriteLine("内容为：\n" + sContent);
            Console.WriteLine("==============================================================");
            Console.WriteLine(sentiment.ST_GetOneObjectResult("", sContent, ""));
            Console.WriteLine("==============================================================");
            Console.WriteLine(sentiment.ST_GetMultiObjectResult("", sContent, ""));
            Console.WriteLine("==============================================================");
            Console.WriteLine(sentiment.ST_GetSentencePoint(""));

            sentiment.ST_Exit();

            Console.WriteLine("结束");
            Console.WriteLine("按任意键继续...");
            Console.ReadKey(true);

        }
    }
}
