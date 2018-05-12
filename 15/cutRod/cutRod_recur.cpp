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

int cutRod(vector<int> &p, int n) {
    if(n == 0)
        return 0;
    int result = -1;
    for(int i = 1; i <= n; i++) {
        result = std::max(result, p[i - 1] + cutRod(p, n - i));
    }
    return result;
}

int main() {
    vector<int> p {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    auto result = cutRod(p, 10);
    cout << result << endl;
}
