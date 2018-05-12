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

struct activity {
	int number;
	int startTime;
	int endTime;

};
class minEndTime {
public:
	int operator() (activity &a1, activity &a2) {
		// build minHeap, need use > operator
		return a1.endTime > a2.endTime;
	}
};
int greedy(vector<activity>& vec) {
	sort(vec.begin(), vec.end(), [](activity &a, activity &b) { return a.startTime < b.startTime;});
//	for(auto i : vec) {
//		cout << i.startTime << '\t';
//		cout << i.endTime << endl;
//	}
	if(vec.empty()) return 0;
	// create a minHeap
	priority_queue<activity, vector<activity>, minEndTime> pq;
	pq.push(vec[0]);
	//  the activity has been sorted by the start time
	int n = vec.size();
	for(int i = 1; i < n; i++) {
		if(vec[i].startTime >= pq.top().endTime) {
			pq.pop();
			pq.push(vec[i]);
		} else {
			pq.push(vec[i]);
		}
	}
	return pq.size();
}

int main() {
	vector<activity> vec{{1, 1, 4}, {2, 3, 5}, {3, 0, 6}, {4, 5, 7}, {5, 3, 8}, {6, 5, 9}, {7, 6, 10}, {8, 8, 11}, {9, 8, 12}, {10, 2, 13}, {11, 12, 14}};
	auto result = greedy(vec);
	cout << result;
}
