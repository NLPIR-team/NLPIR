using System;
using System.Runtime.InteropServices;
using Lingjoin.Global;

namespace Lingjoin.ICTCLASTest
{
    [StructLayout(LayoutKind.Sequential)]
    public struct result_t
    {
        public int start; //start position,词语在输入句子中的开始位置
        public int length; //length,词语的长度
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 40)]
        public char[] sPOS;//word type，词性ID值，可以快速的获取词性表
        public int iPOS;//词性标注的编号
        public int word_ID; //该词的内部ID号，如果是未登录词，设成0或者-1
        public int word_type; //区分用户词典;1，是用户词典中的词；0，非用户词典中的词
        public int weight;//word weight,read weight
    };

    public class ICTCLAS : Base
    {

        private delegate bool D_NLPIR_Init(string sDataPath, int encode, string sLicenseCode);
        private delegate IntPtr D_NLPIR_GetLastErrorMsg();
        private delegate IntPtr D_NLPIR_ParagraphProcess(string sSrc, int bPOSTagged);
        private delegate double D_NLPIR_FileProcess(string sSourceFilename, string sResultFilename, int bPOStagged);
        private delegate IntPtr D_NLPIR_FinerSegment(string lenWords);
        private delegate IntPtr D_NLPIR_GetKeyWords(string sLine, int nMaxKeyLimit, bool bWeightOut);
        private delegate IntPtr D_NLPIR_GetFileKeyWords(string sFilename, int nMaxKeyLimit, bool bWeightOut);
        private delegate IntPtr D_NLPIR_GetNewWords(string sLine, int nMaxKeyLimit, bool bWeightOut);
        private delegate IntPtr D_NLPIR_GetFileNewWords(string sFilename, int nMaxKeyLimit, bool bWeightOut);
        private delegate int D_NLPIR_AddUserWord(string userWord);
        private delegate int D_NLPIR_ImportUserDict(string dictFileName, bool bOverWrite);
        private delegate int D_NLPIR_ImportKeyBlackList(string sFilename);
        private delegate long D_NLPIR_FingerPrint(string sLine);
        private delegate IntPtr D_NLPIR_GetWordPOS(string sWords);
        private delegate bool D_NLPIR_IsWord(string word);
        private delegate IntPtr D_NLPIR_WordFreqStat(string sText);
        private delegate IntPtr D_NLPIR_FileWordFreqStat(string sFilename);
        private delegate IntPtr D_NLPIR_GetEngWordOrign(string sWord);
        private delegate bool D_NLPIR_Exit();
        private delegate int D_NLPIR_SaveTheUsrDic();
        private delegate int D_NLPIR_DelUsrWord(string sWord);
        private delegate int D_NLPIR_GetParagraphProcessAWordCount(string sParagraph);
        private delegate IntPtr D_NLPIR_ParagraphProcessA(string sParagraph, ref int pResultCount, bool bUserDict);

        private D_NLPIR_DelUsrWord d_NLPIR_DelUsrWord;
        private D_NLPIR_SaveTheUsrDic d_NLPIR_SaveTheUsrDic;
        private D_NLPIR_Init d_NLPIR_Init;
        private D_NLPIR_GetLastErrorMsg d_NLPIR_GetLastErrorMsg;
        private D_NLPIR_ParagraphProcess d_NLPIR_ParagraphProcess;
        private D_NLPIR_FileProcess d_NLPIR_FileProcess;
        private D_NLPIR_FinerSegment d_NLPIR_FinerSegment;
        private D_NLPIR_GetKeyWords d_NLPIR_GetKeyWords;
        private D_NLPIR_GetFileKeyWords d_NLPIR_GetFileKeyWords;
        private D_NLPIR_GetNewWords d_NLPIR_GetNewWords;
        private D_NLPIR_GetFileNewWords d_NLPIR_GetFileNewWords;
        private D_NLPIR_AddUserWord d_NLPIR_AddUserWord;
        private D_NLPIR_ImportUserDict d_NLPIR_ImportUserDict;
        private D_NLPIR_ImportKeyBlackList d_NLPIR_ImportKeyBlackList;
        private D_NLPIR_FingerPrint d_NLPIR_FingerPrint;
        private D_NLPIR_GetWordPOS d_NLPIR_GetWordPOS;
        private D_NLPIR_IsWord d_NLPIR_IsWord;
        private D_NLPIR_WordFreqStat d_NLPIR_WordFreqStat;
        private D_NLPIR_FileWordFreqStat d_NLPIR_FileWordFreqStat;
        private D_NLPIR_GetEngWordOrign d_NLPIR_GetEngWordOrign;
        private D_NLPIR_Exit d_NLPIR_Exit;
        private D_NLPIR_GetParagraphProcessAWordCount d_NLPIR_GetParagraphProcessAWordCount;
        private D_NLPIR_ParagraphProcessA d_NLPIR_ParagraphProcessA;

        protected override bool InitFunctions()
        {
            d_NLPIR_Init = (D_NLPIR_Init)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_Init", typeof(D_NLPIR_Init));

            d_NLPIR_GetLastErrorMsg = (D_NLPIR_GetLastErrorMsg)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_GetLastErrorMsg", typeof(D_NLPIR_GetLastErrorMsg));

            d_NLPIR_ParagraphProcess = (D_NLPIR_ParagraphProcess)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_ParagraphProcess", typeof(D_NLPIR_ParagraphProcess));

            d_NLPIR_FileProcess = (D_NLPIR_FileProcess)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_FileProcess", typeof(D_NLPIR_FileProcess));

            d_NLPIR_FinerSegment = (D_NLPIR_FinerSegment)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_FinerSegment", typeof(D_NLPIR_FinerSegment));

            d_NLPIR_GetKeyWords = (D_NLPIR_GetKeyWords)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_GetKeyWords", typeof(D_NLPIR_GetKeyWords));

            d_NLPIR_GetFileKeyWords = (D_NLPIR_GetFileKeyWords)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_GetFileKeyWords", typeof(D_NLPIR_GetFileKeyWords));

            d_NLPIR_GetNewWords = (D_NLPIR_GetNewWords)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_GetNewWords", typeof(D_NLPIR_GetNewWords));

            d_NLPIR_GetFileNewWords = (D_NLPIR_GetFileNewWords)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_GetFileNewWords", typeof(D_NLPIR_GetFileNewWords));

            d_NLPIR_AddUserWord = (D_NLPIR_AddUserWord)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_AddUserWord", typeof(D_NLPIR_AddUserWord));

            d_NLPIR_ImportUserDict = (D_NLPIR_ImportUserDict)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_ImportUserDict", typeof(D_NLPIR_ImportUserDict));

            d_NLPIR_Exit = (D_NLPIR_Exit)DllWrapper.GetFunctionAddress(
                 DllWrapper.hModule, "NLPIR_Exit", typeof(D_NLPIR_Exit));

            d_NLPIR_ImportKeyBlackList = (D_NLPIR_ImportKeyBlackList)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_ImportKeyBlackList", typeof(D_NLPIR_ImportKeyBlackList));

            d_NLPIR_FingerPrint = (D_NLPIR_FingerPrint)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_FingerPrint", typeof(D_NLPIR_FingerPrint));

            d_NLPIR_GetWordPOS = (D_NLPIR_GetWordPOS)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_GetWordPOS", typeof(D_NLPIR_GetWordPOS));

            d_NLPIR_IsWord = (D_NLPIR_IsWord)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_IsWord", typeof(D_NLPIR_IsWord));

            d_NLPIR_WordFreqStat = (D_NLPIR_WordFreqStat)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_WordFreqStat", typeof(D_NLPIR_WordFreqStat));

            d_NLPIR_FileWordFreqStat = (D_NLPIR_FileWordFreqStat)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_FileWordFreqStat", typeof(D_NLPIR_FileWordFreqStat));

            d_NLPIR_GetEngWordOrign = (D_NLPIR_GetEngWordOrign)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_GetEngWordOrign", typeof(D_NLPIR_GetEngWordOrign));

            d_NLPIR_SaveTheUsrDic = (D_NLPIR_SaveTheUsrDic)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_SaveTheUsrDic", typeof(D_NLPIR_SaveTheUsrDic));

            d_NLPIR_DelUsrWord = (D_NLPIR_DelUsrWord)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "NLPIR_DelUsrWord", typeof(D_NLPIR_DelUsrWord));

            if (d_NLPIR_Init == null || d_NLPIR_GetLastErrorMsg == null || d_NLPIR_ParagraphProcess == null || d_NLPIR_FileProcess == null
                || d_NLPIR_FinerSegment == null || d_NLPIR_GetKeyWords == null || d_NLPIR_GetFileKeyWords == null || d_NLPIR_GetNewWords == null
                || d_NLPIR_GetFileNewWords == null || d_NLPIR_AddUserWord == null || d_NLPIR_ImportUserDict == null || d_NLPIR_Exit == null
                || d_NLPIR_ImportKeyBlackList == null || d_NLPIR_FingerPrint == null || d_NLPIR_GetWordPOS == null || d_NLPIR_IsWord == null
                || d_NLPIR_WordFreqStat == null || d_NLPIR_FileWordFreqStat == null || d_NLPIR_GetEngWordOrign == null || d_NLPIR_DelUsrWord == null)
            {
                return false;
            }
            else
            {
                return true;
            }

        }

        public override string DllFileName
        {
            get { return "NLPIR.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "NLPIR.user"; }
        }

        public ICTCLAS() : base() { }

        public ICTCLAS(string dllDir, string authorizationDir) : base(dllDir, authorizationDir) { }

        /**
         * 组件初始化
         * @param sDataPath Data文件夹的父目录，如果为空字符串（即：""），那么，程序自动从项目的根目录中寻找
         * @param encoding 编码格式，具体的编码对照如下：
                                        0：GBK
                                        1：UTF8
                                        2：BIG5
                                        3：GBK，里面包含繁体字；
         * @param sLicenceCode 授权码，为空字符串（即：""）就可以了
         * @return true：初始化成功；false：初始化失败
        */
        public bool NLPIR_Init(string sDataPath, int encode, string sLicenseCode)
        {
            return d_NLPIR_Init(sDataPath, encode, sLicenseCode);
        }

        public int NLPIR_DelUsrWord(string sWord)
        {
            return d_NLPIR_DelUsrWord(sWord);
        }

        public int NLPIR_SaveTheUsrDic()
        {
            return d_NLPIR_SaveTheUsrDic();
        }

        /**
         * 返回最后一次的出错信息
         * @return 最后一次的出错信息
         */
        public string NLPIR_GetLastErrorMsg()
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_GetLastErrorMsg());
        }

        /**
         * 分词
         * @param sSrc 文本内容
         * @param bPOSTagged 1：显示词性，0：不显示词性
         * @return 分词后的结果
         */
        public string NLPIR_ParagraphProcess(string sSrc, int bPOSTagged)
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_ParagraphProcess(sSrc, bPOSTagged));
        }

        public double NLPIR_FileProcess(string sSourceFilename, string sResultFilename, int bPOStagged)
        {
            return d_NLPIR_FileProcess(sSourceFilename, sResultFilename, bPOStagged);
        }

        /**
         * 细粒度分词
         * @param lenWords 文本内容
         * @return 分词后的结果
         */
        public string NLPIR_FinerSegment(string lenWords)
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_FinerSegment(lenWords));
        }

        /**
         * 获得关键词
         * @param sLine 文本内容
         * @param nMaxKeyLimit 生成的关键词的个数上限
         * @param bWeightOut true:显示词性信息；false:不显示词性信息
         * @return 关键词组成的字符串
         * 备注：黑名单中出现的词，不会作为关键词出现
         */
        public string NLPIR_GetKeyWords(string sLine, int nMaxKeyLimit, bool bWeightOut)
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_GetKeyWords(sLine, nMaxKeyLimit, bWeightOut));
        }

        /**
         * 获得关键词
         * @param sFilename 文本文件的路径
         * @param nMaxKeyLimit 生成的关键词的个数上限
         * @param bWeightOut true:显示词性信息；false:不显示词性信息
         * @return 关键词组成的字符串
         * 备注：黑名单中出现的词，不会作为关键词出现
         */
        public string NLPIR_GetFileKeyWords(string sFilename, int nMaxKeyLimit, bool bWeightOut)
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_GetFileKeyWords(sFilename, nMaxKeyLimit, bWeightOut));
        }

        /**
         * 获得新词
         * @param sLine 文本内容 
         * @param nMaxKeyLimit 生成的新词的个数上限
         * @param bWeightOut true:显示词性信息；false:不显示词性信息
         * @return 新词组成的字符串
         */
        public string NLPIR_GetNewWords(string sLine, int nMaxKeyLimit, bool bWeightOut)
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_GetNewWords(sLine, nMaxKeyLimit, bWeightOut));
        }

        /**
         * 获得新词
         * @param string 文本文件的路径
         * @param nMaxKeyLimit 生成的新词的个数上限
         * @param bWeightOut true:显示词性信息；false:不显示词性信息
         * @return 新词组成的字符串
         */
        public string NLPIR_GetFileNewWords(string sFilename, int nMaxKeyLimit, bool bWeightOut)
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_GetFileNewWords(sFilename, nMaxKeyLimit, bWeightOut));
        }

        /**
         * 添加自定义单词（退出程序即失效）
         * @param userWord
         * @return
         */
        public int NLPIR_AddUserWord(string userWord)
        {
            return d_NLPIR_AddUserWord(userWord);
        }

        /**
         * 导入用户词典
         * @param dictFileName 用户词典的路径（请使用全路径）
         * @param bOverwrite 是否删除原有的自定义用户词典，true：删除；false：不删除
         * @return
         * 备注：系统会自动处理重复词的问题
         */
        public int NLPIR_ImportUserDict(string dictFileName, bool bOverWrite)
        {
            return d_NLPIR_ImportUserDict(dictFileName, bOverWrite);
        }

        /**
         * 退出，释放资源
         * @return
         */
        public bool NLPIR_Exit()
        {
            return d_NLPIR_Exit();
        }

        /**
         * 导入黑名单，成功导入后，黑名单中出现的词，不会作为关键词出现。
         * @param sFilename 文件的路径
         * @return
         */
        public int NLPIR_ImportKeyBlackList(string sFilename)
        {
            return d_NLPIR_ImportKeyBlackList(sFilename);
        }

        /**
         * 提取文章的指纹码
         * @param sLine 文本内容
         * @return 指纹码
         */
        public long NLPIR_FingerPrint(string sLine)
        {
            return d_NLPIR_FingerPrint(sLine);
        }

        /**
         * 获得单词在核心词库中的词性
         * @param sWords 单词，例如：中华人民共和国
         * @return  单词的词性，例如：中华人民共和国/ns/607#
         */
        public string NLPIR_GetWordPOS(string sWords)
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_GetWordPOS(sWords));
        }

        /**
         * 判断单词是否在核心词库中
         * @param word 输入的单词
         * @return  如果单词不存在就返回-1，否则返回单词在词典中的句柄
         */
        public bool NLPIR_IsWord(string word)
        {
            return d_NLPIR_IsWord(word);
        }

        /**
         * 获取输入文本的词，词性，频统计结果，按照词频大小排序
         * @param sText 文本内容
         * @return 词频统计结果形式如下：张华平/nr/10#博士/n/9#分词/n/8
         */
        public string NLPIR_WordFreqStat(string sText)
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_WordFreqStat(sText));
        }

        /**
         * 获取输入文本文件的词，词性，频统计结果，按照词频大小排序
         * @param sFilename 文本文件的全路径
         * @return 词频统计结果形式如下：张华平/nr/10#博士/n/9#分词/n/8
         */
        public string NLPIR_FileWordFreqStat(string sFilename)
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_FileWordFreqStat(sFilename));
        }

        /**
         * 获取各类英文单词的原型，考虑了过去分词、单复数等情况
         * @param sWord 输入的单词
         * @return 词原型形式，例如：driven->drive   drives->drive   drove-->drive
         */
        public string NLPIR_GetEngWordOrign(string sWord)
        {
            return Marshal.PtrToStringAnsi(d_NLPIR_GetEngWordOrign(sWord));
        }


    }
}
