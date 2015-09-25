#include "../include/DeepClassifier.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <map>
#include "scanfile.h"


#include <stdio.h>
using namespace std;
#ifdef WIN64
#pragma comment(lib, "../../../bin/Classifier/x64/DeepClassifier.lib")
#else
#ifdef	_WIN32
#pragma comment(lib, "../../../bin/Classifier/DeepClassifier.lib")
#endif
#endif 
void keep_window_open()
{
	char c;
	printf("enter a character to exit\n");
	//cin >> c;
	getchar();
}


using std::ifstream;


void test_svmtextc(int num,string & working_path,string & path)
{
	const double ratio = 0.8;
	//const string working_path = "D:/NLPIR/Data/DeepClassifier/";
	int encoding=UTF8_CODE;//GBK_CODE
	if (!DC_Init(working_path.c_str(),encoding))
	{
		printf("Init Failed! Reason is %s\n",DC_GetLastErrorMsg());
		return ;
	}
	int handle=DC_NewInstance();
	handle=DC_NewInstance();

	std::map < string, vector<string> > class_map;
	vector<string> dirs;
	get_dirs(path, dirs);
	int  nFileCount=0;
	for (vector<string>::iterator p = dirs.begin(); p != dirs.end(); ++p) {
		string spath = path+*p+"/";
		cout << "process : "<< spath << endl;
		vector<string> files;
		get_files(spath, files);
		nFileCount+=files.size();
		class_map[*p] = files;
	}

	dirs.clear();
	printf("Start to training!\n");
	int count = 0;
	nFileCount*=ratio;
	for (std::map< string, vector<string> >::iterator p = class_map.begin(); p != class_map.end(); ++p)
	{
		const int maxindex = p->second.size() * ratio;
		for (int i = 0; i < maxindex; ++i) {
			string spath = path + p->first + "/" + p->second[i];
			//cout << "process : "<< spath<< "i"<< i <<"maxindex"<< maxindex <<endl;
			DC_AddTrainFile(p->first.c_str(), spath.c_str(),handle);
			++count;
			printf("Training %d%%(%d/%d)\r",count*100/nFileCount,count,nFileCount);
		}
	}
	//DC_AddTrainComplete();
	//printf("DC_AddTrainComplete Completed!\n");
	
	DC_Train(handle);
	printf("DC_Train Completed!\n");
	DC_Exit();
	//return ;
	///////////////////////////////////////////////////////////////////////////
	//
	//Classify
	//
	///////////////////////////////////////////////////////////////////////////
	if (!DC_Init(working_path.c_str(),encoding))
	{
		printf("Init Failed! Reason is %s\n",DC_GetLastErrorMsg());
		return ;
	}
	handle=DC_NewInstance();
	handle=DC_NewInstance();
	DC_LoadTrainResult(handle);
	
	printf("DC_LoadTrainResult Completed!\n");

	//??????????????????????????????precision??
	//unordered_map<string, int> c_info1;
	map<string, int> c_info1;
	//???????????????????
	map<string, int> c_info2;
	map<string, double> recall;
	int count_all_right = 0;
	int count_all = 0;
	for (std::map< string, vector<string> >::iterator p = class_map.begin(); p != class_map.end(); ++p) {
		c_info2[p->first] = 0;
	}

	for (std::map< string, vector<string> >::iterator p = class_map.begin(); p != class_map.end(); ++p) {
		int count_right = 0;
		int count = 0;
		const int min = p->second.size() * ratio;
		for (int i = min; i < p->second.size(); ++i) {
			//for (int i = 0; i < min; ++i) {
			string spath = path + p->first + "/" + p->second[i];
			

			string sc = DC_ClassifyFile(spath.c_str(),handle);
			++count;
			++count_all;
			c_info1[sc]++;
			//cout << p->first << endl;
			if(p->first == sc) {
				++count_right;
				++count_all_right;
			}
		}
		c_info2[p->first] = count_right;
		cout << endl;
		cout << p->first <<  "    right number : " << count_right << endl;
		//cout << "Recall Rate : " << count_right / (double)vf.size() << endl;
		recall[p->first] = count_right / (double)count;
	}
	int all = 0;
	cout << c_info1.size() << endl;
	//ofstream outfile(, ios::app);
	std::string sFile=working_path+"result.txt";
	FILE *outfile=fopen(sFile.c_str(),"ab");


	if (outfile==0) {
		printf("open outifle %s error \n",sFile.c_str());
		return;
	}
//	system_clock::time_point today = system_clock::now();
//	std::time_t tt = system_clock::to_time_t (today);
	time_t tt;
	time(&tt);
	string sTime=string(ctime(&tt));
	fprintf(outfile,"%s\nfeatures : \t%d\n",sTime.c_str(), num);
	fprintf(outfile,"class name\ttraining set\ttesting set\tprecision\trecall rate\tF value\n");

//	outfile << "class name\t"<<"training set\t"<<"testing set\t"<<"precision\t"<<"recall rate\t"<<"F value\n";
	for (std::map<string, int>::iterator p = c_info1.begin(); p != c_info1.end(); ++p) 
	{
		all += p->second;
		const double precision = c_info2[p->first] / (double)p->second;
		//fprintf(outfile,"class %s\n",p->first.c_str());
		cout << "class " << p->first << " : \n";
		//fprintf(outfile,"precision : %.2f\n",precision);
		cout << "precision : " << precision << endl;
		//fprintf(outfile,"recall rate : %.2f\n",recall[p->first]);
		cout << "recall rate : " << recall[p->first] << endl;
		cout << "F : " << precision * recall[p->first] * 2 /(recall[p->first] + precision) << endl;
		
		fprintf(outfile,"%s\t%d\t%d\t%lf\t%lf\t%lf\n",
			p->first.c_str(),
			int(class_map[p->first].size() * ratio),
			(int) (class_map[p->first].size() * (1.0-ratio)),
			precision,
			recall[p->first],
			precision * recall[p->first] * 2 /(recall[p->first] + precision)
			);

	/*	outfile << p->first << "\t" << int(class_map[p->first].size() * ratio) << "\t"
			<< (int) (class_map[p->first].size() * (1.0-ratio)) << "\t" << precision << "\t" << recall[p->first] << "\t"
			<< precision * recall[p->first] * 2 /(recall[p->first] + precision) << endl;*/
	}
	const double drecall = count_all_right / (double)count_all;
	//outfile << "total :\t" << drecall << endl << endl;
	fprintf(outfile,"total :\t%lf\n",
		drecall
		);
	//const double precision = count_all_right / (double)all;
	//cout << "total recall rate : " << drecall << endl;
	//cout << "total precision : " << precision << endl;
	//cout << "total F : " << 2 * precision * drecall /(precision + drecall) << endl;
	//cout << "total accuracy :\t" << drecall << endl;
	fclose(outfile);
	DC_Exit();
	return ;
}


int main(int argc,const char **argv)
{
	//testsvm();
	//for (int i = 700; i < 5000; i+=100)
	string corpus_path="./";
	string data_path="./";
	if (argc>=2)
	{
		data_path=argv[1];
	}
	if (argc>=3)
	{
		corpus_path=argv[2];
	}
	test_svmtextc(800,data_path,corpus_path);

	//vector<string> t;
	//char_separator(t, "I love 000 haha!", " \n\t");
	//for_each(t.begin(), t.end(), [&t](string c){cout << c << endl;});

	keep_window_open();
	return 0;
}