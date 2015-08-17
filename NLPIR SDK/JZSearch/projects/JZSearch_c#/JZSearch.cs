/************************************************************************************
 * 创建人：  huoshan12345
 * 电子邮箱：89009143@qq.com
 * 创建时间：2015/3/17 13:03:40
 * 描述：
/************************************************************************************/

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Lingjoin.Global;

namespace Lingjoin.JZSearchTest
{
    public class JZSearch : Base
    {
        public const int INDEX_ENCODING_GBK = 0;
        public const int INDEX_ENCODING_UTF8 = 1;
        public const int INDEX_ENCODING_BIG5 = 2;
        public const int INDEX_ENCODING_GBK_FANTI = 3;//GBK中包含繁体字，统一兼容，推荐使用INDEX_ENCODING_GBK_FANTI
        public const int INDEX_ENCODING_COUNT = 4;

        public const int LANGUAGE_TYPE_UNKNOWN = 0;
        public const int LANGUAGE_TYPE_CHINESE = 1;
        public const int LANGUAGE_TYPE_UYGHAN = 2;

        public override string DllFileName
        {
            get { return "JZSearchAPI.dll"; }
        }

        public override string AuthorizationFileName
        {
            get { return "JZSearch.user"; }
        }

        public JZSearch(params string[] dllNames) : base(dllNames) { }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZIndexer_Init(String sDictPath, String sFieldInfoFile, int encoding, bool bICTCLAS, int lang_type, String sLicenceCode);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_JZIndexer_FieldAdd(String sFieldName, String sDBFieldName, int nFieldType,
            bool bIndexed, bool bRetrieved, bool bGeneral, bool bAbstracted);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_JZIndexer_FieldSave(String sFieldInfoDataFile);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_JZIndexer_FieldLoad(String sFieldInfoDataFile);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZIndexer_NewInstance(String pcIndexFile, int nMaxMemSize);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZIndexer_MemIndexing(int handle, String pText, String sFieldName, int nMemSize);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZIndexer_FileIndexing(int handle, String TextFilename, String sFieldName);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZIndexer_BigFileIndexing(int handle, String sBigFilename, int nOffset, int nSize, String sFieldName);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZIndexer_IntIndexing(int handle, int value, String sFieldName);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZIndexer_FloatIndexing(int handle, float value, String sFieldName);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZIndexer_Save(int handle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZIndexer_AddDoc(int handle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZIndexer_DeleteInstance(int handle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate bool D_JZIndexer_Exit();
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZSearch_Init(String sIndexFile, String sDictPath, String sFieldInfoFile, int MaxMemSize, int encoding, int nGroupMaxCount, bool bICTCLAS, int lang_type, String sLicenceCode);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZSearch_Reload(int searcher_handle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZSearch_Exit(int searcher_handle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZSearcher_NewInstance(int sort_type, int searcher_handle);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate IntPtr D_JZSearcher_Search(int handle, String query_line, int nStart, int nPageCount);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZSearcher_DeleteInstance(int handle);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZSearch_SetAbstractArgu(uint nAbstractLength, String sTagStart, String sTagEnd, int iFrontLen);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZSearch_DocDelete(int handle, int doc_id);
        [UnmanagedFunctionPointer(CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private delegate int D_JZSearch_SetIndexSizeLimit(int nLimitSize = 20480);

        private D_JZIndexer_Init d_JZIndexer_Init;
        private D_JZIndexer_FieldAdd d_JZIndexer_FieldAdd;
        private D_JZIndexer_FieldSave d_JZIndexer_FieldSave;
        private D_JZIndexer_FieldLoad d_JZIndexer_FieldLoad;
        private D_JZIndexer_NewInstance d_JZIndexer_NewInstance;
        private D_JZIndexer_MemIndexing d_JZIndexer_MemIndexing;
        private D_JZIndexer_FileIndexing d_JZIndexer_FileIndexing;
        private D_JZIndexer_BigFileIndexing d_JZIndexer_BigFileIndexing;
        private D_JZIndexer_IntIndexing d_JZIndexer_IntIndexing;
        private D_JZIndexer_FloatIndexing d_JZIndexer_FloatIndexing;
        private D_JZIndexer_Save d_JZIndexer_Save;
        private D_JZIndexer_AddDoc d_JZIndexer_AddDoc;
        private D_JZIndexer_DeleteInstance d_JZIndexer_DeleteInstance;
        private D_JZIndexer_Exit d_JZIndexer_Exit;
        private D_JZSearch_Init d_JZSearch_Init;
        private D_JZSearch_Reload d_JZSearch_Reload;
        private D_JZSearch_Exit d_JZSearch_Exit;
        private D_JZSearcher_NewInstance d_JZSearcher_NewInstance;
        private D_JZSearcher_Search d_JZSearcher_Search;
        private D_JZSearcher_DeleteInstance d_JZSearcher_DeleteInstance;
        private D_JZSearch_SetAbstractArgu d_JZSearch_SetAbstractArgu;
        private D_JZSearch_DocDelete d_JZSearch_DocDelete;
        private D_JZSearch_SetIndexSizeLimit d_JZSearch_SetIndexSizeLimit;

/*
        private Dictionary<Type, Delegate> delegates = new Dictionary<Type, Delegate>()
        {
            { typeof(D_JZIndexer_Init), null},
            { typeof(D_JZIndexer_FieldAdd), null},
            { typeof(D_JZIndexer_FieldSave), null},
            { typeof(D_JZIndexer_FieldLoad), null},
            { typeof(D_JZIndexer_NewInstance), null},
            { typeof(D_JZIndexer_MemIndexing), null},
            { typeof(D_JZIndexer_FileIndexing), null},
            { typeof(D_JZIndexer_BigFileIndexing), null},
            { typeof(D_JZIndexer_IntIndexing), null},
            { typeof(D_JZIndexer_FloatIndexing), null},
            { typeof(D_JZIndexer_Save), null},
            { typeof(D_JZIndexer_AddDoc), null},
            { typeof(D_JZIndexer_DeleteInstance), null},
            { typeof(D_JZIndexer_Exit), null},
            { typeof(D_JZSearch_Init), null},
            { typeof(D_JZSearch_Reload), null},
            { typeof(D_JZSearch_Exit), null},
            { typeof(D_JZSearcher_NewInstance), null},
            { typeof(D_JZSearcher_Search), null},
            { typeof(D_JZSearcher_DeleteInstance), null},
            { typeof(D_JZSearch_SetAbstractArgu), null},
        };
 */

        protected override bool InitFunctions()
        {

            d_JZIndexer_Init = (D_JZIndexer_Init)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_Init", typeof(D_JZIndexer_Init));

            d_JZIndexer_FieldAdd = (D_JZIndexer_FieldAdd)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_FieldAdd", typeof(D_JZIndexer_FieldAdd));

            d_JZIndexer_FieldSave = (D_JZIndexer_FieldSave)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_FieldSave", typeof(D_JZIndexer_FieldSave));

            d_JZIndexer_FieldLoad = (D_JZIndexer_FieldLoad)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_FieldLoad", typeof(D_JZIndexer_FieldLoad));

            d_JZIndexer_NewInstance = (D_JZIndexer_NewInstance)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_NewInstance", typeof(D_JZIndexer_NewInstance));

            d_JZIndexer_MemIndexing = (D_JZIndexer_MemIndexing)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_MemIndexing", typeof(D_JZIndexer_MemIndexing));

            d_JZIndexer_FileIndexing = (D_JZIndexer_FileIndexing)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_FileIndexing", typeof(D_JZIndexer_FileIndexing));

            d_JZIndexer_BigFileIndexing = (D_JZIndexer_BigFileIndexing)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_BigFileIndexing", typeof(D_JZIndexer_BigFileIndexing));

            d_JZIndexer_IntIndexing = (D_JZIndexer_IntIndexing)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_IntIndexing", typeof(D_JZIndexer_IntIndexing));

            d_JZIndexer_FloatIndexing = (D_JZIndexer_FloatIndexing)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_FloatIndexing", typeof(D_JZIndexer_FloatIndexing));

            d_JZIndexer_Save = (D_JZIndexer_Save)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_Save", typeof(D_JZIndexer_Save));

            d_JZIndexer_AddDoc = (D_JZIndexer_AddDoc)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_AddDoc", typeof(D_JZIndexer_AddDoc));

            d_JZIndexer_DeleteInstance = (D_JZIndexer_DeleteInstance)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_DeleteInstance", typeof(D_JZIndexer_DeleteInstance));

            d_JZIndexer_Exit = (D_JZIndexer_Exit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZIndexer_Exit", typeof(D_JZIndexer_Exit));

            d_JZSearch_Init = (D_JZSearch_Init)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZSearch_Init", typeof(D_JZSearch_Init));

            d_JZSearch_Reload = (D_JZSearch_Reload)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZSearch_Reload", typeof(D_JZSearch_Reload));

            d_JZSearch_Exit = (D_JZSearch_Exit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZSearch_Exit", typeof(D_JZSearch_Exit));

            d_JZSearcher_NewInstance = (D_JZSearcher_NewInstance)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZSearcher_NewInstance", typeof(D_JZSearcher_NewInstance));

            d_JZSearcher_Search = (D_JZSearcher_Search)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZSearcher_Search", typeof(D_JZSearcher_Search));

            d_JZSearcher_DeleteInstance = (D_JZSearcher_DeleteInstance)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZSearcher_DeleteInstance", typeof(D_JZSearcher_DeleteInstance));

            d_JZSearch_SetAbstractArgu = (D_JZSearch_SetAbstractArgu)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZSearch_SetAbstractArgu", typeof(D_JZSearch_SetAbstractArgu));

            d_JZSearch_DocDelete = (D_JZSearch_DocDelete)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZSearch_DocDelete", typeof(D_JZSearch_DocDelete));

            d_JZSearch_SetIndexSizeLimit = (D_JZSearch_SetIndexSizeLimit)DllWrapper.GetFunctionAddress(
                DllWrapper.hModule, "JZSearch_SetIndexSizeLimit", typeof(D_JZSearch_SetIndexSizeLimit));

            if (d_JZSearcher_DeleteInstance == null || d_JZSearcher_Search == null
                || d_JZSearcher_NewInstance == null || d_JZSearch_Exit == null
                || d_JZSearch_Reload == null || d_JZSearch_Init == null
                || d_JZIndexer_Exit == null || d_JZIndexer_DeleteInstance == null
                || d_JZIndexer_AddDoc == null || d_JZIndexer_Save == null
                || d_JZIndexer_FloatIndexing == null || d_JZIndexer_IntIndexing == null
                || d_JZIndexer_BigFileIndexing == null || d_JZIndexer_FileIndexing == null
                || d_JZIndexer_MemIndexing == null || d_JZIndexer_NewInstance == null
                || d_JZIndexer_FieldLoad == null || d_JZIndexer_FieldSave == null
                || d_JZIndexer_FieldAdd == null || d_JZIndexer_Init == null
                || d_JZSearch_SetAbstractArgu == null || d_JZSearch_DocDelete == null
                || d_JZSearch_SetIndexSizeLimit == null)
            {
                return false;
            }

            return true;
            // return InitFunctions(delegates);
        }


        /**
         * 索引系统初始化，必须初始化后，才能使用CJZIndexer
         * @param sDictPath 词典文件名；为空时，采用n-gram索引方法
         * @param sFieldInfoFile 域字段信息，用于支持多域索引，为空则只支持一个字段
         * @param encoding 编码格式，具体的编码对照如下：
                                        0：GBK
                                        1：UTF8
                                        2：BIG5
                                        3：GBK，里面包含繁体字；
         * @param bICTCLAS false
         * @param lang_type 语言类型， 0 : LANGUAGE_TYPE_UNKNOWN;
         *                         1 : LANGUAGE_TYPE_CHINESE;
         *                         2 : LANGUAGE_TYPE_UYGHAN;   
         * @param sLicenceCode 授权码，为空字符串（即：""）就可以了
         * @return 1：初始化成功；0：初始化失败
         */
        public int JZIndexer_Init(String sDictPath, String sFieldInfoFile, int encoding, bool bICTCLAS,
            int lang_type = LANGUAGE_TYPE_CHINESE, String sLicenceCode = "")
        {
            return d_JZIndexer_Init(sDictPath, sFieldInfoFile, encoding, bICTCLAS, lang_type, sLicenceCode);
            // return ((D_JZIndexer_Init)delegates[typeof(D_JZIndexer_Init)])(sDictPath, sFieldInfoFile, encoding, bICTCLAS, lang_type, sLicenceCode);
        }

        /**
         * 在字段文件中添加字段
         * @param sFieldName 域名称，在索引建立与搜索过程中，域的唯一标示符
         * @param sDBFieldName 对应于数据库的字段名称；在数据库搜索的时候，用于获取数据库的数据
         * @param nFieldType 数据类型   1 :  FIELD_TYPE_TEXT;
         *                         2 : FIELD_TYPE_INT;
         *                         3 : FIELD_TYPE_LONG;
         *                         4 : FIELD_TYPE_DATETIME;
         *                         5 : FIELD_TYPE_FLOAT;
         * @param bIndexed 是否需要索引
         * @param bRetrieved 搜索结果中是否要输出该字段内容
         * @param bGeneral 是否纳入通配搜索的范畴
         * @param bAbstracted 是否进行搜索摘要提取并红显
         * @return
         */
        public bool JZIndexer_FieldAdd(String sFieldName, String sDBFieldName, int nFieldType, bool bIndexed, bool bRetrieved, bool bGeneral, bool bAbstracted)
        {
            return d_JZIndexer_FieldAdd(sFieldName, sDBFieldName, nFieldType, bIndexed, bRetrieved, bGeneral, bAbstracted);
        }


        /**
         * 保存的域信息数据文件
         * @param sFieldInfoDataFile(.dat格式的文件)
         * @return
         */
        public bool JZIndexer_FieldSave(String sFieldInfoDataFile)
        {
            return d_JZIndexer_FieldSave(sFieldInfoDataFile);
        }

        /**
         * 读取已经保存好的域信息数据文件
         * @param sFieldInfoDataFile(.dat格式的文件)
         * @return
         */
        public bool JZIndexer_FieldLoad(String sFieldInfoDataFile)
        {
            return d_JZIndexer_FieldLoad(sFieldInfoDataFile);
        }

        /**
         * 生成实例失败，则返回为-1，否则为实例的Handle
         * @param pcIndexFile
         * @param nMaxMemSize 512000000
         * @return 生成实例失败，则返回为-1，否则为实例的Handle
         */
        public int JZIndexer_NewInstance(String pcIndexFile, int nMaxMemSize)
        {
            return d_JZIndexer_NewInstance(pcIndexFile, nMaxMemSize);
        }

        /**
         * 索引一段内存
         * @param handle handle为JZIndexer_NewInstance返回的结果
         * @param pText
         * @param sFieldName 字段名称，为空则表示无字段信息
         * @param nMemSize 0
         * @return
         */
        public int JZIndexer_MemIndexing(int handle, String pText, String sFieldName, int nMemSize)
        {
            return d_JZIndexer_MemIndexing(handle, pText, sFieldName, nMemSize);
        }


        /**
         * 索引一个文本文件
         * @param handle
         * @param TextFilename
         * @param sFieldName 字段名称，为空则表示无字段信息
         * @return
         */
        public int JZIndexer_FileIndexing(int handle, String TextFilename, String sFieldName)
        {
            return d_JZIndexer_FileIndexing(handle, TextFilename, sFieldName);
        }

        /**
         * 索引一个Big File中指定的偏移量和长度的文本文件
         * @param handle
         * @param sBigFilename Big File的文件名；
         * @param nOffset 偏移量；
         * @param nSize 文件长度
         * @param sFieldName 字段名称，为空则表示无字段信息
         * @return
         */
        public int JZIndexer_BigFileIndexing(int handle, String sBigFilename, int nOffset, int nSize, String sFieldName)
        {
            return d_JZIndexer_BigFileIndexing(handle, sBigFilename, nOffset, nSize, sFieldName);
        }

        /**
         * 对数值进行索引
         * @param handle
         * @param value
         * @param sFieldName 字段名称，为空则表示无字段信息
         * @return
         */
        public int JZIndexer_IntIndexing(int handle, int value, String sFieldName)
        {
            return d_JZIndexer_IntIndexing(handle, value, sFieldName);
        }

        /**
         * 对数值进行索引
         * @param handle
         * @param value
         * @param sFieldName 字段名称，为空则表示无字段信息
         * @return
         */
        public int JZIndexer_FloatIndexing(int handle, float value, String sFieldName)
        {
            return d_JZIndexer_FloatIndexing(handle, value, sFieldName);
        }

        /**
         * 索引保存的名称
         * @param handle
         * @return
         */
        public int JZIndexer_Save(int handle)
        {
            return d_JZIndexer_Save(handle);
        }

        /**
         * 增加文档
         * @param handle
         * @return
         */
        public int JZIndexer_AddDoc(int handle)
        {
            return d_JZIndexer_AddDoc(handle);
        }

        /**
         * 删除实例
         * @param handle
         * @return
         */
        public int JZIndexer_DeleteInstance(int handle)
        {
            return d_JZIndexer_DeleteInstance(handle);
        }

        /**
         * 程序退出
         * @return
         */
        public bool JZIndexer_Exit()
        {
            return d_JZIndexer_Exit();
        }

        /**
         * @param sIndexFile
         * @param sDictPath 词典文件名；为空时，采用n-gram索引方法
         * @param sFieldInfoFile 域字段信息，用于支持多域索引，为空则只支持一个字段
         * @param MaxMemSize 512000000
         * @param encoding 编码格式，具体的编码对照如下：
                                        0：GBK
                                        1：UTF8
                                        2：BIG5
                                        3：GBK，里面包含繁体字；
         * @param nGroupMaxCount
         * @param bICTCLAS false
         * @param lang_type 语言类型， 0 : LANGUAGE_TYPE_UNKNOWN;
         *                         1 : LANGUAGE_TYPE_CHINESE;
         *                         2 : LANGUAGE_TYPE_UYGHAN;   
         * @param sLicenceCode 授权码，为空字符串（即：""）就可以了
         * @return 初始化失败会返回-1，成功会返回searcher_handle值，用于调用JZSearcher_NewInstance方法、JZSearch_Reload方法、JZSearch_Exit方法
         */
        public int JZSearch_Init(String sIndexFile, String sDictPath, String sFieldInfoFile,
            int maxMemSize, int encoding, int nGroupMaxCount, bool bICTCLAS, int lang_type = LANGUAGE_TYPE_CHINESE, String sLicenceCode = "")
        {
            return d_JZSearch_Init(sIndexFile, sDictPath, sFieldInfoFile, maxMemSize, encoding, nGroupMaxCount, bICTCLAS, lang_type, sLicenceCode);
        }

        /**
         * 系统索引增量更新后，重新加载
         * @param handle JZSearch_Init方法返回的searcher_handle值
         * @return
         */
        public int JZSearch_Reload(int searcher_handle)
        {
            return d_JZSearch_Reload(searcher_handle);
        }

        /**
         * 第handle个搜索器系统退出，如果(handle==0)，则要求退出并销毁所有内存开销
         * @param searcher_handle JZSearch_Init方法返回的searcher_handle值
         * @return
         */
        public int JZSearch_Exit(int searcher_handle)
        {
            return d_JZSearch_Exit(searcher_handle);
        }

        /**
         * @param sort_type 排序方式   1 : 按照DocID排序(SORT_TYPE_DOCID);
         *                        2 : 按照相关度排序(SORT_TYPE_RELEVANCE)
         *			  			  3 : 按照DocID倒序排序(SORT_TYPE_DOCID_REVERSE)
         * @param searcher_handle 
         * @return 生成实例失败，则返回为-1，否则为实例的Handle
         */
        public int JZSearcher_NewInstance(int sort_type, int searcher_handle)
        {
            return d_JZSearcher_NewInstance(sort_type, searcher_handle);
        }

        /**
         * @param handle
         * @param query_line  查询表达式
         * @param nStart 记录起始地址
         * @param nPageCount 当前页返回结果数目
         * @return 当前页需要返回所有的结果xml字符串
         */
        public String JZSearcher_Search(int handle, String query_line, int nStart, int nPageCount)
        {
            return Marshal.PtrToStringAnsi(d_JZSearcher_Search(handle, query_line, nStart, nPageCount));
        }

        /**
         * @param handle
         * @return
         */
        public int JZSearcher_DeleteInstance(int handle)
        {
            return d_JZSearcher_DeleteInstance(handle);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="nAbstractLength">摘要长度</param>
        /// <param name="sTagStart">关键字标签-前部</param>
        /// <param name="sTagEnd">关键字标签-后部</param>
        /// <param name="iFrontLen">关键字之前内容字符串的长度</param>
        /// <returns></returns>
        public int JZSearch_SetAbstractArgu(uint nAbstractLength, String sTagStart, String sTagEnd, int iFrontLen = 6)
        {
            return d_JZSearch_SetAbstractArgu(nAbstractLength, sTagStart, sTagEnd, iFrontLen);
        }
        
        /// <summary>
        /// //删除handle搜索引擎中的内部编号为doc_id的文档
        /// </summary>
        /// <param name="handle"></param>
        /// <param name="doc_id"></param>
        /// <returns></returns>
        public int JZSearch_DocDelete(int handle, int doc_id)
        {
            return d_JZSearch_DocDelete(handle, doc_id);
        }

        /// <summary>
        /// 设置索引内容的长度限制，默认为20KB；设为-1表示不限制
        /// </summary>
        /// <param name="nLimitSize"></param>
        /// <returns></returns>
        public int JZSearch_SetIndexSizeLimit(int nLimitSize = 20480)
        {
            return d_JZSearch_SetIndexSizeLimit(nLimitSize);
        }
    }
}
