#include "strokeSearch.h"

extern "C"{

TernarySearchTree tst1;
TernarySearchTree tst2;

int strokeSearchInit()
{
	FILE*fp1 = fopen(STROKE_FILE_1, "rb");
	FILE*fp2 = fopen(STROKE_FILE_2, "rb");	
	if(!fp1||!fp2){return -1;}
	
	// read information of nodes and node number from files
	size_t nodesCount = 0;
	fread(&nodesCount, sizeof(size_t), 1, fp1);
	fread(tst1.getNodeBuffer(0),sizeof(TstNode),nodesCount,fp1);
	tst1.setNodesCount(nodesCount);
	fread(&nodesCount, sizeof(size_t), 1, fp2);
	fread(tst2.getNodeBuffer(0),sizeof(TstNode),nodesCount,fp2);
	tst2.setNodesCount(nodesCount);

	fclose(fp1);
	fclose(fp2);
	return 0;
}

int strokeSearchSearch(const char* keyword,size_t maxCandidateNum,char16*outputArray)
{
	if(keyword == NULL) {return -1;}
	if(*keyword=='?') {return -2;} //Do not consider the situation where the first stroke is a match key.
	// choose which tree to search according to the first stroke in the inquery string
	TernarySearchTree* tst = (*keyword<'p')?(&tst1):(&tst2);
	(*tst).preciseSearch(keyword);
	(*tst).vagueSearch(keyword,maxCandidateNum);
	size_t candidateNum = (*tst).getCandidateCount();
	for (size_t i = 0; i < candidateNum; i++)
	{
		outputArray[i] = (*tst).getCandidateElement(i);
	}
	return 0;
}

}