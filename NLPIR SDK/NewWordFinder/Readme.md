## NLPIR NewWordFinder##


新词发现支持混合编码

1 初始化时将编码设置为-1

if(!NWF_Init(sDataPath,nCode))
	{
		printf("ICTCLAS INIT FAILED!\n");
		return ;
	}

2处理单个文件或者内存调用 NWF_GetFileNewWords/NWF_GetNewWords，bool bFormatJson参数为true输出json格式，false为XML格式；
Json格式如下：

##Json格式内容##
[
   {
      "freq" : 152,
      "pos" : "n_new",
      "weight" : 77.884208081632579,
      "word" : "公允价值"
   },
   {
      "freq" : 71,
      "pos" : "n_new",
      "weight" : 75.102183562405372,
      "word" : "长期股权投资"
   }
]
	
	
3)处理大量文件的时候，采用批处理模式，先调用NWF_Batch_Start；循环调用NWF_Batch_AddFile NWF_Batch_AddMem添加文件或者内存，调用NWF_Batch_Complete结束处理，调用NWF_Batch_GetResult输出结果

