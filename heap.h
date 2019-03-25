#include <iostream>
#include <assert.h>
#include <algorithm>

using namespace std;

const int MAX_SIZE=100;

class Heap{
public:
    Heap() { heapLength=0; }
    Heap( int initData[], int len );

    //return true if heap property is satisfied, false if violated
    bool IsHeap() { return IsComplete(1) && IsMax(1); } // '&&' because if it violates either of these, it is not a heap
  
    void heapify(int i);
    void heap_up(int i);
    void heap_up(int someArray[], int i);
    void Insert(int item);
    void Modify(int i, int newValue); 
    int RemoveRoot();
    inline int GetRoot();

private:
     inline int parent(int i);     
     inline int leftchild (int i); 
     inline int rightchild (int i); 
     void build_heap();

     int data[MAX_SIZE];  //You could store elements from index 1 (i.e., leave
     	//first slot of the array empty), this way, you can use abvoe parent(),leftchild(),
	//rightchild() function to return the location of the nodes
     int heapLength;   // the actual number of elements in the heap

     // NEW
     bool IsComplete(int i) {
	// base case:
	// a single leaf node is a complete BST
	if (leftchild(i) == -1) return true;
	else if (i > heapLength) return false;

	bool left_check = IsComplete(2*i);
	bool right_check = IsComplete(2*i+1);

	return left_check && right_check;
     }
     
     bool IsMax(int i) {
	// base case:
	// a single leaf node is a max heap
	if (leftchild(i) == -1) return true; // no children
	
	if (data[i] < data[leftchild(i)]) return false;
	if (data[i] < data[rightchild(i)]) return false;

	bool left_check = IsMax(2*i);
	bool right_check = IsMax(2*i+1);

	return left_check && right_check;
     }
};

 
//Initialize the heap with the given data, and call build_heap to make it a heap
Heap::Heap(int initData[], int len)
{
   for (int i=1;i<=len;i++)
	   data[i] = initData[i-1];

   heapLength=len;
   build_heap();

   assert( IsHeap() );
}

/*  node i's value is smaller than its children, node is shifted down the tree
 *  precondition:
     *   1) heapLength>=i>1
     *   2) node i's left subtree and right subtree meet the heap property, 
     *   node i might violate heap property, 
 *  postcondition: the subtree rooted at node i met heap property */
void Heap::heapify(int i) {
    if (leftchild(i) == -1) return; //no children

    bool fixed = false;

    while (!fixed) {
    	if (data[i] >= data[leftchild(i)] && data[i] >= data[rightchild(i)]) 
	    fixed=true;	// compare current node to its parent
			// if current is not greater, nothing to heap up
	else if (data[i] < data[leftchild(i)]) {
	    swap(data[i],data[leftchild(i)]);
	    i=leftchild(i);
	}
	else if (data[i] < data[rightchild(i)]) {
	    swap(data[i],data[rightchild(i)]);
	    i=rightchild(i);
	}
    }	
}

/*  node i's value is larger than its parents, node is shifted up the tree
 *  precondition:
     *   1) heapLength>=i>1  
     *   2) node i's left subtree and right subtree meet the heap property, 
     *   node i might violate heap property, 
 *  postcondition: the subtree rooted at node i met heap property */
void Heap::heap_up(int i) {
    if (i==1) return; // cannot heap_up at root node

    bool fixed = false;

    while (!fixed) {
    	if (data[i] <= data[parent(i)]) 
	    fixed=true;	// compare current node to its parent
			// if current is not greater, nothing to heap up
	else {
	    swap(data[i],data[parent(i)]);
	    i=parent(i);
	}
    }	
}

void Heap::heap_up(int someArray[], int i) {
    if (i==1) return; // cannot heap_up at root node

    bool fixed = false;

    while (!fixed) {
    	if (someArray[i] <= someArray[parent(i)]) 
	    fixed=true;	// compare current node to its parent
			// if current is not greater, nothing to heap up
	else {
	    swap(someArray[i], someArray[parent(i)]);
	    i=parent(i);
	}
    }	
}
/* insert a new item into the heap. 
/* insert a new item into the heap. 
 * Precondition: length+1<MAX_SIZE; //We have room to grow 
	1. increment heap length by 1
	2. store new item at the end of the heap, say the location is j
	3. walk your way up from node j to root (going one level up to parent in each step,
		compare values stored at a node with its parent and swap
	  the items if necessary. */
void Heap::Insert(int item) {
    heapLength++;
    data[heapLength] = item;
    heap_up(heapLength); // dont have to worry about item being smaller than its children because it has none, 
			 // only a problem if its larger than its parents
}

/*  modify item stored in position i to the newValue, and repair heap property.
      *   Precondition: heap property is statisfied, 
      *   	        1<=i<=length
      *   Postcondition: i-th element is modified, and heap property is satisfied 
      *   Note that you cannot just call build_heap, which is overkill, instead you 
      *   need to repair heap property as efficient as possible).
*/
void Heap::Modify(int i, int newValue) {

    if (newValue > data[i]) {
	// search for smaller root node
    	while (newValue > data[parent(i)]) {
	     i=i/2;
        }
    }
    
    data[i] = newValue;
    heapify(i);
} 

// remove and return item stored in root from the heap
int Heap::RemoveRoot(){
    int rootElement=data[1];
    //remove this root element
	data[1]=data[heapLength];
	heapLength--;
	heapify(1);
    return rootElement;
}

// return the item stored in the root node of the heap
inline int Heap::GetRoot() {
    return data[1];
}

//precondition: i is the numbering of node (starting from 1)
//              i is not 1 (as root node has no parent)
//postcondition: the numbering of node i's parent is returned
//return i/2 (calculating i/2 using bitewise shift operators)
inline int Heap::parent(int i) {
    return i/2;
    //bitwise right-shift by 1 bit
    //return i>>1;
}    

//return the numbering of the left child of node i
// if node i has no left child, return -1 (note use heapLength to see if there is one)
// return 2*i (calculated using bitwise shift operators)
inline int Heap::leftchild (int i) {
    if (i*2 > heapLength) return -1;
    else
    	return 2*i;
    	//bitwise left-shift by 1 bit
    	//return i<<1;
}

//return the numbering of the right child of node i
// if node i has no right child, return -1 (note use heapLength to see if there is one)
// return 2*i+1 (left shift, bitwise OR)
inline int Heap::rightchild (int i) {
    if (i*2 > heapLength) return -1;
    else
    	return 2*i+1;
	//bitwise left-shift by 1 bit and bitwise or with '1'
	//return i<<1|1;
}

/* Precond: 
      the array has been filled with elements, but heap property is not satisfied
      Postcondition:  rearrange elements so that the whole heap statisfies heap property. 
      *This method should be called in the second constructor*/
void Heap::build_heap(){
    int temp_heap[heapLength];

    for (int i=1; i<=heapLength; i++) {
	temp_heap[i]=data[i];
	heap_up(temp_heap, i); 	//no need for heapify conditions bc the only case that the current tree is violating the
			// heap property is if it is larger than its parent --> call heap_up fixes this
    }	
    
    for (int i=1; i<=heapLength; i++) {
        data[i] = temp_heap[i];
    }

    assert( IsHeap() );
}
