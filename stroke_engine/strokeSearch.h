#ifndef STROKE_SERACH_H
#define STROKE_SERACH_H

#include <iostream>
//#include "vector.h"
//#include <time.h>
//#include "mystring.h"
#include "arrayTernaryTree.h"


#define MAX_LINE_LEN	40
#define	MAX_CANDIDATE_NUM	64
# define TREE_FILE_NAME	"builtTree.txt"

//int arrayTernarySearch(const char* stroke);
//void loadTreeFile (TernarySearchTree &tst, const char*treeFileName);

extern "C"{
class strokeSearch
{
public:
	strokeSearch();
	//~strokeSearch();
	int search(const char* keyword,size_t maxCandidateNum);
	int search(const char* keyword,size_t maxCandidateNum,wchar_t*outputArray);
	void init(const char*treeFileName);
private:
	//char* keyword;
	TernarySearchTree tst;
	wchar_t candidatesCode[MAX_CANDIDATE_NUM];
	//size_t maxCandidateNum;
	//size_t candidateNum;
	//char* treeFileName;
	//char* chineseDictName;
};
void strokeSearchInit();
int strokeSearchSearch(const char* keyword,size_t maxCandidateNum,wchar_t*outputArray);


}

#endif