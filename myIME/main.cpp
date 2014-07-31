//#include "ternarySearchTree.h"
//include "ternaryTreeX.h"
#include "arrayTernaryTree.h"
//#include "heapSort.h"
#include <iostream>
//#include "naiveSearch.h"
using namespace std;
//int ternarySearch();
//int weightedTernarySearch();
int arrayTernarySearch(const char*stroke);

/*int main()
{
	//naiveSearch();return 0;
	//return ternarySearch();
	//return weightedTernarySearch();
	return arrayTernarySearch();
	//return 0;
}*/
int
main(int argc, char* argv[]) {
  char stroke[256] = "hsp";
  if (argc > 1) {
    strncpy(stroke, argv[1], 256);
  }
  arrayTernarySearch(stroke);
  return 0;
}