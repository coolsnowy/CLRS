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


int cutRodBottomUpExtended(vector<int> &p, int n) {
    vector<int> r(n + 1, -1), s(n + 1, -1);
    r[0] = 0;
    for(int i = 1; i <= n; ++i) {
        int result = -1;
        for(int j = 1; j <= i; ++j) {
            if(result < p[j - 1] + r[i - j]) {
                result = p[j - 1] + r[i - j];
                s[i] = j;
            }
        }
        r[i] = result;
    }
    int nCopy = n;
    cout << "length" << '\t' << "price" << endl;
    while(nCopy > 0) {
        cout << s[nCopy] << "\t\t" << p[s[nCopy] - 1] << endl;
        nCopy = nCopy - s[nCopy];
    }
    return r[n];
}

int main() {
    vector<int> p {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    auto result = cutRodBottomUpExtended(p, 10);
    cout << "\ntotal price = " << result << endl;
}