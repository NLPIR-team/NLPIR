using System;
using System.IO;

namespace Lingjoin.ClusterTest
{
    class Program
    {
        static void Main(string[] args)
        {

            Cluster cluster = new Cluster();
            if (!cluster.CLUS_Init(cluster.RootDir, "", 1))
            {
                Console.WriteLine("初始化失败：" + cluster.CLUS_GetLastErrMsg());
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }

            cluster.CLUS_SetParameter(500, 200);


            /**
             * 根据文本文件聚类
             */
            string TestFilesPath = cluster.RootDir + @"test\"; // 读取项目根目录下名为test的文件夹内的所有文档
            string[] files = Directory.GetFiles(TestFilesPath, "*.txt", SearchOption.AllDirectories);
            foreach (string file in files)
            {
                string signature = Path.GetFileNameWithoutExtension(file);
                cluster.CLUS_AddFile(file, signature);
            }
            // 打印结果
            if (cluster.CLUS_GetLatestResult(cluster.RootDir + "ClusterResultByFile.xml"))
            {
                Console.WriteLine("根据【文件】聚类结果已经保存到文件，请到项目根目录下查看");
            }
            
            cluster.CLUS_CleanData();

            /**
             * 根据文本内容聚类
             */
            cluster.CLUS_SetParameter(10, 20);
            String content = "周公恐惧流言日，王莽谦恭下士时。假使当年身便死，一生真伪有谁知。";
            for (int i = 0; i < 7; ++i)
            {
                cluster.CLUS_AddContent(content, "文章" + i);
            }
            // 打印结果
            if (cluster.CLUS_GetLatestResult(cluster.RootDir + "ClusterResultByContent.xml"))
            {
                Console.WriteLine("根据【内容】聚类结果已经保存到文件，请到项目根目录下查看");
            }

            cluster.CLUS_Exit();

            Console.WriteLine("结束");
            Console.WriteLine("按任意键继续...");
            Console.ReadKey(true);
        }
    }
}
