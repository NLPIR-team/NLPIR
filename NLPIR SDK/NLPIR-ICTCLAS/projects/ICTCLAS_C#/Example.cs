
using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;


namespace win_csharp
{
	[StructLayout(LayoutKind.Explicit)] 
	public struct result_t
	{ 
		[FieldOffset(0)] public int start; 
		[FieldOffset(4)] public int length;
        [FieldOffset(8)] public int sPos1;
        [FieldOffset(12)] public int sPos2;
        [FieldOffset(16)] public int sPos3;
        [FieldOffset(20)] public int sPos4;
        [FieldOffset(24)] public int sPos5;
        [FieldOffset(28)] public int sPos6;
        [FieldOffset(32)] public int sPos7;
        [FieldOffset(36)] public int sPos8;
        [FieldOffset(40)] public int sPos9;
        [FieldOffset(44)] public int sPos10;
       //[FieldOffset(12)] public int sPosLow;
        [FieldOffset(48)] public int POS_id; 
		[FieldOffset(52)] public int word_ID;
        [FieldOffset(56)] public int word_type;
        [FieldOffset(60)] public int weight;
	}
    /*
    struct result_t{
  int start; //start position,词语在输入句子中的开始位置
  int length; //length,词语的长度
  char  sPOS[POS_SIZE];//word type，词性ID值，可以快速的获取词性表
  int	iPOS;//词性标注的编号
  int word_ID; //该词的内部ID号，如果是未登录词，设成0或者-1
  int word_type; //区分用户词典;1，是用户词典中的词；0，非用户词典中的词
  int weight;//word weight,read weight
 };*/

	/// <summary>
	/// Class1 的摘要说明。
	/// </summary>
	class Class1
	{
        const string path = @"NLPIR.dll";//设定dll的路径
        //对函数进行申明
        [DllImport(path, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Winapi, EntryPoint = "NLPIR_Init")]
		public static extern bool NLPIR_Init(String sInitDirPath,int encoding,String sLicenseCode);

        //特别注意，C语言的函数NLPIR_API const char * NLPIR_ParagraphProcess(const char *sParagraph,int bPOStagged=1);必须对应下面的申明
        [DllImport(path, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Winapi, EntryPoint = "NLPIR_ParagraphProcess")]
        public static extern IntPtr NLPIR_ParagraphProcess(String sParagraph, int bPOStagged = 1);
	
        [DllImport(path,CharSet=CharSet.Ansi,EntryPoint="NLPIR_Exit")]
		public static extern bool NLPIR_Exit();
	
		[DllImport(path,CharSet=CharSet.Ansi,EntryPoint="NLPIR_ImportUserDict")]
		public static extern int NLPIR_ImportUserDict(String sFilename);

		[DllImport(path,CharSet=CharSet.Ansi,EntryPoint="NLPIR_FileProcess")]
		public static extern bool NLPIR_FileProcess(String sSrcFilename,String sDestFilename,int bPOStagged=1);
		
		[DllImport(path,CharSet=CharSet.Ansi,EntryPoint="NLPIR_FileProcessEx")]
		public static extern bool NLPIR_FileProcessEx(String sSrcFilename,String sDestFilename);
		
		[DllImport(path,CharSet=CharSet.Ansi,EntryPoint="NLPIR_GetParagraphProcessAWordCount")]
		static extern int NLPIR_GetParagraphProcessAWordCount(String sParagraph);
		//NLPIR_GetParagraphProcessAWordCount
		[DllImport(path,CharSet=CharSet.Ansi,EntryPoint="NLPIR_ParagraphProcessAW")]
		static extern void NLPIR_ParagraphProcessAW(int nCount, [Out,MarshalAs(UnmanagedType.LPArray)] result_t[] result);

        [DllImport(path, CharSet = CharSet.Ansi, EntryPoint = "NLPIR_AddUserWord")]
        static extern int NLPIR_AddUserWord(String sWord);

        [DllImport(path, CharSet = CharSet.Ansi, EntryPoint = "NLPIR_SaveTheUsrDic")]
        static extern int NLPIR_SaveTheUsrDic();

        [DllImport(path, CharSet = CharSet.Ansi, EntryPoint = "NLPIR_DelUsrWord")]
        static extern int NLPIR_DelUsrWord(String sWord);

       [DllImport(path, CharSet = CharSet.Ansi, EntryPoint = "NLPIR_NWI_Start")]
        static extern bool NLPIR_NWI_Start();

       [DllImport(path, CharSet = CharSet.Ansi, EntryPoint = "NLPIR_NWI_Complete")]
        static extern bool NLPIR_NWI_Complete();

       [DllImport(path, CharSet = CharSet.Ansi, EntryPoint = "NLPIR_NWI_AddFile")]
        static extern bool NLPIR_NWI_AddFile(String sText);

       [DllImport(path, CharSet = CharSet.Ansi, EntryPoint = "NLPIR_NWI_AddMem")]
        static extern bool NLPIR_NWI_AddMem(String sText);

       [DllImport(path, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Winapi, EntryPoint = "NLPIR_NWI_GetResult")]
      public static extern IntPtr NLPIR_NWI_GetResult(bool bWeightOut = false);

      [DllImport(path, CharSet = CharSet.Ansi, EntryPoint = "NLPIR_NWI_Result2UserDict")]
        static extern uint NLPIR_NWI_Result2UserDict();
    
        [DllImport(path, CharSet = CharSet.Ansi,CallingConvention = CallingConvention.Winapi, EntryPoint = "NLPIR_GetKeyWords")]
       public static extern IntPtr NLPIR_GetKeyWords(String sText,int nMaxKeyLimit=50,bool bWeightOut=false);

        [DllImport(path, CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Winapi, EntryPoint = "NLPIR_GetFileKeyWords")]
        public static extern IntPtr NLPIR_GetFileKeyWords(String sFilename, int nMaxKeyLimit = 50, bool bWeightOut = false);
         /// <summary>
		/// 应用程序的主入口点。
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			//
			// TODO: 在此处添加代码以启动应用程序
			//
            if (!NLPIR_Init("../../", 0,""))//给出Data文件所在的路径，注意根据实际情况修改。
			{
				System.Console.WriteLine("Init ICTCLAS failed!");
				return;
			}
            System.Console.WriteLine("Init ICTCLAS success!");
            
            String s = "　　【环球网综合报道】据俄罗斯军工综合体新闻网12月27日报道，俄罗斯世界武器贸易分析中心12月26日根据已经签订的合同和采购意向，对2012年除了俄罗斯之外的其他国家巨额武器交易情况进行总结，推出了年度世界20大武器交易排行榜，其中印度不仅高居榜首，而且还6次上榜。具体情况如下：";

            int count = NLPIR_GetParagraphProcessAWordCount(s);//先得到结果的词数
            System.Console.WriteLine("NLPIR_GetParagraphProcessAWordCount success!");

            result_t[] result = new result_t[count];//在客户端申请资源
			NLPIR_ParagraphProcessAW(count,result);//获取结果存到客户的内存中
            int i=1;
            foreach(result_t r in result)
            {
                String sWhichDic="";
                switch (r.word_type)
                {
                    case 0:
                        sWhichDic = "核心词典";
                        break;
                    case 1:
                        sWhichDic = "用户词典";
                        break;
                    case 2:
                        sWhichDic = "专业词典";
                        break;
                    default:
                        break;
                }
                Console.WriteLine("No.{0}:start:{1}, length:{2},POS_ID:{3},Word_ID:{4}, UserDefine:{5}\n", i++, r.start, r.length, r.POS_id, r.word_ID, sWhichDic);//, s.Substring(r.start, r.length)
           }
          StringBuilder sResult = new StringBuilder(600); 
            //准备存储空间         
   
          IntPtr intPtr =NLPIR_ParagraphProcess(s);//切分结果保存为IntPtr类型
          String str = Marshal.PtrToStringAnsi(intPtr);//将切分结果转换为string
          Console.WriteLine(str);

          intPtr = NLPIR_GetFileKeyWords("../test/test.TXT", 50, true);
          str = Marshal.PtrToStringAnsi(intPtr);//将切分结果转换为string
          Console.WriteLine(str);

          s = "　　【环球网综合报道】据俄罗斯军工综合体新闻网12月27日报道，俄罗斯世界武器贸易分析中心12月26日根据已经签订的合同和采购意向，对2012年除了俄罗斯之外的其他国家巨额武器交易情况进行总结，推出了年度世界20大武器交易排行榜，其中印度不仅高居榜首，而且还6次上榜。具体情况如下：";
  
          intPtr = NLPIR_GetKeyWords(s, 10, true);
          str = Marshal.PtrToStringAnsi(intPtr);//将切分结果转换为string
          Console.WriteLine(str);



          System.Console.WriteLine("Before Userdict imported:");
          String ss;
          Console.WriteLine("insert user dic:");
          ss = Console.ReadLine();
        while (ss[0]!='q'&&ss[0]!='Q')
        {
            //用户词典中添加词
            int iiii = NLPIR_AddUserWord(ss);//词 词性 example:点击下载 vyou
            intPtr = NLPIR_ParagraphProcess(s, 1);
            str = Marshal.PtrToStringAnsi(intPtr);
            System.Console.WriteLine(str);
            NLPIR_SaveTheUsrDic(); // save the user dictionary to the file

            //删除用户词典中的词
            Console.WriteLine("delete usr dic:");
            ss = Console.ReadLine();
            iiii = NLPIR_DelUsrWord(ss);
            str = Marshal.PtrToStringAnsi(intPtr);
            System.Console.WriteLine(str);
            NLPIR_SaveTheUsrDic();                

        }

        //测试新词发现与自适应分词功能
	    NLPIR_NWI_Start();//新词发现功能启动
        NLPIR_NWI_AddFile("../../test/屌丝，一个字头的诞生.TXT");//添加一个待发现新词的文件，可反复添加

        NLPIR_NWI_Complete();//新词发现完成
            
    
        intPtr = NLPIR_NWI_GetResult();
        str = Marshal.PtrToStringAnsi(intPtr);


        System.Console.WriteLine("新词识别结果:");
        System.Console.WriteLine(str);
        NLPIR_FileProcess("../test/屌丝，一个字头的诞生.TXT", "../test/屌丝，一个字头的诞生-分词结果.TXT");
        NLPIR_NWI_Result2UserDict();//新词识别结果导入分词库
        NLPIR_FileProcess("../test/屌丝，一个字头的诞生.TXT", "../test/屌丝，一个字头的诞生-自适应分词结果.TXT");
        NLPIR_Exit();
       }
	}
}
