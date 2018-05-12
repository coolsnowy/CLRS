#include <iostream>
#include <vector>
#include <ctime>
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

struct pivot{
    int q;
    int t;
};

pivot partition(std::vector<int> &a, int p, int r) {
    int key = a[r];
    int i = p - 1;
    for(int j = p; j <= r - 1; j++) {
        if(a[j] < key) {
            i++;
            std::swap(a[i],a[j]);
        }
    }
    std::swap(a[r], a[i + 1]);
    int t = i + 1; // t point to the first element >= key
    while(a[t] == key) {
        t++;
    }
    // now t point to the first continue element > key, but not equal
    // be caution the element after t still exist some element equal to key
    for(int j = r - 1; j >= t; j--) {
        if(a[j] == key) {
            std::swap(a[j], a[t]);
            t++;
        }
    }
    // now t point to the first element > key
    return pivot{i + 1, t - 1};
}

pivot randomizedPartition(std::vector<int> &a, int p, int r) {
    srand((unsigned)time(nullptr));
    int i = rand()%(r - p) + p;
    std::swap(a[r], a[i]);
    return partition(a, p, r);
}
void quickSort(std::vector<int> &a, int p, int r) {

    if(p < r) {
        pivot pivot = randomizedPartition(a, p, r);
        quickSort(a, p, pivot.q - 1);
        quickSort(a, pivot.t + 1, r);
    }
}

int main() {
    std::vector<int> vec{1, 2,6, 4, 5, 1, 1 ,1, 10,23, 1, 1};
//    std::vector<int> vec{1, 1, 1, 1, 1, 1};
    quickSort(vec, 0, vec.size() - 1);
    for(auto i : vec) {
        cout<< i << '\t';
    }
    cout << endl;

}

