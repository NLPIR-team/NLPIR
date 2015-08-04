using System;
using System.Runtime.InteropServices;

namespace Lingjoin.SentimentTest
{
    public class Sentiment : Lingjoin.Global.Base
    {
        public override string DllFileName
        {
            get { return "LJSentiment.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "sentiment.user"; }
        }

        protected override bool InitFunctions()
        {
            d_ST_Init = (D_ST_Init)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "ST_Init", typeof(D_ST_Init));

            d_ST_GetOneObjectResult = (D_ST_GetOneObjectResult)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "ST_GetOneObjectResult", typeof(D_ST_GetOneObjectResult));

            d_ST_GetMultiObjectResult = (D_ST_GetMultiObjectResult)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "ST_GetMultiObjectResult", typeof(D_ST_GetMultiObjectResult));

            d_ST_GetLastErrMsg = (D_ST_GetLastErrMsg)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "ST_GetLastErrMsg", typeof(D_ST_GetLastErrMsg));

            d_ST_Exit = (D_ST_Exit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "ST_Exit", typeof(D_ST_Exit));

            d_ST_SentiDictIO = (D_ST_SentiDictIO)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "ST_SentiDictIO", typeof(D_ST_SentiDictIO));

            if (d_ST_Init == null || d_ST_GetOneObjectResult == null
                || d_ST_GetMultiObjectResult == null || d_ST_GetLastErrMsg == null
                || d_ST_Exit == null || d_ST_SentiDictIO == null)
            {
                return false;
            }

            return true;
        }

        private delegate bool D_ST_Init(String sInitDirPath, int encode, String sLicenseCode);
        private delegate IntPtr D_ST_GetOneObjectResult(String sTitle, String sContent, String sObject);
        private delegate IntPtr D_ST_GetMultiObjectResult(String sTitle, String sContent, String sObjectRuleFile);
        private delegate void D_ST_Exit();
        private delegate IntPtr D_ST_GetLastErrMsg();
        private delegate int D_ST_SentiDictIO(String sPositiveFile, String sNegativeFile, bool bInputOutput);

        private D_ST_Init d_ST_Init;
        private D_ST_GetOneObjectResult d_ST_GetOneObjectResult;
        private D_ST_GetMultiObjectResult d_ST_GetMultiObjectResult;
        private D_ST_Exit d_ST_Exit;
        private D_ST_GetLastErrMsg d_ST_GetLastErrMsg;
        private D_ST_SentiDictIO d_ST_SentiDictIO;

        public Sentiment(params string[] otherDllNames) : base(otherDllNames) { }

        public bool ST_Init(String sInitDirPath, int encode, String sLicenseCode)
        {
            return d_ST_Init(sInitDirPath, encode, sLicenseCode);
        }

        public String ST_GetOneObjectResult(String sTitle, String sContent, String sObject)
        {
            return Marshal.PtrToStringAnsi(d_ST_GetOneObjectResult(sTitle, sContent, sObject));
        }

        public String ST_GetMultiObjectResult(String sTitle, String sContent, String sObjectRuleFile)
        {
            return Marshal.PtrToStringAnsi(d_ST_GetMultiObjectResult(sTitle, sContent, sObjectRuleFile));
        }

        public void ST_Exit()
        {
            d_ST_Exit();
        }

        public String ST_GetLastErrMsg()
        {
            return Marshal.PtrToStringAnsi(d_ST_GetLastErrMsg());
        }

        /**
         * 功能：批量导入导出情感词典
         * @param sPositiveFile 积极词典文件名；
         * @param sNegativeFile 消极词典文件名
         * @param bInputOutput true: 导入词典到系统中； false:导出系统词典到文本文件
         * @return int: 1:成功；0:失败
         */
        public int ST_SentiDictIO(String sPositiveFile, String sNegativeFile, bool bInputOutput)
        {
            return d_ST_SentiDictIO(sPositiveFile, sNegativeFile, bInputOutput);
        }
    }
}
