using System;
using System.Configuration;
using System.IO;
using System.Text;
using System.Xml;
using Lingjoin.Global;
using Util.File;

namespace Lingjoin.JZSearchTest
{
    class Program
    {
        public const int INDEX_ENCODING_GBK = 0;
        public const int INDEX_ENCODING_UTF8 = 1;
        public const int INDEX_ENCODING_BIG5 = 2;
        public const int INDEX_ENCODING_GBK_FANTI = 3;//GBK中包含繁体字，统一兼容，推荐使用INDEX_ENCODING_GBK_FANTI
        public const int INDEX_ENCODING_COUNT = 4;

        public const int LANGUAGE_TYPE_UNKNOWN = 0;
        public const int LANGUAGE_TYPE_CHINESE = 1;
        public const int LANGUAGE_TYPE_UYGHAN = 2;

        public const int FIELD_TYPE_TEXT = 1;
        public const int FIELD_TYPE_INT = 2;
        public const int FIELD_TYPE_LONG = 3;
        public const int FIELD_TYPE_DATETIME = 4;
        public const int FIELD_TYPE_FLOAT = 5;
        public const int DATA_TYPE_BIGTEXT = 6;
        public const int FIELD_TYPE_NAME = 8;

        public const int SORT_TYPE_DOCID = 1;//按照Doc ID排序，默认方式
        public const int SORT_TYPE_RELEVANCE = 2;//按照相关度排序
        public const int SORT_TYPE_DOCID_REVERSE = 3;//按照Doc ID倒序排序，默认方式


        public static JZSearch search = new JZSearch();

        public const int ENCODING = INDEX_ENCODING_GBK; // 目前测试使用utf-8编码还有乱码的情况，原因还在排查
        public static string indexDir = search.RootDir + @"Index\";
        public static string indexPath = indexDir + "JZSearch";
        public static string fieldDir = search.RootDir + @"Field\";
        public static string fieldPath = fieldDir + @"field.dat";

        public static int searcherHandle = 0;

        private static void Main(string[] args)
        {
            while (true)
            {
                Console.WriteLine("建立字段，输入：0");
                Console.WriteLine("建立索引，输入：1");
                Console.WriteLine("搜索，输入：2");
                Console.WriteLine("列出所有索引内容：3");
                Console.WriteLine("退出，输入：其他");
                string input = Console.ReadLine();

                switch (input)
                {
                    case "0":
                    CreateField();
                    break;

                    case "1":
                    StartIndex();
                    break;

                    case "2":
                    Console.Write("请输入搜索内容：");
                    string keyword = Console.ReadLine();
                    StartSearch(keyword);
                    break;

                    case "3":
                    StartSearch();
                    break;

                    default:
                    if (searcherHandle != 0)
                    {
                        search.JZSearch_Exit(searcherHandle);
                    }
                    return;
                }
            }
        }

        public static void CreateField()
        {
            if (!Directory.Exists(fieldDir))
            {
                Directory.CreateDirectory(fieldDir);
            }
            else
            {
                DirectoryInfo di = new DirectoryInfo(fieldDir);
                try
                {
                    di.Delete(true);
                    Directory.CreateDirectory(fieldDir);
                }
                catch
                {
                    Console.WriteLine("清除旧字段失败");
                    return;
                }
            }

            // 初始化函数要保证全局只执行一次
            if (search.JZIndexer_Init(search.DataDir, "", ENCODING, true) == 0)
            {
                Console.WriteLine("索引初始化失败");
                return;
            }

            Console.WriteLine("索引初始化成功");
            search.JZIndexer_FieldAdd("key", "", FIELD_TYPE_TEXT, true, true, true, true);
            search.JZIndexer_FieldAdd("value", "", FIELD_TYPE_TEXT, true, true, true, true);

            if (search.JZIndexer_FieldSave(fieldPath))
            {
                Console.WriteLine("字段构建完毕");
            }
            else
            {
                Console.WriteLine("字段构建失败");
            }
            search.JZIndexer_Exit();
            Console.WriteLine("");
        }

        public static void StartIndex()
        {
            if (!Directory.Exists(indexDir))
            {
                Directory.CreateDirectory(indexDir);
            }
            else
            {
                DirectoryInfo di = new DirectoryInfo(indexDir);
                try
                {
                    di.Delete(true);
                    Directory.CreateDirectory(indexDir);
                }
                catch
                {
                    Console.WriteLine("清除旧索引失败");
                    return;
                }
            }

            // 2、添加新的索引文件
            int flag = search.JZIndexer_Init(search.DataDir, fieldPath, ENCODING, true); // 初始化函数要保证全局只执行一次
            if (flag == 0)
            {
                Console.WriteLine("JZIndexer_Init初始化失败");

            }
            Console.WriteLine("JZIndexer_Init初始化成功");

            int handle = search.JZIndexer_NewInstance(indexPath, 512000000);
            if (handle < 0)
            {
                Console.WriteLine("JZIndexer_NewInstance生成实例失败");
                return;
            }
            Console.WriteLine("JZIndexer_NewInstance生成实例成功");

            string testFilesPath = search.RootDir + @"test\";
            string[] files = Directory.GetFiles(testFilesPath, "*.*", SearchOption.AllDirectories);

            search.JZSearch_SetIndexSizeLimit(-1);             // 建索引前调用该方法
            foreach (var file in files)
            {
                FileInfo fi = new FileInfo(file);

                string sContext = FileHelper.ReadFile(file);
                switch (fi.Extension.ToLower())
                {
                    case ".xml":
                    {
                        try
                        {
                            sContext = GetXmlContent(sContext);
                        }
                        catch
                        {
                            Console.WriteLine("解析{0}文件失败，格式为{1}", fi.Name, fi.Extension.ToLower());
                        }
                        break;
                    }
                    default:
                    break;
                }
//              search.JZSearch_SetIndexSizeLimit();             // 建索引前调用该方法
                search.JZIndexer_MemIndexing(handle, fi.Name, "key", 0);
//                 int contentLength = Encoding.GetEncoding("gbk").GetByteCount(sContext);
//                 search.JZSearch_SetIndexSizeLimit(contentLength);             // 建索引前调用该方法
                search.JZIndexer_MemIndexing(handle, sContext, "value", 0);
                
                // search.JZIndexer_FileIndexing(handle, file, "value");

                if (search.JZIndexer_AddDoc(handle) < 1)
                {
                    Console.WriteLine(fi.Name + " : 索引添加失败！");
                    return;
                }
                Console.WriteLine(fi.Name + " : 索引添加成功！");
            }

            search.JZIndexer_Save(handle);
            search.JZIndexer_DeleteInstance(handle);
            search.JZIndexer_Exit();
            Console.WriteLine("索引建立完成");
        }

        public static void StartSearch(string keyword = null)
        {
            if (searcherHandle <= 0)
            {
                // 初始化函数要保证全局只执行一次
                searcherHandle = search.JZSearch_Init(indexPath, search.DataDir, fieldPath, 512000000, ENCODING, 0, true);
                if (searcherHandle < 0)
                {
                    return;
                }
            }

            int handle = search.JZSearcher_NewInstance(1, searcherHandle);
            if (handle < 0)
            {
                Console.WriteLine("JZSearcher_NewInstance生成实例失败！！！！");
                return;
            }
            Console.WriteLine("JZSearcher_NewInstance生成实例成功");

            search.JZSearch_SetAbstractArgu(1000, "", "", 0);

            string query = "[cmd] listall";
            if (!string.IsNullOrWhiteSpace(keyword))
            {
                Console.WriteLine("开始以关键字“{0}”进行搜索", keyword);
                query = string.Format("[FIELD] * [OR] {0} [SORT] {1}", keyword, "relevance");
            }

            String xml = search.JZSearcher_Search(handle, query, 0, 10);
            Console.WriteLine(xml);
            search.JZSearcher_DeleteInstance(handle);
        }

        private static void ReadXml(XmlNodeList xmlnl, StringBuilder sb)
        {
            foreach (XmlNode xl in xmlnl)
            {
                if (xl.ChildNodes.Count == 0)
                {
                    if (xl.NodeType == XmlNodeType.XmlDeclaration)
                    {
                        continue;
                    }
                    if (!string.IsNullOrWhiteSpace(xl.InnerText))
                    {
                        sb.Append(xl.InnerText);
                        sb.Append(" ");
                    }
                }
                else
                {
                    ReadXml(xl.ChildNodes, sb);
                }
            }
        }

        private static string GetXmlContent(string xml)
        {
            XmlDocument doc = new XmlDocument();
            doc.LoadXml(xml);
            StringBuilder sb = new StringBuilder();
            ReadXml(doc.ChildNodes, sb);
            return sb.ToString();
        }
    }
}
