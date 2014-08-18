#include "arrayTernaryTree.h"
#include "strokeSearch.h"
//#include "dictBuild.h"
#include <iostream>
#include <time.h>
using namespace std;


extern "C" {

void testStrokeSearch(const char*stroke,wchar_t*outputArray)
{
	clock_t start,finish;
	double duration;
	//wchar_t output[64];
	strokeSearch testss;
	testss.init(TREE_FILE_NAME);
	start = clock();
	for (size_t i = 0 ; i<1;i++)
	{
		testss.search(stroke,50);
		//testss.search(stroke,50,outputArray);
	}
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf( "%f seconds\n", duration );
	return;
}
  



int main(int argc, char* argv[]) {
  char stroke[256] = "hhh";
  if (argc > 1) {
    strncpy(stroke, argv[1], 256);
  }
  wchar_t output [50];
  //buildTreeFile (RAW_DICT, CHINESE_DICT_NAME,BIN_DICT,TREE_FILE_NAME);
  strokeSearchInit();
  strokeSearchSearch(stroke,50,output);
  //testStrokeSearch(stroke,output);
  
  return 0;
}

/*int main(int argc, char* argv[]) {
  char stroke[256] = "hhh";
  if (argc > 1) {
    strncpy(stroke, argv[1], 256);
  }
  wchar_t output [50];
  //buildTreeFile (RAW_DICT, CHINESE_DICT_NAME,BIN_DICT,TREE_FILE_NAME);
  testStrokeSearch(stroke,output);
  
  return 0;
}*/


}