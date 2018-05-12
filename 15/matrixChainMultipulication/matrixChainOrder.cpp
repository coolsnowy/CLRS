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

struct result {
public:
    vector<vector<int>> m;
    vector<vector<int>> s;
};

result matrixChainOrder(vector<int> &p) {
    int n = p.size() - 1;
    vector<vector<int>> m(n + 1, vector<int> (n + 1, INT_MAX));
    vector<vector<int>> s(m);
    for (int i = 1; i <= n; ++i) {
        m[i][i] = 0;
    }
    for(int l = 2; l <= n; ++l) {
        for(int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k <= j - 1; ++k) {
                int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (t < m[i][j]) {
                    m[i][j] = t;
                    s[i][j] = k;
                }
            }
        }
    }

    return result{m , s};
}

void printOptimalParens(vector<vector<int>> &s, int i, int j) {
    if(i == j)
        cout << "A" << i;
    else {
        cout << " (";
        printOptimalParens(s, i, s[i][j]);
        printOptimalParens(s, s[i][j] + 1, j);
        cout << ") ";
    }
}

int main() {
//    vector<int> p {30, 35, 15, 5, 10, 20, 25};
    vector<int> p {5, 10, 3, 12, 5, 50, 6};
    auto result = matrixChainOrder(p);
    cout << "minimal multiplication num = " << result.m[1][p.size() - 1] << endl;
    printOptimalParens(result.s, 1, p.size() - 1);

}