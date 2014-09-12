#include "assocTernaryTree.h"

AssocTST::AssocTST ( )
{
	for (size_t i =0; i<MAX_PHRASE_NODES_LEN ; i++)
	{
		nodes[i] = AssocNode(0,0);
	}
	itemCount =0;
	existingItemIndex = -1;
	heap_size = 0;
	nodesCount = 0;
}

AssocTST::~AssocTST ( )
{
	clearTree();
}

void AssocTST::clearTree()
{
	nodesCount = 0;
	candidateCount = 0;
	heap_size = 0;
	itemCount = 0;
	existingItemIndex = -1;
}

int16 AssocTST::add( const char16* key, const int16 & value , const int16 & freq)
{
	int16 index = add(key,freq);
	// add if the phrase does not exist in the ternary tree
	if ( index!=int16(-1) && this->existingItemIndex == int16(-1) )
	{
		nodes[index].phraseId = value;
	}
	return index;
}

int16 AssocTST::add( const char16* key , const int16 & freq)
{
	int16 index = 0;
	int16 parent = -1;
	if( key == 0 || *key == 0){return -1;}
	while(index != int16(-1))
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
				this->existingItemIndex = nodes[index].phraseId;
				break;
			}
			//compare frequency
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
	if(index == int16(-1))
	{
		this->existingItemIndex = -1;
		index = nodesCount;
		++nodesCount;
		nodes[index].splitChar = *key;
		nodes[index].freq = freq; // add new frequency 
		if(parent != int16(-1))
		{
			int diff = *key - nodes[parent].splitChar;
			diff == 0 ? nodes[parent].mid = index :diff < 0? nodes[parent].left = index: nodes[parent].right = index;
		}
		while( nodes[index].splitChar)
		{
			++key;
			nodes[index].mid = nodesCount;
			++nodesCount;
			nodes[nodes[index].mid].splitChar = *key;
			nodes[nodes[index].mid].freq = freq; // add new frequency
			index = nodes[index].mid; // move to new node
		}
		++itemCount;
	}
	return index;
}

void AssocTST::getInitHeap(int16 index, char16*key)
{	
	if(index == int16(-1)){return;}
	if (*key == 0)
	{
		insert( nodes[index].freq, index);
		return;
	}
	// vague search left
	if( *key < nodes[index].splitChar)
	{
		getInitHeap( nodes[index].left,key);
	}
	//vague search right
	if ( *key > nodes[index].splitChar )
	{
		getInitHeap(nodes[index].right,key);
	}
	// vague search middle
	if ( *key == nodes[index].splitChar && *key)
	{
		getInitHeap( nodes[index].mid , key+1);
	}
}

void AssocTST::clearCandidates()
{
	for (size_t i = 0;i<MAX_PHRASE_RET_LEN;i++)
	{
		candidateIndex[i] = -1;
	}
	candidateCount = 0;
}

void AssocTST::vagueSearch(char16*key, size_t k)
{
	clearCandidates();
	clearHeap();
	getInitHeap(0,key);
	int16 index = delete_max();
	for(size_t i =0 ;i<k; i++)
	{
		if(index == int16(-1))
		{
			break;
		}	
		while(nodes[index].splitChar)	
		{
			if(nodes[index].left!= int16(-1) ){insert(nodes[nodes[index].left].freq,nodes[index].left);}
			if(nodes[index].right!=int16(-1) ){insert(nodes[nodes[index].right].freq,nodes[index].right);}
			index = nodes[index].mid;
		}
		// only need to compare right child
		if(nodes[index].right!=int16(-1) ){insert(nodes[nodes[index].right].freq,nodes[index].right);}
			
		// fetch the highest freq
		candidateIndex[i] = nodes[index].phraseId;

		//get new highest frequency node
		index = delete_max();
		++candidateCount;
	}
	return;
}

//about the heap sort
void AssocTST::swap(int16* a, int16* b,int16* ap, int16*bp)
 {
 	int16 temp = *b;
 	*b = *a;
 	*a = temp;
 	int16 tempp = *bp;
 	*bp = *ap;
 	*ap = tempp;
 }

//heap sort, shift up
void AssocTST::shift_up(int i)
 {
 	int done = 0;		
	if( i == 0) {return;}            //node is the root already
 	while((i!=0)&&(!done)) 
 	{
 		if(heap[i] > heap[(i-1)/2])		
 		{
			//if the current is larger than the parent, then swap
 			swap(&heap[i],&heap[(i-1)/2],&heap_pt[i],&heap_pt[(i-1)/2]);
 		}
 		else
 		{
			// the job is already done.
 			done =1;
 		}
 		i = (i-1)/2;
 	}
 }

//heap sort, shift down
void AssocTST::shift_down(int i)
 {
 	int done = 0;	
	if (2*i + 1> heap_size) {return;}         // node i is a leaf
 
 	while((2*i+1 < heap_size)&&(!done))
 	{
 		i =2*i+1;                       // jump to left child
 		if ((i+1< heap_size) && (heap[i+1] > heap[i]))
 		{
			// find the bigger one of the two children	
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

//heap sort, delete an element
void AssocTST::hdelete(int i)
 {
 	int16 last = heap[heap_size - 1];     // get the last one;
	int16 last_pt = heap_pt[heap_size - 1];   
 	heap_size--;                        // shrink the heap
	if (i == heap_size) {return;}
 	heap[i] = last;                     // use the last item to overwrite the current
	heap_pt[i] = last_pt;
 	shift_down(i);
 }

// heap sort, pop up the highest frequency
int16 AssocTST::delete_max()
{
	if(!heap_size){return -1;}
 	int16 ret = heap_pt[0];
 	hdelete(0);	
 	return ret;  
 }

 // heap sort, insert a new element into the heap
 void AssocTST::insert(int16 new_data,int16 new_node)
 {
 	if(heap_size >= MAX_PHRASE_HEAP_LEN) {return;}
 	heap_size++;
 	heap[heap_size - 1] = new_data;	
	heap_pt[heap_size - 1] = new_node;	
 	shift_up(heap_size - 1); 
 }

 // clear elements in the heap
 void AssocTST ::clearHeap()
 {
	 heap_size = 0;
 }

size_t AssocTST::getNodeSize ()
{
	return sizeof(AssocNode);
}
size_t AssocTST::getNodesCount()
{
	return nodesCount;
}
void AssocTST::setNodesCount(size_t count)
{
	nodesCount = count;
}
void AssocTST::setPhrasesCount(size_t count, size_t phlen)
{
	switch(phlen)
	{
	case 2:
		phrases2Count = count;
	case 3:
		phrases3Count = count;
	case 4:
		phrases4Count = count;
	}
}
size_t AssocTST::getCandidateCount()
{
	return candidateCount;
}
int16 AssocTST::getCandidateElement (size_t index)
{
	return candidateIndex[index];
}
AssocNode* AssocTST::getNodeBuffer (size_t index)
{
	return nodes+index;
}

size_t AssocTST::getPhrasesCount(size_t phlen)
{
	return (phlen==2)?phrases2Count:((phlen==3)?phrases3Count:phrases4Count);
}