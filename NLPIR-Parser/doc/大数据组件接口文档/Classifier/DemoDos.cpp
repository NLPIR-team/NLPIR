
#include "../API/LJClassifier.h"
//#include "../ICTClassifier/ICTClassifier.h"

#ifdef _DEBUG
#pragma comment(lib, "../../../bin/Classifier/LJClassifierD.lib")    // debug版编译采用LJClassifierD.lib库
#else
#pragma comment(lib, "../../../bin/Classifier/LJClassifier.lib")     // release版编译采用LJClassifier.lib库
#endif

#include <string>
#include <vector>
using namespace std;
#pragma warning(disable:4786)	

bool gfn_bSplit(const char* lpszText, vector<string>& vResult, const char* lpszDelimiter);
int main(int argc, char* argv[])
{

	if(!classifier_init("rulelist.xml")) {
		printf("classifier_init failed!\n");
		return 1;
	}

	stDoc d;
	d.sTitle = "天翼定制手机天语E600";  
	d.sContent = "全球旅行必备:天翼定制手机天语E600 新浪 2011-9-26 15:53手机——这项人们使用率最高的电子产品,其更新换代速度更是快得无法想象。那么对于我们消费者而言,应当如何选择呢? 显然,频繁的换机是非常不划算的,更会增加生活开支,平白增添生活负担。因此,我们在购机之初就应当选择一款满足自身需求的手机。..."; 

	d.sAuthor = "飞香";
	d.sBoard = "69"; 
	d.sDatatype = "论坛";

	string sResult = classifier_exec(d);
	printf("\n过滤结果： %s\n\n", sResult.c_str());

	vector<string> vsItems;
	gfn_bSplit(sResult.c_str(), vsItems, "\t");

	for(int i=0; i<vsItems.size(); i++) {              //保存分类结果到内存

		string sDetail = classifier_detail(vsItems[i].c_str());
		printf("过滤理由： %s\n", sDetail.c_str());

	}

	classifier_exit();	

	printf("Please input enter to quit...");
	getchar();

	return 0;
}

bool gfn_bSplit(const char* lpszText, vector<string>& vResult, const char* lpszDelimiter) {

	vResult.clear();

	int iOldSize = strlen(lpszText);
	if(!lpszText || (iOldSize==0))
		return false;

	int iDeSize = strlen(lpszDelimiter);
	if(!lpszDelimiter || (iDeSize==0)) {
		vResult.push_back(lpszText);
		return true;
	}//if

	char* pOccur = strstr((char*)lpszText, lpszDelimiter);
	if(!pOccur) {
		vResult.push_back(lpszText);
		return true;
	}

	int iSize = pOccur-lpszText;

	char* pSeg = new char[iOldSize+1];
	memset(pSeg, 0, iOldSize+1);

	pSeg = strncpy(pSeg, lpszText, iSize);

	if(strlen(pSeg) > 0) {
		vResult.push_back(pSeg);
	}//if

	pOccur += iDeSize;
	char* pOldOccur = pOccur;

	while(pOccur) {
		pOccur = strstr(pOccur, lpszDelimiter);
		if(!pOccur) {
			if(strlen(pOldOccur) > 0)
				vResult.push_back(pOldOccur);

			break;
		}

		iSize = pOccur - pOldOccur;
		memset(pSeg, 0, iOldSize+1);
		pSeg = strncpy(pSeg, pOldOccur, iSize);

		if(strlen(pSeg) > 0) {
			vResult.push_back(pSeg);
		}

		pOccur += iDeSize;
		pOldOccur = pOccur;
	}//while

	delete pSeg;

	return true;
}//gfn_bSplit


//// DemoDos.cpp : 定义控制台应用程序的入口点。
////
//#include "../ICTClassifier/ICTClassifier.h"
//#include "ReadData.h"
//
//#pragma comment(lib, "../bin/LJClassifier.lib")
//
//typedef struct _stDocResult {
//
//    stDoc theDoc;
//	string sDetail;
//
//}stDocResult;
//
//time_t tBegin,tEnd;
//
//int main(int argc, char* argv[])
//{
//	//if (argc != 2){
//	//	printf("usage: DemoDos <TestDataDir>\n");
//	//	return 1;
//	//}
//
///*	if(!classifier_db_ruleread()) {
//		printf("classifier_db_ruleread failed!\n");
//		return 1;
//	}
//*/
//	if(!classifier_init("rulelist.xml", "LingJoinClassifier*~!@#%&&%#@!~*")) {
//        printf("classifier_init failed!\n");
//		return 1;
//	}
//
//	stDoc d;
//	d.sTitle = "8岁男童跟大人看 A片 后猥亵4岁女童";  
//	d.sContent = "应该还好教育下孩子不要看色情片，否则对孩子不好"; 
//
//	//d.sAuthor = "飞香";
//	//d.sBoard = "69"; 
//	//d.sDatatype = "论坛";
//
//	string sResult = classifier_exec(&d);
//	printf("%s\n", sResult.c_str());
//
//	vector<string> vsItems;
//	gfn_bSplit(sResult.c_str(), vsItems, " ");
//
//	for(int i=0; i<vsItems.size(); i++) {              //保存分类结果到内存
//
//		string sDetail = classifier_detail(vsItems[i].c_str());
//		printf("%s\n", sDetail.c_str());
//
//	}
//
///*	stDoc d;
//	d.sTitle = "丧福林是一个大骗子";  
//	d.sContent = "尚福林自从担任证监会主席以来，股市一直下跌；目前，已有多家公司进行维权和诉讼，甚至上诉到最高人民法院，控诉证贱会和尚.福.林，这样的证监会应该被砸掉，只有证监会被取缔以后，股市才能上涨。"; 
//	d.sContent = "  \
//	81个交易日56次列单日买卖额前十，昨包揽买卖额榜首  \
//	任亮  \
//	自中国平安（601318.SH）6月27日跌破50元以来，中国国际金融有限公司（下称“中金”）上海淮海中路证券营业部的身影在中国平安上频频出没，昨日又包揽买入、卖出金额席位榜首。\
//	上海证券交易所公开信息显示，该营业部在买入13770.3万元（人民币，下同）中国平安而居买入金额席位之首的同时，又以10638.02万元居卖出席位之首，合计净买入3132.28万元。昨日中国平安成交额为25.73亿元。\
//	在中国平安近期的下跌过程中，该营业部的身影频频出没。据Topview数据，自6月27日中国平安跌破50元至10月28日的81个交易日中，该营业部56次出现在中国平安单日买卖金额前十位之中，净卖出逾5亿元。不过，10月6日至28日，该营业部则呈现出净买入状态，累计净买入接近1.09亿元。\
//	东海证券保险行业研究员陶正傲认为，中国平安昨日涨停，应该不是基本面上有什么变化，主要是因为跌幅过大。机构的介入短期内可能拉动中国平安大涨，但对其长期走势不会有太大影响。如果从三五年的中长期投资角度看，中国平安还是很不错的。\
//	从中国平安三季报情况分析，中金认为，利润表项目的变动主要源于三季度保费收入稳健增长、投资收益持续恶化和对富通投资计提减值准备。目前市净率估值已接近历史底部，但由于基本面形势仍较严峻，参照中国人寿H股（02628.HK）1.5倍的市净率历史最低值，中国平安股价仍有下调空间。\
//	撰稿人：\
//	郑重声明：第一财经网站所载内容不作为投资依据,仅供参考,据此入市,风险自担。";
//	
//	d.sAuthor = "飞香";
//	d.sBoard = "69"; 
//	d.sDatatype = "博客";
//
//	string sResult = classifier_exec(&d);
//	printf("%s\n", sResult.c_str());
//
//	vector<string> vsItems;
//	gfn_bSplit(sResult.c_str(), vsItems, " ");
//
//	for(int i=0; i<vsItems.size(); i++) {              //保存分类结果到内存
//
//		string sDetail = classifier_detail(vsItems[i].c_str());
//		printf("%s\n", sDetail.c_str());
//	
//	}
//*/
//	//time(&tBegin);
//
//	//ReadData theReadData(argv[1]);
//	//vector<string> vsFolderName;
//	//theReadData.fn_vScanFolders(vsFolderName);
//
//	//for(int i=0; i<vsFolderName.size(); i++) {	
//	//	theReadData.fn_vScanXmlFiles(vsFolderName[i]);
//	//}
//
//	//gfn_bCleanDirectory("./output");
//
//	//int iDocCount = 0;
//	//string sLog;
//	//for(int i=0; i<theReadData.m_vsXmlFileName.size(); i++) {
//
//	//	sLog += theReadData.m_vsXmlFileName[i];
//	//	sLog += "\n";
//	//	gfn_bWriteFile("log.txt", sLog.c_str());
//	//	
//	//	list<stItem> theItems;
//	//	theReadData.fn_iGetItems(theItems, theReadData.m_vsXmlFileName[i]);
//
//	//	string sTextFileName = theReadData.m_vsXmlFileName[i];
//	//	gfn_vReplaceSubstr(sTextFileName, ".xml", ".txt");
//
//	//	FILE* fp = fopen(sTextFileName.c_str(), "rb");
//	//	if(!fp)
//	//		continue;
//
//	//	list<stItem>::iterator it = theItems.begin();
//	//	for(; it!=theItems.end(); it++) {
//
//	//		stDoc d;
//	//		d.sTitle = it->sTitle;
//	//		d.sAuthor = it->sAuthor;
//	//		char buf[MAX_FILE_PATH];
//	//		itoa(it->iBoardcode, buf, 10);			
//	//		d.sBoard = buf;
//	//		itoa(it->iGroupid, buf, 10);		
//	//		d.sDatatype = buf;
//
//	//		gfn_bReadFile(sTextFileName.c_str(), d.sContent);
//
//	//		long lTxtlen = it->iTxtlen;
//	//		long lOffset = it->i64Txtoffset;
//
//	//		char* lpszFileText = (char*)calloc(lTxtlen+1, sizeof(char));
//	//		if(!lpszFileText) {
//	//			fclose(fp);
//	//			return false;
//	//		}
//
//	//		memset(lpszFileText, 0, lTxtlen+1);
// //
// //           fseek(fp, lOffset, SEEK_SET);
//	//		fread(lpszFileText, sizeof(char), lTxtlen,fp);
//
//	//		d.sContent = lpszFileText;
//	//		free(lpszFileText);                                //以上是读取cache下每一个文章内容    
//
//	//		string sResult = classifier_exec(&d, 1);
//	//		printf("%d: %s\n", iDocCount++, sResult.c_str());		
//
//	//		vector<string> vsItems;
//	//		gfn_bSplit(sResult.c_str(), vsItems, "\t");
//
//	//		for(int i=0; i<vsItems.size(); i++) {              //保存分类结果到内存
//
//	//			vector<string> vsItem2;
//	//			gfn_bSplit(vsItems[i].c_str(), vsItem2, " ");
//	//			if(vsItem2.size() != 2)
//	//				continue;
//
//	//			string sTextFileName = "./output/" + vsItem2[0] + ".xml";
//	//			string sTextContent = "";
//	//			sTextContent += "<doc>\n\t<title>";
//	//			sTextContent += d.sTitle;
//	//			sTextContent += "</title>\n\t<author>";
//	//			sTextContent += d.sAuthor;
//	//			sTextContent += "</author>\t<board>";
//	//			sTextContent += d.sBoard;
//	//			sTextContent += "</board>\t<datatype>";
//	//			sTextContent += d.sDatatype;
//	//			sTextContent += "</datatype>\n\t<certainty>";
//	//			sTextContent += vsItem2[1];
//	//			sTextContent += "</certainty>\n\t<ruledetail>\n";
//	//			sTextContent += classifier_detail(vsItem2[0].c_str());		
//	//			sTextContent += "\t</ruledetail>\n\t<content>\n";
//	//			sTextContent += d.sContent;
//	//			sTextContent += "\n\t</content>\n</doc>\n\n";
//	//			FILE* fp1 = fopen(sTextFileName.c_str(), "a+");
//	//			if(!fp1) continue;
//	//			fprintf(fp1, "%s", sTextContent.c_str());
//	//			fclose(fp1);
//	//			
//	//		}
//
//	//	}
//
//	//	fclose(fp);
//
//	//}
//
//	//sLog += "[End]\nTotal Count: ";
//	//char buf[MAX_FILE_PATH];
//	//itoa(iDocCount, buf, 10);
//	//sLog += buf;
//
//	//time(&tEnd);
//	//double fDiff = difftime(tEnd, tBegin);
//	//char sDiff[10];
//	//sprintf(sDiff, "%.1f", fDiff);
//
//	//sLog += "\nTime: ";
//	//sLog += sDiff;
//
//	//gfn_bWriteFile("log.txt", sLog.c_str());
//
//
//	classifier_exit();	
//
//	printf("Please input enter to quit...");
//	getchar();
//	
//	return 0;
//}
//
