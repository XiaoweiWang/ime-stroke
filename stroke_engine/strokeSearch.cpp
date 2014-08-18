
#include "strokeSearch.h"


void strokeSearch::init(const char*treeFileName)
{
	if(treeFileName)
	{
		FILE*fp = fopen(treeFileName, "rb");
		if(fp != NULL)
		{
			size_t i = 0;
			while( fread(tst.getNodeBuffer(i), sizeof(TstNode), 1, fp)!= NULL)
			{
				++i;
			}
			fclose(fp);
		}
	}
	return;
	//candidateNum = 0;
	//loadTreeFile(tst, treeFileName);
	//tst.loadChineseDictUnicode(chineseDictName);
}


extern "C"{
int strokeSearch::search(const char* keyword,size_t maxCandidateNum)
{
	if(keyword == NULL)
	{
		return -1;
	}
	tst.vagueSearch(keyword,maxCandidateNum);
	size_t candidateNum = tst.getCandidateCount();
	for (size_t i = 0; i < candidateNum; i++)
	{
		//candidatesCode[i] = tst.getChineseElement(tst.getCandidateElement(i));
		candidatesCode[i] = tst.getCandidateElement(i);
	}
	//print results	
	printf("Total %d candidates",candidateNum);
	for (size_t i = 0; i<candidateNum; i++)
	{
		if ( i%10 == 0)
		{
			printf("\n");
		}
		printf("%d\t",candidatesCode[i]);
	}
	printf("\n");
	return 0;
}


int strokeSearch::search(const char* keyword,size_t maxCandidateNum,wchar_t*outputArray)
{
	if(keyword == NULL)
	{
		return -1;
	}
	tst.vagueSearch(keyword,maxCandidateNum);
	size_t candidateNum = tst.getCandidateCount();
	for (size_t i = 0; i < candidateNum; i++)
	{
		//candidatesCode[i] = tst.getCandidateElement(i);
		outputArray[i] = tst.getCandidateElement(i);
	}
	return 0;
}


}

strokeSearch::strokeSearch()
{
	TernarySearchTree tst = TernarySearchTree();
	//candidatesCode = {0};
	//candidateNum = 0;
	//treeFileName = TREE_FILE_NAME;
	//chineseDictName = CHINESE_DICT_NAME;
	//maxCandidateNum = 100;
}

extern "C"{

TernarySearchTree tst;


//void strokeSearchInit(const char*treeFileName)
void strokeSearchInit()
{
	if(TREE_FILE_NAME)
	{
		FILE*fp = fopen(TREE_FILE_NAME, "rb");
		if(fp != NULL)
		{
			size_t i = 0;
			while( fread(tst.getNodeBuffer(i), sizeof(TstNode), 1, fp)!= NULL)
			{
				++i;
			}
			fclose(fp);
		}
	}
	return;
}

int strokeSearchSearch(const char* keyword,size_t maxCandidateNum,wchar_t*outputArray)
{
	if(keyword == NULL)
	{
		return -1;
	}
	tst.vagueSearch(keyword,maxCandidateNum);
	size_t candidateNum = tst.getCandidateCount();
	for (size_t i = 0; i < candidateNum; i++)
	{
		outputArray[i] = tst.getCandidateElement(i);
	}
	return 0;
}

}