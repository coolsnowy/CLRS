#include <iostream>
#include "maxHeap.h"

using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int main()
{
    int i= 0;
    for(;i < 10 ;i++) {
        i  = i+ 1;
    }
    std::vector<int> vec {1, 2, 3, 4, 5, 6};
    MaxHeap heap(vec);
    heap.showHeap();
    cout << endl << "after heap sort" << endl;
    heap.heapSort();
    heap.showHeap();
    cout << endl << "max heap " << endl;
    heap.buildMaxHeap();
    heap.showHeap();
    cout << endl << "increase " << endl;
    heap.increaseKey(2, 8);
    heap.showHeap();

    cout << endl << "insert " << endl;
    heap.insert(10);
    heap.showHeap();
}
