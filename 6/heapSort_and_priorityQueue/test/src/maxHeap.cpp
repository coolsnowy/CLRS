#include "maxHeap.h"

using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

MaxHeap::MaxHeap() {
    for(int i = 0; i < SIZE; i++) {
        heap[i] = 0;
    }
    heapSize = 0;
    maxSize = SIZE;
}

MaxHeap::MaxHeap(std::vector<int> vec) {
    MaxHeap();
    for(int i = 0; i < vec.size(); i++) {
        heap[i + 1] = vec[i];
    }
    heapSize = vec.size();
    buildMaxHeap();
}

int MaxHeap::left(int i) {
    if(2 * i <= heapSize) {
        return 2 * i;
    } else
//        cerr << "left index over the heap size" << endl;
    return SIZE + 1;
}

int MaxHeap::right(int i) {
    if(2 * i + 1 <= heapSize) {
        return 2 * i + 1;
    } else
//        cerr << "right index over the heap size" << endl;
    return SIZE + 1;
}

int MaxHeap::parent(int i) {
    if(i / 2 >= 1) {
        return i / 2;
    } else {
        return 0;
    }
}

void MaxHeap::maxHeapify(int i) {
	int max = i;
	int leftIndex = left(i);
	int rightIndex = right(i);

	if(leftIndex <= heapSize && heap[leftIndex] >  heap[i]) {
		max = leftIndex;
	} else {
		max = i;
	}
	if(rightIndex <= heapSize && heap[rightIndex] > heap[max]) {
		max = rightIndex;
	}
	if(max != i ) {
		std::swap(heap[i], heap[max]);
		maxHeapify(max);
	}
}

void MaxHeap::buildMaxHeap() {
    // beacause the heap indice start from 1
    for(int i = heapSize / 2; i >= 1; i--) {
        maxHeapify(i);
    }
}

void MaxHeap::showHeap() {
    int i = 1;
    int stage = 1;
    while(i <= heapSize ) {
        cout << heap[i] << '\t';
        if(i == pow(2, stage) - 1){
            stage++;
            cout << endl;
        }
        i++;
    }
}

void MaxHeap::heapSort()  {
    // the following procedure will change the value of the heapsize
    // save it before process
    int saveHeapSize = heapSize;
    for(int i = heapSize; i >= 2; i--) {
        std::swap(heap[1], heap[i]);
        heapSize--;
        maxHeapify(1);
    }
    heapSize = saveHeapSize;
}

int MaxHeap::extractMax() {
    int max = heap[1];
    heap[1] = heap[heapSize];
    heapSize--;
    maxHeapify(1);
    return max;
}
 void MaxHeap::increaseKey(int index, int value) {
     if(index > heapSize || value <= heap[index]) {
         cerr << "error increase" << endl;
     } else {
         heap[index] = value;
         while( index > 1 && heap[parent(index)] < value) {
             heap[index] = heap[parent(index)];
             index = parent(index);
         }
         heap[index] = value;
     }
 }
void MaxHeap::insert(int x) {
    heapSize++;
    heap[heapSize] = INT_MIN;
    increaseKey(heapSize, x);
}