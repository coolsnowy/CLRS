//
// Created by coolsnowy on 2018/10/14.
//

#ifndef TEST_GRAPH_H
#define TEST_GRAPH_H

#include <vector>
// 起点、终点、重量
typedef std::pair<std::pair<int, int>, double> edge;
class Graph {
public:
	Graph(std::vector<int> &v, std::vector<edge> &e)
							: vertex(v),
							  edges(e) {

	}
	std::vector<int> V() {
		return vertex;
	}
	std::vector<edge> E() {
		return edges;
	}

private:
	// 图中的所有端点
	std::vector<int> vertex;
	// 图中所有的边
	std::vector<edge> edges;
};

#endif //TEST_GRAPH_H
