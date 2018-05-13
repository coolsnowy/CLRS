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
 * 我们看到的求最优解的背包问题题目中，事实上有两种不太相同的问法。有的题目要求“恰好装满背包”时的最优解，有的题目则并没有要求必须把背包装满。
 * 一种区别这两种问法的实现方法是在初始化的时候有所不同。

	如果是第一种问法，要求恰好装满背包，那么在初始化时除了f[0]为0(对于空间未优化版本，即第一列全为0，剩下都是未定义状态)其它f[1..V]均设为-∞，
 	这样就可以保证最终得到的f[N]是一种恰好装满背包的最优解。

	如果并没有要求必须把背包装满，而是只希望价格尽量大，初始化时应该将f[0..V]全部设为0。
	为什么呢？可以这样理解：初始化的f数组事实上就是在没有任何物品可以放入背包时的合法状态。
	如果要求背包恰好装满，那么此时只有容量为0的背包可能被价值为0的nothing“恰好装满”，其它容量的背包均没有合法的解，属于未定义的状态，它们的值就都应该是-∞了。
	如果背包并非必须被装满，那么任何容量的背包都有一个合法解“什么都不装”，这个解的价值为0，所以初始时状态的值也就全部为0了。
 */
int  knapsack0_1 (vector<object> &vec, int w) {
	vector<vector<double>> dp(vec.size() + 1, vector<double > (w + 1, INT_MIN));
	int n = vec.size();
	for(int i = 0; i <= n; i++)
		dp[i][0] = 0;
	// be caution the place where use vector, should decrease the index by 1
	for(int i = 1; i <= n; i++ ) {
		for(int j = 1; j <= w; j++) {
			if(j < vec[i - 1].weight) {
				dp[i][j] = dp[i - 1][j];
			} else {
				dp[i][j] = std::max(dp[i - 1][j] , dp[i - 1][j - vec[i - 1].weight] + vec[i - 1].value);
			}
		}
	}
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= w; j++) {
			cout << dp[i][j] << "  ";
		}
		cout << endl;
	}
	return dp[n][w];
}

int main() {
//	 {weight, value}
//	vector<object> vec{{5, 12}, {4, 3}, {7, 10}, {2, 3}, {6, 6}};
	vector<object> vec{{1, 60}, {2, 20}, {3, 120}};
	auto result = knapsack0_1(vec, 5);
	cout << result;
}
