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
#include <ctime>
#include <sstream>
using namespace std;

struct result {
public:
    vector<vector<int>> c;
};

result lcsLength(const string &x, const string &y) {
    size_t m = x.size(), n = y.size();
    vector<vector<int>> c (2, vector<int> (n + 1, 0));
    // has set all the c[i][0] = 0, and c[0][j] = 0;
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {
            // -1 cause the string index start from 0
            if(x[i - 1] == y[j - 1]) {
                c[1][j] = c[0][j - 1] + 1;
            } else if(c[0][j] >= c[1][j - 1]) {
                c[1][j] = c[0][j];
            } else {
                c[1][j] = c[1][j - 1];
            }
            for(int s = 1; s <= n; ++s) {
                c[0][s] = c[1][s];
            }
        }
    }
    return result{c};
}


int main() {
    string x, y;
    x = "ABCBDAB";
    y = "BDCABA";
    auto result = lcsLength(x, y);
    cout << result.c[1][y.size()] << endl;

}



