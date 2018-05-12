#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#define SIZE 100 // size of the array
class MaxHeap {
public:
    MaxHeap();
    MaxHeap(std::vector<int> vec);
    int left(int i);
    int right(int i);
    int parent(int i);
    /**
     * @brief maxHeapify
     * sink the bigger element
     */
    void maxHeapify(int i);
    void buildMaxHeap();
    void heapSort();
    void showHeap();
    void insert(int x);
    int maximum();
    int extractMax();
    /**
     * increase the ith value up to k
     * swim the element
     */
    void increaseKey(int i, int k);
private:
    int heap[SIZE];
    int heapSize;
    int maxSize;
};

#endif
