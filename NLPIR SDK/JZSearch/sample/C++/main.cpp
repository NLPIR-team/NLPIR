#ifdef _WIN64
#pragma comment(lib, "../lib/win64/JZSearchAPI.lib")
#else
#pragma comment(lib, "../lib/win32/JZSearchAPI.lib")
#endif

#include <cstdio>
#include <string>
#include <iostream>
#include <sstream>
#include "JZSearchAPI.h"
#include <io.h>
#include <direct.h>

using namespace std;

const string rootDir = "../";
const string indexDir = rootDir + "Index/";
const string indexPath = indexDir + "JZSearch";
const string fieldDir = rootDir + "Field/";
const string fieldPath = fieldDir + "field.dat";
const int encoding = INDEX_ENCODING_GBK; // 目前测试使用utf-8编码还有乱码的情况，原因还在排查

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

vector<string> GetFiles(string folderPath, SearchOption op = TopDirectoryOnly)
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
	JZIndexer_FieldAdd("key", "", FIELD_TYPE_TEXT, true, true, true, true);
	JZIndexer_FieldAdd("value", "", FIELD_TYPE_TEXT, true, true, true, true);

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
		return;
	}

	printf("JZIndexer_Init初始化成功");

	auto indexer = new(nothrow)CJZIndexer(indexPath.c_str());
	if (indexer == nullptr)
	{
		printf("JZIndexer生成实例失败");
		return;
	}
	printf("JZIndexer生成实例成功");

	string testFilesPath = rootDir + "test/";

	vector<string> files = GetFiles(testFilesPath, AllDirectories);
	JZSearch_SetIndexSizeLimit(-1);             // 建索引前调用该方法

	for (auto file : files)
	{
		string fileName = file.substr(file.find_last_of("\\") + 1);
		// string sContext = FileOperate.ReadFile(file);
		indexer->MemIndexing(fileName.c_str(), "key", 0);
		// search.JZIndexer_MemIndexing(handle, sContext, "value", 0);
		indexer->FileIndexing(file.c_str(), "value");

		if (indexer->AddDoc() < 1)
		{
			printf("索引添加失败：%s\n", fileName.c_str());
			return;
		}
		printf("索引添加成功：%s\n", fileName.c_str());
	}

	indexer->Save();
	delete indexer;
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
	auto searcher = new(nothrow)CJZSearcher(SORT_TYPE_RELEVANCE);
	if (searcher == nullptr)
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
	string xml = searcher->Search(query.c_str(), 0, 10);
	cout << xml << endl;

	delete searcher;
}

int main(void)
{
	while (true)
	{
		printf("建立字段，输入：0");
		printf("建立索引，输入：1");
		printf("搜索，输入：2");
		printf("列出所有索引内容：3");
		printf("退出，输入：其他");
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
				cin >> keyword;
				StartSearch(keyword);
				break;
			}

			case 3:
				StartSearch();
				break;

			default:
				break;
		}
	}
}