using System;

namespace Lingjoin.KeyExtractTest
{
    class Program
    {
        static void Main(string[] args)
        {
            KeyExtract keyExtract = new KeyExtract();

            if (!keyExtract.KeyExtract_Init(keyExtract.RootDir, 0
                , ""))
            {
                Console.WriteLine("初始化失败");
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }

            String content = "去年开始，打开百度李毅吧，满屏的帖子大多含有“屌丝”二字，一般网友不仅不懂这词什么意思，更难理解这个词为什么会这么火。然而从下半年开始，“屌丝”已经覆盖网络各个角落，人人争说屌丝，人人争当屌丝。";
            Console.WriteLine("内容为：\n" + content);


            String keyWordsStr = keyExtract.KeyExtract_GetKeyWords(content, 10, true);
            Console.WriteLine("\n关键字：\n" + keyWordsStr);

            keyExtract.KeyExtract_Exit();

            Console.WriteLine("结束");
            Console.WriteLine("按任意键继续...");
            Console.ReadKey(true);
        }
    }
}
