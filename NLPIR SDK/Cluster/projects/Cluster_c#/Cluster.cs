using System;
using System.Runtime.InteropServices;
using Lingjoin.Global;

namespace Lingjoin.ClusterTest
{
    public class Cluster : Base
    {
        public override string DllFileName
        {
            get { return "LJCluster.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "cluster.user"; }
        }

        protected override bool InitFunctions()
        {
            d_CLUS_Init = (D_CLUS_Init)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "CLUS_Init", typeof(D_CLUS_Init));

            d_CLUS_SetParameter = (D_CLUS_SetParameter)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "CLUS_SetParameter", typeof(D_CLUS_SetParameter));

            d_CLUS_AddContent = (D_CLUS_AddContent)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "CLUS_AddContent", typeof(D_CLUS_AddContent));

            d_CLUS_AddFile = (D_CLUS_AddFile)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "CLUS_AddFile", typeof(D_CLUS_AddFile));

            d_CLUS_GetLatestResult = (D_CLUS_GetLatestResult)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "CLUS_GetLatestResult", typeof(D_CLUS_GetLatestResult));

            d_CLUS_CleanData = (D_CLUS_CleanData)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "CLUS_AddFile", typeof(D_CLUS_CleanData));

            d_CLUS_Exit = (D_CLUS_Exit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "CLUS_GetLatestResult", typeof(D_CLUS_Exit));

            d_CLUS_GetLastErrMsg = (D_CLUS_GetLastErrMsg)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "CLUS_Exit", typeof(D_CLUS_GetLastErrMsg));

            if (d_CLUS_Init == null || d_CLUS_SetParameter == null
                || d_CLUS_AddContent == null || d_CLUS_AddFile == null
                || d_CLUS_GetLatestResult == null || d_CLUS_CleanData == null
                || d_CLUS_Exit == null || d_CLUS_GetLastErrMsg == null)
            {
                return false;
            }

            return true;
        }


        private delegate bool D_CLUS_Init(String sDefaultPath, String sLicenseCode, int encode);
        private delegate bool D_CLUS_SetParameter(int nMaxClus, int nMaxDoc);
        private delegate bool D_CLUS_AddContent(String sText, String sSignature);
        private delegate bool D_CLUS_AddFile(String sFileName, String sSignature);
        private delegate bool D_CLUS_GetLatestResult(String sXmlFileName);
        private delegate void D_CLUS_CleanData();
        private delegate void D_CLUS_Exit();
        private delegate IntPtr D_CLUS_GetLastErrMsg();

        private D_CLUS_Init d_CLUS_Init;
        private D_CLUS_SetParameter d_CLUS_SetParameter;
        private D_CLUS_AddContent d_CLUS_AddContent;
        private D_CLUS_AddFile d_CLUS_AddFile;
        private D_CLUS_GetLatestResult d_CLUS_GetLatestResult;
        private D_CLUS_CleanData d_CLUS_CleanData;
        private D_CLUS_Exit d_CLUS_Exit;
        private D_CLUS_GetLastErrMsg d_CLUS_GetLastErrMsg;


        public Cluster() : base() { }

        public Cluster(string dllDir, string authorizationDir) : base(dllDir, authorizationDir) { }

        /**
         * 初始化
         * @param sDefaultPath Data文件夹的路径，置为空字符串时从项目根目录下寻找Data文件夹
         * @param sLicenseCode 授权码，置为空字符串就可以了
         * @param encode 文档编码格式，具体对照为：0：GBK；1：UTF8；2：BIG5；3：GBK（里面包含繁体字）
         * @return true - 成功；false - 失败
         */
        public bool CLUS_Init(String sDefaultPath, String sLicenseCode, int encode)
        {
            return d_CLUS_Init(sDefaultPath, sLicenseCode, encode);
        }

        /**
         * 功能：设置参数
         * @param nMaxClus 最多输出前多少个类
         * @param nMaxDoc 每个类最多输出前多少个文档
         * @return true - 成功；false - 失败
         *	备注：在进程中此函数必须在其他函数(除了初始化函数)之前调用
         *       如果不调用，参数默认均为2000； 参数越大，系统占用内存越大，处理速度越慢
         *       类和类内的文档均已按照重要性和及时性排过序
         */
        public bool CLUS_SetParameter(int nMaxClus, int nMaxDoc)
        {
            return d_CLUS_SetParameter(nMaxClus, nMaxDoc);
        }

        /**
         * 功能：追加内存内容
         * @param sText  正文内容
         * @param sSignature 唯一标识符
         * @return true - 成功；false - 失败
         * 备注：在进程中此函数可以在打印结果之前执行多次
         */
        public bool CLUS_AddContent(string sText, string sSignature)
        {
            return d_CLUS_AddContent(sText.ToEncode("utf-8", "GBK"), sSignature.ToEncode("utf-8", "GBK"));
        }

        /**
         * 功能：追加文件内容
         * @param sFileName 文件全路径名称
         * @param sSignature 唯一标识符
         * @return true - 成功；false - 失败
         * 备注：在进程中此函数可以在打印结果之前执行多次
         */
        public bool CLUS_AddFile(String sFileName, String sSignature)
        {
            return d_CLUS_AddFile(sFileName.ToEncode("utf-8", "GBK"), sSignature.ToEncode("utf-8", "GBK"));
        }

        /**
         * 打印结果
         * @param sXmlFileName 聚类内容输出到XML文件中
         * @return true - 成功；false - 失败
         */
        public bool CLUS_GetLatestResult(String sXmlFileName)
        {
            return d_CLUS_GetLatestResult(sXmlFileName);
        }

        /**
         * 清空历史数据
         */
        public void CLUS_CleanData()
        {
            d_CLUS_CleanData();
        }

        /**
         * 退出，释放资源；进程结束前须调用它释放所占用的内存资源
         */
        public void CLUS_Exit()
        {
            d_CLUS_Exit();
        }

        /**
         * 获得最后一次的错误消息
         * @return 最后一次的错误消息
         */
        public String CLUS_GetLastErrMsg()
        {
            // 返回的字符串指针需要由intptr转换成string
            return Marshal.PtrToStringAnsi(d_CLUS_GetLastErrMsg());
        }
    }
}
