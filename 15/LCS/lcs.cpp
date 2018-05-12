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
    vector<vector<char>> b;
};

result lcsLength(const string &x, const string &y) {
    size_t m = x.size(), n = y.size();
    vector<vector<int>> c (m + 1, vector<int> (n + 1, 0));
    vector<vector<char>> b(m + 1, vector<char> (n + 1, '0'));
    // has set all the c[i][0] = 0, and c[0][j] = 0;
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {
            // -1 cause the string index start from 0
            if(x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = '\\'; // use a \ 转义
            } else if(c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = '|';
            } else {
                c[i][j] = c[i][j - 1];
                b[i][j] = '-';
            }
        }
    }
    return result{c, b};
}

void printLCS(vector<vector<char>> &b, string &x, int i, int j) {
    if(i == 0 || j == 0) {
        return;
    }
    if(b[i][j] == '\\') {
        printLCS(b, x, i - 1, j - 1);
        cout << x[i - 1];
    } else if(b[i][j] == '|') {
        printLCS(b, x, i - 1, j);
    } else {
        printLCS(b, x, i, j - 1);
    }
}

int main() {
    string x, y;
    x = "ABCBDAB";
    y = "BDCABA";
    auto result = lcsLength(x, y);
    cout << result.c[x.size()][y.size()] << endl;
    for(auto i : result.b) {
        for(auto j : i) {
            cout << j << '\t';
        }
        cout << '\n';
    }
    printLCS(result.b, x, x.size(), y.size());
}



