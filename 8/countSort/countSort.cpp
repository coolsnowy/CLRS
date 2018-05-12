#include <iostream>
#include <vector>
#include <ctime>
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

std::vector<int> countSort(std::vector<int> vec) {
    std::vector<int> count(vec.size(), 0);
    for(auto i : vec) {
        count[vec[i]]++;
    }
    for(int i = 1; i < count.size(); i++) {
        count[i] = count[i] + count[i - 1];
    }
    std::vector<int> result(vec.size(), 0);
    for(int i = vec.size() - 1; i >= 0; i--) {
        // -1 because the vector start from 0
        // element means the number of element <= key
        // for example, three element <= 4, besides itself, two element < 4, then 4 should be set to 2th location
        result[count[vec[i]] - 1] = vec[i];
        count[vec[i]]--;
    }
    return result;
}

int main() {
    std::vector<int> vec{2, 5, 3, 0, 2, 3, 0, 3};
    auto result = countSort(vec);
    for(auto i : result) {
        cout << i << '\t';
    }
    cout << endl;
}
