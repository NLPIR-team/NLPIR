using System;

namespace Lingjoin.SentimentAnalysisTest
{
    public class SentimentAnalysis : Lingjoin.Global.Base
    {
        public override string DllFileName
        {
            get { return "LJSentimentAnalysis.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "sentiment.user"; }
        }

        protected override bool InitFunctions()
        {
            d_LJST_Inits = (D_LJST_Inits)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "LJST_Inits", typeof(D_LJST_Inits));

            d_LJST_ImportUserDict = (D_LJST_ImportUserDict)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "LJST_ImportUserDict", typeof(D_LJST_ImportUserDict));

            d_LJST_GetFileSent = (D_LJST_GetFileSent)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "LJST_GetFileSent", typeof(D_LJST_GetFileSent));

            d_LJST_GetParagraphSent = (D_LJST_GetParagraphSent)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "LJST_GetParagraphSent", typeof(D_LJST_GetParagraphSent));

            d_LJST_Exits = (D_LJST_Exits)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "LJST_Exits", typeof(D_LJST_Exits));

            if (d_LJST_Inits == null || d_LJST_ImportUserDict == null
                || d_LJST_GetFileSent == null || d_LJST_GetParagraphSent == null
                || d_LJST_Exits == null)
            {
                return false;
            }

            return true;
        }

        private delegate int D_LJST_Inits(String path, int encode, String sLicenceCode);
        private delegate int D_LJST_ImportUserDict(String dicPath, bool overwriter);
        private delegate bool D_LJST_GetFileSent(String lpszFilename, byte[] szRes);
        private delegate bool D_LJST_GetParagraphSent(String lpszParagraph, byte[] szRes);
        private delegate void D_LJST_Exits();

        private D_LJST_Inits d_LJST_Inits;
        private D_LJST_ImportUserDict d_LJST_ImportUserDict;
        private D_LJST_GetFileSent d_LJST_GetFileSent;
        private D_LJST_GetParagraphSent d_LJST_GetParagraphSent;
        private D_LJST_Exits d_LJST_Exits;

        public int LJST_Inits(String path, int encode, String sLicenceCode)
        {
            return d_LJST_Inits(path, encode, sLicenceCode);
        }

        public int LJST_ImportUserDict(String dicPath, bool overwriter)
        {
            return d_LJST_ImportUserDict(dicPath, overwriter);
        }
        public bool LJST_GetFileSent(String lpszFilename, byte[] szRes)
        {
            return d_LJST_GetFileSent(lpszFilename, szRes);
        }
        public bool LJST_GetParagraphSent(String lpszParagraph, byte[] szRes)
        {
            return d_LJST_GetParagraphSent(lpszParagraph, szRes);
        }
        public void LJST_Exits()
        {
            d_LJST_Exits();
        }
    }
}
