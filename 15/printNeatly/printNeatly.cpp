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
#include <cmath>
#include <ctime>
#include <sstream>
#include <iomanip>
using namespace std;



int costSum(const vector<string> &v, int i, int j, int M) {
    int sum = 0;
    for(int k = i; k <= j; k++) {
        sum += v[k - 1].size();
    }
    sum +=  (j - i);
    return M - sum;
}

int  printNeatly(const int M, const vector<string> &v, vector<int> &s) {
    int n = v.size();
    vector<int> cost(n + 1, INT_MAX); // cost[i] means from 1 to i, the smallest blank cost
    cost[0] = 0;
    int  min = INT_MAX;
    for(int i = 1; i <= n; i++) {
        min = INT_MAX;
        for(int k = i; k > 0; --k) {
            int q = costSum(v, k, i, M);
            if(q < 0)
                break;
            double newMin = cost[k - 1] + pow(q, 1);
            if(newMin < min) {
                min = newMin;
                s[i] = k; // 当计算 q < 0时，就跳出，所以 s 的值保存为这一行中在第几个元素换行
            }
        }
        cost[i] = min;
        cout << s[i] << '\t' << cost[i] << endl;
    }
    /*
     * 因为不考虑最后一行剩余的空格数，cost【n】肯定是最后一行的，所以要找出倒数第二行的 cost
     * 因为维护了s[n]表示换行时选择的 k，根据此值确定倒数第二行的 cost
     */
    int result = cost[n];
    for(int i = n; i > 0; --i) {
        if(s[i] != s[n]) {
            result = cost[i];
            break;
        }
    }


    return result;
}

int main() {
    vector<string>  vec{"slc", "is", "a", "man"};
    vector<int> s(vec.size() + 1, 0);
    const int M = 6;
    auto result = printNeatly(M, vec, s);
    cout << "minimal blank cost = " << result << endl;
    for(int i = 1; i <= vec.size(); i++) { // s[i]变化，代表换行了
        if(i > 1 && s[i] != s[i - 1])
            cout << endl;
        cout << vec[i - 1] << " ";
    }
}