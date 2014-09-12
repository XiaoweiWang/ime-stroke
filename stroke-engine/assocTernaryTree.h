#ifndef ASSOC_TERNARY_TREE_H
#define ASSOC_TERNARY_TREE_H

#include <stddef.h>

#define MAX_PHRASE_HEAP_LEN 20000
#define MAX_PHRASE_RET_LEN 100
#define MAX_PHRASE_NODES_LEN 100000
#define MAX_PHRASE_DICT_LEN 50000
#define MAX_PHRASE_LEN 6
#define MAX_PHRASE_DICT2_LEN 20000
#define MAX_PHRASE_DICT3_LEN 5000
#define MAX_PHRASE_DICT4_LEN 5000

typedef unsigned short char16;
typedef unsigned short int16;
typedef struct AssocNode * AssocTree;

typedef struct AssocNode 
{
	AssocNode (){};
	AssocNode( char16 c ,int16 f)
	{
		 splitChar = c;
		 left = -1;
		 right = -1;
		 mid  = -1;
		 freq = f;
		 phraseId = 0;
	}
	char16 splitChar; // a Chinese character
	int16 left, right,mid;
	int16 phraseId;
	int16 freq;
} assocNode;

// The class AssocTST is similar with the class TernarySearchTree
class AssocTST 
{

public:

	AssocTST ();
	~AssocTST ();
	size_t getNodeSize ();
	size_t getNodesCount();
	size_t getPhrasesCount(size_t phlen);
	void setNodesCount(size_t count);
	void setPhrasesCount(size_t count, size_t phlen);
	size_t getCandidateCount();
	int16 getCandidateElement (size_t index);
	AssocNode* getNodeBuffer (size_t index);
	int16 add( const char16 * key, const int16 & value ,const int16 & freq);
	void getInitHeap( int16 index,char16*key);
	void vagueSearch(char16*key, size_t k);
	void clearTree();

	// phrases consist of 2, 3, or 4 characters, stored in different arrays
	char16 phrases2 [MAX_PHRASE_DICT2_LEN][2];
	char16 phrases3 [MAX_PHRASE_DICT3_LEN][3];
	char16 phrases4 [MAX_PHRASE_DICT4_LEN][4];

private:

	AssocNode nodes[MAX_PHRASE_NODES_LEN];

	size_t nodesCount;
	size_t candidateCount;

	// number of phrases with 2, 3, or 4 characters
	size_t phrases2Count;
	size_t phrases3Count;
	size_t phrases4Count;

	//about the heap
	int16 heap_pt[MAX_PHRASE_HEAP_LEN];
	int16 heap[MAX_PHRASE_HEAP_LEN]; 
	int heap_size;        // the number of elements in the heap
	void swap(int16* a, int16* b,int16* ap, int16* bp);
	void shift_up(int i);
	void shift_down(int i);
	void hdelete(int i);
	int16 delete_max();
	void  insert(int16 new_data,int16 new_node);
	void clearHeap();

	int16 add(const char16* key, const int16 & freq);
	int16 candidateIndex[MAX_PHRASE_RET_LEN]; 
	void clearCandidates();
	int itemCount;	// total number of phrases in the tree
	int16 existingItemIndex; // When inserting, if item already exists, it will be set the index of the existing item. If not, set to -1
};


#endif