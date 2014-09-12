#include <iostream>
#include <time.h>
#include "arrayTernaryTree.h"
#include "strokeSearch.h"
//#include "dictBuild.h"
#include "assocTernaryTree.h"
//#include "build.h"
#include "assocSearch.h"
//using namespace std;


extern "C" {

void testStrokeSearch(const char*stroke,char16*outputArray)
{
	clock_t start,finish;
	double duration;
    strokeSearchInit();
	start = clock();
	for (size_t i = 0 ; i<100;i++)
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
	//wchar_t resultArray[50 * MAX_PHRASE_LEN] = {};
	start = clock();
	for (size_t i =0; i<100000;i++)
	{
		assocSearchSearch(keyword,50,resultArray);
	}
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf( "%f seconds\n", duration );
	return;
}

void directSearch(char16*resultArray)
{
	//assocSearchSearch(L"",50,resultArray);
}


int main(int argc, char* argv[]) {

  //Stroke search for single character.
  //char stroke[256] = "??????????????????????????????????????????????????";
  char stroke[256] = "s??????";
  if (argc > 1) {
    strncpy(stroke, argv[1], 256);
  }
  char16 output [50]={};
  //buildTreeFile (RAW_DICT1, CHINESE_DICT_NAME1,TREE_FILE_NAME1);
  //buildTreeFile (RAW_DICT2, CHINESE_DICT_NAME2,TREE_FILE_NAME2);
  strokeSearchInit();
  strokeSearchSearch(stroke,50,output);
  //testStrokeSearch(stroke,output);


  //Associative search for phrases.
  //int successBuildTree1 = treeBuild(STRNAME1, NUMNAME1, TREE1_FILE_NAME);
  //int successBuildTree2 = treeBuild(STRNAME2, NUMNAME2, TREE2_FILE_NAME);
  char16 keyword[6] = {19981,26159,0,0,0,0};
	//char16 keyword[6] = {25509,0,0,0,0,0};
	//char16 keyword[6] = {26159,0,0,0,0,0};
  char16 resultArray[50 * MAX_PHRASE_LEN] = {};
  assocSearchInit();
  assocSearchSearch(keyword,50,resultArray);
  //testAssocSearch(keyword,resultArray);
 
  return 0;
}



}