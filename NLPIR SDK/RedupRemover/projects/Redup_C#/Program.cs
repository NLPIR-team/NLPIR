using System;
using System.IO;
using System.Text;

namespace Lingjoin.RedupTest
{
    public static class Program
    {
        [STAThread]
        static void Main(string[] args)
        {
            Redup redup = new Redup();
            if (!redup.RR_Init(redup.RootDir + "History.Data", redup.RootDir, false, "", 0))
            {
                Console.WriteLine("初始化失败！");
                Console.WriteLine("按任意键继续...");
                Console.ReadKey(true);
                return;
            }

            Console.WriteLine("去重开始：");

            string testFilesPath = redup.RootDir + @"Test\";
            string[] files = Directory.GetFiles(testFilesPath, "*.txt", SearchOption.AllDirectories);

            FileStream fs = null;
            StreamReader sr = null;
            string fileName = "";
            StringBuilder pcFindAll = new StringBuilder();
            int iFileNum = files.Length;
            for (int i = 0; i < iFileNum; ++i)
            {
                fs = new FileStream(files[i], FileMode.Open, FileAccess.Read);
                sr = new StreamReader(fs);
                fileName = Path.GetFileName(files[i]);
                string sContext = sr.ReadToEnd();
                if (redup.RR_FileProcess(sContext, fileName) == 1)
                {
                    redup.RR_FindRepeat(pcFindAll, true);
                    Console.WriteLine("当前文件{0}和已有文件{1}重复",fileName, pcFindAll);
                }
                else
                {
                    Console.WriteLine("当前文件{0}未发现重复", fileName);
                }
            }

            if (sr != null)
            {
                sr.Close();
            }
            if (fs != null)
            {
                fs.Close();
            }

            redup.RR_SaveHistoryData(redup.RootDir + "History.Data");
            if (redup.RR_Output(redup.RootDir + "RepeatFile.txt"))
            {
                Console.WriteLine("\n处理结果已经保存文件\n");
            }
            
            redup.RR_Exit();

            Console.WriteLine("结束");
            Console.WriteLine("按任意键继续...");
            Console.ReadKey(true);
        }
    }
}
