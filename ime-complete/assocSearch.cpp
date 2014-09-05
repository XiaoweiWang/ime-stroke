#include "assocSearch.h"

extern "C" {

AssocTST asst1,asst2;

int assocSearchInit()
{
	FILE*fp1 = fopen(ASSOC_FILE_1,"rb");
	FILE*fp2 = fopen(ASSOC_FILE_2,"rb");
	if(fp1 == NULL || fp2 == NULL){return -1;}

	//Read phrases.
	size_t phrasesCount = 0;
	fread( &phrasesCount, sizeof(size_t),1,fp1);
	fread( asst1.phrases2, sizeof(char16), 2*phrasesCount, fp1);
	asst1.setPhrasesCount(phrasesCount,2);
	fread( &phrasesCount, sizeof(size_t),1,fp1);
	fread( asst1.phrases3, sizeof(char16), 3*phrasesCount, fp1);
	asst1.setPhrasesCount(phrasesCount,3);
	fread( &phrasesCount, sizeof(size_t),1,fp1);
	fread( asst1.phrases4, sizeof(char16), 4*phrasesCount, fp1);
	asst1.setPhrasesCount(phrasesCount,4);

	fread( &phrasesCount, sizeof(size_t),1,fp2);
	fread( asst2.phrases2, sizeof(char16), 2*phrasesCount, fp2);
	asst2.setPhrasesCount(phrasesCount,2);
	fread( &phrasesCount, sizeof(size_t),1,fp2);
	fread( asst2.phrases3, sizeof(char16), 3*phrasesCount, fp2);
	asst2.setPhrasesCount(phrasesCount,3);
	fread( &phrasesCount, sizeof(size_t),1,fp2);
	fread( asst2.phrases4, sizeof(char16), 4*phrasesCount, fp2);
	asst2.setPhrasesCount(phrasesCount,4);	
	
	// Read nodes.
	size_t nodesCount = 0;
	fread( &nodesCount, sizeof(size_t),1,fp1);
	fread(asst1.getNodeBuffer(0), sizeof(AssocNode), nodesCount, fp1);
	asst1.setNodesCount(nodesCount);
	fread( &nodesCount, sizeof(size_t),1,fp2);
	fread(asst2.getNodeBuffer(0), sizeof(AssocNode), nodesCount, fp2);
	asst2.setNodesCount(nodesCount);

	fclose(fp1);
	fclose(fp2);
	return 0;
}

int assocSearchSearch(char16* keyword,size_t maxCandidateNum, char16 * resultArray)
{
	if(keyword == NULL){return -1;}
	//start search, judge which tree to search
	AssocTST* asst=(*keyword<25510)?(&asst1):(&asst2);
	(*asst).vagueSearch(keyword,maxCandidateNum);
	size_t candidateNum = (*asst).getCandidateCount();
	if(!candidateNum){return 0;}
	size_t keywordLength = 0;
	while(keywordLength <MAX_PHRASE_LEN && keyword[keywordLength])
	{
		++keywordLength;
	}	

	for (size_t id = 0; id < candidateNum; id++)
	{
		size_t phraseId = (*asst).getCandidateElement(id);
		switch(phraseId>>14) // Switch the highest 2 bits
		{
		case 0: //"00", length is 2
			for (size_t i = 0 ; i < 2 - keywordLength ; i++)
			{
				// the character(s) in the keyword is excluded from the result array
				resultArray[id*MAX_PHRASE_LEN+i] = (*asst).phrases2[phraseId][i+keywordLength];
			}
			break;
		case 2: // "10", length is 3
			for (size_t i = 0 ; i < 3 - keywordLength ; i++)
			{
				resultArray[id*MAX_PHRASE_LEN+i] = (*asst).phrases3[phraseId%(1<<14)][i+keywordLength];
			}
			break;
		case 3: //"11", length is 4
			for (size_t i = 0 ; i < 4 - keywordLength ; i++)
			{
				resultArray[id*MAX_PHRASE_LEN+i] = (*asst).phrases4[phraseId%(1<<14)][i+keywordLength];
			}
			break;
		default:
			break;
		}
	}
	
	if( !resultArray[0] )//First candidate is empty
	{
		// put forward the remaining candidates
		for (size_t i= 0 ;i <(candidateNum-1)*MAX_PHRASE_LEN;i++)
		{
			resultArray[i] = resultArray[i+MAX_PHRASE_LEN];
		}
		for (size_t i= (candidateNum-1)*MAX_PHRASE_LEN ;i <candidateNum*MAX_PHRASE_LEN;i++)
		{
			resultArray[i] = '\0';
		}
	}

	return 0;
}

}
