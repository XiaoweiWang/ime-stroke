#define MAX_HEAP_LEN 10000
#define MAX_DICT_LEN 20000
#define MAX_RET_LEN 100
# define MAX_NODES_LEN 100000

//#include "vector.h"
#include "mystring.h"

typedef struct TstNode * TstTree;

typedef struct TstNode 
{
	TstNode (){};
	TstNode( char c ,int f)
	{
		 splitChar = c;
		 left = -1;
		 right = -1;
		 mid  = -1;
		 freq = f;
		 charIndex = -1;
	}
	char splitChar;
	int left, right,mid;
	size_t charIndex;
	size_t freq;
} tstNode;

template <class Object>
class TernarySearchTree 
{

public:

	TernarySearchTree ();
	~TernarySearchTree ();

	int add( const char * key, const size_t & value ,const size_t & freq);
	void getInitHeap( int index,const char*key);
	void vagueSearch(const char*key, size_t k);
	void clear()
	{ 
		nodesCount = 0;
		candidateCount = 0;
		heap_size = 0;
		itemCount = 0;
		existingItemIndex = -1;
		/*if (NULL != nodes){
			delete [] nodes;
		}*/
	}

private:

  TstNode nodes[MAX_NODES_LEN];
  size_t nodesCount;
  size_t candidateCount;

  //about the heap
  int heap_pt[MAX_HEAP_LEN];
  int heap[MAX_HEAP_LEN]; 
  int heap_size;              // the number of elements in heaps
  void swap(int* a, int* b,int* ap, int* bp);
  void shift_up(int i);
  void shift_down(int i);
  void hdelete(int i);
  int delete_max();
  void  insert(int new_data,int new_node);
  void clearHeap();

  int add( const char* key, const size_t & freq );
  size_t candidateIndex[MAX_RET_LEN]; 
  void clearCandidates();

  int itemCount;	// total number of items in the tree

  int existingItemIndex; // when inserting, if item already existed, it will be set the index of the existing item. If no existed, set to -1
};

/// definition of functions

template <class Object>
TernarySearchTree<Object>::TernarySearchTree ( )
{
	for (size_t i =0; i<MAX_NODES_LEN ; i++)
	{
		nodes[i] = TstNode(0,0);
	}
	itemCount =0;
	existingItemIndex = -1;
	heap_size = 0;
	nodesCount = 0;
}

template <class Object>
TernarySearchTree<Object>::~TernarySearchTree ( )
{
	this->clear();
}

template <class Object>
int TernarySearchTree<Object>::add( const char* key, const size_t & value , const size_t & freq)
{
	int index = add(key,freq);
	if ( index!=-1 )
	{
		if ( this->existingItemIndex == -1 )
		{	// key not existed in tst tree
			nodes[index].charIndex = value;
		}
		else
		{
			// still add the item with the same key into the vector,
			++itemCount;
		}
	}
	return index;
}

template <class Object>
int TernarySearchTree<Object>::add( const char* key , const size_t & freq)
{

	int index = 0;
	int parent = -1;
	if( key == 0 || *key == 0){return -1;}
	while(index != -1)
	{
		parent = index;
		if( *key < nodes[index].splitChar)
		{
			// add max frequency to nodes in path
			if(freq > nodes[index].freq)
			{
				nodes[index].freq = freq;
			}
			index = nodes[index].left;
		}
		else if ( *key == nodes[index].splitChar)
		{
			// return true, if the current character is the end-of-string character 0
			if ( *key == 0 )
			{
				this->existingItemIndex = nodes[index].charIndex;
				break;
			}
			//compare p->freq with key's frequency
			if( freq > nodes[index].freq)
			{
				nodes[index].freq = freq;
			}
			index = nodes[index].mid;
			++key;
		} 
		else
		{
			if(freq > nodes[index].freq)
			{
				nodes[index].freq = freq;
			}
			index = nodes[index].right;
		}
	}
	if(index == -1)
	{
		this->existingItemIndex = -1;
		index = nodesCount;
		++nodesCount;
		nodes[index].splitChar = *key;
		nodes[index].freq = 0;
		//p = new TstNode( *key );
		// add new frequency 
		nodes[index].freq = freq;
		if(parent != -1)
		{
			int diff = *key - nodes[parent].splitChar;
			diff == 0 ? nodes[parent].mid = index :diff < 0? nodes[parent].left = index: nodes[parent].right = index;
		}
		//if ( ! root )
		//{
			//root = p;
		//}
		while( nodes[index].splitChar)
		{
			++key;
			nodes[index].mid = nodesCount;
			++nodesCount;
			nodes[nodes[index].mid].splitChar = *key;
			nodes[nodes[index].mid].freq = 0;
			//p->mid = new TstNode( *key );
			// add new frequency
			nodes[nodes[index].mid].freq = freq;
			index = nodes[index].mid; // move to new node
		}
		++itemCount;
	}
	return index;
}

template <class Object>
void TernarySearchTree<Object>::getInitHeap(int index, const char*key)
{	
	if(index == -1){return;}
	if (*key == 0)
	{
		insert( nodes[index].freq, index);
		return;
	}
	// vague search left
	if( *key == '?' || *key < nodes[index].splitChar)
	{
		getInitHeap( nodes[index].left,key);
	}
	//vague search right
	if (*key == '?' || *key > nodes[index].splitChar )
	{
		getInitHeap(nodes[index].right,key);
	}
	// vague search middle
	if (*key == '?' || ( *key == nodes[index].splitChar && *key))
	{
		if(*(key+1)==0 && nodes[index].splitChar>= '1' && nodes[index].splitChar <= '9')
		{return;}
		else
		{
			getInitHeap( nodes[index].mid , key+1);
		}
	}
}

template <class Object>
void TernarySearchTree<Object>::clearCandidates()
{
	for (size_t i = 0;i<MAX_RET_LEN;i++)
	{
		candidateIndex[i] = -1;
	}
	candidateCount = 0;
}

template <class Object>
void TernarySearchTree<Object>::vagueSearch(const char*key, size_t k)
{
	clearCandidates();
	clearHeap();
	getInitHeap(0,key);
	int index = delete_max();
	for(size_t i =0 ;i<k; i++)
	{
		if(index == -1)
			{
				break;
			}	
		while(nodes[index].splitChar)	
			{
				if(nodes[index].left!= -1 ){insert(nodes[nodes[index].left].freq,nodes[index].left);}
				if(nodes[index].right!=-1 ){insert(nodes[nodes[index].right].freq,nodes[index].right);}
				index = nodes[index].mid;
			}
			// seems only need to compare right child
			if(nodes[index].right!=-1 ){insert(nodes[nodes[index].right].freq,nodes[index].right);}
			
			// fetch the highest freq
			candidateIndex[i] = nodes[index].charIndex;

			//get new highest frequency node
			index = delete_max();
			++candidateCount;
	}
	return;
}

//about the heap sort
template <class Object>
void TernarySearchTree<Object>::swap(int* a, int* b,int* ap, int*bp)
 {
 	int temp = *b;
 	*b = *a;
 	*a = temp;
 	int tempp = *bp;
 	*bp = *ap;
 	*ap = tempp;
 }

template <class Object>
void TernarySearchTree<Object>::shift_up(int i)
 {
 	int done = 0;		
 	if( i == 0) return;            //node is the root already
 	while((i!=0)&&(!done)) 
 	{
 		if(heap[i] > heap[(i-1)/2])		
 		{//if the current is larger than the parent, then swap
 			swap(&heap[i],&heap[(i-1)/2],&heap_pt[i],&heap_pt[(i-1)/2]);
 		}
 		else
 		{// the job is already done.
 			done =1;
 		}
 		i = (i-1)/2;
 	}
 }

template <class Object>
void TernarySearchTree<Object>::shift_down(int i)
 {
 	int done = 0;	
 	if (2*i + 1> heap_size) return;         // node i is a leaf
 
 	while((2*i+1 < heap_size)&&(!done))
 	{
 		i =2*i+1;                       // jump to left child
 		if ((i+1< heap_size) && (heap[i+1] > heap[i]))
 		{// find the bigger one of the two children	
 			i++;
 		}
 		if (heap[(i-1)/2] < heap[i])
 		{
             swap(&heap[(i-1)/2], &heap[i],&heap_pt[(i-1)/2], &heap_pt[i]);
		}
 		else
 		{
 			done  = 1;
 		}
 	}
 }

template <class Object>
void TernarySearchTree<Object>::hdelete(int i)
 {
 	int last = heap[heap_size - 1];     // get the last one;
	int last_pt = heap_pt[heap_size - 1];   
 	heap_size--;                        // shrink the heap
 	if (i == heap_size) return;
 	heap[i] = last;                     // use the last item to overwrite the current
	heap_pt[i] = last_pt;
 	shift_down(i);
 }

template <class Object>
int TernarySearchTree<Object>::delete_max()
{
	if(!heap_size){return -1;}
 	int ret = heap_pt[0];
 	hdelete(0);	
 	return ret;  
 }
 
template <class Object>
 void TernarySearchTree<Object>::insert(int new_data,int new_node)
 {
 	if(heap_size >= MAX_HEAP_LEN) return;  
 	heap_size++;
 	heap[heap_size - 1] = new_data;	
	heap_pt[heap_size - 1] = new_node;	
 	shift_up(heap_size - 1); 
 }

 template < class Object >
 void TernarySearchTree<Object>::clearHeap()
 {
	 heap_size = 0;
 }
 