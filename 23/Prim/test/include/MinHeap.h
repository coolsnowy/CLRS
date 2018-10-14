//
// Created by coolsnowy on 2018/10/14.
//

#ifndef TEST_MINHEAP_H
#define TEST_MINHEAP_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "Graph.h"

#define SIZE 100 // size of the array
class MinHeap {
public:
	MinHeap();
	MinHeap(std::vector<Edge> vec);
	int left(int i);
	int right(int i);
	int parent(int i);

	void minHeapify(int i);
	void buildMinHeap();
	void heapSort();
	void showHeap();
	void insert(Edge);
	int minimum();
	Edge extractMin();
	bool isEmpty() {
		return heapSize == 0;
	}
	void decreaseKey(int i, Edge value);
private:
	Edge heap[SIZE];
	int heapSize;
	int maxSize;
};


#endif //TEST_MINHEAP_H
