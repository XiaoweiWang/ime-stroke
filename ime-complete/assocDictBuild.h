#ifndef ASSOC_DICT_BUILD_H
#define	ASSOC_DICT_BUILD_H

#include <iostream>
#include "assocTernaryTree.h"

//#define MAX_PHRASE_DICT_LEN 50000
//#define MAX_PHRASE_LEN 6
//#define TREE_DICT_FILE_NAME "builtTreeDict.txt"
#define ASSOC_FILE_1 "builtTreeDict1.txt"
#define ASSOC_FILE_2 "builtTreeDict2.txt"
#define ASSOC_DICT_PHRASE_1 "str1.txt"  // Extra '\n' needed at the end of the character strings file
#define ASSOC_DICT_FREQ_1 "num16bit1.txt"
#define ASSOC_DICT_PHRASE_2 "str2.txt"  // Extra '\n' needed at the end of the character strings file
#define ASSOC_DICT_FREQ_2 "num16bit2.txt"

typedef unsigned short char16;
int assocDictBuild(const char*strFileName, const char*numFileName, const char*treeAndDictFileName);

#endif