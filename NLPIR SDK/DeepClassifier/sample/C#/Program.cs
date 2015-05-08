using System;
using System.Collections.Generic;
using System.Configuration;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Lingjoin.ClassifierTest;

namespace Lingjoin.DeepClassifierTest
{
    class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            DeepClassifier dc = new DeepClassifier();

            //////////////////////////////////////
            //
            //训练过程
            //
            //////////////////////////////////////
            //1、训练过程--初始化

            if (dc.DC_Init(dc.RootDir, 0, 800, ""))
            {
                Console.WriteLine("deepClassifier初始化成功");
            }
            else
            {
                Console.WriteLine("deepClassifier初始化失败：" + dc.DC_GetLastErrorMsg());
                Console.WriteLine("结束");
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }
            //2、训练过程--遍历训练分类文本的文件夹，添加所有的训练分类文本

            string testFilesPath = ConfigurationManager.AppSettings["RootDirPath"] + @"test\训练语料";

            string[] dirs = Directory.GetDirectories(testFilesPath, "*", SearchOption.TopDirectoryOnly);

            foreach (string dir in dirs)
            {
                string className = dir.Substring(dir.LastIndexOf("\\") + 1);

                string[] files = Directory.GetFiles(dir, "*.txt", SearchOption.AllDirectories);

                foreach (string file in files)
                {
//                     fs = new FileStream(file, FileMode.Open, FileAccess.Read);
//                     sr = new StreamReader(fs);
//                     string sContext = sr.ReadToEnd();
// 
//                     //将训练分类文本加载到内存中
//                     DC.DC_AddTrain(className, sContext);

                    dc.DC_AddTrainFile(className, file);
                }
            }

            //3、训练过程--开始训练
            dc.DC_Train();
            //4、训练过程--训练结束，退出
            dc.DC_Exit();



            //////////////////////////////////////
            //
            //分类过程
            //
            /////////////////////////////////////
            //1、分类过程--初始化

            if (dc.DC_Init(dc.RootDir, 1, 800, ""))
            {
                Console.WriteLine("deepClassifier初始化成功");
            }
            else
            {
                Console.WriteLine("deepClassifier初始化失败：" + dc.DC_GetLastErrorMsg());
                Console.WriteLine("结束");
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }
            //2、分类过程--加载训练结果
            dc.DC_LoadTrainResult();

            //3、分类过程--读取待分类的文本
            string testFile = dc.RootDir + @"test\test.txt";

            string result = dc.DC_ClassifyFile(testFile);
            //4、分类过程--输出分类结果
            Console.WriteLine("分类结果：" + result);

            //5、分类过程--退出
            dc.DC_Exit();

            Console.WriteLine("结束");
            Console.WriteLine("按任意键继续...");
            Console.ReadKey(true);
        }
    }
}
