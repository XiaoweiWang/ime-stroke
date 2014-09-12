#ifndef ARRAY_TERNARY_TREE_H
#define ARRAY_TERNARY_TREE_H

#include <stddef.h>

#define MAX_HEAP_LEN 18000
#define MAX_DICT_LEN 20000
#define MAX_RET_LEN 100
#define MAX_NODES_LEN 150000
#define MAX_CHINESE_LEN 16

typedef unsigned short char16;
typedef unsigned short int16;
typedef unsigned char int8;

typedef struct TstNode * TstTree;

typedef struct TstNode 
{
	TstNode (){};
	TstNode( char c ,int8 f)
	{
		 splitChar = c;
		 left = -1;
		 right = -1;
		 mid  = -1;
		 freq = f;
		 charCode = 0;
	}

	char splitChar;
	int8 freq;
	int16 left, right,mid;
	char16 charCode;

} tstNode;

class TernarySearchTree 
{

public:

	TernarySearchTree ();
	~TernarySearchTree ();
	size_t getNodeSize ();
	size_t getNodesCount();
	void setNodesCount(size_t count);
	size_t getCandidateCount();
	char16 getCandidateElement (size_t index);
	TstNode* getNodeBuffer (size_t index);
	int16 add( const char * key, const char16 & value ,const int8 & freq);
	void getInitHeap( int16 index,const char*key);
	void vagueSearch(const char*key, size_t k);
	void clear()
	{ 
		nodesCount = 0;
		candidateCount = 0;
		heap_size = 0;
		itemCount = 0;
		existingItemIndex = -1;
	}
	//void loadChineseDict( const char*chineseDictName);
	//void loadChineseDictUnicode( const char*chineseDictName);
	//wchar_t getChineseElement (size_t index);
	//char* getChineseElement (size_t index);

private:

  TstNode nodes[MAX_NODES_LEN];
  //char chineseDict[MAX_DICT_LEN][MAX_CHINESE_LEN];
  //wchar_t chineseUniDict[MAX_DICT_LEN];
  size_t nodesCount;
  size_t candidateCount;


  //about the heap
  int16 heap_pt[MAX_HEAP_LEN];
  int8 heap[MAX_HEAP_LEN]; 
  int heap_size;              // the number of elements in heaps
  void swap(int8* a, int8* b,int16 * ap, int16 * bp);
  void shift_up(int i);
  void shift_down(int i);
  void hdelete(int i);
  int16 delete_max();
  void  insert(int8 new_data,int16 new_node);
  void clearHeap();
  int16 add( const char* key, const int8 & freq );
  char16 candidateIndex[MAX_RET_LEN]; 
  void clearCandidates();

  int itemCount;	// total number of items in the tree

  int16 existingItemIndex; // when inserting, if item already existed, it will be set the index of the existing item. If no existed, set to -1
};

#endif