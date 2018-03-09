
#include "../API/LJClassifier.h"
//#include "../ICTClassifier/ICTClassifier.h"

#ifdef _DEBUG
#pragma comment(lib, "../../../bin/Classifier/LJClassifierD.lib")    // debug��������LJClassifierD.lib��
#else
#pragma comment(lib, "../../../bin/Classifier/LJClassifier.lib")     // release��������LJClassifier.lib��
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
	d.sTitle = "�������ֻ�����E600";  
	d.sContent = "ȫ�����бر�:�������ֻ�����E600 ���� 2011-9-26 15:53�ֻ�������������ʹ������ߵĵ��Ӳ�Ʒ,����»����ٶȸ��ǿ���޷�������ô�������������߶���,Ӧ�����ѡ����? ��Ȼ,Ƶ���Ļ����Ƿǳ��������,�����������֧,ƽ����������������,�����ڹ���֮����Ӧ��ѡ��һ����������������ֻ���..."; 

	d.sAuthor = "����";
	d.sBoard = "69"; 
	d.sDatatype = "��̳";

	string sResult = classifier_exec(d);
	printf("\n���˽���� %s\n\n", sResult.c_str());

	vector<string> vsItems;
	gfn_bSplit(sResult.c_str(), vsItems, "\t");

	for(int i=0; i<vsItems.size(); i++) {              //������������ڴ�

		string sDetail = classifier_detail(vsItems[i].c_str());
		printf("�������ɣ� %s\n", sDetail.c_str());

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


//// DemoDos.cpp : �������̨Ӧ�ó������ڵ㡣
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
//	d.sTitle = "8����ͯ�����˿� AƬ �����4��Ůͯ";  
//	d.sContent = "Ӧ�û��ý����º��Ӳ�Ҫ��ɫ��Ƭ������Ժ��Ӳ���"; 
//
//	//d.sAuthor = "����";
//	//d.sBoard = "69"; 
//	//d.sDatatype = "��̳";
//
//	string sResult = classifier_exec(&d);
//	printf("%s\n", sResult.c_str());
//
//	vector<string> vsItems;
//	gfn_bSplit(sResult.c_str(), vsItems, " ");
//
//	for(int i=0; i<vsItems.size(); i++) {              //������������ڴ�
//
//		string sDetail = classifier_detail(vsItems[i].c_str());
//		printf("%s\n", sDetail.c_str());
//
//	}
//
///*	stDoc d;
//	d.sTitle = "ɥ������һ����ƭ��";  
//	d.sContent = "�и����Դӵ���֤�����ϯ����������һֱ�µ���Ŀǰ�����ж�ҹ�˾����άȨ�����ϣ��������ߵ��������Ժ������֤�������.��.�֣�������֤���Ӧ�ñ��ҵ���ֻ��֤��ᱻȡ���Ժ󣬹��в������ǡ�"; 
//	d.sContent = "  \
//	81��������56���е���������ǰʮ����������������  \
//	����  \
//	���й�ƽ����601318.SH��6��27�յ���50Ԫ�������й����ʽ������޹�˾���³ơ��н𡱣��Ϻ�������·֤ȯӪҵ������Ӱ���й�ƽ����ƵƵ��û�������ְ������롢�������ϯλ���ס�\
//	�Ϻ�֤ȯ������������Ϣ��ʾ����Ӫҵ��������13770.3��Ԫ������ң���ͬ���й�ƽ������������ϯλ֮�׵�ͬʱ������10638.02��Ԫ������ϯλ֮�ף��ϼƾ�����3132.28��Ԫ�������й�ƽ���ɽ���Ϊ25.73��Ԫ��\
//	���й�ƽ�����ڵ��µ������У���Ӫҵ������ӰƵƵ��û����Topview���ݣ���6��27���й�ƽ������50Ԫ��10��28�յ�81���������У���Ӫҵ��56�γ������й�ƽ�������������ǰʮλ֮�У���������5��Ԫ��������10��6����28�գ���Ӫҵ������ֳ�������״̬���ۼƾ�����ӽ�1.09��Ԫ��\
//	����֤ȯ������ҵ�о�Ա��������Ϊ���й�ƽ��������ͣ��Ӧ�ò��ǻ���������ʲô�仯����Ҫ����Ϊ�������󡣻����Ľ�������ڿ��������й�ƽ�����ǣ������䳤�����Ʋ�����̫��Ӱ�졣�������������г���Ͷ�ʽǶȿ����й�ƽ�����Ǻܲ���ġ�\
//	���й�ƽ������������������н���Ϊ���������Ŀ�ı䶯��ҪԴ�������ȱ��������Ƚ�������Ͷ����������񻯺ͶԸ�ͨͶ�ʼ����ֵ׼����Ŀǰ�о��ʹ�ֵ�ѽӽ���ʷ�ײ��������ڻ����������Խ��Ͼ��������й�����H�ɣ�02628.HK��1.5�����о�����ʷ���ֵ���й�ƽ���ɼ������µ��ռ䡣\
//	׫���ˣ�\
//	֣����������һ�ƾ���վ�������ݲ���ΪͶ������,�����ο�,�ݴ�����,�����Ե���";
//	
//	d.sAuthor = "����";
//	d.sBoard = "69"; 
//	d.sDatatype = "����";
//
//	string sResult = classifier_exec(&d);
//	printf("%s\n", sResult.c_str());
//
//	vector<string> vsItems;
//	gfn_bSplit(sResult.c_str(), vsItems, " ");
//
//	for(int i=0; i<vsItems.size(); i++) {              //������������ڴ�
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
//	//		free(lpszFileText);                                //�����Ƕ�ȡcache��ÿһ����������    
//
//	//		string sResult = classifier_exec(&d, 1);
//	//		printf("%d: %s\n", iDocCount++, sResult.c_str());		
//
//	//		vector<string> vsItems;
//	//		gfn_bSplit(sResult.c_str(), vsItems, "\t");
//
//	//		for(int i=0; i<vsItems.size(); i++) {              //������������ڴ�
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
