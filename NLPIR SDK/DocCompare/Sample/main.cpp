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
        "E:\\tmp\\contract_in/my\\劳务合同（5）.docx",
        "../../..\\bin\\DocCompare\\test\\500.txt",
		"../../..\\bin\\DocCompare\\test\\498.txt",
		"../../..\\bin\\DocCompare\\test\\497.txt",
	};
	std::vector<std::string> testfiles = {
		"../../..\\bin\\DocCompare\\test\\test.txt"
	};

    if(!DocComp_Init())
    {
        printf("初始化失败\n");
        return 1;
    }
    void * test = DocComp_NewInstance("./", "./", false);
    DocComp_setConvertexeDir(test, "E:\\code\\GIT/");
    DocComp_setOutputDir(test, "E:\\tmp\\contract_out/");
    
    double start = clock();
    size_t length = filelist.size();
    const bool isTestFile = true;
    for(size_t i = 0; i < length; i++)
    {
        if(DocComp_ImportTemplate(test, filelist[i].c_str()))
            printf("%s 加载完成(%zd)\n", filelist[i].c_str(), i + 1);
        else
            printf("%s 加载失败(X)\n", filelist[i].c_str());
    }

    DocComp_compareDoc2Files(test, testfiles[0].c_str(), filelist[0].c_str());

    printf("耗时：%.2fs\n", (clock() - start) / CLOCKS_PER_SEC);

    DocComp_Exit(test);

    //system("pause");
    return 0;
}