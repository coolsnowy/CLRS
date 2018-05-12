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


int cutRod(vector<int> &p, vector<int> &r, vector<int> &s, int n) {
    if(r[n] >= 0) return r[n];
    int result = -1;

    if(n == 0) {
        return 0;
    } else {
        for(int i = 1; i <= n; ++i) {
            int t = p[i - 1] + cutRod(p, r, s, n - i);
            if(t > result) {
                result = t;
                s[n] = i;
            }
        }
    }
    r[n] = result;
    return result;

}

int main() {
    vector<int> p {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n = 7;
    vector<int> r(n + 1, INT_MIN);
    vector<int> s(n + 1, -1);
    auto result = cutRod(p, r, s, n);
    while(n > 0) {
        cout << s[n] << '\t' << p[s[n] - 1] << endl;
        n = n - s[n];
    }
    cout << result << endl;
}