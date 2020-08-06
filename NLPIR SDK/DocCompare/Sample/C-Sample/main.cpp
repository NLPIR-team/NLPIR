#include "include/DocCompare.h"
#include <string>
#include <vector>
#include <time.h>

#ifdef WIN64
#pragma comment(lib, "../../../bin/DocCompare/x64/DocCompare.lib")
#else
#pragma comment(lib, "../../../bin/DocCompare/DocCompare.lib")
#endif
int main()
{
    std::vector<std::string> filelist = {
		"D:\\NLPIR\\test\\compare\\doc.doc",
        
	};
	std::vector<std::string> testfiles = 
	{
		"D:\\NLPIR\\test\\compare\\pdf.pdf"
	};

    if(DC_Init("D:\\NLPIR")!=1)
    {
        printf("初始化失败!错误原因是：%s\n",DC_GetLastErrorMsg());
        return -1;
    }
    printf("初始化成功！\n");
    DC_HANDLE test = DC_NewInstance("D:\\NLPIR\\test\\compare\\", false);//第一个参数为结果存放路径，第二个参数选择的是XML存储
    double start = clock();
    size_t length = filelist.size();
    const bool isTestFile = true;
	DC_Cmp2Files(test, testfiles[0].c_str(), filelist[0].c_str());//比较两个文件，比较结果存放在指定路径


	printf("耗时：%.2fs\n", (clock() - start) / CLOCKS_PER_SEC);


    for(size_t i = 0; i < length; i++)
    {
		if (DC_AddFile2Lib(test, filelist[i].c_str()))//加载待比较的文件进入模板库
		{
			printf("%s 加载完成(%zd)\n", filelist[i].c_str(), i + 1);
		}
		else
		{
			printf("%s 加载失败(X)\n", filelist[i].c_str());
		}
    }

	DC_Cmp2Files(test, testfiles[0].c_str(), filelist[0].c_str());//将指定的文件与模板库大批量数据进行比较，得到结果存储在指定路径下


    printf("耗时：%.2fs\n", (clock() - start) / CLOCKS_PER_SEC);
	DC_DeleteInstance(test);
    DC_Exit();

    //system("pause");
    return 0;
}