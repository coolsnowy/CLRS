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
    vector<int> c;
};

result lcsLength( vector<int> &x,  vector<int> &y) {
    if(y.size() > x.size()) {
        auto temp = x;
        x = y;
        y = temp;
    }
    size_t m = x.size(), n = y.size();
    //用 n 作为维度，要求x 的长度比 y 长度长，如果不是，传递进来的时候交换一下即可
    vector<int> c (n + 1, 0);
    // has set all the c[i][0] = 0, and c[0][j] = 0;
    int temp1 = 0;
    for(int i = 1; i <= m; ++i) {
        for(int j = 1; j <= n; ++j) {
            // use temp1 to save c[i - 1][j - 1]，其他值都是当前的状态可用，不需要临时变量存储
            temp1 = c[j - 1];
            // -1 cause the string index start from 0
            if(x[i - 1] == y[j - 1]) {
                c[j] = temp1 + 1;
            } else if(c[j] >= c[j - 1]) {
                c[j] = c[j];
            } else {
                c[j] = c[j - 1];
            }
        }
    }
    return result{c};
}


int main() {
    vector<int> v1{6, 5, 3, 8, 10};
    vector<int> v2(v1);
    std::sort(v2.begin(), v2.end());
    auto result = lcsLength(v1, v2);
    cout << result.c[v2.size()] << endl;
    vector<int> vec{1 , 2, 4, 6,2, 4, 5};
}



