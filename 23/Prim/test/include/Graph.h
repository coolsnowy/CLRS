//
// Created by coolsnowy on 2018/10/14.
//

#ifndef TEST_GRAPH_H
#define TEST_GRAPH_H

#include <vector>
using std::vector;

class Edge {
public:
	Edge() = default;
	Edge(int v, int w, double weight) {
		this->v = v;
		this->w = w;
		this->weight = weight;
	}
	int either() {
		return v;
	}
	int other(int vertex) {
		if(vertex == v)
			return w;
		else return v;
	}
	int compareTo(Edge that) {
		if(this->weight < that.weight)
			return -1;
		else if(this->weight > that.weight)
			return 1;
		else return 0;
	}

public:
	int v, w;
	double weight;
};

class EdgeWeightedGraph {
public:
	int v() {
		return this->V;
	}
	EdgeWeightedGraph(int V) {
		this->V = V;
		vector<Edge> vec;
		adj = vector< vector<Edge>> (V, vector<Edge> ());
	}
	void addEdge(Edge e) {
		int v = e.either();
		int w = e.other(v);
		adj[v].push_back(e);
		adj[w].push_back(e);
	}
	vector<Edge> adjcent(int v) {
		return adj[v];
	}
private:
	int V;
	vector< vector<Edge> >  adj;
};

#endif //TEST_GRAPH_H
