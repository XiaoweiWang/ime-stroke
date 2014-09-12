#ifndef STROKE_TERNARY_TREE_H
#define STROKE_TERNARY_TREE_H

#include <stddef.h>

#define MAX_HEAP_LEN 18000 // Heap length for search
#define MAX_CHAR_RET_LEN 300 // Maximum number of output Chinese characters
#define MAX_NODES_LEN 60000 // Maximum number of nodes in a ternary tree
#define MAX_LINE_LEN 55 // Maximum number of strokes in a single character
#define MAX_PRECISE_LEN 10

typedef unsigned short char16;
typedef unsigned short int16;
typedef unsigned char int8;

typedef struct TstNode * TstTree;

typedef struct TstNode 
{
	TstNode (){};
	TstNode( char c ,int8 f)
	{
		 splitChar = c; // stroke character, 'h', 's', 'p', 'n', 'z', or '?'
		 left = -1; // node index of left, right, and middle child
		 right = -1;
		 mid  = -1;
		 freq = f; // maximum word frequency of its descendent nodes' characters 
		 charCode = 0; // the Chinese character's Unicode value
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
	size_t getNodeSize (); // return the size of a node
	size_t getNodesCount(); // return the number of nodes in the ternary tree
	void setNodesCount(size_t count); // set the number of nodes in the ternary tree
	size_t getCandidateCount(); // return the number of output candidates of the search
	char16 getCandidateElement (size_t index); // return a specific output candidate
	TstNode* getNodeBuffer (size_t index); // return the buffer of a specific tree node
	int16 add( const char * key, const char16 & value ,const int8 & freq); // add a character, its strokes and its word frequency to the ternary tree
	void getPreciseMatch (int16 index, const char*key); // assistant function for precise stroke-match characters
	void getInitHeap( int16 index,const char*key); // insert datas into the sorting heap according to the given strokes (key)
	void vagueSearch(const char*key, size_t k); // search and send results to candidates, k is the expected number of candidates
	void preciseSearch(const char*key); // store precise stroke-match characters, get prepared for vague frequency-based search
	void clearTree();

private:

	TstNode nodes[MAX_NODES_LEN];
	size_t nodesCount;
	size_t candidateCount;
	size_t preciseCount;

	// the heap for frequency heap sort
	int16 heap_pt[MAX_HEAP_LEN];
	int8 heap[MAX_HEAP_LEN]; 
	int heap_size;              // the number of elements in heaps
	void swap(int8* a, int8* b,int16 * ap, int16 * bp);
	void shift_up(int i);
	void shift_down(int i);
	void hdelete(int i);
	int16 delete_max(); // pop up the highest frequency
	void  insert(int8 new_data,int16 new_node);
	void clearHeap();

	int16 add( const char* key, const int8 & freq );
	char16 preciseIndex[MAX_PRECISE_LEN]; // array for precisely matched characters' codes
	void clearPrecise(); // clear preciseIndex array
	void addPrecise(char16 charCode); // add a character code to preciseIndex array
	char16 candidateIndex[MAX_CHAR_RET_LEN]; // results of the single character search
	void clearCandidates();
	int itemCount;	// total number of Chinese characters in the tree
	int16 existingItemIndex; // when inserting, if item already exists, it will be set the index of the existing item. If not, set to -1
};

#endif