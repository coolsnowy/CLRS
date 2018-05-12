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

int  knapsack0_1 (vector<object> &vec, int w) {
	vector<vector<double>> dp(vec.size() + 1, vector<double > (w + 1, 0));
	int n = vec.size();
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
	// {weight, value}
//	vector<object> vec{{5, 12}, {4, 3}, {7, 10}, {2, 3}, {6, 6}};
	vector<object> vec{{1, 60}, {2, 20}, {3, 120}};
	auto result = knapsack0_1(vec, 5);
	cout << result;
}
