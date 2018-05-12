#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

#define EXCHANGE(a,b) {int tmp = a; a = b; b = tmp;}

void show(std::vector<int> vec) {
    for (auto i : vec) {
        cout << i << '\t';
    }
    cout << endl;
}

int partition(std::vector<int> &vec, int  p, int r) {
    int pivot = vec[r - 1];
    int i = p;
    for(int j = p; j < r - 1; j++) {
        if(vec[j] < pivot) {
            EXCHANGE(vec[j], vec[i]);
            i++;
        }
    }
    EXCHANGE(vec[i], vec[r - 1]);
    return i;
}

int randomizedPartition(std::vector<int> &vec, int p, int r) {
    srand((unsigned) time (0));
    int pivot = rand()%(r - p) + p;
    EXCHANGE(vec[pivot], vec[r - 1]);
    return partition(vec, p, r);
}

int randomizedSelect(std::vector<int> &vec, int p, int r, int i) {
    // p == r-1 means there are only one element in the vector
    if( p == r - 1) {
        return vec[p];
    }
    int q = randomizedPartition(vec, p, r);
    int k = q - p + 1;
    if(i == k) return vec[q];
    else if(i < k) {
        // not q - 1, because the r point to the one pass the end
        return randomizedSelect(vec, p, q, i);
    } else {
        return randomizedSelect(vec, q + 1, r, i - k);
    }
}


int main() {
    std::vector<int> vec{3, 1, 2, 4, 6, 8, 7, 5};
    cout << randomizedSelect(vec, 0, vec.size(), 6) << endl;

}