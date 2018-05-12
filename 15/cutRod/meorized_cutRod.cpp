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


int cutRod(vector<int> &p, vector<int> &r, int n) {
    if(r[n] >= 0) return r[n];
    int result = -1;
    if(n == 0) {
        return 0;
    } else {
        for(int i = 1; i <= n; ++i) {
            result = std::max(result, p[i - 1] + cutRod(p, r, n - i));
        }
    }
    r[n] = result;
    return result;

}

int main() {
    vector<int> p {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n = 8;
    vector<int> r(n + 1, INT_MIN);
    auto result = cutRod(p, r, n);
    cout << result << endl;
}