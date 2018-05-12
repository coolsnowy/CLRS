#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void show(std::vector<int> vec) {
    for (auto i : vec) {
        cout << i << '\t';
    }
    cout << endl;
}

// this program is in place and run in linear time, but it is not stable
void inPlaceCountSort(std::vector<int> &vec, int range) {
    std::vector<int> count(range, 0);
    for(int i = 0; i < vec.size(); i++) {
        count[vec[i]]++;
    }
    for(int i = 1; i < count.size(); i++) {
        count[i] += count[i - 1];
    }
    std::vector<int> position(count);
    int i = 0;
    while(i < vec.size()) {
        bool placed = (position[vec[i] - 1] <= i && i <= position[vec[i]]);
        if(placed) i++;
        else {
            int key = vec[i];
            using std::swap;
            std::swap(vec[i], vec[count[vec[i]] - 1]);
            // beacause the vec[i] has been changed, so we must preserve it as key used here
            count[key]--;
        }
    }
}



int main() {
    std::vector<int> vec{4, 5, 3, 2, 1, 8, 7, 9};
    inPlaceCountSort(vec, 10);
    show(vec);
}