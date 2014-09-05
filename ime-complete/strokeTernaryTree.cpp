#include "strokeTernaryTree.h"

TernarySearchTree::TernarySearchTree()
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

void TernarySearchTree::clearTree()
{
	nodesCount = 0;
	candidateCount = 0;
	heap_size = 0;
	itemCount = 0;
	existingItemIndex = -1;
}

TernarySearchTree::~TernarySearchTree()
{
	clearTree();
}

int16 TernarySearchTree::add( const char* key, const char16 & value , const int8 & freq)
{
	int16 index = add(key,freq);
	// a position is found and key does not exist in the tree
	if ( index!=int16(-1) && this->existingItemIndex == int16(-1) )
	{
		nodes[index].charCode = value;
	}
	return index;
}

int16 TernarySearchTree::add( const char* key , const int8 & freq)
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
				this->existingItemIndex = nodes[index].charCode;
				break;
			}
			// compare frequency, replace the former one if current one is higher
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
	// true if the current node is unused
	if(index == int16(-1))
	{
		this->existingItemIndex = -1;
		// create new node
		index = nodesCount;
		++nodesCount;
		nodes[index].splitChar = *key;
		// add new frequency 
		nodes[index].freq = freq;
		if(parent != int16(-1))
		{
			int diff = *key - nodes[parent].splitChar;
			diff == 0 ? nodes[parent].mid = index :diff < 0? nodes[parent].left = index: nodes[parent].right = index;
		}
		while (nodes[index].splitChar)
		{
			++key;
			// create new mid child node
			nodes[index].mid = nodesCount;
			++nodesCount;
			nodes[nodes[index].mid].splitChar = *key;
			// add new frequency
			nodes[nodes[index].mid].freq = freq;
			index = nodes[index].mid; // move to new node
		}
		++itemCount;
	}
	return index;
}

void TernarySearchTree::getPreciseMatch (int16 index, const char*key)
{
	if (index == int16(-1) || *key == '?') { return; } // return if current node is empty or inquery string contains "?"
	if (*key == 0)
	{
		// add the character code to precise search results if no other strokes follow
		if(nodes[index].splitChar == '\0')
		{
			addPrecise(nodes[index].charCode);
		}
		// characters '1' to '9' are not meaningful strokes
		if(nodes[index].splitChar>= '1' && nodes[index].splitChar <= '9')
		{
			addPrecise(nodes[nodes[index].mid].charCode);
		}
		getPreciseMatch(nodes[index].left,key); // search left and right chile
		getPreciseMatch(nodes[index].right,key);

		return;
	}
	// find the middle child node of the node that matches the inquery stroke string
	if (*key < nodes[index].splitChar)
	{
		getPreciseMatch(nodes[index].left,key);
	}
	if (*key > nodes[index].splitChar)
	{
		getPreciseMatch(nodes[index].right,key);
	}
	if (*key == nodes[index].splitChar && *key)
	{
		getPreciseMatch(nodes[index].mid, key+1);
	}

}

void TernarySearchTree::getInitHeap(int16 index, const char*key)
{	
	if(index == int16(-1)){return;}
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
		// skip if the last character is a difference indicator
		if(*(key+1)==0 && nodes[index].splitChar>= '1' && nodes[index].splitChar <= '9')
		{return;}
		else
		{
			getInitHeap( nodes[index].mid , key+1);
		}
	}
}

void TernarySearchTree::clearPrecise()
{
	for (size_t i = 0;i<MAX_PRECISE_LEN;i++)
	{
		preciseIndex[i] = -1;
	}
	preciseCount = 0;
}

void TernarySearchTree::addPrecise(char16 charCode)
{
	preciseIndex[preciseCount] = charCode;
	++preciseCount;
}

void TernarySearchTree::preciseSearch(const char*key)
{
	clearPrecise();
	getPreciseMatch(0,key);
}

void TernarySearchTree::clearCandidates()
{
	for (size_t i = 0;i<MAX_CHAR_RET_LEN;i++)
	{
		candidateIndex[i] = -1;
	}
	candidateCount = 0;
}

void TernarySearchTree::vagueSearch(const char*key, size_t k)
{
	clearCandidates();
	clearHeap();
	getInitHeap(0,key);
	int16 index = delete_max();
	size_t matchCount = 0; // the number of precisely matched characters which have become candidates
	for(size_t i =0 ;i < k; i++)
	{
		if(index == int16(-1))
		{
			break;
		}
		// insert left and right children into the heap while going through mid children
		while(nodes[index].splitChar)	
		{
			if(nodes[index].left!= int16(-1) ){insert(nodes[nodes[index].left].freq,nodes[index].left);}
			if(nodes[index].right!=int16(-1) ){insert(nodes[nodes[index].right].freq,nodes[index].right);}
			index = nodes[index].mid;
		}
		// only need to compare right child
		if(nodes[index].right!=int16(-1) ){insert(nodes[nodes[index].right].freq,nodes[index].right);}
			
		// fetch the character with the highest frequency
		candidateIndex[i] = nodes[index].charCode;
		if(i < k - preciseCount)
		{
			if(nodes[index].charCode == preciseIndex[matchCount]) { ++matchCount; } // count a precise match
		}
		else if(i < k - matchCount)
		{
			candidateIndex[i] = preciseIndex[i + preciseCount + matchCount - k]; // add precise search results
		}
		else
		{
			candidateIndex[i] = 0;
			break;
		}

		// get new highest frequency node
		index = delete_max();
		++candidateCount;
	}
	return;
}

//about the heap sort
void TernarySearchTree::swap(int8* a, int8* b,int16* ap, int16*bp)
 {
 	int8 temp = *b;
 	*b = *a;
 	*a = temp;
 	int16 tempp = *bp;
 	*bp = *ap;
 	*ap = tempp;
 }

//heap sort, shift up
void TernarySearchTree::shift_up(int i)
 {
 	int done = 0;		
	if( i == 0) {return;}    //node is the root already
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
void TernarySearchTree::shift_down(int i)
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
void TernarySearchTree::hdelete(int i)
 {
 	int8 last = heap[heap_size - 1];     // get the last one;
	int16 last_pt = heap_pt[heap_size - 1];   
 	heap_size--;                        // shrink the heap
	if (i == heap_size) {return;}
 	heap[i] = last;                     // use the last item to overwrite the current
	heap_pt[i] = last_pt;
 	shift_down(i);
 }

// heap sort, delete the max element
int16 TernarySearchTree::delete_max()
{
	if(!heap_size){return -1;}
 	int16 ret = heap_pt[0];
 	hdelete(0);	
 	return ret;  
 }

 // heap sort, insert a new element into the heap
 void TernarySearchTree::insert(int8 new_data,int16 new_node)
 {
	 if(heap_size >= MAX_HEAP_LEN) {return;} 
 	heap_size++;
 	heap[heap_size - 1] = new_data;	
	heap_pt[heap_size - 1] = new_node;	
 	shift_up(heap_size - 1); 
 }

 // clear elements in the heap
 void TernarySearchTree ::clearHeap()
 {
	 heap_size = 0;
 }


size_t TernarySearchTree::getNodeSize ()
{
	return sizeof(TstNode);
}
size_t TernarySearchTree::getNodesCount()
{
	return nodesCount;
}
void TernarySearchTree::setNodesCount(size_t count)
{
	nodesCount = count;
}
size_t TernarySearchTree::getCandidateCount()
{
	return candidateCount;
}
char16 TernarySearchTree::getCandidateElement (size_t index)
{
	return candidateIndex[index];
}
TstNode* TernarySearchTree::getNodeBuffer (size_t index)
{
	return nodes+index;
}