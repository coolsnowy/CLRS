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
#include <iomanip>
using namespace std;

struct result {
public:
    vector<vector<double>> e;
    vector<vector<int>> root;
};

result optimalBST(vector<double> &p, vector<double> &q, int n) {
    vector<vector<double>> e (n + 2, vector<double> (n + 1, INT_MAX)), w(e);
    vector<vector<int>> root(n + 1, vector<int> (n + 1, 0));
    for(int i = 1; i <= n+ 1; ++i) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }
    for(int l = 1; l <= n; ++l) {
        for(int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            w[i][j] = w[i][j - 1] + p[j] + q[j];
            for(int r = i; r <= j; ++r) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if(t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }

    }
    return result {e, root};
}

int main() {
    vector<double> p{0, 0.15, 0.10, 0.05, 0.10, 0.20};
    vector<double> q{0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
    int n = p.size() - 1;
    auto result = optimalBST(p, q, n);
    cout << "optimal expect = " << result.e[1][n] << endl;
    for(int i = 1; i <= n; ++i) {
        for(int j = 0; j <= n; j++) {
            if(j >= i - 1)
                cout << std::left << setw(4) << result.e[i][j] << "   ";
        }
        cout << endl;
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; j++) {
            if(j < i)
                cout << "    ";
            if (j >= i)
                cout << result.root[i][j] << "   ";
        }
        cout << endl;
    }
}



