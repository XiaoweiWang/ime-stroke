#ifndef STROKE_SERACH_H
#define STROKE_SERACH_H

#include <iostream>
#include "strokeTernaryTree.h"
#include "strokeDictBuild.h"

extern "C"{

int strokeSearchInit();
int strokeSearchSearch(const char* keyword,size_t maxCandidateNum, char16*outputArray);

}

#endif