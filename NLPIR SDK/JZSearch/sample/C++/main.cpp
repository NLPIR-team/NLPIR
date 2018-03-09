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
const int encoding = INDEX_ENCODING_GBK; // Ŀǰ����ʹ��utf-8���뻹������������ԭ�����Ų�

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
		//�ж��Ƿ�����Ŀ¼
		if (FileInfo.attrib & _A_SUBDIR)
		{
			//���������Ҫ
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
			printf("������ֶ�ʧ��");
			return;
		}
	}

	// ��ʼ������Ҫ��֤ȫ��ִֻ��һ��
	if (JZIndexer_Init(rootDir.c_str(), "", encoding, true) == 0)
	{
		printf("������ʼ��ʧ��");
		return;
	}

	printf("������ʼ���ɹ�");
	JZIndexer_FieldAdd("key", "", FIELD_TYPE_TEXT, true, true, true, true);
	JZIndexer_FieldAdd("value", "", FIELD_TYPE_TEXT, true, true, true, true);

	if (JZIndexer_FieldSave(fieldPath.c_str()))
	{
		printf("�ֶι������");
	}
	else
	{
		printf("�ֶι���ʧ��");
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
			printf("���������ʧ��");
			return;
		}
	}

	// 2������µ������ļ�
	int flag = JZIndexer_Init(rootDir.c_str(), fieldPath.c_str(), encoding, 1); // ��ʼ������Ҫ��֤ȫ��ִֻ��һ��

	if (flag == 0)
	{
		printf("JZIndexer_Init��ʼ��ʧ��");
		return;
	}

	printf("JZIndexer_Init��ʼ���ɹ�");

	auto indexer = new(nothrow)CJZIndexer(indexPath.c_str());
	if (indexer == nullptr)
	{
		printf("JZIndexer����ʵ��ʧ��");
		return;
	}
	printf("JZIndexer����ʵ���ɹ�");

	string testFilesPath = rootDir + "test/";

	vector<string> files = GetFiles(testFilesPath, AllDirectories);
	JZSearch_SetIndexSizeLimit(-1);             // ������ǰ���ø÷���

	for (auto file : files)
	{
		string fileName = file.substr(file.find_last_of("\\") + 1);
		// string sContext = FileOperate.ReadFile(file);
		indexer->MemIndexing(fileName.c_str(), "key", 0);
		// search.JZIndexer_MemIndexing(handle, sContext, "value", 0);
		indexer->FileIndexing(file.c_str(), "value");

		if (indexer->AddDoc() < 1)
		{
			printf("�������ʧ�ܣ�%s\n", fileName.c_str());
			return;
		}
		printf("������ӳɹ���%s\n", fileName.c_str());
	}

	indexer->Save();
	delete indexer;
	JZIndexer_Exit();
	printf("�����������\n");
}

void StartSearch(string keyword = "")
{
	if (handle < 0)
	{
		// ��ʼ������Ҫ��֤ȫ��ִֻ��һ��
		handle = JZSearch_Init(indexPath.c_str(), rootDir.c_str(), fieldPath.c_str(), 512000000, encoding, 0, true);
		if (handle < 0)
		{
			return;
		}

	}
	auto searcher = new(nothrow)CJZSearcher(SORT_TYPE_RELEVANCE);
	if (searcher == nullptr)
	{
		printf("JZSearcher����ʵ��ʧ�ܣ�������");
		return;
	}
	printf("JZSearcher_NewInstance����ʵ���ɹ�");

	JZSearch_SetAbstractArgu(1000, "", "", 0);
	string query = "[cmd] listall";
	if (!keyword.empty())
	{
		printf("��ʼ�Թؼ��֡�%s����������", keyword.c_str());
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
		printf("�����ֶΣ����룺0");
		printf("�������������룺1");
		printf("���������룺2");
		printf("�г������������ݣ�3");
		printf("�˳������룺����");
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
				printf("�������������ݣ�");
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