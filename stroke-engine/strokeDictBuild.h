#ifndef STROKE_DICT_BUILD_H
#define STROKE_DICT_BUILD_H

#include <iostream>
#include <stdio.h>
#include "strokeTernaryTree.h"

#define STROKE_DICT_STROKE_1 "dictSecF_F1.txt"
#define STROKEC_DICT_CHAR_1	"dictC_F1.txt"
#define STROKE_FILE_1	"builtTree1.txt"

#define STROKE_DICT_STROKE_2 "dictSecF_F2.txt"
#define STROKEC_DICT_CHAR_2	"dictC_F2.txt"
#define STROKE_FILE_2	"builtTree2.txt"

int strokeDictBuild (const char*rawDictName, const char*chineseDictName,const char*treeFileName);

#endif