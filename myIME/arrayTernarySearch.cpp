#include "arrayTernaryTree.h"
#include <iostream>
//#include "vector.h"
#include <time.h>
#include "mystring.h"


#define MAX_LINE_LEN			1024
#define DIC_FILE_NAME			"dictstrokesimpleSeFI_F.txt"


int arrayTernarySearch(const char* stroke)
{
	// calculate time
	clock_t start,finish;
	double duration;

	const char * fileName = DIC_FILE_NAME;
	TernarySearchTree<size_t> tst;
	if ( fileName )
	{
		/* get token string from input file */
		FILE * fp = fopen( fileName,"r" );
		if ( fp != NULL )
		{
			char s[MAX_LINE_LEN];
			size_t charFreq = 0;
			size_t charIndex = 0;
			while(fscanf( fp,"%s%d%d",s,&charFreq,&charIndex) != EOF)
			{
				string str = s;
				string key = str.trimEnd();
				tst.add( key.c_str(), charIndex,charFreq);
			}
			fclose( fp );
		}
	}

	//char stroke [100] = "?ph?" ;
	start = clock();
	for(size_t i = 0; i<100000;i++)
	{
		tst.vagueSearch(stroke,100);
	}
	//tst.vagueSearch("zzz",20);
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "%f seconds\n", duration );
	//tst.~TernarySearchTree();
	return 0;
}