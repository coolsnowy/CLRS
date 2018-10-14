//
// Created by coolsnowy on 2018/10/14.
//

#include "MinHeap.h"

using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

MinHeap::MinHeap() {
	for(int i = 0; i < SIZE; i++) {
		heap[i] = Edge();
	}
	heapSize = 0;
	maxSize = SIZE;
}

MinHeap::MinHeap(std::vector<Edge> vec) {
	MinHeap();
	for(int i = 0; i < vec.size(); i++) {
		heap[i + 1] = vec[i];
	}
	heapSize = vec.size();
	buildMinHeap();
}

int MinHeap::left(int i) {
	if(2 * i <= heapSize) {
		return 2 * i;
	} else
//		 cerr << "left index over the heap size" << endl;
		return SIZE + 1;
}

int MinHeap::right(int i) {
	if(2 * i + 1 <= heapSize) {
		return 2 * i + 1;
	} else
//		cerr << "right index over the heap size" << endl;
		return SIZE + 1;
}

int MinHeap::parent(int i) {
	if(i / 2 >= 1) {
		return i / 2;
	} else {
		return 0;
	}
}

void MinHeap::minHeapify(int i) {
	int min = i;
	int leftIndex = left(i);
	int rightIndex = right(i);
//		int val = std::min(heap[leftIndex], heap[rightIndex]);
	if(leftIndex <= heapSize && heap[leftIndex].weight < heap[i].weight) {
		min = leftIndex;
	} else {
		min = i;
	}
	if(rightIndex <= heapSize && heap[rightIndex].weight < heap[min].weight) {
		min = rightIndex;
	}
	if(min != i ) {
		std::swap(heap[i], heap[min]);
		minHeapify(min);
	}

}

void MinHeap::buildMinHeap() {
	// beacause the heap indice start from 1
	for(int i = heapSize / 2; i >= 1; i--) {
		minHeapify(i);
	}
}

void MinHeap::showHeap() {
	int i = 1;
	int stage = 1;
	while(i <= heapSize ) {
		cout << heap[i].weight << '\t';
		if(i == (pow(2, stage) - 1)){
			stage++;
			cout << endl;
		}
		i++;
	}
}

void MinHeap::heapSort()  {
	buildMinHeap();
	// the following procedure will change the value of the heapsize
	// save it before process
	int saveHeapSize = heapSize;
	for(int i = heapSize; i >= 2; i--) {
		std::swap(heap[1], heap[i]);
		heapSize--;
		minHeapify(1);
	}
	heapSize = saveHeapSize;
}

Edge MinHeap::extractMin() {
	Edge min = heap[1];
	heap[1] = heap[heapSize];
	heapSize--;
	minHeapify(1);
	return min;
}
void MinHeap::decreaseKey(int index, Edge value) {
	if(index > heapSize || value.weight >= heap[index].weight) {
		cerr << "error increase" << endl;
	} else {
		heap[index] = value;
		while( index > 1 && heap[parent(index)].weight > value.weight) {
			heap[index] = heap[parent(index)];
			index = parent(index);
		}
		heap[index] = value;
	}
}
void MinHeap::insert(Edge x) {
	heapSize++;
	heap[heapSize].weight = INT_MAX;
	decreaseKey(heapSize, x);
}