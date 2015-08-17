using System;
using Lingjoin.Global;
using Util.File;

namespace Lingjoin.SummaryTest
{
    class Program
    {
        static void Main(string[] args)
        {
            Summary summary = new Summary();

            if (!summary.DS_Init(summary.DataDir, 0, ""))
            {
                Console.WriteLine("初始化失败");
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }


            String content = FileHelper.ReadFile(summary.RootDir + @"test\test.txt", "gbk");
            String result = summary.DS_SingleDoc(content, 1, 50, true);
            Console.WriteLine("内容为：" + content);
            Console.WriteLine();
            Console.WriteLine("摘要为：" + result);

            summary.DS_Exit();
            Console.WriteLine();
            Console.WriteLine("结束");
            Console.WriteLine("按任意键继续...");
            Console.ReadKey(true);
        }
    }
}
