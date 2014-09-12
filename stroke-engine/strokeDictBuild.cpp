#include "strokeDictBuild.h"

int strokeDictBuild (const char*rawDictName, const char*chineseDictName,const char*treeFileName)
{
	TernarySearchTree tst;
	if((!rawDictName)||(!chineseDictName)||(!treeFileName)){return -1;}
	FILE * fr = fopen( rawDictName,"r" );
	FILE * fc = fopen( chineseDictName,"rb" );
	FILE * ft = fopen (treeFileName,"wb");
	if( !fr || !fc || !ft){return -1;}

	char s[MAX_LINE_LEN] = {};
	int8 charFreq = 0;
	size_t tmpFreq = 0;
	char16 charCode = 0;
	if(fread(&charCode,sizeof(char16),1,fc)==NULL){return -1;} // skip the little endian flag at the beginning of the file
	while(fscanf( fr,"%s%d",s,&tmpFreq) != EOF)
	{
		charFreq = int8(tmpFreq);
		fread(&charCode, sizeof(char16),1,fc);
		tst.add( s, charCode,charFreq);

		//Reset temporary char string.
		for (size_t i = 0; i<MAX_LINE_LEN; i++)
		{
			s[i] = '\0';
		}
	}
	size_t nodesCount = tst.getNodesCount();
	fwrite(&nodesCount,sizeof(size_t),1,ft);
	fwrite(tst.getNodeBuffer(0),sizeof(TstNode),nodesCount,ft);

	fclose(fr);
	fclose(fc);
	fclose(ft);

	return 0;
}

