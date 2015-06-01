using System;
using System.Collections.Generic;
using System.Configuration;

namespace Lingjoin.ClassifierTest
{
    public static class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Classifier classifier = new Classifier();
            if (!classifier.Classifier_Init(classifier.DataDir + "rulelist.xml",
                classifier.DataDir + "DataFile"))
            {
                Console.WriteLine("初始化失败");
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }

            Console.WriteLine("分类开始：");

            String title = "天翼定制手机天语E600";
            String content = "全球旅行必备:天翼定制手机天语E600 新浪 2011-9-26 15:53手机——这项人们使用率最高的电子产品,其更新换代速度更是快得无法想象。那么对于我们消费者而言,应当如何选择呢? 显然,频繁的换机是非常不划算的,更会增加生活开支,平白增添生活负担。因此,我们在购机之初就应当选择一款满足自身需求的手机。...";

            Console.WriteLine("文本内容：\n" + content);

            String sResult = classifier.Classifier_Exec(title, content, 0);


            Console.WriteLine("\n过滤结果：" + sResult);

            List<string> results = classifier.ClassifierDetailForClasses(sResult);
            foreach (var s in results)
            {
                Console.WriteLine("过滤理由：" + s);
            }
            classifier.Classifier_Exit();

            Console.WriteLine("分类结束");
            Console.WriteLine("按任意键继续...");
            Console.ReadKey(true);
        }
    }
}
