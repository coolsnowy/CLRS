#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

int partition(std::vector<int>& a, int p, int r) {
    int key = a[r];
    int i = p - 1;
    for(int j = p; j <= r - 1; j++) {
        if(a[j] <= key) {
            i++;
            std::swap(a[i],a[j]);
        }
    }
    std::swap(a[r], a[i + 1]);
    return i + 1;
}

void quickSort(std::vector<int>& a, int p, int r) {
    // only p < r, there exist two element, then we need to sort it, else we needn't sort!
    i(p < r) {
        int q = partition(a, p, r);
        quickSort(a, p, q - 1);
        quickSort(a, q + 1, r);
    }
}

int main() {
    std::vector<int> vec {2, 3 ,5, 6, 1, 4};
//    std::vector<int> vec{1, 1, 1, 1, 1, 1};
    quickSort(vec, 0, vec.size() - 1);
    for(auto i : vec) {
        cout<< i << '\t';
    }
    cout << endl;

}

