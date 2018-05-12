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
	int startTime;
	int endTime;
};

int main() {
	vector<activity> vec{{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 9}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 14}, {12, 16}};
	// hypothesis the activity is ascended by the end time
	vector<activity> result{*vec.begin()};
	int n = vec.size();
	cout << "choose : activity1" << '\t';
	for(int i = 1; i < n; i++) {
		if(vec[i].startTime > result[result.size() - 1].endTime) {
			cout << "activity" << i + 1<<'\t';
			result.push_back(vec[i]);
		}
	}
	cout << endl;
	int totalTime = 0;
	for(auto ele : result ) {
		cout << ele.startTime << '\t' << ele.endTime << endl;
		totalTime += (ele.endTime - ele.startTime);
	}
	cout <<  "total time = " << totalTime;

}