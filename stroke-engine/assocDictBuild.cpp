#include "assocDictBuild.h"

int assocDictBuild(const char*strFileName, const char*numFileName, const char*treeAndDictFileName)
{
	// Build tree.
	AssocTST asst;
	FILE*fr = fopen(strFileName,"rb");
	FILE*fn = fopen(numFileName,"r");
	if(fr==NULL || fn==NULL){return -1;}

	char16 tmp = 0;
	if(fread(&tmp,sizeof(char16),1,fr)==NULL){return -1;} //For Unicode file endian sign
	int16 phraseId = 0;
	int16 phraseId2 = 0;
	int16 phraseId3 = 0;
	int16 phraseId4 = 0;
	while(fread(&tmp,sizeof(char16),1,fr)!=NULL)
	{
		size_t charFreq;	
		char16 s[MAX_PHRASE_LEN] = {};
		size_t i = 0;
		while(tmp!='\n') // Extra '\n' needed at the end of file
		{
			s[i] = tmp;
			fread(&tmp,sizeof(char16),1,fr);
			i++;
		}
		size_t phraseLength = i-1; //For windows files.
		s[i-1] = '\0';//For windows files.
		switch(phraseLength)
		{
		case 2:
			for(int i = 0; i < 2; i++)
			{
				asst.phrases2[phraseId2][i] = s[i];
			}
			// Highest bit is zero. The digits of lower 14 bits represent phrases' id in the domain of the same length.
			phraseId = phraseId2;
			++phraseId2;
			break;
		case 3:
			for(int i = 0; i < 3; i++)
			{
				asst.phrases3[phraseId3][i] = s[i];
			}
			phraseId = (2<<14)+phraseId3; // Highest 2 bits is "10".
			++phraseId3;
			break;
		case 4:
			for(int i = 0; i < 4; i++)
			{
				asst.phrases4[phraseId4][i] = s[i];
			}
			phraseId = (3<<14)+phraseId4; //Highest 2 bits is "11".
			++phraseId4;
			break;
		default:
			break;
		}
		fscanf(fn,"%d",&charFreq);
		asst.add(s, phraseId, charFreq);
	}
	asst.setPhrasesCount( phraseId2, 2);
	asst.setPhrasesCount( phraseId3, 3);
	asst.setPhrasesCount( phraseId4, 4);
	fclose(fr);
	fclose(fn);

	// Save file.
	FILE* fd = fopen(treeAndDictFileName,"wb");
	if(fd == NULL){return -1;}

	size_t phrasesCount = 0;
	phrasesCount = asst.getPhrasesCount(2);
	fwrite( &phrasesCount, sizeof(size_t),1,fd);
	fwrite( asst.phrases2, sizeof(char16), 2*phrasesCount, fd);
	phrasesCount = asst.getPhrasesCount(3);
	fwrite( &phrasesCount, sizeof(size_t),1,fd);
	fwrite( asst.phrases3, sizeof(char16), 3*phrasesCount, fd);
	phrasesCount = asst.getPhrasesCount(4);
	fwrite( &phrasesCount, sizeof(size_t),1,fd);
	fwrite( asst.phrases4, sizeof(char16), 4*phrasesCount, fd);

	size_t nodesCount = asst.getNodesCount();
	fwrite( &nodesCount, sizeof(size_t),1,fd);
	for (size_t i = 0; i<nodesCount; i++)
	{
		fwrite( asst.getNodeBuffer(i), sizeof(AssocNode) , 1 , fd);
	}

	fclose(fd);
	return 0;

}