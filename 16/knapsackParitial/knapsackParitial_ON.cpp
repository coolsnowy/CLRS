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

struct node {
	double weight;
	double value;
};
/*
 * 说明如何在O(n)时间内解决部分背包问题

	常规算法：
	先求avgi = vi/wi，按照avgi从大到小排序，再贪心选择，时间复杂度为O(nlgn)
	该算法主要难点在排序。

	改进：
	本文要求的时间是O(n)，但O(n)排序的都基于非比较的排序算法。这里的性价比avg是浮点型了，不适用于非比较排序算法。
	进一步观察数据特点，发现某些情况是不需要排序的。
	例如:如果a1, a2，a3是avgi 最大的三个物品，如果它们的总量和不大于W，我们是不需要知道它们间的相对顺序的。
	这一特性类似于分类，即把物品分为性价比高和性价比两类，这让我们想到了partition。

	O(n)算法：
	选择一个物品作为主元，对所有物品进行Paitition操作。将avg 分为三个集合G = {ai: avgi > m}, Q = {ai： avgi = m}, P = {ai: avgi < m}。分别对G, Q, P中元素求和得SG, SQ, SP。
	1. 如果W < SG, 则令物体的集合为O = G，对集合O递归进行上述过程。
	2. 如果 SG <= W <= SG+SQ，则将集合G中的元素都放入包中，并将集合Q总元素尽可能多的放入包中，结束。
	3. 如果 SG+SQ < W, 将G，Q中元素放入包中。令物体集合O = P，总重W = W - SG - SQ。递归进行上述过程。
 */

void swap(node &i, node &j) {
	double temp1 = i.value, temp2 = i.weight;
	i.value = j.value; i.weight = j.weight;
	j.value = temp1; j.weight = temp2;
}

int Partition(vector<node> &A, int p, int r)
{
	node x = A[r];
	int i = p-1, j;
	for(j = p; j < r; j++)
	{
		//划分的依据是avg = value / weight
		double t1 = x.value * 1.0 / x.weight;
		double t2 = A[j].value * 1.0 / A[j].weight;
		if(t2 >= t1)
		{
			i++;
			swap(A[i], A[j]);
		}
	}
	swap(A[i+1], A[r]);
	return i+1;
}


int Randomized_Partition(vector<node> &A, int p, int r)
{
	//随机选择数组中一个数作为主元
	int i = rand() % (r-p+1) + p;
	swap(A[r], A[i]);
	//划分
	return Partition(A, p, r);
}
//i是从1开使计数的，不是从p开始
double Randomized_Select(vector<node> &A, int p, int r, int weight, int value)
{
	if(p == r)
	{
		if(A[p].weight <= weight)
			return value + A[p].value;
		else
			return value + (double)A[p].value * weight / A[p].weight;
	}
	else if(p > r)
		return value;
	//以某个元素为主元，把数组分为两组，A[p..q-1] < A[q] < A[q+1..r]，返回主元在整个数组中的位置
	int q = Randomized_Partition(A, p, r);
	//主元是整个数组中的第q个元素
	int i, w = 0, v = 0;
	//求SG
	for(i = p; i < q; i++)
	{
		w = w + A[i].weight;
		v = v + A[i].value;
	}
	if(w == weight)//正是所求的元素
		return value + v;
		//主元物品取一部分
	else if(w < weight && w + A[q].weight >= weight)
		return value + v + (double)A[q].value * (weight-w) / A[q].weight;
	else if(w > weight)//所求元素<主元，则在A[p..q-1]中继续寻找
		return Randomized_Select(A, p, q-1, weight, value);
	else//所求元素>主元，则在A[q+1..r]中继续寻找
		return Randomized_Select(A, q+1, r, weight - w - A[q].weight, value + v + A[q].value);
}

double partialPackage(int weight, int len, vector<node> &material)
{
	if(weight == 0 || len == 0)
		return 0;
	return Randomized_Select(material, 1, len-1, weight, 0);
}

int main() {
//	 {weight, value}
//	vector<object> vec{{5, 12}, {4, 3}, {7, 10}, {2, 3}, {6, 6}};
	vector<node> vec{{0, 0}, {1, 60}, {2, 20}, {3, 120}};
//	vector<node> vec{{0, 0}, {3, 5}, {2, 4}, {2, 7}};
	auto result = partialPackage(10, vec.size(), vec);
	cout << result;
}
