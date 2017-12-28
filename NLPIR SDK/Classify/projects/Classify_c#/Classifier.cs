using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Lingjoin.Global;

namespace Lingjoin.ClassifierTest
{
    public class Classifier : Lingjoin.Global.Base
    {
        public override string DllFileName
        {
            get { return "LJClassifier.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "classifier.user"; }
        }

        private delegate bool D_Classifier_Init(String sPathRulelist, string sInitDirPath);
        private delegate void D_Classifier_Exit();
        private delegate IntPtr D_Classifier_Exec(string sTitle, string sContent, int iType); //返回值是const char* 应替换为intptr
        private delegate IntPtr D_Classifier_Detail(string sClassName);

        private D_Classifier_Init d_Classifier_Init;
        private D_Classifier_Exit d_Classifier_Exit;
        private D_Classifier_Exec d_Classifier_Exec;
        private D_Classifier_Detail d_Classifier_Detail;

        protected override bool InitFunctions()
        {
            d_Classifier_Init = (D_Classifier_Init)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "classifier_init", typeof(D_Classifier_Init));

            d_Classifier_Exit = (D_Classifier_Exit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "classifier_exit", typeof(D_Classifier_Exit));

            d_Classifier_Exec = (D_Classifier_Exec)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "classifier_exec", typeof(D_Classifier_Exec));

            d_Classifier_Detail = (D_Classifier_Detail)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "classifier_detail", typeof(D_Classifier_Detail));

            if (d_Classifier_Init == null || d_Classifier_Exit == null
                || d_Classifier_Exec == null || d_Classifier_Detail == null)
            {
                return false;
            }

            return true;
        }

        public Classifier() : base() { }

        public Classifier(string dllDir, string authorizationDir) : base(dllDir, authorizationDir) { }

        /**
         * 文件方式初始化
         * @param conf 规则文件的路径
         * @param sInitDirPath Data文件夹的父路径
         * @return true:成功；false：失败  
         * 出错信息记录在硬盘的./ljclassifier.log和./DataFile/ljclassifier.log
         */
        public bool Classifier_Init(String sPathRulelist = "rulelist.xml", String sInitDirPath = "DataFile")
        {
            return d_Classifier_Init(sPathRulelist, sInitDirPath);
        }

        /// <summary>
        /// 功能：退出，释放资源
        /// </summary>
        public void Classifier_Exit()
        {
            d_Classifier_Exit();
        }

        /**
         * 对输入的文章结构进行分类
         * @param sTitle 文章的标题
         * @param sContent 文章的内容
         * @param iType 输出类名和置信度：
         *      	 	iType=0:  输出类名，各类之间用\t隔开  内容格式举例：“要闻	敏感	诉讼”       
         *       		iType=1:  输出类名和置信度，各类之间用\t隔开，类名和权重用“ ”隔开   内容格式举例：“要闻 1.00	敏感 0.95	诉讼 0.82”
         * @return 主题类别串  各类之间用\t隔开，类名按照置信度从高到低排序
         */
        public string Classifier_Exec(String sTitle, String sContent, int iType = 0)
        {
            // 返回的字符串指针需要由intptr转换成string
            string s = Marshal.PtrToStringAnsi(d_Classifier_Exec(sTitle, sContent, iType));
            return s.ToEncode("gbk", "utf-8");
        }

        /**
         * 对于当前文档，输入类名，取得结果明细
         * @param classname classname:结果类名
         * @return 结果明细 例如:
                   RULE3:
                   SUBRULE1: 内幕 1	
                   SUBRULE2: 股市 1	基金 3	股票 8	
                   SUBRULE3: 书摘 2	
         */
        public string Classifier_Detail(String sClassName)
        {
            // 返回的字符串指针需要由intptr转换成string
            return Marshal.PtrToStringAnsi(d_Classifier_Detail(sClassName));
        }

        public List<string> ClassifierDetailForClasses(String sClassNames)
        {
            List<string> results = new List<string>();

            string[] vsItems = sClassNames.Split(new char[] { '\t' }, StringSplitOptions.RemoveEmptyEntries);

            foreach (var item in vsItems)
            {
                string s = Classifier_Detail(item);
                results.Add(s);
            }

            return results;
        }
    }
}
