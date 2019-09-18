#ifdef _WIN64
#pragma comment(lib, "..\\..\\..\\bin\\JZSearch\\x64\\JZSearchAPI.lib")
#else
#pragma comment(lib, "../lib/win32/JZSearchAPI.lib")
#endif

#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include "../API/JZSearchAPI.h"
#include <io.h>
#include <direct.h>

using namespace std;

const string rootDir = "D:\\NLPIR\\JZSearchInstall\\dict\\";//搜索词典存放地址，改地址下面有个Data目录
const string testFilesPath = rootDir + "../test/境内新闻(20181212)/";//测试的文本文件所在路径
const string indexDir = rootDir + "../indexfile/";//索引存储的地址
const string indexPath = indexDir + "JZSearch";//索引名称
const string fieldDir = rootDir + "../Field/";//字段存储的地址
const string fieldPath = fieldDir + "field.dat";//字段存储的文件名
const int encoding = INDEX_ENCODING_GBK; // 编码信息
SEARCHER_HANDLE handle = -1;

enum SearchOption
{
	TopDirectoryOnly = 0,
	AllDirectories = 1,
};

void GetFiles(string folderPath, vector<string> &files, SearchOption op)
{
	_finddata_t FileInfo;
	string strfind = folderPath + "\\*";
	intptr_t Handle = _findfirst(strfind.c_str(), &FileInfo);

	if (Handle == -1L)
	{
		return;
	}
	do
	{
		//判断是否有子目录
		if (FileInfo.attrib & _A_SUBDIR)
		{
			//这个语句很重要
			if ((strcmp(FileInfo.name, ".") != 0) && (strcmp(FileInfo.name, "..") != 0))
			{
				string newPath = folderPath + "\\" + FileInfo.name;
				if (op == AllDirectories)
				{
					GetFiles(newPath, files, op);
				}
			}
		}
		else
		{
			files.push_back(folderPath + "\\" + FileInfo.name);
		}
	} while (_findnext(Handle, &FileInfo) == 0);
	_findclose(Handle);
}

vector<string> GetFiles(string folderPath, SearchOption op = AllDirectories)
{
	vector<string> files;
	GetFiles(folderPath, files, op);
	return files;
}

void CreateField()
{
	if (!_access(fieldDir.c_str(), _A_NORMAL))
	{
		_mkdir(fieldDir.c_str());
	}
	else
	{
		ostringstream ss;
		ss << "rm -rf " << "\"" << fieldDir << "\"";
		system(ss.str().c_str());

		if (_access(fieldDir.c_str(), _A_NORMAL))
		{
			printf("清除旧字段失败");
			return;
		}
	}

	// 初始化函数要保证全局只执行一次
	if (JZIndexer_Init(rootDir.c_str(), "", encoding, true) == 0)
	{
		printf("索引初始化失败");
		return;
	}

	printf("索引初始化成功");
	JZIndexer_FieldAdd("id", "", FIELD_TYPE_INT, true, true);
	JZIndexer_FieldAdd("key", "", FIELD_TYPE_TEXT, true, true);
	JZIndexer_FieldAdd("text", "", FIELD_TYPE_TEXT, true, true);
	JZIndexer_FieldAdd("value", "", FIELD_TYPE_FLOAT, true, true);

	if (JZIndexer_FieldSave(fieldPath.c_str()))
	{
		printf("字段构建完毕");
	}
	else
	{
		printf("字段构建失败");
	}
	JZIndexer_Exit();
	printf("");
}

void StartIndex()
{
	if (!_access(indexDir.c_str(), _A_NORMAL))
	{
		_mkdir(indexDir.c_str());
	}
	else
	{
		ostringstream ss;
		ss << "rm -rf " << "\"" << indexDir << "\"";
		system(ss.str().c_str());

		if (_access(indexDir.c_str(), _A_NORMAL))
		{
			printf("清除旧索引失败");
			return;
		}
	}

	// 2、添加新的索引文件
	int flag = JZIndexer_Init(rootDir.c_str(), fieldPath.c_str(), encoding, 1); // 初始化函数要保证全局只执行一次

	if (flag == 0)
	{
		printf("JZIndexer_Init初始化失败");
		JZIndexer_Exit();
		return;
	}

	printf("JZIndexer_Init初始化成功");

	JZSEARCH_HANDLE indexer = JZIndexer_NewInstance(indexPath.c_str());
	if (indexer<0)
	{
		printf("JZIndexer生成实例失败");
		JZIndexer_DeleteInstance(indexer);
		JZIndexer_Exit();

		return;
	}
	printf("JZIndexer生成实例成功");

	

	vector<string> files = GetFiles(testFilesPath, AllDirectories);
	JZSearch_SetIndexSizeLimit(-1);             // 建索引前调用该方法

	int i = 0;
	char sVal[10];
	for (auto file : files)
	{
		string fileName = file.substr(file.find_last_of("\\") + 1);
		// string sContext = FileOperate.ReadFile(file);
		JZIndexer_MemIndexing(indexer,fileName.c_str(), "key", 0);
		// search.JZIndexer_MemIndexing(handle, sContext, "value", 0);
		JZIndexer_FileIndexing(indexer,file.c_str(), "text");
		sprintf(sVal, "%d", i);
//		JZIndexer_IntIndexing(indexer,i, "id");
		JZIndexer_MemIndexing(indexer, sVal, "id");
		JZIndexer_FloatIndexing(indexer,i, "value");
		i++;

		if (JZIndexer_AddDoc(indexer) < 1)
		{
			printf("索引添加失败：%s\n", fileName.c_str());
			return;
		}
		printf("索引添加成功：%s\n", fileName.c_str());
	}
	JZIndexer_Save(indexer);
	JZIndexer_DeleteInstance(indexer);
	JZIndexer_Exit();
	printf("索引建立完成\n");
}

void StartSearch(string keyword = "")
{
	if (handle < 0)
	{
		// 初始化函数要保证全局只执行一次
		handle = JZSearch_Init(indexPath.c_str(), rootDir.c_str(), fieldPath.c_str(), 512000000, encoding, 0, true);
		if (handle < 0)
		{
			return;
		}

	}

	JZSEARCH_HANDLE  instance=JZSearcher_NewInstance(SORT_TYPE_RELEVANCE, handle);
	//生成实例失败，则返回为-1，否则为实例的Handle；每个多线程使用一个实例

	if (instance<0)
	{
		printf("JZSearcher生成实例失败！！！！");
		return;
	}
	printf("JZSearcher_NewInstance生成实例成功");

	JZSearch_SetAbstractArgu(1000, "", "", 0);
	string query = "[cmd] listall";
	if (!keyword.empty())
	{
		printf("开始以关键字“%s”进行搜索", keyword.c_str());
		ostringstream ss;
		ss << "[FIELD] * [OR] " << keyword << " [SORT] relevance";
		query = ss.str();
	}
	query = " [field] * [and] 区块链 [field] id [max] 6";
	////string xml = searcher->Search(query.c_str(), 0, 10);
	const char *pResult = JZSearcher_Search(instance, query.c_str(), 0, 10);
	//query_line: 查询表达式
	//nStart:记录起始地址
	//nPageCount：当前页返回结果数目
	//当前页需要返回所有的结果jason字符串
	//const char *sResultXMLFile	默认为0，否则，存储到结果文件中；added in 2
	if (pResult!=0)
	{
		cout << pResult << endl;
	}

	JZSearcher_DeleteInstance(instance);//释放实例


}

int main(void)
{
	while (true)
	{
		printf("\n建立字段，输入：0\n");
		printf("建立索引，输入：1\n");
		printf("搜索，输入：2\n");
		printf("列出所有索引内容：3\n");
		printf("退出，输入：其他\n");
		int input;
		cin >> input;

		switch (input)
		{
			case 0:
				CreateField();
				break;

			case 1:
				StartIndex();
				break;

			case 2:
			{
				printf("请输入搜索内容：");
				string keyword;
				//std::getline(std::cin, keyword);
				cin >> keyword;
				//StartSearch("[field] id [and] 3");
				StartSearch(keyword);
				break;
			}

			case 3:
				StartSearch();
				break;

			default:

				JZSearch_Exit();//全局退出才需要使用这个
				return 1;
		}
	}
}