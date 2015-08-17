using System;
using System.Runtime.InteropServices;

namespace Lingjoin.DocExtractorTest
{
    public class DocExtractor : Lingjoin.Global.Base
    {
        public const int DOC_EXTRACT_TYPE_PERSON = 0;// 输出的人名
        public const int DOC_EXTRACT_TYPE_LOCATION = 1;// 输出的地名
        public const int DOC_EXTRACT_TYPE_ORGANIZATION = 2;// 输出的机构名
        public const int DOC_EXTRACT_TYPE_KEYWORD = 3;// 输出的关键词
        public const int DOC_EXTRACT_TYPE_AUTHOR = 4;// 输出的文章作者
        public const int DOC_EXTRACT_TYPE_MEDIA = 5;// 输出的媒体
        public const int DOC_EXTRACT_TYPE_COUNTRY = 6;// 输出的文章对应的所在国别
        public const int DOC_EXTRACT_TYPE_PROVINCE = 7;// 输出的文章对应的所在省份
        public const int DOC_EXTRACT_TYPE_ABSTRACT = 8;// 输出文章的摘要
        public const int DOC_EXTRACT_TYPE_POSITIVE = 9;// 输出文章的正面情感词为
        public const int DOC_EXTRACT_TYPE_NEGATIVE = 10;// 输出文章的副面情感词
        public const int DOC_EXTRACT_TYPE_DEL_HTML = 11;// 输出文章去除网页等标签后的正文
        public const int DOC_EXTRACT_TYPE_USER_DEFINED1 = 12;//用户自定义词1
        // .................................................................

        public const int PERSON_REQUIRED = 0x0001;
        public const int LOCATION_REQUIRED = 0x0002;
        public const int ORGANIZATION_REQUIRED = 0x0004;
        public const int KEYWORD_REQUIRED = 0x0008;
        public const int AUTHOR_REQUIRED = 0x0010;
        public const int MEDIA_REQUIRED = 0x0100;
        public const int COUNTRY_REQUIRED = 0x0200;
        public const int PROVINCE_REQUIRED = 0x0400;
        public const int ABSTRACT_REQUIRED = 0x0800;
        public const int TRANS_REQUIRED = 0x1000;
        public const int FOOD_REQUIRED = 0x2000;
        public const int APPS_REQUIRED = 0x4000;
        public const int SENTIMENT_REQUIRED = 0x8000;
        public const int ALL_REQUIRED = 0xffff;

        public override string DllFileName
        {
            get { return "DocExtractor.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "DocExtractor.user"; }
        }

        protected override bool InitFunctions()
        {
            d_DE_Init = (D_DE_Init)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_Init", typeof(D_DE_Init));

            d_DE_ParseDocE = (D_DE_ParseDocE)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_ParseDocE", typeof(D_DE_ParseDocE));

            d_DE_GetResult = (D_DE_GetResult)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_GetResult", typeof(D_DE_GetResult));

            d_DE_GetLastErrMsg = (D_DE_GetLastErrMsg)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_GetLastErrMsg", typeof(D_DE_GetLastErrMsg));

            d_DE_GetSentimentScore = (D_DE_GetSentimentScore)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_GetSentimentScore", typeof(D_DE_GetSentimentScore));

            d_DE_ReleaseHandle = (D_DE_ReleaseHandle)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_ReleaseHandle", typeof(D_DE_ReleaseHandle));

            d_DE_ImportSentimentDict = (D_DE_ImportSentimentDict)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_GetResult", typeof(D_DE_ImportSentimentDict));

            d_DE_ImportUserDict = (D_DE_ImportUserDict)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_ImportUserDict", typeof(D_DE_ImportUserDict));

            d_DE_ImportKeyBlackList = (D_DE_ImportKeyBlackList)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_ImportUserDict", typeof(D_DE_ImportKeyBlackList));

            d_DE_ComputeSentimentDoc = (D_DE_ComputeSentimentDoc)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_ComputeSentimentDoc", typeof(D_DE_ComputeSentimentDoc));

            d_DE_Exit = (D_DE_Exit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DE_Exit", typeof(D_DE_Exit));

            if (d_DE_Exit == null || d_DE_ComputeSentimentDoc == null
                || d_DE_ImportKeyBlackList == null || d_DE_ImportUserDict == null
                || d_DE_ImportSentimentDict == null || d_DE_ReleaseHandle == null
                || d_DE_GetSentimentScore == null || d_DE_GetLastErrMsg == null
                || d_DE_GetResult == null || d_DE_ParseDocE == null
                || d_DE_Init == null)
            {
                return false;
            }

            return true;
        }

        private delegate int D_DE_Init(String sPath, int nEncoding, String sLicenseCode);
        private delegate long D_DE_ParseDocE(String sText, String sUserDefPos, bool bSummaryNeeded, int nFuncRequired);
        private delegate IntPtr D_DE_GetResult(long handle, int nDocExtractType);
        private delegate int D_DE_GetSentimentScore(long handle);
        private delegate void D_DE_ReleaseHandle(long handle);
        private delegate int D_DE_ComputeSentimentDoc(String sText);
        private delegate bool D_DE_Exit();
        private delegate IntPtr D_DE_GetLastErrMsg();
        private delegate int D_DE_ImportSentimentDict(String sFilename);
        private delegate int D_DE_ImportUserDict(String sFilename);
        private delegate int D_DE_ImportKeyBlackList(String sFilename);

        private D_DE_Init d_DE_Init;
        private D_DE_ParseDocE d_DE_ParseDocE;
        private D_DE_GetResult d_DE_GetResult;
        private D_DE_GetSentimentScore d_DE_GetSentimentScore;
        private D_DE_ReleaseHandle d_DE_ReleaseHandle;
        private D_DE_ComputeSentimentDoc d_DE_ComputeSentimentDoc;
        private D_DE_Exit d_DE_Exit;
        private D_DE_GetLastErrMsg d_DE_GetLastErrMsg;
        private D_DE_ImportSentimentDict d_DE_ImportSentimentDict;
        private D_DE_ImportUserDict d_DE_ImportUserDict;
        private D_DE_ImportKeyBlackList d_DE_ImportKeyBlackList;



        public int DE_Init(String sPath, int nEncoding, String sLicenseCode)
        {
            return d_DE_Init(sPath, nEncoding, sLicenseCode);
        }

        /**
         * 进行文本提取
         * 
         * @param content
         *            :进行文本提取的内容
         * @param sUserDefPos
         *            :用户自定义或已有的三个标注，用#分割，如：a#v#adj
         * @param bSummaryNeeded
         *            ：是否需要摘要，默认为true
         * @param nFuncRequired
         *            ：需要提取的内容
         * @return: 句柄
         */
        public long DE_ParseDocE(String sText, String sUserDefPos, bool bSummaryNeeded, int nFuncRequired)
        {
            return d_DE_ParseDocE(sText, sUserDefPos, bSummaryNeeded, nFuncRequired);
        }
        /**
         * 获得结果
         * 
         * @param handle
         *            :DE_ParseDocE返回的handle标志
         * @param nDocExtractType
         *            ：实体抽取类型
         * @return：抽取结果
         */
        public String DE_GetResult(long handle, int nDocExtractType)
        {
            return Marshal.PtrToStringAnsi(d_DE_GetResult(handle, nDocExtractType));
        }

        /**
         * 
         * @param handle
         *            :DE_ParseDocE返回的handle标志
         * @return:情感分值
         */
        public int DE_GetSentimentScore(long handle)
        {
            return d_DE_GetSentimentScore(handle);
        }

        /**
         * 
         * @param handle
         *            :DE_ParseDocE返回的handle标志
         * @description:释放handle
         */
        public void DE_ReleaseHandle(long handle)
        {
            d_DE_ReleaseHandle(handle);
        }

        public int DE_ComputeSentimentDoc(String sText)
        {
            return d_DE_ComputeSentimentDoc(sText);
        }

        // 退出
        public bool DE_Exit()
        {
            return d_DE_Exit();
        }

        // 获得错误消息
        public String DE_GetLastErrMsg()
        {
            return Marshal.PtrToStringAnsi(d_DE_GetLastErrMsg());
        }

        // 导入用户情感词典
        public int DE_ImportSentimentDict(String sFilename)
        {
            return d_DE_ImportSentimentDict(sFilename);
        }

        // 导入用户词典
        public int DE_ImportUserDict(String sFilename)
        {
            return d_DE_ImportUserDict(sFilename);
        }

        // 导入关键词黑名单
        public int DE_ImportKeyBlackList(String sFilename)
        {
            return d_DE_ImportKeyBlackList(sFilename);
        }
    }
}
