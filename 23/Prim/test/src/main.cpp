
#include "MinHeap.h"
#include "Graph.h"
using std::cout;
using std::endl;
//!prim：最小生成树的Prim算法，算法导论23章23.2节
/*
*
* ## 最小生成树
*
* 最小生成树：对于一个连通无向图G=(V,E)，对于每一条边(u,v)属于E都赋予了一个权重w(u,v)。我们希望找出一个无环子集T，其中T为E的子集，使得所有的顶点V位于T中，
* 同时T具有最小的权重。由于T是无环的，且连通所有结点因此T必然是一棵树。我们称这样的树为生成树。称从G中求取该生成树的问题为最小生成树问题。
*
* 通用的最小生成树使用贪心策略。该策略在每个时刻找到最小生成树的一条边，并在整个策略过程中维持循环不变式：边的集合A在每次循环之前是某棵最小生成树的一个子集。
*
* 在每一步，选择一条边(u,v)，将其加入集合A中，使得A不违反循环不变式。称这样的边(u,v)为边集合A的安全边。
*
* ## Prim算法
*
* ### 算法原理
*
* 在Prim算法所具有的一个性质是集合A中的边总是构成一棵树。这棵树从一个任意的根结点r开始，一直长大到覆盖V中的所有结点为止。算法每一步在连接集合A和A之外的结点的所有边中，
* 选择一条边加入到A中（经特殊选择的边）。
*
* 为了有效地实现Prim算法，需要一种快速的方法来选择一条新的边以便加入到由集合A中的边所构成的树中。在算法执行过程中，所有不在树A中的结点都存放在一个基于key的属性的最小优先级队列Q中。
* 对于每个结点v，属性v.key保存的是连接v和树中结点的所有边中最小边的权重。若这样的边不存在则权重为正无穷。属性v.pai给出的是结点v在树中的父结点。
*
* ### 算法步骤
*
* - 初始化：将所有结点的key设为正无穷，所有结点的父结点置为空(结点构造时，父结点默认为空）
* - 设置源点：将源点的key设为0，
* - 构造最小优先级队列：将所有顶点放入最小优先级队列Q中
* - 循环，直到最小优先级队列为空。循环中执行下列操作：
*   - 弹出最小优先级队列的头部顶点u
*   - 从结点u出发的所有边，找出它的另一端的结点v。如果v也在Q中，且w(u,v)<v.key，则证明(u,v)是v到集合A的最短边，因此设置v.pai=u,v.key=w(u,v)
*   >这里隐含着一个最小优先级队列的decreate_key操作
*
* ### 算法性能
*
* Prim总时间代价为O(VlgV+ElgV)=O(ElgV)(使用最小堆实现的最小优先级队列），或者O(E+VlgV)（使用斐波那契堆实现最小优先级队列）
*/
class PrimMst {
public:
	PrimMst(EdgeWeightedGraph &G) {
		marked = vector<bool> (G.v(), false);
	}
	void visit(EdgeWeightedGraph &graph, int v) {
		marked[v] = true;
		for(Edge e : graph.adjcent(v)) {
			if(!marked[e.other(v)]) {
				pq.insert(e);
			}
		}
	}
	void prim(EdgeWeightedGraph &graph) {
		visit(graph, 0);
		while(!pq.isEmpty() && mst.size() < graph.v() - 1) {
			Edge e = pq.extractMin();
			int v = e.either(), w = e.other(v);
			// disregard if both point are marked(both in MST)
			if(marked[v] && marked[w] )
				continue;
			// otherwise, let w be the unmarked vertex(not in MST)
			// add to PQ any edge incident to w(assuming other endpoint not in MST)
			// add e to MST and marked w
			mst.push_back(e);
			if(!marked[v]) visit(graph, v);
			if(!marked[w]) visit(graph, w);
		}
	}
	vector<Edge> mstResult() {
		return mst;
	}

private:
	vector<bool> marked;
	MinHeap pq;	// pq中存放的一个端点在mst中的所有边
	vector<Edge> mst;
};


int main() {
	// 见书上367页例子
	std::vector<int> point {0, 1, 2, 3, 4, 5, 6, 7, 8};
	EdgeWeightedGraph graph(point.size());
	graph.addEdge(Edge(0, 1, 4));
	graph.addEdge(Edge(1, 2, 8));
	graph.addEdge(Edge(2, 3, 7));
	graph.addEdge(Edge(3, 4, 9));
	graph.addEdge(Edge(4, 5, 10));
	graph.addEdge(Edge(5, 6, 2));
	graph.addEdge(Edge(6, 7, 1));
	graph.addEdge(Edge(0, 7, 8));
	graph.addEdge(Edge(1, 7, 11));
	graph.addEdge(Edge(2, 8, 2));
	graph.addEdge(Edge(8, 7, 7));
	graph.addEdge(Edge(8, 6, 6));
	graph.addEdge(Edge(2, 5, 4));
	graph.addEdge(Edge(3, 5, 14));
	PrimMst prim(graph);
	prim.prim(graph);
	auto mst = prim.mstResult();
	for(auto item : mst) {
		cout << static_cast<char>('a' + item.either()) << "---"
		<< static_cast<char>('a' + item.other(item.either()) )<< endl;
	}



}

