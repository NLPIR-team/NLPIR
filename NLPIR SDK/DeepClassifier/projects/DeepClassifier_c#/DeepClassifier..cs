using System;
using System.Runtime.InteropServices;

namespace Lingjoin.ClassifierTest
{
    public class DeepClassifier : Lingjoin.Global.Base
    {
        public override string DllFileName
        {
            get { return "DeepClassifier.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "DeepClassifier.user"; }
        }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_DC_Init(string sDataPath, int encode, int nFeatureCount, string sLicenceCode);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_DC_Exit();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_DC_AddTrain(string sClassName, string sText);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_DC_AddTrainFile(string sClassName, string sFilePath);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_DC_Train();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_DC_LoadTrainResult();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate IntPtr D_DC_Classify(string sText);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate IntPtr D_DC_ClassifyFile(string sFilename);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate IntPtr D_DC_GetLastErrorMsg();

        private D_DC_Init d_DC_Init;
        private D_DC_Exit d_DC_Exit;
        private D_DC_AddTrain d_DC_AddTrain;
        private D_DC_AddTrainFile d_DC_AddTrainFile;
        private D_DC_Train d_DC_Train;
        private D_DC_LoadTrainResult d_DC_LoadTrainResult;
        private D_DC_Classify d_DC_Classify;
        private D_DC_ClassifyFile d_DC_ClassifyFile;
        private D_DC_GetLastErrorMsg d_DC_GetLastErrorMsg;

        public DeepClassifier() : base() { }

        public DeepClassifier(string dllDir, string authorizationDir) : base(dllDir, authorizationDir) { }

        public bool DC_Init(string sDataPath = "", int encode = 0, int nFeatureCount = 800, string sLicenceCode = "")
        {
            return d_DC_Init(sDataPath, encode, nFeatureCount, sLicenceCode);
        }

        public bool DC_Exit()
        {
            return d_DC_Exit();
        }

        public bool DC_AddTrain(string sClassName, string sText)
        {
            return d_DC_AddTrain(sClassName, sText);
        }

        public bool DC_AddTrainFile(string sClassName, string sFilePath)
        {
            return d_DC_AddTrainFile(sClassName, sFilePath);
        }

        public bool DC_Train()
        {
            return d_DC_Train();
        }

        public bool DC_LoadTrainResult()
        {
            return d_DC_LoadTrainResult();
        }

        public string DC_Classify(string sText)
        {
            return Marshal.PtrToStringAnsi(d_DC_Classify(sText));
        }

        public string DC_ClassifyFile(string sFilename)
        {
            return Marshal.PtrToStringAnsi(d_DC_ClassifyFile(sFilename));
        }

        public string DC_GetLastErrorMsg()
        {
            return Marshal.PtrToStringAnsi(d_DC_GetLastErrorMsg());
        }

        protected override bool InitFunctions()
        {
            d_DC_Init = (D_DC_Init)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DC_Init", typeof(D_DC_Init));

            d_DC_Exit = (D_DC_Exit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DC_Exit", typeof(D_DC_Exit));

            d_DC_AddTrain = (D_DC_AddTrain)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DC_AddTrain", typeof(D_DC_AddTrain));

            d_DC_AddTrainFile = (D_DC_AddTrainFile)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DC_AddTrainFile", typeof(D_DC_AddTrainFile));

            d_DC_Train = (D_DC_Train)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DC_Train", typeof(D_DC_Train));

            d_DC_LoadTrainResult = (D_DC_LoadTrainResult)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DC_LoadTrainResult", typeof(D_DC_LoadTrainResult));

            d_DC_Classify = (D_DC_Classify)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DC_Classify", typeof(D_DC_Classify));

            d_DC_ClassifyFile = (D_DC_ClassifyFile)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DC_ClassifyFile", typeof(D_DC_ClassifyFile));

            d_DC_GetLastErrorMsg = (D_DC_GetLastErrorMsg)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "DC_GetLastErrorMsg", typeof(D_DC_GetLastErrorMsg));

            if(d_DC_Init == null || d_DC_Exit == null || d_DC_AddTrain == null
                || d_DC_AddTrainFile == null || d_DC_Train == null || d_DC_LoadTrainResult == null
                || d_DC_Classify == null || d_DC_ClassifyFile == null || d_DC_GetLastErrorMsg == null)
            {
                return false;
            }
            else
            {
                return true;
            }

        }
    }
}
