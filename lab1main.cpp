/*	Author: 	Katie Mays
 *	Last Modified:	Feb 3 2019
 *	Title:		Lab 1
 *	Goals:		1. Implement bubblesort, insertion sort and selection sort algorithms as function template
 *			2. Practice testing (for correctness), measuring and comparing performance of different algorithms
 *			3. Familiarize with C++ STL class vector
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <assert.h>
#include <sys/time.h>

using namespace std;

// Declarations

// Bubble Sort
template <class T>
void BubbleSort (vector<T> &  v); 

// Selection Sort
template <class T>
void SelectionSort (vector<T> & v);

// Insertion Sort
template <class T>
void InsertionSort (vector<T> & v);


// Helper Functions
vector<int> GenerateRandomVector(int size);
void PrintVector (vector<int> & v);
template <class T>
bool IsSorted (vector<T> v);
template <class T>
int BinarySearch (vector<T> v, int left_index, int right_index, T value);
void MeasureSortingFunction (int input_size, int run_number);

int main() {
	
	cout << "1. Testing the three algorithms each with a different randomly generated array of size 10:" << endl;
	
	vector<int> v1;
	v1 = GenerateRandomVector(10);
	cout << "\t~ Testing BubbleSort ~" << endl;
	cout << "\tBefore:\n\t";
	PrintVector(v1);
	BubbleSort(v1);
	cout << "\tAfter:\n\t";
	PrintVector(v1);
	if ( IsSorted(v1) )
	    cout << "\tVector is sorted - BubbleSort worked!" << endl;
	else
	    cout << "\tVector is not sorted - BubbleSort does not work." << endl;

	vector<int> v2;
	v2 = GenerateRandomVector(10);
	cout << "\t~ Testing SelectionSort ~" << endl;
	cout << "\tBefore:\n\t";
	PrintVector(v2);
	BubbleSort(v2);
	cout << "\tAfter:\n\t";
	PrintVector(v2);
	if ( IsSorted(v2) )
	    cout << "\tVector is sorted - SelectionSort worked!" << endl;
	else
	    cout << "\tVector is not sorted - SelectionSort does not work." << endl;
	
	vector<int> v3;
	v3 = GenerateRandomVector(10);
	cout << "\t~ Testing InsertionSort ~" << endl;
	cout << "\tBefore:\n\t";
	PrintVector(v3);
	BubbleSort(v3);
	cout << "\tAfter:\n\t";
	PrintVector(v3);
	if ( IsSorted(v3) )
	    cout << "\tVector is sorted - InsertionSort worked!" << endl;
	else
	    cout << "\tVector is not sorted - InsertionSort does not work.\n" << endl;

	cout << "2. Measuring the three sorting algorithms with 10 ranondomly generated inputs of size 20.\n" << endl;
    	cout << "3. Summary of measurement result:" << endl;
 	MeasureSortingFunction (20, 10);
}

// Definitions

// Bubble Sort
/* swap() function is called below to exchage the values of two variables.
 * It's implemented as a function template in C++ standard library. 
 * The following is provided as an example for you to study function template.
template <class T>
void swap (T & first, T & second) 
{
    T temp;  // a temp variable 

    temp = first;
    first = second;
    second = temp;

}
 */

template <class T>
void BubbleSort (vector<T> &  v) //Why use &? -> because we want the changes to the order in the vector to be saved 
{
     	int end_index = v.size()-1; 

     	for (; end_index>0; end_index--)
     	{
	    for (int i=0; i<=end_index-1;i++)
		if (v[i] > v[i+1])
		    swap (v[i], v[i+1]);
     	}
}

// Selection Sort
template <class T>
void SelectionSort (vector<T> & v)
{
	int largest_index;

	for ( int end_index=v.size()-1; end_index>2; end_index-- )
	{
	    // find largest element in the list
	    largest_index = 1;

	    for ( int i=2; i<end_index; i++ )
	    {
		if (v[i] > v[largest_index])
		    largest_index = i;
	    }
	
	    // v[largest_index] is the largest in v[1...end_index]
	    // swap largest to the end of sublist
	    if (largest_index != end_index)
		swap(v[largest_index], v[end_index]);
	} 
}

// Insertion Sort
template <class T>
void InsertionSort (vector<T> & v)
{
	T value;
	int k;

	for ( int i=2; i<v.size(); i++ )
	{
	    // insert v[i] into sorted sublist: v[1...i-1]
	    value = v[i];
	    k = abs( BinarySearch(v,1,i-1,value) );
	    // value should be stored at v[k]
	    // shift all elements in v[k...i-1] to the right by one
	    for ( int j=i-1; j>0; j-- )
		v[j+1] = v[j];
	    v[k] = value;
	}
}

// Helper Functions
/* Generates a vector and fills it with random integers between 1 and 10,000
   returns the address of the array
   @param size: the size of the array to be generated
   @return: 	the vector */
vector<int> GenerateRandomVector(int size)
{
	vector<int> v;
	int n;
    
	for ( int i=0; i<size; i++ )
	{
	    n = rand() % 10000 + 1;	// a random number between 1 and 10,000
            v.push_back(n);
    	}

	return v;
}
/* display the content of the vector */
void PrintVector (vector<int> & v)
{
	for ( int i=0; i<v.size(); i++ )
	{
	    cout << v[i] << " ";
	}
	cout << endl;
}
/* return true if elements in vector is arranged in ascending order
   return false otherwise */
template <class T>
bool IsSorted (vector<T> v)
{
	int n = v.size();
	
	// a list is sorted if there is only 0 or 1 elements
	if ( n==0 || n==1 )
	    return true;

	for ( int i=1; i<n; i++ )
	{
	    if ( v[i] < v[i-1] )
		return false;
	}
	
	// no unsorted pair found
	return true;
}

// BinarySearch
/* recursive binary search
 * left and right indexes must be defined initially before entering function as 0 and v.size()
 * @param left_index: leftmost sublist index to be searched 
 * @param right_index: rightmost sublist index to be searched
 * @return: index of value if found, returns would-be index if value not found
 */
template <class T>
int BinarySearch (vector<T> v, int left_index, int right_index, T value)
{
	// base case
	if (left_index > right_index)
	    return -left_index;

	int middle_index = (left_index + right_index)/2;
	
	if (value == v[middle_index])
	    return middle_index;
	else if (value < v[middle_index])
	    // if value is less than middle value, search the left half of list
	    return BinarySearch(v, left_index, middle_index-1, value);
	else
	    // if value is greater than middle value, search the right half of list
	    return BinarySearch(v, middle_index+1, right_index, value);
}

/*
 Measure running time of three sorting algorithms, using
 randomly generated array of given size (input_size)
 Find and return avg, min and max running time for the @run_number runs 
   (recall that for different input instance, the running time of an algorithm
    can vary due to many factors, one of them being some input are easier to
     sort), here we want to repeat the experiements for @run_number times
     and report the minimum, maximum, and average from these runs
*/
void MeasureSortingFunction (int input_size, int run_number)
{
	// BubbleSort
   	double b_min, b_max, b_sum=0;
	// SelectionSort
	double s_min, s_max, s_sum=0;
	// InsertionSort
	double i_min, i_max, i_sum=0;

	vector<int> same_input, work_copy;
 	struct timeval begin,end;
	double elapsed;

   	for ( int i=0; i<run_number; i++ )
	{
	    // generate one random vector so the 3 sorting algorithms are tested with the same input
	    same_input = GenerateRandomVector(input_size);
	    // make copy that will be sorted by each algorithm and original @same_input can be untouched for next one's use
	    work_copy = same_input; 

	    // BubbleSort
	    // Sort work_copy using bubble sort, and measure the running time
   	    gettimeofday (&begin,NULL);   
   	    BubbleSort(work_copy);
	    gettimeofday (&end,NULL);   
	    elapsed = (end.tv_sec-begin.tv_sec)+((end.tv_usec-begin.tv_usec)/1000000.0);
	   	
	    //update min, max and sum of bubble sort running time
	    b_sum += elapsed;
	    if ( i == 0 ) 
	    {
		b_min = elapsed;
		b_max = elapsed;
	    }
	    else {
	    	if ( elapsed < b_min )
		    b_min = elapsed;
	    	else if ( elapsed > b_max )
		    b_max = elapsed;
 	    }

       	    work_copy = same_input;

	    // SelectionSort
	    // Sort work_copy using selection sort, and measure the running time  
   	    gettimeofday (&begin,NULL);   
   	    SelectionSort(work_copy);
	    gettimeofday (&end,NULL);   
	    elapsed = (end.tv_sec-begin.tv_sec)+((end.tv_usec-begin.tv_usec)/1000000.0);
	
	    //update min, max and sum of selection sort running time
	    s_sum += elapsed;
	    if ( i == 0 ) 
	    {
		s_min = elapsed;
		s_max = elapsed;
	    }
	    else {
		if ( elapsed < s_min )
		    s_min = elapsed;
	     	else if ( elapsed > s_max )
		    s_max = elapsed;
 	    }

       	    work_copy = same_input;

	    // InsertionSort       
	    // Sort work_copy using insertion sort, and measure the running time time 
   	    gettimeofday (&begin,NULL);   
   	    InsertionSort(work_copy);
	    gettimeofday (&end,NULL);   
	    elapsed = (end.tv_sec-begin.tv_sec)+((end.tv_usec-begin.tv_usec)/1000000.0);
	
	    //update min, max and sum of selection sort running time
	    i_sum += elapsed;
	    if ( i == 0 ) 
	    {
		i_min = elapsed;
		i_max = elapsed;
	    }
	    else {
		if ( elapsed < i_min )
		    i_min = elapsed;
	    	else if (elapsed > i_max)
		    i_max = elapsed;
	    }
	}
        	
	// Display average, display avg, min and max for each sorting algorithms
	cout << "	Input	Runs	BubbleSort			SelectionSort			InsertionSort" << endl;
        cout << "\t" << input_size << "\t" << run_number << "\t";
	cout << 			"AVG\tMIN\tMAX\t\tAVG\tMIN\tMAX\t\tAVG\tMIN\tMAX" << endl; 
	cout << "\t\t\t" << b_sum/run_number << "\t" << b_min << "\t" << b_max;
	cout << "\t\t" << s_sum/run_number << "\t" << s_min << "\t" << s_max;
	cout << "\t\t" << i_sum/run_number << "\t" << i_min << "\t" << i_max << endl;	        
}
