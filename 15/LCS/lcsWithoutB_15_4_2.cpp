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
    vector<vector<int>> c (m + 1, vector<int> (n + 1, 0));
    // has set all the c[i][0] = 0, and c[0][j] = 0;
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {
            // -1 cause the string index start from 0
            if(x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
            } else if(c[i - 1][j] >= c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
            } else {
                c[i][j] = c[i][j - 1];
            }
        }
    }
    return result{c};
}
// my solution, 根据书上的 b 数组图以及数组 b 的思想，优先上移，然后有左移就左移，没有的话斜向上就是 lcs 的一个数组
// 因为先递归再输出，所以输出就直接是正序
void print1(vector<vector<int>> &c, const string &y, int i, int j) {
    if(i == 1 ) {
        return;
    }
     if(c[i][j] == c[i - 1][j]) {
         print1(c, y, i - 1, j);
     } else if(c[i][j] == c[i][j - 1]){
         print1(c, y, i, j - 1);
     } else if(c[i][j] == c[i - 1][j - 1] + 1) {
        print1(c, y, i - 1, j - 1);
        cout << y[j - 1];
    }
}
// betteer solution, 更符合书上的定义，根据c 和 s[i] == s[j]的关系来判断
void print2(vector<vector<int>> &c, const string &x, const string &y) {
    int n = c[x.size()][y.size()];
    vector<char> s(n + 1, '0'); // 建立数组的原因主要在于，输出是倒序的，所以将值从后向前保存，然后正序输出
    int i = x.size(), j = y.size();
    while(i > 0 && j > 0) {
        // -1 cause the string start begin with 0
        if(x[i - 1] == y[j - 1] ) {
            s[n] = x[i - 1];
            n--;
            i--;
            j--;
        } else if(c[i - 1][j] >= c[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    cout << endl << "LCS = " ;
    for(int k = 1; k <= c[x.size()][y.size()]; k++) {
        cout << s.at(k);
    }
    cout << endl;
}

int main() {
    string x, y;
    x = "ABCBDAB";
    y = "BDCABA";
    auto result = lcsLength(x, y);
    cout << result.c[x.size()][y.size()] << endl;
    print1(result.c, y, x.size(), y.size());
    print2(result.c, x, y);
}



