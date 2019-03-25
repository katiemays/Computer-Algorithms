#include "heap.h"
#include <array>
#include <new>

int main() {

    Heap h1,h2;
    
    int a[8] = {1,0,18,21,5,3,2,8};
    //should work but isnt:
    //h1(a, 8);

    for (int i=0; i<8; i++) 
	h2.Insert(a[i]);

    for (int i=0; i<8; i++)
	cout << h2.RemoveRoot() << " ";

    cout << endl;
}
