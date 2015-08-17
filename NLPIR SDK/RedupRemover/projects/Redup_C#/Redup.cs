using System;
using System.Runtime.InteropServices;
using System.Text;
using Lingjoin.Global;

namespace Lingjoin.RedupTest
{
    public class Redup : Base
    {
        public override string DllFileName
        {
            get { return "LJRedupRemover.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "LJRedupRemover.user"; }
        }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_RR_Init(String sHistoryDataFile, String sInitDirPath, bool bHistoryLoad, String sLicenseCode, int encode);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_RR_FileProcess(String fileContent, String sID);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_RR_FindRepeat(StringBuilder ReturnString, bool bAllOutput);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_RR_Output(String sHistoryDataFile);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_RR_SaveHistoryData(String DataFilePath);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate void D_RR_Exit();
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate IntPtr D_RR_GetLastErrMsg();

        private D_RR_Init d_RR_Init;
        private D_RR_FileProcess d_RR_FileProcess;
        private D_RR_FindRepeat d_RR_FindRepeat;
        private D_RR_Output d_RR_Output;
        private D_RR_SaveHistoryData d_RR_SaveHistoryData;
        private D_RR_Exit d_RR_Exit;
        private D_RR_GetLastErrMsg d_RR_GetLastErrMsg;

        public Redup() : base() { }

        public Redup(string dllDir, string authorizationDir) : base(dllDir, authorizationDir) { }

        protected override bool InitFunctions()
        {

            d_RR_Init = (D_RR_Init)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "RR_Init", typeof(D_RR_Init));

            d_RR_FileProcess = (D_RR_FileProcess)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "RR_FileProcess", typeof(D_RR_FileProcess));

            d_RR_FindRepeat = (D_RR_FindRepeat)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "RR_FindRepeat", typeof(D_RR_FindRepeat));

            d_RR_Output = (D_RR_Output)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "RR_Output", typeof(D_RR_Output));

            d_RR_SaveHistoryData = (D_RR_SaveHistoryData)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "RR_SaveHistoryData", typeof(D_RR_SaveHistoryData));

            d_RR_Exit = (D_RR_Exit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "RR_Exit", typeof(D_RR_Exit));

            d_RR_GetLastErrMsg = (D_RR_GetLastErrMsg)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "RR_GetLastErrMsg", typeof(D_RR_GetLastErrMsg));

            if (d_RR_Init == null || d_RR_FileProcess == null || d_RR_FindRepeat == null
                || d_RR_Output == null || d_RR_SaveHistoryData == null || d_RR_Exit == null)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        /**
         * 初始化,并装载已有的查重数据
         * @param sHistoryDataFile
         * @param sInitDirPath
         * @param bHistoryLoad
         * @param sLicenseCode
         * @return
         */
        public bool RR_Init(String sHistoryDataFile, String sInitDirPath, bool bHistoryLoad, String sLicenseCode, int encode)
        {
            return d_RR_Init(sHistoryDataFile, sInitDirPath, bHistoryLoad, sLicenseCode, encode);
        }


        /// <summary>
        /// 处理文档
        /// </summary>
        /// <param name="fileContent">文本内容</param>
        /// <param name="sID">能够唯一标识该文本的字符串（比如：可以是文本的标题）</param>
        /// <returns>返回1说明该文档是重复的，否则是不重复的</returns>
        public int RR_FileProcess(String fileContent, String sID)
        {
            return d_RR_FileProcess(fileContent, sID);
        }

        /// <summary>
        /// 处理发现的重复文档。该方法在RR_FileProcess的返回值是1时可以调用
        /// </summary>
        /// <param name="ReturnString">返回结果</param>
        /// <param name="bAllOutput">返回所有重复的文件；false：只返回当前文件</param>
        /// <returns></returns>
        public bool RR_FindRepeat(StringBuilder ReturnString, bool bAllOutput)
        {
            return d_RR_FindRepeat(ReturnString, bAllOutput);
        }

        /**
         * 保存重复文件信息
         * @param sHistoryDataFile
         * @return
         */
        public bool RR_Output(String sHistoryDataFile)
        {
            return d_RR_Output(sHistoryDataFile);
        }

        /**
         * 保存查重数据
         * @param DataFilePath
         * @return
         */
        public bool RR_SaveHistoryData(String DataFilePath)
        {
            return d_RR_SaveHistoryData(DataFilePath);
        }

        /**
         * 退出
         */
        public void RR_Exit()
        {
            d_RR_Exit();
        }

        /**
         * 获得最后一次错误信息
         * @return
         */
        public String RR_GetLastErrMsg()
        {
            return Marshal.PtrToStringAnsi(d_RR_GetLastErrMsg());
        }
    }
}
