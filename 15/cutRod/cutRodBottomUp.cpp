/**
 * Reverse a singly linked list.
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <map>
#include <list>
#include <stack>
#include <stdexcept>
#include <typeinfo>
#include <exception>
#include <queue>
#include <iterator>
#include <unistd.h>
#include <cassert>
#include <fstream>
#include <time.h>
#include <sstream>
using namespace std;
//#define NDEBUG


int cutRodBottomUp(vector<int> &p, int n) {
    vector<int> r(n + 1, -1);
    r[0] = 0;
    for(int i = 1; i <= n; ++i) {
        int result = -1;
        for(int j = 1; j <= i; ++j) {
            result = std::max(result, p[j - 1] + r[i - j]);
        }
        r[i] = result;
    }
    return r[n];
}

int main() {
    vector<int> p {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    auto result = cutRodBottomUp(p,10);
    cout << result << endl;
}
