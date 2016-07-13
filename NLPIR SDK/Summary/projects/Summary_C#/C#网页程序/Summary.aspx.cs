using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using System.Runtime.InteropServices;
using System.Text.RegularExpressions;




    public  partial class Summary : System.Web.UI.Page
    {
        //引用  lib\win64\KeyExtract.dll    以具体存放路径为准
        //const string path = @"../lib/LJSummary.dll";//设定dll的路径
        const string path = @"D:\NLPIR\bin\Summary\LJSummary.dll";

        //对函数进行声明  C++原函数    DS_Init(const char *sPath=0,int nEncoding=GBK_CODE,const char *sLicenseCode=0);    初始化，仅运行一次
        [DllImport(path, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, EntryPoint = "DS_Init")]
        public static extern bool DS_Init(string sPath, int nEncoding, string sLicenseCode);

        //对函数进行声明  C++原函数    const char* DS_SingleDoc(const char *sText, float fSumRate=0.00, int iSumLen=250,int bHtmlTagRemove=0);
        /*-----------------------------------------------------------------------
        * 功能：生成单文档摘要
        * 参数：sText	    -[IN] 文档内容
        *		fSumRate	-[IN] 文档摘要占原文百分比（为0.00则不限制）
        *		iSumLen		-[IN] 用户限定的摘要长度  （为0则不限制）
        *		bHtmlTagRemove-[IN] 是否需要对原文进行Html标签的去除
        * 返回：摘要字符串；出错返回空串
        * 备注：在进程中此函数可以执行多次
        ------------------------------------------------------------------------*/
        [DllImport(path, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, EntryPoint = "DS_SingleDoc")]
        public static extern IntPtr DS_SingleDoc(string sText, float fSumRate = (float) 0.00, int iSumLen = 250, int bHtmlTagRemove = 0);

        //对函数进行声明  C++原函数    const char* DS_SingleDocE(char *sResult,const char *sText, float fSumRate=0.00, int iSumLen=250,int bHtmlTagRemove=0);
        /*-----------------------------------------------------------------------
        * 功能：生成单文档摘要该函数支持多线程，是多线程安全的
        * 参数：sResult    -[IN] 摘要内容
        *		sText	    -[IN] 文档内容
        *		fSumRate	-[IN] 文档摘要占原文百分比（为0.00则不限制）
        *		iSumLen		-[IN] 用户限定的摘要长度  （为0则不限制）
        *		bHtmlTagRemove-[IN] 是否需要对原文进行Html标签的去除
        * 返回：摘要字符串；出错返回空串
        * 备注：在进程中此函数可以执行多次
        ------------------------------------------------------------------------*/
        [DllImport(path, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, EntryPoint = "DS_SingleDocE")]
        public static extern string DS_SingleDocE(string sResult, string sText, float fSumRate = (float)0.00, int iSumLen = 250, int bHtmlTagRemove = 0);

        //对函数进行声明  C++原函数    const char* DS_FileProcess(const char *sTextFilename, float fSumRate=0.00, int iSumLen=250,int bHtmlTagRemove=0);
        /*-----------------------------------------------------------------------
        * 功能：生成单文档摘要该函数支持多线程，是多线程安全的
        * 参数：sTextFilename	    -[IN] 文档文件名
        *		fSumRate	-[IN] 文档摘要占原文百分比（为0.00则不限制）
        *		iSumLen		-[IN] 用户限定的摘要长度  （为0则不限制）
        *		bHtmlTagRemove-[IN] 是否需要对原文进行Html标签的去除
        * 返回：摘要字符串；出错返回空串
        * 备注：在进程中此函数可以执行多次
        ------------------------------------------------------------------------*/
        [DllImport(path, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, EntryPoint = "DS_FileProcess")]
        public static extern string DS_FileProcess(string sTextFilename, float fSumRate = (float)0.00, int iSumLen = 250, int bHtmlTagRemove = 0);

        //对函数进行声明  C++原函数    void DS_Exit();
        //退出，释放资源；进程结束前须调用它释放所占用的内存资源
        [DllImport(path, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, EntryPoint = "DS_Exit")]
        public static extern void DS_Exit();

        //对函数进行声明  C++原函数    const char* DS_GetLastErrMsg();
        //获得错误消息
        [DllImport(path, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl, EntryPoint = "DS_GetLastErrMsg")]
        public static extern string DS_GetLastErrMsg();



        protected void Page_Load(object sender, EventArgs e)
        {
            //string dataPath = AppDomain.CurrentDomain.SetupInformation.ApplicationBase;
            //C:\work\NLPIR\NLPIR SDK\Summary
            if (!DS_Init(@"D:\NLPIR", 1, ""))//数据在上一层目录下，默认为GBK编码的分词
            {
                Response.Write("自动摘要初始化失败！");
                return;
            }

            string str = "";
             try 
            {/*
                IntPtr intPtr = DS_SingleDoc(@"
对于有的粉丝，我真的无语了！大家都为姚贝娜感到惋惜，都觉得太可惜了。但有歌迷的观点真的让人无语，说什么:吴奇隆在姚贝娜追悼会的时候结婚，这样好吗？首先吴刘跟姚的不幸有半毛钱关系啊;其次难道说姚的不幸，全中国有人结婚都得为这事让行？
", (float)0.50, 100, 0);
                String str = Marshal.PtrToStringAnsi(intPtr);//将切分结果转换为string
                Console.WriteLine(str);*/
                IntPtr intPtr =                 DS_SingleDoc(@"
对于有的粉丝，我真的无语了！大家都为姚贝娜感到惋惜，都觉得太可惜了。但有歌迷的观点真的让人无语，说什么:吴奇隆在姚贝娜追悼会的时候结婚，这样好吗？首先吴刘跟姚的不幸有半毛钱关系啊;其次难道说姚的不幸，全中国有人结婚都得为这事让行？
", (float)0.50, 100, 0);
                string strSum = Marshal.PtrToStringAnsi(intPtr);//将切分结果转换为string
                Response.Write(strSum);
               // strSum = DS_GetLastErrMsg();
                //Response.Write(strSum);
               
            }
             catch (Exception ea)
             {
                 //Console.WriteLine(e.Message);
                 Response.Write(ea.Message);
                 //Message返回异常对象中包含的错误信息 
             } 
                //
             Response.Write(str);
               // string a = str;
             DS_Exit();
            
        }

        
        
    }
