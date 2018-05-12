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
#include <forward_list>
#include <ctime>
#include <array>
#include <sstream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <iomanip>
using namespace std;

struct object {
	double weight;
	double value;
};

/*
 * 优化空间复杂度：
	以上方法的时间和空间复杂度均为O(VN)，其中时间复杂度应该已经不能再优化了，但空间复杂度却可以优化到O(V)
	先考虑上面讲的基本思路如何实现，肯定是有一个主循环i=1..N，每次算出来二维数组f[i][0..V]的所有值。
 	那么，如果只用一个数组f[0..V]，能不能保证第i次循环结束后f[v]中表示的就是我们定义的状态f[i][v]呢？
 	f[i][v]是由f[i-1][v]和f[i-1][v-c[i]]两个子问题递推而来，能否保证在推f[i][v]时（也即在第i次主循环中推f[v]时）能够得到f[i-1][v]和f[i-1][v-c[i]]的值呢？
 	事实上，这要求在每次主循环中我们以v=V..0的顺序推f[v]，这样才能保证推f[v]时f[v-c[i]]保存的是状态f[i-1][v-c[i]]的值。
 	*/
/*
 * 可以看出f[v]=max{f[v],f[v-c[i]]+w[i]};
	V是从大到小的
	其中的f[v],f[v-c[i]]是前面的值比较的结果赋值给f[v]

 	！！！即数据是从右到左计算的,然后计算下一次迭代时，从右向左算，计算时，用到的左边的值还没更新，是上一次循环计算出来的，即相当于是v[i - 1][*]
 */
int knapsack0_1 (vector<object> &vec, int w) {
	vector<double> dp(w + 1, 0);
	int n = vec.size();
	// be caution the place where use vector, should decrease the index by 1
	for(int i = 1; i <= n; i++ ) {
		for(int j = w; j >= 1; j--) {
			if(j < vec[i - 1].weight) {
				dp[j] = dp[j];
			} else {
				dp[j] = std::max(dp[j] , dp[j - vec[i - 1].weight] + vec[i - 1].value);
			}
		}
	}

	return dp[w];
}

int main() {
//	 {weight, value}
	vector<object> vec{{5, 12}, {4, 3}, {7, 10}, {2, 3}, {6, 6}};
//	vector<object> vec{{1, 60}, {2, 20}, {3, 120}};
	auto result = knapsack0_1(vec, 10);
	cout << result;
}
