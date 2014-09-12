#include <iostream>
#include <time.h>
#include "strokeTernaryTree.h"
#include "strokeDictBuild.h"
#include "strokeSearch.h"
#include "assocTernaryTree.h"
#include "assocDictBuild.h"
#include "assocSearch.h"

extern "C" {

void testStrokeSearch(const char*stroke,char16*outputArray)
{
	clock_t start,finish;
	double duration;
    strokeSearchInit();
	start = clock();
	for (size_t i = 0 ; i<10000;i++)
	{
      strokeSearchSearch(stroke,50,outputArray);
	}
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf( "%f seconds\n", duration );
	return;
}
  
void testAssocSearch(char16*keyword, char16*resultArray)
{
	clock_t start,finish;
	double duration;
	assocSearchInit();
	start = clock();
	for (size_t i =0; i<10000;i++)
	{
		assocSearchSearch(keyword,50,resultArray);
	}
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf( "%f seconds\n", duration );
	return;
}

int main(int argc, char* argv[]) {

	//Stroke search for single character.
	char stroke[256] = "szpn";
	if (argc > 1) {
	  strncpy(stroke, argv[1], 256);
	}
	char16 output [100]={};
	//int successStrokeBuild1 = strokeDictBuild(STROKE_DICT_STROKE_1, STROKEC_DICT_CHAR_1,STROKE_FILE_1);
	//int successStrokeBuild2 = strokeDictBuild(STROKE_DICT_STROKE_2, STROKEC_DICT_CHAR_2,STROKE_FILE_2);
	strokeSearchInit();
	strokeSearchSearch(stroke,50,output);
	//testStrokeSearch(stroke,output);

	//Associative search for phrases.
	char16 keyword[6] = {19981,26159,0,0,0,0};
	//char16 keyword[6] = {25509,0,0,0,0,0};
	char16 resultArray[50 * MAX_PHRASE_LEN] = {};
	//int successAssocBuild1 = assocDictBuild(ASSOC_DICT_PHRASE_1, ASSOC_DICT_FREQ_1, ASSOC_FILE_1);
	//int successAssocBuild2 = assocDictBuild(ASSOC_DICT_PHRASE_2, ASSOC_DICT_FREQ_2, ASSOC_FILE_2);
	assocSearchInit();
	assocSearchSearch(keyword,50,resultArray);
	//testAssocSearch(keyword,resultArray);

	return 0;
}

}