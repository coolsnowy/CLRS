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

int partition(std::vector<int> &red, std::vector<int> &blue, int p, int r) {
     srand((unsigned)time(0));
     int i = rand()%(r - p) + p;
     EXCHANGE(red[i],red[r - 1]);
     int redPivot = red[r - 1];

     // find the blue pivot and set is at final location
    for(int index = p; index < r; index++) {
        if(blue[index] == redPivot) {
            EXCHANGE(blue[index], blue[r - 1]);
            break;
        }
    }

    // partition blue jugs around the red pivot
    int pivot = p;
    for(int j = p; j < r - 1; j++) {
        if(blue[j] < redPivot) {
            EXCHANGE(blue[j], blue[pivot]);
            pivot++;
        }
    }
    EXCHANGE(blue[pivot], blue[r - 1]);

    // partition red jugs around the bluePivots
    int bluePivot = blue[pivot];
    pivot = p;
    for(int i = p; i < r - 1; i++) {
        if(red[i] < bluePivot) {
            EXCHANGE(red[i], red[pivot]);
            pivot++;
        }
    }
    EXCHANGE(red[r - 1], red[pivot]);
    return pivot;
}

void quickPair(std::vector<int> &red, std::vector<int> &blue, int p, int r) {
    if(p < r) {
        int q = partition(red, blue, p, r);
        quickPair(red, blue, p, q - 1);
        quickPair(red, blue, q + 1, r);
    }
}

int main() {
    std::vector<int> red{4, 5, 3, 2, 1, 8, 7, 9};
    std::vector<int> blue{2, 1, 3, 5, 4, 9, 7, 8};
    show(red);
    show(blue);
    quickPair(red, blue, 0, red.size());
    cout << " after quick pair" << endl;
    show(red);
    show(blue);
}