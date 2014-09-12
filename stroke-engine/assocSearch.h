#ifndef ASSOC_SEARCH
#define ASSOC_SEARCH

#include "assocTernaryTree.h"
#include "assocDictBuild.h"
#include <iostream>

extern "C" {

int assocSearchInit();
int assocSearchSearch(char16* keyword,size_t maxCandidateNum, char16 * resultArray);

}

#endif

