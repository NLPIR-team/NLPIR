using System;
using System.Runtime.InteropServices;

namespace Lingjoin.SummaryTest
{
    public class Summary : Lingjoin.Global.Base
    {

        public override string DllFileName
        {
            get { return "LJSummary.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "summary.user"; }
        }

        private delegate bool D_DS_Init(String sPath, int nEncoding, String sLicenseCode);
        private delegate IntPtr D_DS_SingleDoc(String sText, float fSumRate, int iSumLen, bool bHtmlTagRemove);
        private delegate void D_DS_Exit();
        private delegate IntPtr D_DS_GetLastErrMsg();

        private D_DS_Init d_DS_Init;
        private D_DS_SingleDoc d_DS_SingleDoc;
        private D_DS_Exit d_DS_Exit;
        private D_DS_GetLastErrMsg d_DS_GetLastErrMsg;


        protected override bool InitFunctions()
        {
            d_DS_Init = (D_DS_Init)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DS_Init", typeof(D_DS_Init));

            d_DS_SingleDoc = (D_DS_SingleDoc)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DS_SingleDoc", typeof(D_DS_SingleDoc));

            d_DS_Exit = (D_DS_Exit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DS_Exit", typeof(D_DS_Exit));

            d_DS_GetLastErrMsg = (D_DS_GetLastErrMsg)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DS_GetLastErrMsg", typeof(D_DS_GetLastErrMsg));

            if (d_DS_Init == null || d_DS_SingleDoc == null
                || d_DS_Exit == null || d_DS_GetLastErrMsg == null)
            {
                return false;
            }

            return true;
        }

        /**
         * 功能：初始化
         * @param sPath Data目录的父目录，可以直接传入""来表示寻找项目下的Data目录
         * @param nEncoding 设置分词编码，只能处理相应初始编码的文件.默认为GBK。
         *            0：GBK；1：UTF-8;2:BIG5;3:GBK_FANTI
         * @param sLicenseCode  授权码，这里直接用"0"，就可以了
         * @return true - 成功；false - 失败
         * 备注：在进程中此函数必须在其他函数之前调用（只需执行一次）
         */
        public bool DS_Init(String sPath, int nEncoding, String sLicenseCode)
        {
            return d_DS_Init(sPath, nEncoding, sLicenseCode);
        }


        /**
         * 功能：生成单文档摘要
         * @param sText 文档内容
         * @param fSumRate 文档摘要占原文百分比,该值最大不能超过1.00
         * @param iSumLen 用户限定的摘要长度  
         * @param bHtmlTagRemove-[IN] 是否需要对原文进行Html标签的去除
         * @return
         * 备注：fSumRate和iSumLen这个两个参数设置一个就可以了，例如：
         * 		DS_SingleDoc(sText, 0.00f, 80);
         * 		DS_SingleDoc(sText, 0.50f, 0);
         */
        public String DS_SingleDoc(String sText, float fSumRate, int iSumLen, bool bHtmlTagRemove)
        {
            return Marshal.PtrToStringAnsi(d_DS_SingleDoc(sText, fSumRate, iSumLen, bHtmlTagRemove));
        }

        /**
         * 退出，释放资源；进程结束前须调用它释放所占用的内存资源
         * 备注：如果需要频繁的生成摘要，那么不要调用这个方法
         */
        public void DS_Exit()
        {
            d_DS_Exit();
        }

        /**
         * 获得错误消息
         * @return 错误消息
         * 备注：如果初始化失败，可以用该方法输出初始化失败原因
         */
        public String DS_GetLastErrMsg()
        {
            return Marshal.PtrToStringAnsi(d_DS_GetLastErrMsg());
        }

    }
}
