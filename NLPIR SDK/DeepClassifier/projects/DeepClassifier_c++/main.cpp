#ifdef _WIN64
#pragma comment(lib, "../lib/win64/DeepClassifier.lib")
#else
#pragma comment(lib, "../lib/win32/DeepClassifier.lib")
#endif

#include <cstdio>
#include <string>
#include <vector>
#include <io.h>
#include "DeepClassifier.h"

using namespace std;

enum SearchOption
{
	TopDirectoryOnly = 0,
	AllDirectories = 1,
};

void GetDirectories(string folderPath, vector<string> &dirs, SearchOption op)
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
				dirs.push_back(newPath);
				if (op == AllDirectories)
				{
					GetDirectories(newPath, dirs, op);
				}
			}
		}
	} while (_findnext(Handle, &FileInfo) == 0);
	_findclose(Handle);
}

vector<string> GetDirectories(string folderPath, SearchOption op = TopDirectoryOnly)
{
	vector<string> dirs;
	GetDirectories(folderPath, dirs, op);
	return dirs;
}

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

void Train()
{
	if (DC_Init("..\\", 0, 800, ""))
	{
		printf("��ʼ���ɹ�\n");
	}
	else
	{
		printf("��ʼ��ʧ�ܣ�%s", DC_GetLastErrorMsg());
		printf("\n�����������...\n");
		getchar();
		return;
	}

	vector<string> dirs = GetDirectories("..\\test\\ѵ������");
	for (auto dir : dirs)
	{
		string className = dir.substr(dir.find_last_of("\\") + 1);
		vector<string> files = GetFiles(dir);

		for (auto file : files)
		{
			DC_AddTrainFile(className.c_str(), file.c_str());
		}
	}

	DC_Train();
	DC_Exit();
}

void Classify()
{
	if (DC_Init("..\\", 1, 800, ""))
	{
		printf("��ʼ���ɹ�\n");
	}
	else
	{
		printf("��ʼ��ʧ�ܣ�%s", DC_GetLastErrorMsg());
		printf("\n�����������...\n");
		getchar();
		return;
	}

	DC_LoadTrainResult();

	string testFile = "..\\test\\test.txt";
	string result = DC_ClassifyFile(testFile.c_str());
	printf("��������%s", result.c_str());
	printf("\n");

	DC_Exit();
}


int main(void)
{
	Train();
	Classify();
	getchar();

	return 0;
}

