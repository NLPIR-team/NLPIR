using System;
using System.Runtime.InteropServices;
using Lingjoin.Global;

namespace Lingjoin.KeyExtractTest
{
    public class KeyExtract : Lingjoin.Global.Base
    {
        public override string DllFileName
        {
            get { return "KeyExtract.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "keyExtract.user"; }
        }

        protected override bool InitFunctions()
        {
            d_KeyExtract_Init = (D_KeyExtract_Init)DllWrapper.GetFunctionAddress(
                 DllWrapper.hModule, "KeyExtract_Init", typeof(D_KeyExtract_Init));

            d_KeyExtract_GetKeyWords = (D_KeyExtract_GetKeyWords)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "KeyExtract_GetKeyWords", typeof(D_KeyExtract_GetKeyWords));

            d_KeyExtract_Exit = (D_KeyExtract_Exit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "KeyExtract_Exit", typeof(D_KeyExtract_Exit));

            d_KeyExtract_GetFileKeyWords = (D_KeyExtract_GetFileKeyWords)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "KeyExtract_GetFileKeyWords", typeof(D_KeyExtract_GetFileKeyWords));

            if (d_KeyExtract_Init == null || d_KeyExtract_GetKeyWords == null
                || d_KeyExtract_Exit == null || d_KeyExtract_GetFileKeyWords == null)
            {
                return false;
            }

            return true;
        }


        private delegate bool D_KeyExtract_Init(String sDataPath, int encode, String sLicenceCode);
        private delegate bool D_KeyExtract_Exit();
        private delegate IntPtr D_KeyExtract_GetKeyWords(String sLine, int nMaxKeyLimit, bool bWeightOut);
        private delegate IntPtr D_KeyExtract_GetFileKeyWords(String sFilename, int nMaxKeyLimit, bool bWeightOut);

        private D_KeyExtract_Init d_KeyExtract_Init;
        private D_KeyExtract_Exit d_KeyExtract_Exit;
        private D_KeyExtract_GetKeyWords d_KeyExtract_GetKeyWords;
        private D_KeyExtract_GetFileKeyWords d_KeyExtract_GetFileKeyWords;


        public bool KeyExtract_Init(String sDataPath, int encode, String sLicenceCode)
        {
            return d_KeyExtract_Init(sDataPath, encode, sLicenceCode);
        }

        public bool KeyExtract_Exit()
        {
            return d_KeyExtract_Exit();
        }

        public String KeyExtract_GetKeyWords(String sLine, int nMaxKeyLimit, bool bWeightOut)
        {
            return Marshal.PtrToStringAnsi(d_KeyExtract_GetKeyWords(sLine, nMaxKeyLimit, bWeightOut));
        }

        public String KeyExtract_GetFileKeyWords(String sFilename, int nMaxKeyLimit, bool bWeightOut)
        {
            return Marshal.PtrToStringAnsi(d_KeyExtract_GetFileKeyWords(sFilename, nMaxKeyLimit, bWeightOut));
        }

    }
}
